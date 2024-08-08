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
  LoRa.setSignalBandwidth(7.8E3);
  LoRa.setTxPower(20);
  LoRa.enableCrc();
  
  while (!LoRa.begin(915E6)) {
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
