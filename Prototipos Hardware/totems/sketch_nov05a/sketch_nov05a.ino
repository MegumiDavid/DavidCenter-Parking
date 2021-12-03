// C++ code
//
// bibliotecas para wifi
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
//bibliotecas de mysql
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
//arquivo com as informacoes de rede e bd secretas :o

#include "arduino_segredos.h"

const int sinal1 = 4;
const int eco1 = 14;
const int sinal2 = 12;
const int eco2 = 13;
const int r = 15;
const int g = 2;
const int botao = 5;
const int botaoticket = 16;
const int somzinho = 0;

// variaveis wifi
const char ssid[] = ssid_wifi;
const char senhawifi[] = senha;

// variaveis mysql
IPAddress server_addr(85, 10, 205, 173); // ip do servidor mysql
char user[] = userbd;  // login banco de dados
char password[] = senha_bd;   // senha banco de dados

char sql[] = "insert into davidcenter.TICKETS (hora_entrada, status_saida) values (now(), 'NEGADA');";
char query[128];
WiFiClient client;
MySQL_Connection conn((Client *)&client);

bool detectacarro = false;
bool statusbotao = false;
bool statusticket = false;
bool statusentrada = false;

void setup()
{
    Serial.begin(115200);
    while (!Serial); // espera o serial inicializar.
    pinMode(botao, INPUT_PULLUP);
    pinMode(r, OUTPUT);
    pinMode(g, OUTPUT);
    pinMode(LED_BUILTIN, OUTPUT);

    delay(1000);

    // conectar wifi
    conecta_wifi();

    // conectar no mysql
    Serial.println("");
    Serial.println("Conectando ao bando de dados.");

    while (conn.connect(server_addr, 3306, user, password) != true) 
    {
      delay(1000);
      Serial.print ( "." );
    }
}

void loop() 
{
  
  
  // estabelecendo variaveis para duracao do sinal e distancia em cm
  long tempo, tempo2, cm, cm2;
  int botao1apertado = digitalRead(botao);
  int botao2apertado = digitalRead(botaoticket);
  
  // ping primeiro totem 
  // O PING))) is é ativado por um pulse HIGH de 2 ou mais microsegundos.
  // Dar um pequeno pulso LOW antes, para garantir um pulso HIGH mais limpo:
  pinMode(sinal1, OUTPUT);
  digitalWrite(sinal1, LOW);
  delayMicroseconds(2);
  digitalWrite(sinal1, HIGH);
  delayMicroseconds(5);
  digitalWrite(sinal1, LOW);
  // o pino eco le o sinal
  pinMode(eco1, INPUT);
  tempo = pulseIn(eco1, HIGH);
  // conversao de tempo pra distancia (funcao)
  cm = microsecPraCm(tempo);
  
  // ping segundo totem 
  // O PING))) is é ativado por um pulse HIGH de 2 ou mais microsegundos.
  // Dar um pequeno pulso LOW antes, para garantir um pulso HIGH mais limpo:
  pinMode(sinal2, OUTPUT);
  digitalWrite(sinal2, LOW);
  delayMicroseconds(2);
  digitalWrite(sinal2, HIGH);
  delayMicroseconds(5);
  digitalWrite(sinal2, LOW);
  // o pino eco le o sinal
  pinMode(eco2, INPUT);
  tempo2 = pulseIn(eco2, HIGH);
  // conversao de tempo pra distancia (funcao)
  cm2 = microsecPraCm(tempo2);
  
  
  // primeiro totem:
  //distancia que ativa o primeiro totem
  if (cm < 20 && detectacarro==false)
   {
     detectacarro = true;
     tone(somzinho,277,300);
   }
  //primeiro botao
  if (botao1apertado == HIGH && cm < 20 && statusbotao==false) 
   {
        statusbotao = true;
      tone(somzinho,277,300);
      //parte que gera o ticket 
   } 
  //segundo botao (simula ticket sendo retirado)
  if (botao2apertado == HIGH && statusbotao==true)
  {
     statusticket = true;
     digitalWrite(LED_BUILTIN, HIGH);
  }
  else 
   { 
    digitalWrite(LED_BUILTIN, LOW);
   } 
  
  if (cm > 20)
  {
    detectacarro = false;
    statusbotao = false;
  }
  
  
  //segundo totem:
  //se o ticket for retirado o totem2 faz o bagulho dele
  if (statusticket == true && cm2 < 20 || statusticket == true && cm < 20)
  {
    //led(simula motor da cancela) no modo verde (cancela levantada)
    digitalWrite(r,LOW);
    digitalWrite(g,HIGH);
    //envia entrada apenas uma vez
    if (statusentrada == false) 
    {
      enviaentrada();
      statusentrada=true;
    }
    /* enviar as parada pro banco de dados e tal*/
  }
  else
  {
    //led(simula motor da cancela) no modo vermelho (cancela abaixada)
    digitalWrite(r,HIGH);
    digitalWrite(g,LOW);
    statusticket = false;
    statusentrada = false;
  }
}

void enviaentrada()
{
  sprintf(query, sql);
  MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
  cur_mem->execute(query);
  delete cur_mem;
  Serial.println("Entrada registrada.");
}

long microsecPraCm(long microsec) 
{
  // a velocidade do som eh 340 m/s ou 29 microsegundos por cm.
  //o sinal viaja 2 vezes essa distancia por cm(ida e volta)
  return microsec / 29 / 2;
}

void conecta_wifi()
{
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
