//
//  VRDistortionMaterial
//  SDKSamplesApp
//
//  Created by Aqif Hamid on 3/21/16.
//
//

#include "VRDistortionRenderable.h"

namespace Eegeo
{
    namespace VR
    {
        namespace Distortion
        {
            void VRDistortionRenderable::Render(Eegeo::Rendering::GLState& glState) const
            {
                m_material->SetStatePerRenderable(this, glState);
                m_pMesh->BindVertexBuffers(GetVertexBinding(), glState);
                const u32 indexCount = m_pMesh->GetNumOfIndices();

                Eegeo_ASSERT(indexCount != 0);
                Eegeo_GL(glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_SHORT, (void*)(0)));
                m_pMesh->UnbindVertexBuffers(glState);
                
            }
        }
    }
}
