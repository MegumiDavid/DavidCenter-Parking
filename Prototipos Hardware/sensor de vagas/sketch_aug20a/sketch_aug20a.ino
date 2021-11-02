// C++ code

// bibliotecas para wifi
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
//bibliotecas de mysql
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
//arquivo com as informacoes de rede e bd secretas :o

#include "arduino_segredos.h"

// declarando variaveis globais
const int sinal = 16;
const int eco = 5;
const int r = 12;
const int b = 14;
const int g = 13;
long contador, contador2;

// variaveis wifi
const char ssid[] = ssid_wifi;
const char senhawifi[] = senha;

// variaveis mysql
IPAddress server_addr(85, 10, 205, 173); // ip do servidor mysql
char user[] = userbd;  // login banco de dados
char password[] = senha_bd;   // senha banco de dados

char sql[] = "UPDATE davidcenter.Vagas SET STATUS_VAGA = '%d' WHERE CODIGO_VAGA = 'a1';";
char query[128];
WiFiClient client;
MySQL_Connection conn((Client *)&client);

// setup
void setup()
{
  Serial.begin(115200);
  while (!Serial); // espera o serial inicializar.
    pinMode(r, OUTPUT);
    pinMode(g, OUTPUT);
    pinMode(b, OUTPUT);
  
  delay(1000);

  // conectar wifi
  conecta_wifi();
  

  // conectar no mysql
  Serial.println("");
  Serial.println("Conectando ao bando de dados.");

  while (conn.connect(server_addr, 3306, user, password) != true) {
    delay(1000);
    Serial.print ( "." );
  }

  Serial.println("");
  Serial.println("Conectado ao servidor SQL!");  
}

void loop() {
// estabelecendo variaveis para duracao do sinal e distancia em cm
  long tempo,cm;
  
// O PING é ativado por um pulse HIGH de 2 ou mais microsegundos.
// Dar um pequeno pulso LOW antes, para garantir um pulso HIGH mais limpo:
  pinMode(sinal, OUTPUT);
  digitalWrite(sinal, LOW);
  delayMicroseconds(2);
  digitalWrite(sinal, HIGH);
  delayMicroseconds(5);
  digitalWrite(sinal, LOW);

  // o pino eco le o sinal
  pinMode(eco, INPUT);
  tempo = pulseIn(eco, HIGH);

  // conversao de tempo pra distancia (funcao)
  cm = microsecPraCm(tempo);
  
  // distancias que ativam os timers(e, por consequencia, os LEDS)
  if (cm < 220)
  {
      contador = millis();
  }
  else 
  {
      contador2 = millis();
  }
  // a diferenca entre os timers deve ser de 2500ms (5s) para ativar os leds 
  if (contador - contador2 > 2500)
  {
      digitalWrite(r,HIGH);
      digitalWrite(g,LOW);
      digitalWrite(b,LOW);
      enviastatus(1); // 1 significa que a vaga esta ocupada 
  }
  else if (contador2 - contador > 2500)
  {
      digitalWrite(r,LOW);
      digitalWrite(g,HIGH);
      digitalWrite(b,LOW);     
      enviastatus(0); // 0 significa que a vaga esta livre ;)
  }

  /*
  // impressao de distancia para o terminal (debugging)
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  //impressao dos timers para o terminal (debugging)
  Serial.print(contador);
  Serial.println();
  Serial.print(contador2);
  Serial.print("dois");
  Serial.println();
  delay(100);
*/
}

long microsecPraCm(long microsec) {
  // a velocidade do som eh 340 m/s ou 29 microsegundos por cm.
  //o sinal viaja 2 vezes essa distancia por cm(ida e volta)
  return microsec / 29 / 2;
}

void enviastatus(int stat)
{
  sprintf(query, sql, stat);
  MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
  cur_mem->execute(query);
  delete cur_mem;
  Serial.println("Status enviado");
}

void conecta_wifi(){
  Serial.println();
  Serial.println();
  Serial.print("Conectando à rede ");
  Serial.println(ssid);
  WiFi.hostname("Name");
  WiFi.begin(ssid, senhawifi);
 // enquanto nao conecta ele imprime pontos com um delay de 250ms
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi conectado");
  // imprime endereço ip
  Serial.print("Endereço IP: ");
  Serial.print(WiFi.localIP());

  }
