const int esquerdaFrente = 11;
const int esquerdaTras = 10;
const int direitaFrente = 8;
const int direitaTras = 9;
const int triggerPin1 = 4;
const int echoPin1 = 2;
const int triggerPin2 = 5;
const int echoPin2 = 3; 

const int minDist = 30;

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

  long duracao1, distancia1, duracao2, distancia2;

  digitalWrite(triggerPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin1, LOW);
  
  digitalWrite(triggerPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin2, LOW);

  duracao1 = pulseIn(echoPin1, HIGH);
  distancia1 = duracao1 * 0.034 / 2;

  duracao2 = pulseIn(echoPin2, HIGH);
  distancia2 = duracao2 * 0.034 / 2;

  int diffDist1 = distancia1 - distancia2;
  int diffDist2 = distancia2 - distancia1;
  
  if(distancia1 <= minDist || distancia2 <= minDist){
    if(diffDist1 > 0){
      movEsquerda(diffDist1);
    }else if(diffDist2 > 0){
      movDireita(diffDist2);
    }
  }else{
    movFrente();
  }
}

void movTras(){
  analogWrite(direitaTras,250);
  analogWrite(esquerdaTras, 250);
}

void movFrente() {
  analogWrite(direitaFrente,200);
  analogWrite(esquerdaFrente, 200);
  analogWrite(direitaTras, 0);
  analogWrite(esquerdaTras, 0);
}

void stop(){
  analogWrite(direitaFrente,0);
  analogWrite(esquerdaFrente, 0);
  analogWrite(direitaTras, 0);
  analogWrite(esquerdaTras, 0);
}

void movDireita(int diferenca) {
  analogWrite(esquerdaFrente, 200);
  analogWrite(esquerdaTras, 0);
  analogWrite(direitaFrente, 180 - diferenca);
  analogWrite(direitaTras, 0);
}

void movEsquerda(int diferenca) {
  analogWrite(esquerdaFrente, 180 - diferenca);
  analogWrite(esquerdaTras, 0);
  analogWrite(direitaFrente, 200);
  analogWrite(direitaTras, 0);
}
