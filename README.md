<a href="http://www.eegeo.com/">
    <img src="http://cdn2.eegeo.com/wp-content/uploads/2016/03/eegeo_logo_quite_big.png" alt="eeGeo Logo" title="eegeo" align="right" height="80px" />
</a>

# eeGeo Cardboard API

![eeGeo](http://cdn2.eegeo.com/wp-content/uploads/2016/03/readme-banner.jpg)

* [Support](#support)
* [Getting Started](#getting-started)
    * [eeGeo API Key](#eegeo-api-key)
* [SDK Documentation](#sdk-documentation)
* [License](#support)

This example app showcases the [eeGeo SDK's](http://www.eegeo.com/) integration with Google Cardboard for creating VR experiences.

### What does the API have to offer?

* Intergration with Google Cardboard SDK
* Headtracking and magnet trigger usage
* Lens distortion integration with Google Cardboard QR Code based profile selector
* Ability to add elements on screen and detect gaze on them for interaction 
* API for adding jump points in the world to jump around different locations

## Support

If you have any questions, bug reports, or feature requests, feel free to submit to the [issue tracker](https://github.com/eegeo/cardboard-vr-integration/issues) for this repository.

## Getting Started

This example app demonstrates the use of eeGeo'Cardboard API that allows developers to create VR experiences on Android.

This section will walk you through the process of getting up and running quickly on each platform.

1.  Clone this repo: `git clone https://github.com/eegeo/cardboard-vr-integration/tree/ui`
2.  Obtain an [eeGeo API key](https://www.eegeo.com/developers/apikeys) and place it in the [ApiKey.h](https://github.com/eegeo/cardboard-vr-integration/blob/ui/src/ApiKey.h#L11) file.
3.  Choose a platform from the below table to see detailed instructions for building the app.

Platform                                        | Languages         
------------------------------------------------|-------------------
[Getting started on Android](/android#readme)   | C++, Java         

### eeGeo API Key 

In order to use the eeGeo 3D Maps SDK, you must sign up for a free developer account at https://www.eegeo.com/developers. After signing up, you'll be able to create an [API key](https://www.eegeo.com/developers/apikeys) for your apps. 

To run this example app, you must place the API key in the [ApiKey.h](https://github.com/eegeo/cardboard-vr-integration/blob/ui/src/ApiKey.h#L11) file.

## SDK Documentation

See the [eeGeo API reference](http://cdn1.eegeo.com/docs/mobile-sdk/namespaces.html) for documentation on the individual SDK types.

## License

The eeGeo 3D Maps SDK is released under the Eegeo Platform SDK Evaluation license. See the [LICENSE.md](https://github.com/eegeo/cardboard-vr-integration/blob/master/LICENSE.md) file for details.
