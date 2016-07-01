// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "UIQuadFactory.h"
#include "ShaderIdGenerator.h"
#include "MaterialIdGenerator.h"
#include "Logger.h"

namespace Eegeo
{
    namespace UI
    {
        
        UIQuadFactory::UIQuadFactory(const Eegeo::Modules::Core::RenderingModule& renderingModule,
                                     Eegeo::Helpers::ITextureFileLoader& textureFileLoader
)
        : m_glBufferPool(renderingModule.GetGlBufferPool())
        , m_vertexBindingPool(renderingModule.GetVertexBindingPool())
        , m_vertexLayoutPool(renderingModule.GetVertexLayoutPool())
        , m_shaderIdGenerator(renderingModule.GetShaderIdGenerator())
        , m_materialIdGenerator(renderingModule.GetMaterialIdGenerator())
        , m_textureFileLoader(textureFileLoader)
        , m_pShader(NULL)
        {
            m_pShader = Eegeo::Rendering::Shaders::TexturedUniformColoredShader::Create(m_shaderIdGenerator.GetNextId());
        }
        
        UIQuadFactory::~UIQuadFactory()
        {
            Eegeo_DELETE m_pShader;
            for(TMaterialMap::iterator it = m_materialMap.begin(); it != m_materialMap.end(); ++it)
            {
                Eegeo_DELETE it->second;
            }
            m_materialMap.clear();
        }
        
        UIQuad* UIQuadFactory::CreateUIQuad(const std::string& assetPath,
                             const Eegeo::v2& dimension,
                             const Eegeo::v2& uvMin,
                             const Eegeo::v2& uvMax,
                             const Eegeo::Rendering::LayerIds::Values renderLayer){
            Eegeo::Rendering::Materials::TexturedUniformColoredMaterial* pMaterial = GetMaterialForAsset(assetPath);
            return new UIQuad(assetPath, *pMaterial, m_vertexBindingPool, m_glBufferPool, dimension, uvMin, uvMax, Eegeo::dv3::Zero(), Eegeo::v4::One(), renderLayer);
        }
        
        Eegeo::Rendering::Materials::TexturedUniformColoredMaterial* UIQuadFactory::GetMaterialForAsset(const std::string& assetPath)
        {
            TMaterialMap::const_iterator foundMaterial = m_materialMap.find(assetPath);
            
            if(foundMaterial != m_materialMap.end())
            {
                return foundMaterial->second;
            }
            
            Helpers::GLHelpers::TextureInfo textureInfo;
            textureInfo.textureId = 0;
            textureInfo.width = 0;
            textureInfo.height = 0;
            
            
            const bool generateMipmaps = true;
            bool success = m_textureFileLoader.LoadTexture(textureInfo, assetPath, generateMipmaps);
            
            Eegeo_ASSERT(success, "failed to load texture");
            if (!success)
                return NULL;
            
            const v4& initialColor = v4::One();
            Eegeo::Rendering::Materials::TexturedUniformColoredMaterial* pMaterial = new (Eegeo::Rendering::Materials::TexturedUniformColoredMaterial) (
                                                                               m_materialIdGenerator.GetNextId(),
                                                                               "UIRectMaterial",
                                                                               *m_pShader,
                                                                               textureInfo.textureId,
                                                                               initialColor);
            m_materialMap[assetPath] = pMaterial;
            return pMaterial;
            
        }
        
        
        
    }
}
