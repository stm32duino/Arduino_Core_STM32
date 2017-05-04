/*==============================================================================
 * NETWORK CONFIGURATION
 *
 * You must configure your particular hardware. Follow the steps below.
 *
 * Currently StandardFirmataEthernetPlus is configured as a client. An option to
 * configure as a server may be added in the future.
 *============================================================================*/

/*
 * Only WIZ5100-based shields and boards are currently supported for
 * StandardFirmataEthernetPlus.
 */
#define WIZ5100_ETHERNET

#ifdef WIZ5100_ETHERNET
#include <SPI.h>
#include <Ethernet.h>
EthernetClient client;
#endif

// STEP 1 [REQUIRED for all boards and shields]
// replace with IP of the server you want to connect to, comment out if using 'remote_host'
#define remote_ip IPAddress(10, 0, 0, 3)
// *** REMOTE HOST IS NOT YET WORKING ***
// replace with hostname of server you want to connect to, comment out if using 'remote_ip'
// #define remote_host "server.local"

// STEP 2 [REQUIRED]
// Replace with the port that your server is listening on
#define remote_port 3030

// STEP 3 [REQUIRED unless using DHCP]
// Replace with your board or ethernet shield's IP address
// Comment out if you want to use DHCP
#define local_ip IPAddress(10, 0, 0, 15)

// STEP 4 [REQUIRED]
// replace with ethernet shield mac. Must be unique for your network
const byte mac[] = {0x90, 0xA2, 0xDA, 0x00, 0x53, 0xE5};

/*==============================================================================
 * CONFIGURATION ERROR CHECK (don't change anything here)
 *============================================================================*/

#if defined remote_ip && defined remote_host
#error "cannot define both remote_ip and remote_host at the same time in ethernetConfig.h"
#endif

/*==============================================================================
 * PIN IGNORE MACROS (don't change anything here)
 *============================================================================*/

// ignore SPI pins, pin 10 (Ethernet SS) and pin 4 (SS for SD-Card on Ethernet shield)
#define IS_IGNORE_ETHERNET_SHIELD(p) ((IS_PIN_SPI(p) || (p) == 4) || (p) == 10)
