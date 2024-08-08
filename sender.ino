#include <SPI.h>
#include <LoRa.h>

#define SS 5
#define RST 14
#define DIO0 2

int counter = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("LoRa Sender");

  LoRa.setPins(SS, RST, DIO0);
  LoRa.setSpreadingFactor(12);
  LoRa.setSignalBandwidth(7.8E3);
  LoRa.setTxPower(20);
  LoRa.enableCrc();
  
  while (!LoRa.begin(915E6)) {
    Serial.println(".");
    delay(500);
  }
  
  LoRa.setSyncWord(0xF3);
  Serial.println("LoRa inicializado com sucesso");
}

void loop() {
  Serial.print("Enviando pacote: ");
  Serial.println(counter);

  LoRa.beginPacket();
  LoRa.print("Oi ");
  LoRa.print(counter);
  LoRa.endPacket();

  counter++;

  delay(5000);
}
