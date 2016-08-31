// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "VectorMath.h"
#include "IUICameraProvider.h"

namespace Eegeo
{
    namespace UI
    {
        /*!
         * \brief Interface for items that can receive UI events.
         *
         * This interface is used to notify UI items about events.
         */
        class IUIInteractableItem
        {
            bool m_itemHasFocus;
        public:
            virtual bool IsCollidingWithPoint(const Eegeo::v2& screenPoint, IUICameraProvider& cameraProvider) = 0;
            virtual void OnItemClicked() = 0;
            virtual ~IUIInteractableItem(){}
            
            void SetItemHasFocus(bool focus)
            {
                if(m_itemHasFocus != focus)
                {
                    m_itemHasFocus = focus;
                    
                    if(m_itemHasFocus)
                        OnFocusGained();
                    else
                        OnFocusLost();
                }
            }
            
        protected:
            virtual void OnFocusGained() {}
            virtual void OnFocusLost()   {}
        };
        
    }
}

