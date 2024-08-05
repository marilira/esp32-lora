#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <SSD1306.h>

//Deixe esta linha descomentada para compilar o Master
//Comente ou remova para compilar o Slave
#define MASTER

// definições para comunicação com radio LoRa
#define SCK   5   // GPIO5 SCK
#define MISO  19  // GPIO19 MISO
#define MOSI  27  // GPIO27 MOSI
#define SS    18  // GPIO18 CS
#define RST   14  // GPIO14 RESET
#define DI00  26  // GPIO26 IRQ(Interrupt Request)

#define BAND 915E6  /* 915MHz de frequencia */

// constante para informar ao Slave que queremos os dados
const String GETDATA = "getdata";
// constante qeu o Slave retorna junto com os dados para o Master
const String SETDATA = "setdata=";

//configurações iniciais do LoRa
void setupLoRa() {
  //inicializa a comunicação
  SPI.begin(SCK, MISO, MOSI, SS);
  LoRa.setPins(SS, RST, DI00);

  //inicializa o LoRa
  if(!LoRa.begin(BAND, true)) {
    Serial.println("LoRa não conseguiu inicializar")
    while (1);
  }

  //ativa o crc
  LoRa.enableCrc();
  //ativa o recebimento de pacotes
  LoRa.receive();
}
