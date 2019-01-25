#include "DHT.h"        // including the library of DHT11 temperature and humidity sensor
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>


#define FIREBASE_HOST "agricultureiot-15069.firebaseio.com"
#define FIREBASE_AUTH "lr37reWAOmI2NNZx4MpK8y1baqR6yNfglMRpl5N2"
#define WIFI_SSID "IoT_Lab"
#define WIFI_PASSWORD "iiitbbsr"
#define DHTTYPE DHT11   // DHT 11
#define dht_dpin D3

DHT dht(dht_dpin, DHTTYPE);

int soil_sensor = A0;
int moisture_val;
float h,t;

WiFiServer server(80);
void setup() {
   dht.begin();
   delay(700);
  Serial.begin(9600);
 
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  server.begin();
  Serial.print(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}


void loop() {
//  temp_humid_value = DHT.read11(temp_humid_sensor);
//  humid_val = DHT.humidity;
 // temp_val = DHT.temperature;

   h = dht.readHumidity();
   delay(700);
   t = dht.readTemperature();
   if( isnan(t) || isnan(h))
   {return;}
   else{
    moisture_val= analogRead(soil_sensor);
    moisture_val = map(moisture_val,1023,0,0,100);
   }
  Serial.print("humidity:");
  Serial.println(h);
  Serial.print("temperature:");
  Serial.println(t);
  Serial.print("Soil Moisture:");
  Serial.println(moisture_val);

  //PUSIHNG INTO LOGS.....

  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();

  root["Temperature"] = t;
  root["Humidity"] = h;
  root["Moisture"] = moisture_val;

  String name = Firebase.push("/sensors/data", root);

  Serial.print("pushed: /logs/");
  Serial.println(name);
  delay(5000);
}
