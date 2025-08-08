
#include <Servo.h>

// Definir os pinos para o sensor ultrassônico
const int trigPin = 7;
const int echoPin = 6;

// Definir o pino para o servo motor
const int servoPin = 9;

// Distância mínima para abrir a tampa (ajuste conforme necessário)
const int distanciaMinima = 10;  // em centímetros

Servo servo;  // Objeto para controlar o servo motor

void setup() {
  // Inicializar o monitor serial
  Serial.begin(9600);

  // Configurar os pinos do sensor ultrassônico
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Configurar o pino do servo motor
  servo.attach(servoPin);
  fecharTampa();  // Garantir que a tampa esteja fechada no início
}

void loop() {
  // Ler a distância do sensor ultrassônico
  int distancia = medirDistancia();

  // Se a distância for menor que a distância mínima, abrir a tampa
  if (distancia < distanciaMinima) {
    abrirTampa();
    // Aguardar um momento para evitar abrir e fechar rapidamente se um objeto estiver próximo continuamente
    delay(1000);
  } else {
    fecharTampa();
  }
}

// Função para medir a distância utilizando o sensor ultrassônico
int medirDistancia() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duracao = pulseIn(echoPin, HIGH);
  // A distância é igual à metade do tempo de duração do pulso multiplicado pela velocidade do som (aprox. 343 m/s)
  int distancia = duracao * 0.0343 / 2;
  return distancia;
}

// Funções para abrir e fechar a tampa usando o servo motor
void abrirTampa() {
  servo.write(90);  // Ângulo para abrir a tampa (ajuste conforme necessário)
}

void fecharTampa() {
  servo.write(0);  // Ângulo para fechar a tampa (ajuste conforme necessário)
}
