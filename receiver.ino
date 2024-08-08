#include <SPI.h>
#include <LoRa.h>

#define SS 5
#define RST 14
#define DIO0 2

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("LoRa Receiver");

  LoRa.setPins(SS, RST, DIO0);
  LoRa.setSpreadingFactor(12);
  LoRa.setSignalBandwidth(62.5E3);
  LoRa.enableCrc();
  
  while (!LoRa.begin(928E6)) {
    Serial.println(".");
    delay(500);
  }
  
  LoRa.setSyncWord(0xF3);
  Serial.println("LoRa Inicializado com sucesso.");
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    Serial.print("Pacote recebido: '");

    while (LoRa.available()) {
      String LoRaData = LoRa.readString();
      Serial.print(LoRaData); 
    }

    Serial.print("' RSSI: ");
    Serial.print(LoRa.packetRssi());
    Serial.print(", SNR: ");
    Serial.println(LoRa.packetSnr());

  }
}