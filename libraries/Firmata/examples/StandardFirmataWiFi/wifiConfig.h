/*==============================================================================
 * WIFI CONFIGURATION
 *
 * You must configure your particular hardware. Follow the steps below.
 *
 * Currently StandardFirmataWiFi is configured as a server. An option to
 * configure as a client may be added in the future.
 *============================================================================*/

// STEP 1 [REQUIRED]
// Uncomment / comment the appropriate set of includes for your hardware (OPTION A, B or C)
// Option A is enabled by default.

/*
 * OPTION A: Configure for Arduino WiFi shield
 *
 * This will configure StandardFirmataWiFi to use the original WiFi library (deprecated) provided
 * with the Arduino IDE. It is supported by the Arduino WiFi shield (a discontinued product) and
 * is compatible with 802.11 B/G networks.
 *
 * To configure StandardFirmataWiFi to use the Arduino WiFi shield
 * leave the #define below uncommented.
 */
#define ARDUINO_WIFI_SHIELD

//do not modify these next 4 lines
#ifdef ARDUINO_WIFI_SHIELD
#include "utility/WiFiStream.h"
WiFiStream stream;
#endif

/*
 * OPTION B: Configure for WiFi 101
 *
 * This will configure StandardFirmataWiFi to use the WiFi101 library, which works with the Arduino WiFi101
 * shield and devices that have the WiFi101 chip built in (such as the MKR1000). It is compatible
 * with 802.11 B/G/N networks.
 *
 * To enable, uncomment the #define WIFI_101 below and verify the #define values under
 * options A and C are commented out.
 *
 * IMPORTANT: You must have the WiFI 101 library installed. To easily install this library, opent the library manager via:
 * Arduino IDE Menus: Sketch > Include Library > Manage Libraries > filter search for "WiFi101" > Select the result and click 'install'
 */
//#define WIFI_101

//do not modify these next 4 lines
#ifdef WIFI_101
#include "utility/WiFi101Stream.h"
WiFi101Stream stream;
#endif

/*
 * OPTION C: Configure for HUZZAH
 *
 * HUZZAH is not yet supported, this will be added in a later revision to StandardFirmataWiFi
 */

//------------------------------
// TODO
//------------------------------
//#define HUZZAH_WIFI


// STEP 2 [REQUIRED for all boards and shields]
// replace this with your wireless network SSID
char ssid[] = "your_network_name";

// STEP 3 [OPTIONAL for all boards and shields]
// if you want to use a static IP (v4) address, uncomment the line below. You can also change the IP.
// if this line is commented out, the WiFi shield will attempt to get an IP from the DHCP server
// #define STATIC_IP_ADDRESS 192,168,1,113

// STEP 4 [REQUIRED for all boards and shields]
// define your port number here, you will need this to open a TCP connection to your Arduino
#define SERVER_PORT 3030

// STEP 5 [REQUIRED for all boards and shields]
// determine your network security type (OPTION A, B, or C). Option A is the most common, and the default.


/*
 * OPTION A: WPA / WPA2
 *
 * WPA is the most common network security type. A passphrase is required to connect to this type.
 *
 * To enable, leave #define WIFI_WPA_SECURITY uncommented below, set your wpa_passphrase value appropriately,
 * and do not uncomment the #define values under options B and C
 */
#define WIFI_WPA_SECURITY

#ifdef WIFI_WPA_SECURITY
char wpa_passphrase[] = "your_wpa_passphrase";
#endif  //WIFI_WPA_SECURITY

/*
 * OPTION B: WEP
 *
 * WEP is a less common (and regarded as less safe) security type. A WEP key and its associated index are required
 * to connect to this type.
 *
 * To enable, Uncomment the #define below, set your wep_index and wep_key values appropriately, and verify
 * the #define values under options A and C are commented out.
 */
//#define WIFI_WEP_SECURITY

#ifdef WIFI_WEP_SECURITY
//The wep_index below is a zero-indexed value.
//Valid indices are [0-3], even if your router/gateway numbers your keys [1-4].
byte wep_index = 0;
char wep_key[] = "your_wep_key";
#endif  //WIFI_WEP_SECURITY


/*
 * OPTION C: Open network (no security)
 *
 * Open networks have no security, can be connected to by any device that knows the ssid, and are unsafe.
 *
 * To enable, uncomment #define WIFI_NO_SECURITY below and verify the #define values
 * under options A and B are commented out.
 */
//#define WIFI_NO_SECURITY

/*==============================================================================
 * CONFIGURATION ERROR CHECK (don't change anything here)
 *============================================================================*/

#if ((defined(ARDUINO_WIFI_SHIELD) && (defined(WIFI_101) || defined(HUZZAH_WIFI))) || (defined(WIFI_101) && defined(HUZZAH_WIFI)))
#error "you may not define more than one wifi device type in wifiConfig.h."
#endif //WIFI device type check

#if !(defined(ARDUINO_WIFI_SHIELD) || defined(WIFI_101) || defined(HUZZAH_WIFI))
#error "you must define a wifi device type in wifiConfig.h."
#endif

#if ((defined(WIFI_NO_SECURITY) && (defined(WIFI_WEP_SECURITY) || defined(WIFI_WPA_SECURITY))) || (defined(WIFI_WEP_SECURITY) && defined(WIFI_WPA_SECURITY)))
#error "you may not define more than one security type at the same time in wifiConfig.h."
#endif  //WIFI_* security define check

#if !(defined(WIFI_NO_SECURITY) || defined(WIFI_WEP_SECURITY) || defined(WIFI_WPA_SECURITY))
#error "you must define a wifi security type in wifiConfig.h."
#endif  //WIFI_* security define check

/*==============================================================================
 * PIN IGNORE MACROS (don't change anything here)
 *============================================================================*/

// ignore SPI pins, pin 5 (reset WiFi101 shield), pin 7 (WiFi handshake) and pin 10 (WiFi SS)
// also don't ignore SS pin if it's not pin 10
// TODO - need to differentiate between Arduino WiFi1 101 Shield and Arduino MKR1000
#define IS_IGNORE_WIFI101_SHIELD(p)  ((p) == 10 || (IS_PIN_SPI(p) && (p) != SS) || (p) == 5 || (p) == 7)

// ignore SPI pins, pin 4 (SS for SD-Card on WiFi-shield), pin 7 (WiFi handshake) and pin 10 (WiFi SS)
#define IS_IGNORE_WIFI_SHIELD(p)     ((IS_PIN_SPI(p) || (p) == 4) || (p) == 7 || (p) == 10)
