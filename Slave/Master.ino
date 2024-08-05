//compila apenas se MASTER estiver definido no arquivo principal
#ifdef MASTER

// intervalo entre os envios
#define INTERVAL 500

// tempo do último envio
long lastSendTime = 0;

void setup() {
  Serial.begin(115200);
  // chama a configuração inicial do LoRa
  setupLoRa();

  Serial.println("Master setup");
}

void receive() {
  // tentamos ler o pacote
  int packetSize = LoRa.parsePacket();

  // verificamos se o pacote tem o tamanho mínimo de caracteres que esperamos
  if (packetSize > SETDATA.length()) {
    String received = "";
    // armazena os dados do pacote em uma string
    while(LoRa.available()) {
      received += (char) LoRa.read();
    }
    // verifica se a string possui o que está contido em "SETDATA"
    int index = received.indexOf(SETDATA);
    if (index >= 0) {
      // recuperamos a string que está após o "SETDATA",
      //que no caso serão os dados de nosso interesse
      String data = received.substring(SETDATA.length());

      // tempo que demorou para o Master criar o pacote, enviar o pacote,
      //o Slave receber, fazer a leitura, criar um novo pacote, enviá-lo
      //e o Master receber e ler
      String waiting = String(millis() - lastSendTime);

      // mostrando os dados que a operação demorou
      Serial.println("Recebeu: " + data);
      Serial.println("Tempo: " + waiting + "ms");
    }
  }
}
void loop() {
  // se passou o tempo definido em INTERVAL desde o último envio
  if (millis() - lastSendTime > INTERVAL) {
    // marcamos o tempo que ocorreu o último envio
    lastSendTime = millis();
    // envia o pacote para informar ao Slave que queremos receber os dados
    send();
  }

  //verificamos se há pacotes para recebermos
  receive();
}

#endif
