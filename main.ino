const int esquerdaFrente = // Port for left motor forward;
const int esquerdaTras = // Port for left motor backward;
const int direitaFrente = // Port for right motor forward;
const int direitaTras =// Port for right motor backward ;

const int triggerPin1 = // Port for Sensor 1 Trigger;
const int echoPin1 = // Port for Sensor 1 Echo;
const int triggerPin2 =  // Port for Sensor 2 Trigger;
const int echoPin2 = // Port for Sensor 2 Echo;

const int distanciaMinima = 20; // Min distance
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

  long duracao1, distancia1;

  digitalWrite(triggerPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin1, LOW);
  
  duracao1 = pulseIn(echoPin1, HIGH);
  distancia1 = duracao1 * 0.034 / 2;
  
  long duracao2, distancia2;

  digitalWrite(triggerPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin2, LOW);

  duracao2 = pulseIn(echoPin2, HIGH);
  distancia2 = duracao2 * 0.034 / 2;

  int diferencaDistancia1 = distancia1 - distancia2;
  int diferencaDistancia2 = distancia2 - distancia1;

  if(distancia1 <= 5 || distancia2 <= 5 || distancia1 <= 5 && distancia2 <= 5 || distancia1 == 5 || distancia2 == 5 || distancia1 == 5 && distancia2 <= 5){
    re();
  }else if(distancia1 <= 20 && distancia1 >= 6 || distancia2 <= 20 && distancia2 >= 6){
    if(diferencaDistancia1 > 0){
      moverParaEsquerda(diferencaDistancia1);
    }else if(diferencaDistancia2 > 0){
      moverParaDireita(diferencaDistancia2);
    }
  }else{
      moverParaFrente();
  }

}

void re(){
  analogWrite(direitaTras,250);
  analogWrite(esquerdaTras, 250);
}

void moverParaFrente() {
  analogWrite(direitaFrente,200);
  analogWrite(esquerdaFrente, 200);
  analogWrite(direitaTras, 0);
  analogWrite(esquerdaTras, 0);
}

void freio(){
  analogWrite(direitaFrente,0);
  analogWrite(esquerdaFrente, 0);
  analogWrite(direitaTras, 0);
  analogWrite(esquerdaTras, 0);
}

void moverParaDireita(int diferenca) {
  analogWrite(esquerdaFrente, 200); // Velocidade máxima
  analogWrite(esquerdaTras, 0);
  analogWrite(direitaFrente, 180 - diferenca); // Ajusta a velocidade proporcionalmente à diferença
  analogWrite(direitaTras, 0);
}

void moverParaEsquerda(int diferenca) {
  analogWrite(esquerdaFrente, 180 - diferenca); // Ajusta a velocidade proporcionalmente à diferença
  analogWrite(esquerdaTras, 0);
  analogWrite(direitaFrente, 200); // Velocidade máxima
  analogWrite(direitaTras, 0);
}
