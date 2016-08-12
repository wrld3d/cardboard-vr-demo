// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "document.h"
#include "ApplicationConfigurationJsonParser.h"
#include "IApplicationConfigurationBuilder.h"
#include "MathFunc.h"
#include "WorldLocationData.h"
#include "Logger.h"
#include <vector>
#include <map>
#include <sstream>

namespace Examples
{
    namespace ApplicationConfig
    {
        namespace SdkModel
        {
            typedef rapidjson::GenericValue<rapidjson::UTF8<char>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>> TGenericValue;

            JumpPointConfigData ParseJumpPoint(const TGenericValue& data)
            {
                Eegeo_ASSERT(data.HasMember("id"));
                Eegeo_ASSERT(data.HasMember("lat"));
                Eegeo_ASSERT(data.HasMember("lon"));
                Eegeo_ASSERT(data.HasMember("alt"));
                Eegeo_ASSERT(data.HasMember("icon_id"));
                Eegeo_ASSERT(data.HasMember("size"));
                return JumpPointConfigData(data["id"].GetInt(),
                                           Eegeo::Space::LatLongAltitude::FromDegrees(data["lat"].GetDouble(),
                                                                                      data["lon"].GetDouble(),
                                                                                      data["alt"].GetDouble()),
                                           data["icon_id"].GetInt(),
                                           data["size"].GetDouble());
            }

            void ParseJumpPoints(const TGenericValue& exteriorData, TJumpPointVector& outJumpPointVector)
            {
                if(exteriorData.HasMember("JumpPoints"))
                {
                    for (rapidjson::Value::ConstValueIterator itr = exteriorData["JumpPoints"].Begin(); itr != exteriorData["JumpPoints"].End(); ++itr)
                    {
                        const TGenericValue& exteriorJumpPoint = *itr;
                        outJumpPointVector.push_back(ParseJumpPoint(exteriorJumpPoint));
                    }
                }
            }

            void ParseInteriorJumpPointData(const TGenericValue& interiorData, TInteriorFloorJumpPoints& outInteriorFloorJumpPoints)
            {
                Eegeo_ASSERT(interiorData.HasMember("FloorCount"));
                int floorCount = interiorData["FloorCount"].GetInt();

                for (int i = 0; i < floorCount; i++)
                {
                    std::stringstream ss;
                    ss << "Floor";
                    ss << i;

                    const std::string& floorKey = ss.str();

                    if (interiorData.HasMember(floorKey.c_str()))
                    {
                        const TGenericValue& interiorFloorData = interiorData[floorKey.c_str()];

                        TJumpPointVector floorJumpPointData;

                        for (rapidjson::Value::ConstValueIterator itr = interiorFloorData.Begin(); itr != interiorFloorData.End(); ++itr)
                        {
                            const TGenericValue& interiorJumpPoint = *itr;

                            JumpPointConfigData jpData = ParseJumpPoint(interiorJumpPoint);

                            if (interiorJumpPoint.HasMember("child_jump_points"))
                            {
                                TJumpPointVector childJumpPointData;

                                const TGenericValue& interiorFloorJumpPoints = interiorJumpPoint["child_jump_points"];

                                for (rapidjson::Value::ConstValueIterator floorItr = interiorFloorJumpPoints.Begin(); floorItr != interiorFloorJumpPoints.End(); ++floorItr)
                                {
                                    const TGenericValue& interiorFloorJumpPoint = *floorItr;
                                    childJumpPointData.push_back(ParseJumpPoint(interiorFloorJumpPoint));
                                }

                                jpData.SetChildJumpPoints(childJumpPointData);
                            }

                            floorJumpPointData.push_back(jpData);
                        }
                        
                        outInteriorFloorJumpPoints[i] = floorJumpPointData;
                    }
                }
            }

            ApplicationConfigurationJsonParser::ApplicationConfigurationJsonParser(IApplicationConfigurationBuilder& builder)
            : m_builder(builder)
            {

            }

            ApplicationConfiguration ApplicationConfigurationJsonParser::ParseConfiguration(const std::string& serialized)
            {
                rapidjson::Document document;
                const bool hasParseError(document.Parse<0>(serialized.c_str()).HasParseError());
                Eegeo_ASSERT(!hasParseError);

                Eegeo_ASSERT(document.HasMember("Name"));
                m_builder.SetApplicationName(document["Name"].GetString());

                Eegeo_ASSERT(document.HasMember("EegeoApiKey"));
                m_builder.SetEegeoApiKey(document["EegeoApiKey"].GetString());

                Eegeo_ASSERT(document.HasMember("StartLocationLatitude"));
                Eegeo_ASSERT(document.HasMember("StartLocationLongitude"));
                Eegeo_ASSERT(document.HasMember("StartLocationAltitude"));
                m_builder.SetStartInterestPointLocation(Eegeo::Space::LatLongAltitude::FromDegrees(document["StartLocationLatitude"].GetDouble(),
                                                                                                   document["StartLocationLongitude"].GetDouble(),
                                                                                                   document["StartLocationAltitude"].GetDouble()));

                Eegeo_ASSERT(document.HasMember("StartLocationOrientationDegrees"));
                m_builder.SetStartOrientationAboutInterestPoint(static_cast<float>(document["StartLocationOrientationDegrees"].GetDouble()));

                Eegeo_ASSERT(document.HasMember("CoverageTreeManifestURL"), "CoverageTreeManifestURL config not found");
                m_builder.SetCoverageTreeManifestURL(document["CoverageTreeManifestURL"].GetString());

                Eegeo_ASSERT(document.HasMember("ThemeManifestURL"), "ThemeManifestURL config not found");
                m_builder.SetThemeManifestURL(document["ThemeManifestURL"].GetString());

                Eegeo_ASSERT(document.HasMember("JumpPointsData"));
                const TGenericValue& jumpPointsData = document["JumpPointsData"];

                Eegeo_ASSERT(jumpPointsData.HasMember("SpriteSheet"));
                m_builder.SetJumpPointSpriteSheet(jumpPointsData["SpriteSheet"].GetString());

                Eegeo_ASSERT(jumpPointsData.HasMember("NumberOfTilesAlong1Axis"));
                m_builder.SetJumpPointSpriteSheetSize(jumpPointsData["NumberOfTilesAlong1Axis"].GetInt());

                Eegeo_ASSERT(jumpPointsData.HasMember("Exterior"));
                const TGenericValue& exteriourJumpPointsData = jumpPointsData["Exterior"];

                TWorldLocations worldLocations;
                std::map<std::string,std::vector<JumpPointConfigData>&> exteriorJumpPoints;

                for (rapidjson::Value::ConstMemberIterator itr = exteriourJumpPointsData.MemberBegin();
                     itr != exteriourJumpPointsData.MemberEnd(); ++itr)
                {
                    TJumpPointVector jumpPointsVector;
                    const std::string& locationName = itr->name.GetString();
                    const TGenericValue& locationDocument = itr->value;

                    Eegeo_ASSERT(locationDocument.HasMember("LocationID"));
                    Eegeo_ASSERT(locationDocument.HasMember("LocationIcon"));
                    Eegeo_ASSERT(locationDocument.HasMember("StartLocationLatitude"));
                    Eegeo_ASSERT(locationDocument.HasMember("StartLocationLongitude"));
                    Eegeo_ASSERT(locationDocument.HasMember("StartLocationAltitude"));
                    Eegeo_ASSERT(locationDocument.HasMember("StartLocationOrientationDegrees"));
                    Eegeo_ASSERT(locationDocument.HasMember("WelcomeMessage"));
                    WorldLocationData locationData(locationName,
                                                   locationDocument["LocationID"].GetInt(),
                                                   locationDocument["LocationIcon"].GetInt(),
                                                   Eegeo::Space::LatLongAltitude::FromDegrees(locationDocument["StartLocationLatitude"].GetDouble(),
                                                                                              locationDocument["StartLocationLongitude"].GetDouble(),
                                                                                              locationDocument["StartLocationAltitude"].GetDouble()),
                                                   static_cast<float>(locationDocument["StartLocationOrientationDegrees"].GetDouble()),
                                                   locationDocument["WelcomeMessage"].GetString());

                    ParseJumpPoints(locationDocument, jumpPointsVector);
                    m_builder.AddExteriorJumpPoints(locationName, jumpPointsVector);
                    worldLocations[locationName] = locationData;
                }

                m_builder.SetExteriorLocations(worldLocations);

                Eegeo_ASSERT(jumpPointsData.HasMember("Interior"));
                const TGenericValue& interiorJumpPointsData = jumpPointsData["Interior"];

                for (rapidjson::Value::ConstMemberIterator itr = interiorJumpPointsData.MemberBegin();
                     itr != interiorJumpPointsData.MemberEnd(); ++itr)
                {
                    TInteriorFloorJumpPoints interiorFloorJumpPoints;
                    const std::string& locationName = itr->name.GetString();
                    ParseInteriorJumpPointData(itr->value, interiorFloorJumpPoints);
                    m_builder.AddInteriorJumpPoints(locationName, interiorFloorJumpPoints);
                }

                return m_builder.Build();
            }
        }
    }
}
