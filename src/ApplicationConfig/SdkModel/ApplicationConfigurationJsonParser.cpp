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

            void ParseJumpPoints(const TGenericValue& exteriorData, TJumpPointVector& outJumpPointVector)
            {
                if(exteriorData.HasMember("JumpPoints"))
                {
                    for (rapidjson::Value::ConstValueIterator itr = exteriorData["JumpPoints"].Begin(); itr != exteriorData["JumpPoints"].End(); ++itr)
                    {
                        const TGenericValue& exteriorJumpPoint = *itr;

                        Eegeo_ASSERT(exteriorJumpPoint.HasMember("id"));
                        Eegeo_ASSERT(exteriorJumpPoint.HasMember("lat"));
                        Eegeo_ASSERT(exteriorJumpPoint.HasMember("lon"));
                        Eegeo_ASSERT(exteriorJumpPoint.HasMember("alt"));
                        Eegeo_ASSERT(exteriorJumpPoint.HasMember("icon_id"));
                        Eegeo_ASSERT(exteriorJumpPoint.HasMember("size"));
                        JumpPointConfigData jpData(exteriorJumpPoint["id"].GetInt(),
                                                   Eegeo::Space::LatLongAltitude::FromDegrees(exteriorJumpPoint["lat"].GetDouble(),
                                                                                              exteriorJumpPoint["lon"].GetDouble(),
                                                                                              exteriorJumpPoint["alt"].GetDouble()),
                                                   exteriorJumpPoint["icon_id"].GetInt(),
                                                   exteriorJumpPoint["size"].GetDouble());
                        outJumpPointVector.push_back(jpData);
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

                            Eegeo_ASSERT(interiorJumpPoint.HasMember("id"));
                            Eegeo_ASSERT(interiorJumpPoint.HasMember("lat"));
                            Eegeo_ASSERT(interiorJumpPoint.HasMember("lon"));
                            Eegeo_ASSERT(interiorJumpPoint.HasMember("alt"));
                            Eegeo_ASSERT(interiorJumpPoint.HasMember("icon_id"));
                            Eegeo_ASSERT(interiorJumpPoint.HasMember("size"));
                            JumpPointConfigData jpData(interiorJumpPoint["id"].GetInt(),
                                                       Eegeo::Space::LatLongAltitude::FromDegrees(interiorJumpPoint["lat"].GetDouble(),
                                                                                                  interiorJumpPoint["lon"].GetDouble(),
                                                                                                  interiorJumpPoint["alt"].GetDouble()),
                                                       interiorJumpPoint["icon_id"].GetInt(),
                                                       interiorJumpPoint["size"].GetDouble());
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

                Eegeo_ASSERT(document.HasMember("JumpPointsData"));
                const TGenericValue& jumpPointsData = document["JumpPointsData"];

                Eegeo_ASSERT(jumpPointsData.HasMember("SpriteSheet"));
                m_builder.SetJumpPointSpriteSheet(jumpPointsData["SpriteSheet"].GetString());

                Eegeo_ASSERT(jumpPointsData.HasMember("SpriteSheetWidth"));
                Eegeo_ASSERT(jumpPointsData.HasMember("SpriteSheetHeight"));
                m_builder.SetJumpPointSpriteSheetSize(Eegeo::v2(jumpPointsData["SpriteSheetWidth"].GetDouble(),jumpPointsData["SpriteSheetHeight"].GetDouble()));

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
                    WorldLocationData locationData(locationName,
                                                   locationDocument["LocationID"].GetInt(),
                                                   locationDocument["LocationIcon"].GetInt(),
                                                   Eegeo::Space::LatLongAltitude::FromDegrees(locationDocument["StartLocationLatitude"].GetDouble(),
                                                                                              locationDocument["StartLocationLongitude"].GetDouble(),
                                                                                              locationDocument["StartLocationAltitude"].GetDouble()),
                                                   static_cast<float>(document["StartLocationOrientationDegrees"].GetDouble()));

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
