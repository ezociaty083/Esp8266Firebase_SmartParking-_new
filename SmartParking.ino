#include "Ultrasonic.h"
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
//Connet LQCI2C
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define echoPin1  D7
#define trigPin1  D6
#define echoPin2  D1
#define trigPin2  D3

//connec WiFi
#define SS_iD "iPhone"
#define Pass_word "11111111"
//Connec Firebase
#define FIREBASE_HOST "smart-parking-28c87.firebaseio.com/"
#define FIREBASE_KEY "Je5tvFVGfIIu3N8ayUDIMdIDLBFlThIiloz9S8Rk"
int fals = 0;
int tru = 1;
int maximumRange = 10; 
int minimumRange = 0; 


long duration1,duration2,distance1,distance2; 

FirebaseData firebaseData;
void setup() {
  Serial.begin (115200);
  
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  
    Serial.println(WiFi.localIP());
    WiFi.begin(SS_iD, Pass_word);
    Serial.print("connecting");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.println();
    Serial.print("connected: ");
    Serial.println(WiFi.localIP());
 Firebase.begin(FIREBASE_HOST, FIREBASE_KEY);
}
void loop() {

 sensor_1();
 sensor_2();
 
  
}


void sensor_1(){
  digitalWrite(trigPin1, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);  
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);    
  distance1 = duration1 / 58.2; 
  if (distance1 >= maximumRange || distance1 <= minimumRange) {  
    if(Firebase.setInt(firebaseData, "/channel_1", fals)) {
        Serial.println("Added_Chanal_1 0"); 
    } else {
         Serial.println("Error : " + firebaseData.errorReason());
    }  
    delay(100);
  }
  else {  
    if(Firebase.setInt(firebaseData, "/channel_1", tru)) {
        Serial.println("Added_Chanal_1 1"); 
    } else {
        Serial.println("Error : " + firebaseData.errorReason());
    }
  }
  delay(100); 
}
void sensor_2(){ 
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);  
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);  
  digitalWrite(trigPin2, LOW);  
  duration2 = pulseIn(echoPin2, HIGH);  
 distance2 = duration2 / 58.2;
  if (distance2 >= maximumRange || distance2 <= minimumRange) {    
    if(Firebase.setInt(firebaseData, "/channel_2", fals)) {
        Serial.println("Added_Chanal_2 0"); 
    } else {
         Serial.println("Error : " + firebaseData.errorReason());
    }  
    delay(100);
  }
  else {  
    if(Firebase.setInt(firebaseData, "/channel_2", tru)) {
        Serial.println("Added_Chanal_2 1"); 
    } else {
        Serial.println("Error : " + firebaseData.errorReason());
    }
  }
  delay(100);
}
