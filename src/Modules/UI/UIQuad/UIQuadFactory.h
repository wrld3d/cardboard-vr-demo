// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "IUIQuadFactory.h"

namespace Eegeo
{
    namespace UI
    {
        class UIQuadFactory : public IUIQuadFactory
        {
            
        private:
            
            typedef std::map<std::string, Eegeo::Rendering::Materials::UITexturedUniformColoredMaterial*> TMaterialMap;
            TMaterialMap m_materialMap;
            
            Eegeo::Rendering::Shaders::TexturedUniformColoredShader* m_pShader;
            
            Eegeo::Rendering::GlBufferPool& m_glBufferPool;
            Eegeo::Rendering::VertexLayouts::VertexBindingPool& m_vertexBindingPool;
            Eegeo::Rendering::VertexLayouts::VertexLayoutPool& m_vertexLayoutPool;
            
            Eegeo::Helpers::ITextureFileLoader& m_textureFileLoader;
            Rendering::Shaders::ShaderIdGenerator& m_shaderIdGenerator;
            Rendering::Materials::MaterialIdGenerator& m_materialIdGenerator;
            
            Eegeo::Rendering::Materials::UITexturedUniformColoredMaterial* GetMaterialForAsset(const std::string& assetPath);
            
            
        public:
            UIQuadFactory(const Eegeo::Modules::Core::RenderingModule& renderingModule,
                          Eegeo::Helpers::ITextureFileLoader& textureFileLoader);
            
            virtual ~UIQuadFactory();
            
            UIQuad* CreateUIQuad(const std::string& assetPath,
                                 const Eegeo::v2& dimension,
                                 const Eegeo::v2& uvMin = Eegeo::v2::Zero(),
                                 const Eegeo::v2& uvMax = Eegeo::v2::One(),
                                 const Eegeo::Rendering::LayerIds::Values renderLayer = Eegeo::Rendering::LayerIds::Values::AfterWorld);
            
            
            
        };
        
    }
}



