/************************ Adafruit IO Config *******************************/

// visit io.adafruit.com if you need to create an account,
// or if you need your Adafruit IO key.
#define IO_USERNAME  "felipebcll"
#define IO_KEY       "aio_yanB77kHsqlepPu8QqX9Yp6itKA9"

/******************************* WIFI **************************************/

#define WIFI_SSID   "HomeWarn"
#define WIFI_PASS   "1Ser2Ra3Ne4Gra5"

#include "AdafruitIO_WiFi.h"

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

/****************************************************************************/
