#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

//Wifi name
#define WLAN_SSID       "Pham Truc Phuong"
//Wifi password
#define WLAN_PASS       "15042003"

//setup Adafruit
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
//fill your username                   
#define AIO_USERNAME    "vantri15042003"
//fill your key
#define AIO_KEY         "aio_dTDX57NyYObjn1Gov58XrI4sCbL0"

//setup MQTT
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

//setup publish
Adafruit_MQTT_Publish light_pub = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/LED");
Adafruit_MQTT_Publish msg = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/msg");

//setup subcribe
Adafruit_MQTT_Subscribe light_sub = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/LED", MQTT_QOS_1);
Adafruit_MQTT_Subscribe msg_sub = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/msg", MQTT_QOS_1);// thiet lap voi sv

int led_counter = 0;
int led_status = HIGH;
String combinedString = "";

void lightcallback(char* value, uint16_t len){
  if(value[0] == '0') Serial.print('a');
  if(value[0] == '1') Serial.print('A');
}

void setup() {
  // put your setup code here, to run once:
  //set pin 2,5 as OUTPUT
  pinMode(2, OUTPUT);
  pinMode(5, OUTPUT);
  //set busy pin HIGH
  digitalWrite(5, HIGH);

  Serial.begin(115200);

  //connect Wifi
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  //subscribe light feed
  light_sub.setCallback(lightcallback);
  mqtt.subscribe(&light_sub);
  mqtt.subscribe(&msg_sub);

  //connect MQTT
  while (mqtt.connect() != 0) { 
    mqtt.disconnect();
    delay(500);
  }

  //finish setup, set busy pin LOW
  digitalWrite(5, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  //receive packet
  mqtt.processPackets(1);
  
  //read serial
  if(Serial.available()){
    char msgs = Serial.read();// doc du lieu gui tu stm32  char ma ascii
    if(msgs != 47){
      combinedString += String(msgs);
    }
    if(msgs == 47){// cuoi '/'
      msg.publish(combinedString.c_str());
      combinedString = "";
    }
    //msg.publish(msgs);
    // if(msgs == 'o') Serial.print('O');
    // else if(msgs == 'a') light_pub.publish(0);
    // else if(msgs == 'A') light_pub.publish(1);

  }

  led_counter++;
  if(led_counter == 100){
    // every 1s
    //msg.publish("Hi\n");
    led_counter = 0;
    //toggle LED
    if(led_status == HIGH) led_status = LOW;
    else led_status = HIGH;

    digitalWrite(2, led_status);
  }
  delay(10);
}
