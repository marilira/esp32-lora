// compila apenas se MASTER não estiver definida no arquivo principal
#ifndef MASTER

//contador que irá servir como os dados que o Slave irá enviar
int count = 0;

void setup() {
  Serial.begin(115200);
  // chama a configuração inicial do LoRa
  setupLoRa();
  Serial.println("Slave esperando...");
}

void loop() {
  // tenta ler o pacote
  int packetSize = LoRa.parsePacket();

  // verifica se o pacote possui a quantidade de caracteres que esperamos
  if (packetSize == GETDATA.length()) {
    String received = "";

    // armazena os dados do pacote em uma string
    while(LoRa.available()) {
      received += (char) LoRa.read();
    }
    if (received.equals(GETDATA)) {
      // simula a leitura dos dados
      String data = readData();
      Serial.println("Criando pacote para envio");

      // cria o pacote para envio
      LoRa.beginPacket();
      LoRa.print(SETDATA + data);

      // finaliza e envia o pacote
      LoRa.endPacket();

      // mostra na tela
      Serial.println("Enviou: " + String(data));
    }
  }
} 

//Função onde se faz a leitura dos dados que queira enviar
//Poderia ser o valor lido por algum sensor por exemplo
//Aqui vamos enviar apenas um contador para testes
//mas você pode alterar a função para fazer a leitura de algum sensor
String readData(){
  return String(count++);
}

#endif
