const int esquerdaFrente = 10;
const int esquerdaTras = 11;
const int direitaFrente = 12;
const int direitaTras = 13;

const int triggerPin1 = 8; 
const int echoPin1 = 4;    
const int triggerPin2 = 7; 
const int echoPin2 = 5;    

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
  // Mede a distância do sensor ultrassônico 1
  long duracao1, distancia1;
  digitalWrite(triggerPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin1, LOW);
  duracao1 = pulseIn(echoPin1, HIGH);
  distancia1 = duracao1 * 0.034 / 2;
  
  // Mede a distância do sensor ultrassônico 2
  long duracao2, distancia2;
  digitalWrite(triggerPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin2, LOW);
  duracao2 = pulseIn(echoPin2, HIGH);
  distancia2 = duracao2 * 0.034 / 2;

  Serial.print("Distancia Sensor 1: ");
  Serial.print(distancia1);
  Serial.print(" cm");

  Serial.print("Distancia Sensor 2: ");
  Serial.print(distancia2);
  Serial.print(" cm");

  // Verifica se há obstáculo próximo
  if (distancia1 < distanciaMinima || distancia2 < distanciaMinima) {
    // Calcula a diferença de distância entre os sensores
    int diferencaDistancia = distancia1 - distancia2;

    if (diferencaDistancia > 0) {
      // Vira para a direita
      moverParaDireita(diferencaDistancia);
    } else {
      // Vira para a esquerda
      moverParaEsquerda(-diferencaDistancia);
    }
    delay(1000); 
  } else {
    // Move para frente
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
