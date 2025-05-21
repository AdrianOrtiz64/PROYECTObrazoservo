//version charlie

#include <Servo.h> 
Servo servos[4]; 

// Pines control
const int potModo = A0;    // Potenciómetro cambio de modo

const int potServo1 = A1;    // Potenciómetro servo 1
const int potServo2 = A2;    // Potenciómetro servo 2
const int potServo3 = A3;    // Potenciómetro servo 3
const int potServo4 = A4;    // Potenciómetro servo 4


const int botonizq = 4;       // Botón manual ← 
const int botonder = 5;       // Botón manual →

// Pines LEDs
const int ledmodoa = 2;
const int ledmodob = 3;

const int servoalpha = 8;
const int servobeta = 9;
const int servocharlie = 10;
const int servodelta = 11;

int CurrentPose = 0;

enum Estado { S0_AUTO, S1_MANUAL };
Estado estadoActual = S0_AUTO;

void setup() {

  pinMode(potModo, INPUT);
  pinMode(potServo1, INPUT);
  pinMode(potServo2, INPUT);
  pinMode(potServo3, INPUT);
  pinMode(potServo4, INPUT);

  //--------------------

  int lastButtonStateIzq = HIGH;
  int lastButtonStateDer = HIGH;

  int currentPose = 0;        // Pose actual (0 a 4)

  //---------------------

  pinMode(botonizq, INPUT_PULLUP);
  pinMode(botonder, INPUT_PULLUP);

  pinMode(ledmodoa, OUTPUT);
  pinMode(ledmodob, OUTPUT);

  servos[0].attach(servoalpha);
  servos[1].attach(servobeta);
  servos[2].attach(servocharlie);
  servos[3].attach(servodelta);

  Serial.begin(9600);
}

void loop() {

  int pot = analogRead(potModo);

  int servo1 = analogRead(potServo1);
  int servo2 = analogRead(potServo2);
  int servo3 = analogRead(potServo3);
  int servo4 = analogRead(potServo4);

  int angulo1 = map(servo1, 0, 1023, 0, 180);
  int angulo2 = map(servo2, 0, 1023, 0, 180);
  int angulo3 = map(servo3, 0, 1023, 0, 180);
  int angulo4 = map(servo4, 0, 1023, 0, 180);

  

  Serial.println(pot);

  switch(estadoActual) {
    case S0_AUTO:
      
      digitalWrite(ledmodoa, HIGH);
      digitalWrite(ledmodob, LOW);

      if (digitalRead(botonIzq) == LOW) {
        if (currentPose > 0) currentPose--;  // No permite valores negativos
        executePose(currentPose);
        delay(300); // Delay anti-rebote
        while(digitalRead(botonIzq) == LOW); // Espera hasta soltar
      }
      
      // Botón derecho - incrementar
      if (digitalRead(botonDer) == LOW) {
        if (currentPose < 4) currentPose++;  // No pasa de 4
        executePose(currentPose);
        delay(300); // Delay anti-rebote
        while(digitalRead(botonDer) == LOW); // Espera hasta soltar
      }

      
      if(pot >= 511 && pot <= 1023) estadoActual = S1_MANUAL;
      break;
      
    case S1_MANUAL:
      
      digitalWrite(ledmodoa, LOW);
      digitalWrite(ledmodob, HIGH);

      servos[0].write(angulo1);
      Serial.print("Angulo del motor 1: ");
      Serial.print(angulo1);

      servos[1].write(angulo2);
      Serial.print("Angulo del motor 2: ");
      Serial.print(angulo2);

      servos[2].write(angulo3);
      Serial.print("Angulo del motor 3: ");
      Serial.print(angulo3);

      servos[3].write(angulo4);
      Serial.print("Angulo del motor 4: ");
      Serial.print(angulo4);

      delay(1000); //limitacion para evitar sobrecargas
      

      if(pot <= 512 && pot >= 0) estadoActual = S0_AUTO;
      break;
  }
  delay(100);
}

// Función que llama a cada pose según el número
void executePose(int poseNumber) {
  Serial.print("Ejecutando Pose: ");
  Serial.println(poseNumber);
  
  switch(poseNumber) {
    case 0: pose0(); break;
    case 1: pose1(); break;
    case 2: pose2(); break;
    case 3: pose3(); break;
    case 4: pose4(); break;
  }
}

// Funciones individuales para cada pose
void pose0() {
  Serial.println("Pose 0 activada");
  // Aquí irían los movimientos para la pose 0
  // ej: servo1.write(90); servo2.write(45);...
}

void pose1() {
  Serial.println("Pose 1 activada");
  // Movimientos para pose 1
}

void pose2() {
  Serial.println("Pose 2 activada");
  // Movimientos para pose 2
}

void pose3() {
  Serial.println("Pose 3 activada");
  // Movimientos para pose 3
}

void pose4() {
  Serial.println("Pose 4 activada");
  // Movimientos para pose 4
}