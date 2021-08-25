/*
 * rosserial Publisher Example
 * Prints "hello world!"
 * This intend to connect to a Wifi Access Point
 * and a rosserial socket server.
 * You can launch the rosserial socket server with
 * roslaunch rosserial_server socket.launch
 * The default port is 11411
 *
 */
#include <WiFi.h>
#define ESP32
#define ROSSERIAL_ARDUINO_UDP


#include <ros.h>
//#include <ArduinoTcpHardware.h>

#include <std_msgs/String.h>


const char* ssid     = "Sacchin";
const char* password = "Anirudh.Sacchin";
// Set the rosserial socket server IP address
IPAddress server(192,168,1,8);
// Set the rosserial socket server port
const uint16_t serverPort = 11411;

ros::NodeHandle nh;
//ros::NodeHandle_<ArduinoHardware> nh;
// Make a chatter publisher
std_msgs::String str_msg;
ros::Publisher sacchin("chatter", &str_msg);

// Be polite and say hello
char hello[13] = "ARANYAA ROX";

void setup()
{
  // Use ESP8266 serial to monitor the process
  Serial.begin(115200);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  delay(1000);
  // Connect the ESP8266 the the wifi AP
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Set the connection to rosserial socket server
  nh.getHardware()->setConnection(server, serverPort);
  nh.initNode();

  // Another way to get IP
  Serial.print("IP = ");
  Serial.println(nh.getHardware()->getLocalIP());

  // Start to be polite
  nh.advertise(sacchin);
}

void loop()
{
  

  if (nh.connected()) {
    Serial.println("Connected");
    // Say hello
    str_msg.data = hello;
    sacchin.publish( &str_msg );
  } else {
    Serial.println("Not Connected");
  }
  nh.spinOnce();
  // Loop exproximativly at 1Hz
  delay(1000);
}\
