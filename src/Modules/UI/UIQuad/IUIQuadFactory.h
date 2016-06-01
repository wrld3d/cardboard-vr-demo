//
//  Header.h
//  SDKSamplesApp
//
//  Created by Aqif Hamid on 6/1/16.
//
//

#ifndef IUIQuadFactory_h
#define IUIQuadFactory_h

#include "UIQuad.h"

namespace Eegeo
{
    namespace UI
    {
        class IUIQuadFactory
        {
        public:
            
            virtual UIQuad* CreateUIQuad(const std::string& assetPath, const Eegeo::v2& dimension) = 0;
            
            virtual ~IUIQuadFactory(){};
        };
    }
}


#endif /* IUIQuadFactory_h */
