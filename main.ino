const int esquerdaFrente = // Port for left motor forward;
const int esquerdaTras = // Port for left motor backward;
const int direitaFrente = // Port for right motor forward;
const int direitaTras =// Port for right motor backward 13;

const int triggerPin1 = // Port for Sensor 1 Trigger;
const int echoPin1 = // Port for Sensor 1 Echo;
const int triggerPin2 =  // Port for Sensor 2 Trigger;
const int echoPin2 = // Port for Sensor 2 Echo;

const int distanciaMinima = 20; 

void setup() {
  pinMode(esquerdaFrente, OUTPUT);
  pinMode(esquerdaTras, OUTPUT);
  pinMode(direitaFrente, OUTPUT);
  pinMode(direitaTras, OUTPUT);

  pinMode(triggerPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(triggerPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  
  Serial.begin(9600);
}

void loop() {
  // Measure distance from ultrasonic sensor 1
  long duracao1, distancia1;
  digitalWrite(triggerPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin1, LOW);
  duracao1 = pulseIn(echoPin1, HIGH);
  distancia1 = duracao1 * 0.034 / 2;
  
  // Measure distance from ultrasonic sensor 2
  long duracao2, distancia2;
  digitalWrite(triggerPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin2, LOW);
  duracao2 = pulseIn(echoPin2, HIGH);
  distancia2 = duracao2 * 0.034 / 2;

  Serial.print("Distance Sensor 1: ");
  Serial.print(distancia1);
  Serial.print(" cm");

  Serial.print("Distance Sensor 2: ");
  Serial.print(distancia2);
  Serial.print(" cm");

  // Check for nearby obstacle
  if (distancia1 < distanciaMinima || distancia2 < distanciaMinima) {
    // Calculate distance difference between sensors
    int diferencaDistancia = distancia1 - distancia2;

    if (diferencaDistancia > 0) {
      // Turn right
      moverParaDireita(diferencaDistancia);
    } else {
      // Turn left
      moverParaEsquerda(-diferencaDistancia);
    }
    delay(1000); 
  } else {
    // Move forward
    moverParaFrente();
  }
}

void moverParaFrente() {
  digitalWrite(esquerdaFrente, HIGH);
  digitalWrite(esquerdaTras, LOW);
  digitalWrite(direitaFrente, HIGH);
  digitalWrite(direitaTras, LOW);
}

void moverParaTras() {
  digitalWrite(esquerdaFrente, LOW);
  digitalWrite(esquerdaTras, HIGH);
  digitalWrite(direitaFrente, LOW);
  digitalWrite(direitaTras, HIGH);
}

void moverParaDireita(int diferenca) {
  analogWrite(esquerdaFrente, 255); 
  analogWrite(esquerdaTras, 0);
  analogWrite(direitaFrente, 255 - diferenca); 
  analogWrite(direitaTras, 0);
}

void moverParaEsquerda(int diferenca) {
  analogWrite(esquerdaFrente, 255 - diferenca); 
  analogWrite(esquerdaTras, 0);
  analogWrite(direitaFrente, 255); 
  analogWrite(direitaTras, 0);
}
