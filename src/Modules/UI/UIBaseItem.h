//
//  UIBaseItem.hpp
//  SDKSamplesApp
//
//  Created by Aqif Hamid on 5/24/16.
//
//

#ifndef UIBaseItem_h
#define UIBaseItem_h

#include "VectorMath.h"

namespace Eegeo
{
    namespace UI
    {
        class UIBaseItem
        {
            
        private:
            
            Eegeo::dv3 m_EcefPosition;
            Eegeo::v4 m_Color;
            Eegeo::v3 m_Scale;
            Eegeo::v2 m_Size;
            
            bool m_IsDirty;
            
        protected:
            
            bool IsDirty();
            void SetDirty(bool isDirty = true);
            
        public:
            
            UIBaseItem(Eegeo::dv3 position = Eegeo::dv3::Zero()
                       , Eegeo::v2 size = Eegeo::v2::One()
                       , Eegeo::v3 scale = Eegeo::v3::One()
                       , Eegeo::v4 color = Eegeo::v4::One());
            
            virtual ~UIBaseItem();
            
            virtual void Update(float dt) = 0;
            
            void SetEcefPosition(Eegeo::dv3 position);
            const Eegeo::dv3& GetEcefPosition();
            
            void SetSize(Eegeo::v2 size);
            const Eegeo::v2& GetSize();
            
            void SetColor(Eegeo::v4 color);
            const Eegeo::v4& GetColor();
            
            void SetScale(Eegeo::v3 scale);
            const Eegeo::v3& GetScale();
            
            
        };
        
    }
}


#endif /* UIBaseItem_h */
