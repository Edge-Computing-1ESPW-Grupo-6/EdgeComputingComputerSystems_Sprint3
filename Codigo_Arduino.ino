#include "Arduino.h"
#include "WiFi.h"
#include "HTTPClient.h"

char ssid[] = "Rede Teste";
char pass[] = "senhateste";
char serverAddress[] = "https://api.tago.io/data";
char contentHeader[] = "application/json";
char tokenHeader[]   = "e56316cb-bfcd-40c4-b769-4eb1ac92e6b6"; //Token do Dispositivo

#define trigPin 3
#define echoPin 2

long duration, distance;
bool bueiro1 = true;

void setup() {
  Serial.begin(9600);
  init_wifi(); 

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(trigPin, LOW);

}

void init_wifi() {
  Serial.println("Conectando WiFi");
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("Conectado");
  Serial.print("Meu IP é: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  lerDistancia();

  char anyData[30];
  char postData[300];
  char anyData1[30];
  char bAny[30];
  int statusCode = 0;

  strcpy(postData, "{\n\t\"variable\": \"temperature\",\n\t\"value\": ");
  dtostrf(bueiro1, 6, 2, anyData);
  strncat(postData, anyData, 100);
  Serial.println(postData);

  client.begin(serverAddress);
  client.addHeader("Content-Type", contentHeader);
  client.addHeader("Device-Token", tokenHeader);
  statusCode = client.POST(postData);

  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.println("End of POST to TagoIO");
  Serial.println();
  delay(5000);
}

void lerDistancia(){
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);
	
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;

  if (distance < 10) {
   bueiro1 = false;
  }
  else {
    bueiro1 = true;
  }

}