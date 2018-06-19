// 1-channel LoRa Gateway for ESP8266 & ESP32
// This version includes some enhancements plus support for the TTGO LoRa v2 Board out of the box.
//
// Copyright (c) 2016, 2017, 2018 Maarten Westenberg version for ESP8266
// Version 5.2.1 H
// Date: 2018-06-06
//
// Based on work done by Thomas Telkamp for Raspberry PI 1ch gateway and many others.
// Contibutions of Dorijan Morelj and Andreas Spies for OLED support.
//
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the MIT License
// which accompanies this distribution, and is available at
// https://opensource.org/licenses/mit-license.php
//
// Author: Maarten Westenberg (mw12554@hotmail.com)
//
// This file contains a number of compile-time settings that can be set on (=1) or off (=0)
// The disadvantage of compile time is minor compared to the memory gain of not having
// too much code compiled and loaded on your ESP8266.
//
// ----------------------------------------------------------------------------------------

#define VERSION "V.5.2.1.H; 180606a"

// This value of DEBUG determines whether some parts of code get compiled.
// Also this is the initial value of debug parameter. 
// The value can be changed using the admin webserver
// For operational use, set initial DEBUG vaulue 0
#define DEBUG 0

// Debug message will be put on Serial is this one is set.
// If set to 0, not USB Serial prints are done
// Set to 1 it will prinr all user level messages (with correct debug set)
// If set to 2 it will also print interrupt messages (not recommended)
#define DUSB 1

// Define whether we should do a formatting of SPIFFS when starting the gateway
// This is usually a good idea if the webserver is interrupted halfway a writing
// operation.
// Normally, value 0 is a good default.
#define SPIFF_FORMAT 0

// The spreading factor is the most important parameter to set for a single channel
// gateway. It specifies the speed/datarate in which the gateway and node communicate.
// As the name says, in principle the single channel gateway listens to one channel/frequency
// and to one spreading factor only.
// This parameters contains the default value of SF, the actual version can be set with
// the webserver and it will be stored in SPIFF
// NOTE: The frequency is set in the loraModem.h file and is default 868.100000 MHz.
#define _SPREADING SF9

// Channel Activity Detection
// This function will scan for valid LoRa headers and determine the Spreading 
// factor accordingly. If set to 1 we will use this function which means the 
// 1-channel gateway will become even more versatile. If set to 0 we will use the
// continuous listen mode.
// Using this function means that we HAVE to use more dio pins on the RFM95/sx1276
// device and also connect enable dio1 to detect this state. 
#define _CAD 1

// Definitions for the admin webserver.
// A_SERVER determines whether or not the admin webpage is included in the sketch.
// Normally, leave it in!
#define A_SERVER 1				// Define local WebServer only if this define is set
#define A_REFRESH 1				// Allow the webserver refresh or not?
#define A_SERVERPORT 80			// Local webserver port (normally 80)
#define A_MAXBUFSIZE 192		// Must be larger than 128, but small enough to work

// Definitions for over the air updates. At the moment we support OTA with IDE
// Make sure that tou have installed Python version 2.7 and have Bonjour in your network.
// Bonjour is included in iTunes (which is free) and OTA is recommended to install 
// the firmware on your router witout having to be really close to the gateway and 
// connect with USB.
#define A_OTA 1

// We support two pin-out configurations out-of-the-box: HALLARD and COMPRESULT.
// If you use one of these two, just set the parameter to the right value.
// If your pin definitions are different, update the loraModem.h file to reflect these settings.
//	1: HALLARD
//	2: COMRESULT pin out
//	3: ESP32 Wemos pin out
//	4: ESP32 TTGO pinning
//	5: ESP32 TTGO v2 pinning
#define _PIN_OUT 5

// Gather statistics on sensor and Wifi status
// 0= No statistics
// 1= Keep track of messages statistics, number determined by MAX_STAT
// 2= Option 1 + Keep track of messages received PER each SF (default)
// 3= See Option 2, but with extra channel info (Do not use when no Hopping is done)
#define STATISTICS 3

// Maximum number of statistics records gathered. 20 is a good maximum (memory intensive)
#define MAX_STAT 20

// Single channel gateways if they behave strict should only use one frequency 
// channel and one spreading factor. However, the TTN backend replies on RX2 
// timeslot for spreading factors SF9-SF12. 
// Also, the server will respond with SF12 in the RX2 timeslot.
// If the 1ch gateway is working in and for nodes that ONLY transmit and receive on the set
// and agreed frequency and spreading factor. make sure to set STRICT to 1.
// In this case, the frequency and spreading factor for downlink messages is adapted by this
// gateway
// NOTE: If your node has only one frequency enabled and one SF, you must set this to 1
//		in order to receive downlink messages
// NOTE: In all other cases, value 0 works for most gateways with CAD enabled
#define _STRICT_1CH	0

// Setup WiFi Through Wifi Manager, this will allow you to connect directly
// to the gateway and specify your wifi credentials. You can also setup
// the access point's ssid and password here. Default is off.
#define WIFIMANAGER 0
#define AP_NAME "YourName"
#define AP_PASSWD "YourPassword"

// To connect to a wifi network, you can specify your ssid and password here.
#define WIFI_SSID "YourSSID"
#define WIFI_PASSWORD "YourPassword"

// Defines whether the gateway will also report sensor/status value on MQTT
// after all, a gateway can be a node to the system as well
// Set its LoRa address and key below in this file
// See spec. para 4.3.2
#define GATEWAYNODE 0
#define _CHECK_MIC 0

// This section defines whether we use the gateway as a repeater
// For his, we use another output channle as the channel (default==0) we are 
// receiving the messages on.
#define REPEATER 0

// Will we use Mutex or not?
// +SPI is input for SPI, SPO is output for SPI
#define MUTEX 0

// Define if OLED Display is connected to I2C bus. Note that defining an OLED display does not
// impact performance very much, certainly if no OLED is connected. Wrong OLED will not show
// sensible results on display
// OLED==0; No OLED display connected
// OLED==1; 0.9 Oled Screen based on SSD1306
// OLED==2;	1"3 Oled screens for Wemos, 128x64 SH1106
#define OLED 1


// Define whether we want to manage the gateway over UDP (next to management 
// thru webinterface).
// This will allow us to send messages over the UDP connection to manage the gateway 
// and its parameters. Sometimes the gateway is not accesible from remote, 
// in this case we would allow it to use the SERVER UDP connection to receive 
// messages as well.
// NOTE: Be aware that these messages are NOT LoRa and NOT LoRa Gateway spec compliant.
//	However that should not interfere with regular gateway operation but instead offer 
//	functions to set/reset certain parameters from remote.
#define GATEWAYMGT 0

// Do extensive loggin
// Use the ESP8266 SPIFS filesystem to do extensive logging.
// We must take care that the filesystem never(!) is full, and for that purpose we
// rather have new records/line of statistics than very old.
// Of course we must store enough records to make the filesystem work
//
#define STAT_LOG 1


// Name of he configfile in SPIFFs	filesystem
// In this file we store the configuration and other relevant info that should
// survive a reboot of the gateway		
#define CONFIGFILE "/gwayConfig.txt"

// Set the Server Settings (IMPORTANT)
#define _LOCUDPPORT 1700					// UDP port of gateway! Often 1700 or 1701 is used for upstream comms

// Timing
#define _MSG_INTERVAL 15					// Reset timer in seconds
#define _PULL_INTERVAL 55					// PULL_DATA messages to server to get downstream in milliseconds
#define _STAT_INTERVAL 120					// Send a 'stat' message to server
#define _NTP_INTERVAL 3600					// How often do we want time NTP synchronization
#define _WWW_INTERVAL	60					// Number of seconds before we refresh the WWW page

// MQTT / The Things Network Setup, uncomment if you want the European server
#define _TTNPORT 1700						// Standard port for TTN

//#define _TTNSERVER "router.eu.thethings.network"
#define _TTNSERVER "us-west.thethings.network"

// If you have a second back-end server defined such as Semtech or loriot.io
// your can define _THINGPORT and _THINGSERVER with your own value.
// If not, make sure that you do not defined these, which will save CPU time
// Port is UDP port in this program
//
// Default for testing: Switched off
//#define _THINGPORT <port>					// dash.westenberg.org:8057
//#define _THINGSERVER "<dns.server.com>"		// Server URL of the LoRa-udp.js handler

// Gateway Ident definitions
#define _DESCRIPTION "ESP32 TTGO v2 Gateway"
#define _EMAIL "lina.adkins@gmail.com"
#define _PLATFORM "ESP32"
#define _LAT 42.3760
#define _LON 122.9164
#define _ALT 1

// ntp
// Please add daylight saving time to NTP_TIMEZONES when desired
#define NTP_TIMESERVER "nl.pool.ntp.org"	// Country and region specific
#define NTP_TIMEZONES	2					// How far is our Timezone from UTC (excl daylight saving/summer time)
#define SECS_IN_HOUR	3600
#define NTP_INTR 0							// Do NTP processing with interrupts or in loop();

#if GATEWAYNODE==1
#define _DEVADDR { 0x26, 0x01, 0x01, 0x01 }
#define _APPSKEY { 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
#define _NWKSKEY { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
#define _SENSOR_INTERVAL 300
#endif

// Define the correct radio type that you are using
#define CFG_sx1276_radio		
//#define CFG_sx1272_radio

// Serial Port speed
#define _BAUDRATE 115200					// Works for debug messages to serial momitor

// We can put the gateway in such a mode that it will (only) recognize
// nodes that are put in a list of trusted nodes 
// Values:
// 0: Do not use names for trusted Nodes
// 1: Use the nodes as a translation tabel for hex codes to names (in TLN)
// 2: Same as 1, but is nodes NOT in the nodes list below they are NOT
//		forwarded or counted! (not yet fully implemented)
#define TRUSTED_NODES 1
#if TRUSTED_NODES >= 1
struct nodex  {
	uint32_t id;
	char nm[32];
};

// Add all your named and trusted nodes to this list
nodex nodes[] = {
	{ 0x260116BD , "lora-34 PIR node" },			// F=0
	{ 0x26011152 , "lora-35 temp+humi node" },		// F=0
	{ 0x2601148C , "lora-36 test node" },			// F=0
	{ 0x26011B90 , "lora-39 temp DS18B20" },		// F=1
	{ 0x260119A6 , "lora-40 airquality" },			// F=0
	{ 0x2601117D , "lora-41 temp+humi SR04T" },
	{ 0x26011514 , "lora-43 ch1, no sensors" },		// F=1
	{ 0x26011D77 , "lora-45 not sensor" },
	{ 0x2601160F , "lora-46 HTU21 metal case" },	// F=0
	{ 0x26011E52 , "lora-53 gas sensor" },			// F=ALL
	{ 0x02020441 , "lora-65 Waterproof temp humi" },// F=0
	{ 0x26011999 , "lora-901 distance sensor" }		// F=0
};
#endif

// Wifi definitions
// WPA is an array with SSID and password records. Set WPA size to number of entries in array
// When using the WiFiManager, we will overwrite the first entry with the 
// accesspoint we last connected to with WifiManager
// NOTE: Structure needs at least one (empty) entry.
//		So WPASIZE must be >= 1
struct wpas {
	char login[32];							// Maximum Buffer Size (and allocated memory)
	char passw[64];
};

// You can add more than one SSID here if you'd like. Do NOT use the first and last values in the array.
wpas wpa[] = {
  { "" , "" },							// Reserved for WiFi Manager
  { WIFI_SSID , WIFI_PASSWORD },
  { "", "" }
};

// For asserting and testing the following defines are used.
//
#if !defined(CFG_noassert)
#define ASSERT(cond) if(!(cond)) gway_failed(__FILE__, __LINE__)
#else
#define ASSERT(cond) /**/
#endif