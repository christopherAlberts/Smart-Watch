
void page2(){
  tft.setTextWrap(false);
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 30);
  tft.setTextColor(ST77XX_GREEN);
  tft.setTextSize(4);
  tft.println("Page 2!");
  tft.setCursor(0, 0); 
}

#include <WiFi.h>

// Enter your WiFi SSID and password
char ssid[] = "Periwinkle Downstairs 2.4GH";             // your network SSID (name)
char pass[] = "adri6604";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;                      // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)

char server[] = "wifitest.adafruit.com";    // name address for adafruit test
char path[]   = "/testwifi/index.html";

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
WiFiClient client;

void page2_wifi(){
  tft.setTextWrap(false);
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 30);
  tft.setTextColor(ST77XX_GREEN);
  tft.setTextSize(1);
  tft.println("Page 2!");
  
  // attempt to connect to Wifi network:
  tft.print("Attempting to connect to SSID: ");
  tft.println(ssid);

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      tft.print(".");
  }

  tft.println("");
  tft.println("Connected to WiFi");
  printWifiStatus();

//  Serial.println("\nStarting connection to server...");
//  // if you get a connection, report back via serial:
//  if (client.connect(server, 80)) {
//    Serial.println("connected to server");
//    // Make a HTTP request:
//    client.print("GET "); client.print(path); client.println(" HTTP/1.1");
//    client.print("Host: "); client.println(server);
//    client.println("Connection: close");
//    client.println();
//  }

}




//void setup() {
//  //Initialize serial and wait for port to open:
//  Serial.begin(115200);
//  while (!Serial) {
//    ; // wait for serial port to connect. Needed for native USB port only
//  }
//
//  // attempt to connect to Wifi network:
//  Serial.print("Attempting to connect to SSID: ");
//  Serial.println(ssid);
//
//  WiFi.begin(ssid, pass);
//  while (WiFi.status() != WL_CONNECTED) {
//      delay(500);
//      Serial.print(".");
//  }
//
//  Serial.println("");
//  Serial.println("Connected to WiFi");
//  printWifiStatus();
//
//  Serial.println("\nStarting connection to server...");
//  // if you get a connection, report back via serial:
//  if (client.connect(server, 80)) {
//    Serial.println("connected to server");
//    // Make a HTTP request:
//    client.print("GET "); client.print(path); client.println(" HTTP/1.1");
//    client.print("Host: "); client.println(server);
//    client.println("Connection: close");
//    client.println();
//  }
//}

//void loop() {
//  // if there are incoming bytes available
//  // from the server, read them and print them:
//  while (client.available()) {
//    char c = client.read();
//    Serial.write(c);
//  }
//
//  // if the server's disconnected, stop the client:
//  if (!client.connected()) {
//    Serial.println();
//    Serial.println("disconnecting from server.");
//    client.stop();
//
//    // do nothing forevermore:
//    while (true) {
//      delay(100);
//    }
//  }
//}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  tft.print("SSID: ");
  tft.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  tft.print("IP Address: ");
  tft.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  tft.print("signal strength (RSSI):");
  tft.print(rssi);
  tft.println(" dBm");
}
