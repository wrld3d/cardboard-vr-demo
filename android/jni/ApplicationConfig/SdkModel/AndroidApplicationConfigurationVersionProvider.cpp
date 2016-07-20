// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "AndroidApplicationConfigurationVersionProvider.h"
#include "Types.h"

namespace Examples
{
    namespace ApplicationConfig
    {
        namespace SdkModel
        {

        	AndroidApplicationConfigurationVersionProvider::AndroidApplicationConfigurationVersionProvider(const AndroidNativeState& nativeState)
            {

        		m_productVersion = nativeState.versionName;

            }
            
            std::string AndroidApplicationConfigurationVersionProvider::GetProductVersionString() const
            {
                return m_productVersion;
            }
            
            std::string AndroidApplicationConfigurationVersionProvider::GetBuildNumberString() const
            {
                return m_buildNumber;
            }
        }
    }
}
