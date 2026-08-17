//Author: Raphael Campos Squilaro
//Project: Using an ultrasonic sensor

#define PINO_TRIG 34
#define PINO_ECHO 21

void setup() {
  Serial.begin(9600);
  pinMode(PINO_TRIG, OUTPUT);
  pinMode(PINO_ECHO, INPUT);
}

void loop() {
  long duracao, distancia;

  digitalWrite(PINO_TRIG, LOW);
  delay(20);
  digitalWrite(PINO_TRIG, HIGH);
  delay(20);
  digitalWrite(PINO_TRIG, LOW);

  duracao = pulseIn(PINO_ECHO, HIGH);
  distancia = (duracao / 2) * 0.0343;

  Serial.print("A distância é de: ");
  Serial.print(distancia);
  Serial.println(" cm");

  delay(2000);
}
