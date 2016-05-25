//
//  UIImageButtonClickedCallback.h
//  SDKSamplesApp
//
//  Created by Ali on 5/16/16.
//
//

#pragma once

namespace Eegeo
{
    namespace UI
    {
        
        class IUIImageButtonClickedCallback
        {
        public:
            virtual ~IUIImageButtonClickedCallback() {;}
            virtual void operator()() = 0;
        };
        
        template <class T> class
        TUIImageButtonClickedCallback : public IUIImageButtonClickedCallback
        {
        public:
            TUIImageButtonClickedCallback(T* context, void (T::*callback)())
            : m_callback(callback)
            , m_context(context)
            {
            }

            virtual void operator()()
            {
                (*m_context.*m_callback)();
            }
            
        private:
            void (T::*m_callback)();
            T* m_context;
        };
        
    }
}


