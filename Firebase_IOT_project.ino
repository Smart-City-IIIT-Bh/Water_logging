
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "agricultureiot-15069.firebaseio.com"
#define FIREBASE_AUTH "lr37reWAOmI2NNZx4MpK8y1baqR6yNfglMRpl5N2"
#define WIFI_SSID "IoT_Lab"
#define WIFI_PASSWORD "iiitbbsr"

WiFiServer server(80);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
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

float t = 23.00;
float h = 65.08;
float m = 55;

void loop() {


  //PUSIHNG INTO LOGS.....

  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();

  root["Temperature"] = t;
  root["Humidity"] = h;
  root["Moisture"] = m;

  String name = Firebase.push("/sensor/data", root);

  Serial.print("pushed: /logs/");
  Serial.println(name);
  delay(5000);

  t++;
  h++;
  m++;
}
