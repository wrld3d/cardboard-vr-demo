//
//  UIQuadFactory.h
//  SDKSamplesApp
//
//  Created by Aqif Hamid on 6/1/16.
//
//

#ifndef UIQuadFactory_h
#define UIQuadFactory_h

#include "IUIQuadFactory.h"

namespace Eegeo
{
    namespace UI
    {
        class UIQuadFactory : public IUIQuadFactory
        {
            
        private:
            
            typedef std::map<const char *, Eegeo::Rendering::Materials::TexturedUniformColoredMaterial*> TMaterialMap;
            TMaterialMap m_MaterialMap;
            
            Eegeo::Rendering::Shaders::TexturedUniformColoredShader* m_Shader;
            
            Eegeo::Rendering::GlBufferPool& m_GlBufferPool;
            Eegeo::Rendering::VertexLayouts::VertexBindingPool& m_VertexBindingPool;
            Eegeo::Rendering::VertexLayouts::VertexLayoutPool& m_VertexLayoutPool;
            Eegeo::Rendering::RenderableFilters& m_RenderableFilters;
            
            Eegeo::Helpers::ITextureFileLoader& m_TextureFileLoader;
            Rendering::Shaders::ShaderIdGenerator& m_ShaderIdGenerator;
            Rendering::Materials::MaterialIdGenerator& m_MaterialIdGenerator;
            
            Eegeo::Rendering::Materials::TexturedUniformColoredMaterial* GetMaterialForAsset(const std::string& assetPath);
            
        public:
            UIQuadFactory(const Eegeo::Modules::Core::RenderingModule& renderingModule,
                          Eegeo::Helpers::ITextureFileLoader& textureFileLoader);
            
            virtual ~UIQuadFactory();
            
            UIQuad* CreateUIQuad(const std::string& assetPath, const Eegeo::v2& dimension);
            
            
        };
        
    }
}



#endif /* UIQuadFactory_h */
