/*
 * This is robo 2
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
#define ROSSERIAL_ARDUINO_TCP


#include <ros.h>
//#include <ArduinoTcpHardware.h>

#include <std_msgs/String.h>
#include <std_msgs/Empty.h>
#include <string.h>

const char* ssid     = "Winterfell";
const char* password = "01091978";
// Set the rosserial socket server IP address
IPAddress server(192,168,1,11);
// Set the rosserial socket server port
const uint16_t serverPort = 11412;
int flag=0;
int i=1;

#include <ESP32Servo.h>
Servo myservo;  // create servo object to control a servo
// 16 servo objects can be created on the ESP32

int pos = 0;    // variable to store the servo position
// Recommended PWM GPIO pins on the ESP32 include 2,4,12-19,21-23,25-27,32-33 
int servoPin = 13;

int enA = 33;
int in1 = 25;
int in2 = 26;

// Motor B

int enB = 12;
int in3 = 23;
int in4 = 27;

// Encoder
int encoderPin1a = 32; //Encoder Output 'A' must connected with intreput pin of arduino.
int encoderPin2a = 35; //Encoder Otput 'B' must connected with intreput pin of arduino.
int encoderPin1b = 18; //Encoder Output 'A' must connected with intreput pin of arduino.
int encoderPin2b = 19; //Encoder Otput 'B' must connected with intreput pin of arduino.

volatile int lastEncoded1 = 0; // Here updated value of encoder store.
volatile long encoderValue1 = 0; // Raw encoder value
unsigned int cur;
volatile int lastEncoded2 = 0; // Here updated value of encoder store.
volatile long encoderValue2 = 0; // Raw encoder value

ros::NodeHandle nh;

void messageCallback( const std_msgs::Empty& dat)
{
  digitalWrite(2, HIGH);
  if(i==1)
  {
  digitalWrite(enA, HIGH);
  digitalWrite(enB, HIGH);
  cur=millis();
  
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);  
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH); 
 
    Serial.print(encoderValue1);
    Serial.print(" ");
    Serial.print(encoderValue2);
    Serial.print(" ");
    Serial.println(cur);
  delay(1000);
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);  
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    for(pos = 0; pos <= 150; pos += 1) // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos = 150; pos>=0; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  }
  myservo.detach();
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);  
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW); 
    Serial.print(encoderValue1);
    Serial.print(" ");
    Serial.print(encoderValue2);
    Serial.print(" ");
    Serial.println(cur);
  delay(1000);
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);  
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW); 
    Serial.print(encoderValue1);
    Serial.print(" ");
    Serial.println(encoderValue2);
    flag=1;
    i++;
  }
  digitalWrite(2, LOW);
}
  

// make subscriber
ros::Subscriber<std_msgs::Empty> sub("chatter2", messageCallback);
// Make a chatter publisher
std_msgs::String str_msg;
ros::Publisher sacchin("chatter3", &str_msg);

// Be polite and say hello
char hello[20] = "robo 2 ready";
char bye[20] = "robo 2 finished";

void setup()
{
  
  
  // Use ESP8266 serial to monitor hellothe process
  pinMode(2, OUTPUT);
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
  nh.subscribe(sub);

  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  myservo.setPeriodHertz(50);    // standard 50 hz servo
  myservo.attach(servoPin, 500, 2400); // attaches the servo on pin 18 to the servo object
  // using default min/max of 1000us and 2000us
  // different servos may require different min/max settings
  // for an accurate 0 to 180 sweep
  
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(encoderPin1a, INPUT_PULLUP); 
  pinMode(encoderPin2a, INPUT_PULLUP);
  pinMode(encoderPin1b, INPUT_PULLUP); 
  pinMode(encoderPin2b, INPUT_PULLUP);

  digitalWrite(encoderPin1a, HIGH); //turn pullup resistor on
  digitalWrite(encoderPin2a, HIGH); //turn pullup resistor on
  digitalWrite(encoderPin1b, HIGH); //turn pullup resistor on
  digitalWrite(encoderPin2b, HIGH); //turn pullup resistor on

  attachInterrupt(digitalPinToInterrupt(encoderPin1a), updateEncoder1, CHANGE); 
  attachInterrupt(digitalPinToInterrupt(encoderPin1b), updateEncoder1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderPin2a), updateEncoder2, CHANGE); 
  attachInterrupt(digitalPinToInterrupt(encoderPin2b), updateEncoder2, CHANGE);
}

void updateEncoder1(){
  int MSB1 = digitalRead(encoderPin1a); //MSB = most significant bit
  int LSB1 = digitalRead(encoderPin2a); //LSB = least significant bit

  int encoded1 = (MSB1 << 1) |LSB1; //converting the 2 pin value to single number
  int sum1  = (lastEncoded1 << 2) | encoded1; //adding it to the previous encoded value

  if(sum1 == 0b1101 || sum1 == 0b0100 || sum1 == 0b0010 || sum1 == 0b1011) encoderValue1 --;
  if(sum1 == 0b1110 || sum1 == 0b0111 || sum1 == 0b0001 || sum1 == 0b1000) encoderValue1 ++;

  lastEncoded1 = encoded1; //store this value for next time

}

void updateEncoder2(){
  int MSB2 = digitalRead(encoderPin1b); //MSB = most significant bit
  int LSB2 = digitalRead(encoderPin2b); //LSB = least significant bit

  int encoded2 = (MSB2 << 1) |LSB2; //converting the 2 pin value to single number
  int sum2  = (lastEncoded2 << 2) | encoded2; //adding it to the previous encoded value

  if(sum2 == 0b1101 || sum2 == 0b0100 || sum2 == 0b0010 || sum2 == 0b1011) encoderValue2 --;
  if(sum2 == 0b1110 || sum2 == 0b0111 || sum2 == 0b0001 || sum2 == 0b1000) encoderValue2 ++;

  lastEncoded2 = encoded2; //store this value for next time

}


void loop()
{
  

  if (nh.connected()) {
    
    Serial.println("Connected");
    // Say hello
    digitalWrite(2, HIGH);
    delay(500);
    if(flag==0)
    {
    
      str_msg.data = hello;
    }
    else
    {
      str_msg.data = bye;
    }
    sacchin.publish( &str_msg );
    digitalWrite(2, LOW);
  } else {
    delay(500);
    Serial.println("Not Connected");
  }
  nh.spinOnce();
  // Loop exproximativly at 1Hz
  delay(1000);
//  digitalWrite(2, LOW);
}
