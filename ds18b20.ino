#include <ThingSpeak.h>
#include <SPI.h>
#include <WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into port 2 on the Arduino
#define SECRET_SSID "TIF_LABS"  // replace MySSID with your WiFi network name
#define SECRET_PASS "Robocraze" // replace MyPassword with your WiFi password
#define ONE_WIRE_BUS 23
#define SECRET_CH_ID 726834                    // replace 0000000 with your channel number
#define SECRET_WRITE_APIKEY "PJ72E497E4KSEF45" // replace XYZ with your channel write API Key

char ssid[] = SECRET_SSID; // your network SSID (name)
char pass[] = SECRET_PASS; // your network password
int keyIndex = 0;          // your network key Index number (needed only for WEP)
WiFiClient client;
unsigned long myChannelNumber = SECRET_CH_ID;
const char *myWriteAPIKey = SECRET_WRITE_APIKEY;

OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

void setup()
{
 Serial.begin(115200); //Initialize serial
 sensors.begin();
 WiFi.mode(WIFI_STA);
 ThingSpeak.begin(client); // Initialize ThingSpeak
}

void loop()
{
 // Connect or reconnect to WiFi
 if (WiFi.status() != WL_CONNECTED)
 {
   Serial.print("Attempting to connect to SSID: ");
   Serial.println(SECRET_SSID);
   while (WiFi.status() != WL_CONNECTED)
   {
     WiFi.begin(ssid, pass); // Connect to WPA/WPA2 network. Change this line if using open or WEP network
     Serial.print(".");
     delay(5000);
   }
   Serial.println("\nConnected.");
 }

 Serial.print("Requesting temperatures...");
 sensors.requestTemperatures(); // Send the command to get temperatures
 int x = ThingSpeak.writeField(myChannelNumber, 1, sensors.getTempCByIndex(0), myWriteAPIKey);

 delay(1000); // Wait 2 seconds to update the channel again
}
