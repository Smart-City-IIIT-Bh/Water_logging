#include <printf.h>

#include <RF24_config.h>


#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  //Serial.println(radio.available());
  if (radio.available()) {
    //Serial.println("hey this receiver...");
    char text[32] = "";
   // String str = "";
    radio.read(&text, sizeof(text));
    //delay(1000);
    //Serial.println("I m receiveing data....");
    Serial.println(text);
  }
}
