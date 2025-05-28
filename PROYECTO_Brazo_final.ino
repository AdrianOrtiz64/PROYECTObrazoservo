//VERSION FINAL
#include <Servo.h>

// Configuración de pines
const int potModo = A0;
const int potServo1 = A1;
const int potServo2 = A2;
const int potServo3 = A3;
const int potServo4 = A4;

const int botonIzq = 4;
const int botonDer = 5;

const int ledmodoa = 2;
const int ledmodob = 3;

Servo servoBase;      // Pin 8
Servo servoBrazo;     // Pin 9
Servo servoAltura;    // Pin 10
Servo servoGarral;    // Pin 11

int currentPose = 0;

unsigned long lastButtonPress = 0;
const unsigned long debounceDelay = 200;

enum Estado { S0_AUTO, S1_MANUAL };
Estado estadoActual = S0_AUTO;

void setup() {
  pinMode(botonIzq, INPUT_PULLUP);
  pinMode(botonDer, INPUT_PULLUP);
  pinMode(ledmodoa, OUTPUT);
  pinMode(ledmodob, OUTPUT);

  servoBase.attach(8);
  servoBrazo.attach(9);
  servoAltura.attach(10);
  servoGarral.attach(11);

  Serial.begin(9600);
  ejecutarPose(0); // Iniciar en pose 0
}

void loop() {
  int pot = analogRead(potModo);

  // Cambio entre modos
  if (pot > 511 && estadoActual == S0_AUTO) {
    estadoActual = S1_MANUAL;
    Serial.println("Cambiando a modo MANUAL");
    delay(300);
  } 
  else if (pot <= 511 && estadoActual == S1_MANUAL) {
    estadoActual = S0_AUTO;
    Serial.println("Cambiando a modo AUTOMATICO");
    delay(300);
  }

  switch(estadoActual) {
    case S0_AUTO:
      modoAutomatico();
      break;
    case S1_MANUAL:
      modoManual();
      break;
  }
}

void modoAutomatico() {
  digitalWrite(ledmodoa, HIGH);
  digitalWrite(ledmodob, LOW);

  // Sistema mejorado de detección de botones
  unsigned long control = millis();
  
  if (control - lastButtonPress > debounceDelay) {
    if (digitalRead(botonDer) == LOW) {
      if (currentPose < 4) currentPose++;
      ejecutarPose(currentPose);
      lastButtonPress = control;
      Serial.print("Pose actual: ");
      Serial.println(currentPose);
    }
    else if (digitalRead(botonIzq) == LOW) {
      if (currentPose > 0) currentPose--;
      ejecutarPose(currentPose);
      lastButtonPress = control;
      Serial.print("Pose actual: ");
      Serial.println(currentPose);
    }
  }
}

void modoManual() {
  digitalWrite(ledmodoa, LOW);
  digitalWrite(ledmodob, HIGH);

  // Leer potenciómetros y mover servos
  int angBase = map(analogRead(potServo1), 0, 1023, 0, 180);
  int angBrazo = map(analogRead(potServo2), 0, 1023, 0, 180);
  int angAltura = map(analogRead(potServo3), 0, 1023, 0, 180);
  int angGarral = map(analogRead(potServo4), 0, 1023, 0, 90);

  servoBase.write(angBase);
  servoBrazo.write(angBrazo);
  servoAltura.write(angAltura);
  servoGarral.write(angGarral);

  // Lectura directa después de escribir
  Serial.print("Manual: Base=");
  Serial.print(servoBase.read());
  Serial.print(" Brazo=");
  Serial.print(servoBrazo.read());
  Serial.print(" Altura=");
  Serial.print(servoAltura.read());
  Serial.print(" Garra=");
  Serial.println(servoGarral.read());

  delay(100);

}

void ejecutarPose(int poseNumber) {
  switch(poseNumber) {
    case 0: // Pose Inicio
      servoBase.write(90);
      servoBrazo.write(30);
      servoAltura.write(60);
      servoGarral.write(0);
      break;
    case 1: // Pose Recogida
      servoBase.write(45);
      servoBrazo.write(120);
      servoAltura.write(30);
      servoGarral.write(0);
      break;
    case 2: // Pose Transporte
      servoBase.write(90);
      servoBrazo.write(90);
      servoAltura.write(120);
      servoGarral.write(90);
      break;
    case 3: // Pose Entrega
      servoBase.write(135);
      servoBrazo.write(60);
      servoAltura.write(80);
      servoGarral.write(0);
      break;
    case 4: // Pose Descanso
      servoBase.write(180);
      servoBrazo.write(0);
      servoAltura.write(0);
      servoGarral.write(45);
      break;
  }
}