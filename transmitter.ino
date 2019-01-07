#include <dht.h>

#include <printf.h>
#include <RF24_config.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

int temp_humid_sensor = A1;
dht DHT;
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

int temp_humid_value;
char data[16];


void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}
void loop() {
//  Serial.println("in loop1");
 // const char text[] = "Hello Chandra";
  temp_humid_value = DHT.read11(temp_humid_sensor);
  int humid = DHT.humidity;
  Serial.print("Humidity :");
  Serial.print(humid);
  Serial.println("%");

  itoa(humid, data, 10);
  radio.write(&data, sizeof(data));
  Serial.println("humid after sending");
  Serial.println(data);
  delay(5000);
}
