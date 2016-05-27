//
//  IUIInteractableItem.h
//  SDKSamplesApp
//
//  Created by Ali on 5/16/16.
//
//

#pragma once

#include "VectorMath.h"

namespace Eegeo
{
    namespace UI
    {
        /*!
         * \brief Interface for items that can recieve UI events.
         *
         * This interface is used to notify UI items about events.
         */
        class IUIInteractableItem
        {
            bool m_ItemHasFocus;
        public:
            const virtual float GetItemRadius() = 0;
            const virtual Eegeo::dv3& GetItemEcefPosition() = 0;
            
            void SetItemHasFocus(bool p_focus)
            {
                if(m_ItemHasFocus != p_focus)
                {
                    m_ItemHasFocus = p_focus;
                    
                    if(m_ItemHasFocus)
                        OnFocusGained();
                    else
                        OnFocusLost();
                }
            }
            
            virtual void OnItemClicked() = 0;
            virtual void Update(float dt)   {}
            
        protected:
            virtual void OnFocusGained() {}
            virtual void OnFocusLost()   {}
        };
        
    }
}

