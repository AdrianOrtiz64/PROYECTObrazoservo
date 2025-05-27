//version epsilon

#include <Servo.h> 
Servo servos[4]; 

// Pines control
const int potModo = A0;    // Potenciómetro cambio de modo

const int potServo1 = A1;    // Potenciómetro servo 1
const int potServo2 = A2;    // Potenciómetro servo 2
const int potServo3 = A3;    // Potenciómetro servo 3
const int potServo4 = A4;    // Potenciómetro servo 4


const int botonIzq = 4;       // Botón manual ← 
const int botonDer = 5;       // Botón manual →

// Pines LEDs
const int ledmodoa = 2;
const int ledmodob = 3;

Servo servoalpha;
Servo servobeta;
Servo servocharlie;
Servo servodelta;

int currentPose = 0;


enum Estado { S0_AUTO, S1_MANUAL };
Estado estadoActual = S0_AUTO;

void setup() {

  pinMode(potModo, INPUT);
  pinMode(potServo1, INPUT);
  pinMode(potServo2, INPUT);
  pinMode(potServo3, INPUT);
  pinMode(potServo4, INPUT);

  pinMode(botonIzq, INPUT_PULLUP);
  pinMode(botonDer, INPUT_PULLUP);

  pinMode(ledmodoa, OUTPUT);
  pinMode(ledmodob, OUTPUT);

  servoalpha.attach(8);
  servobeta.attach(9);
  servocharlie.attach(10);
  servodelta.attach(11);

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

      if (digitalRead(botonDer) == LOW) {
        if (currentPose < 4) {
          currentPose++;
          ejecutarPose();
          Serial.print("Pose actual: ");
          Serial.println(currentPose);
        }
        delay(300);
        while (digitalRead(botonDer) == LOW);
      }
    
      if (digitalRead(botonIzq) == LOW) {
        if (currentPose > 0) {
          currentPose--;
          ejecutarPose();
          Serial.print("Pose actual: ");
          Serial.println(currentPose);
        }
        delay(300);
        while (digitalRead(botonIzq) == LOW);
      }
      
      

      
      if(pot >= 511 && pot <= 1023) estadoActual = S1_MANUAL;
      break;
      
    case S1_MANUAL:
      
      digitalWrite(ledmodoa, LOW);
      digitalWrite(ledmodob, HIGH);
      

      if(pot <= 512 && pot >= 0) estadoActual = S0_AUTO;
      break;
  }
  delay(100);
}

//---------------CAMBIO POSE------------------
void ejecutarPose() {
  switch(currentPose) {
    case 0: poseInicio(); break;
    case 1: poseRecogida(); break;
    case 2: poseTransporte(); break;
    case 3: poseEntrega(); break;
    case 4: poseDescanso(); break;
    default:
      Serial.print("Pose inválida: ");
      Serial.println(currentPose);
      break;
  }
}

//-------------POSES--------------
void poseInicio() {
  servoalpha.write(90);    
  servobeta.write(30);   
  servocharlie.write(60);  
  servodelta.write(0);   
}

void poseRecogida() {
  servoalpha.write(45);    
  servobeta.write(120);  
  servocharlie.write(30);  
  servodelta.write(0);    
}

void poseTransporte() {
  servoalpha.write(90);    
  servobeta.write(90);   
  servocharlie.write(120); 
  servodelta.write(90);   
}

void poseEntrega() {
  servoalpha.write(135);   
  servobeta.write(60);   
  servocharlie.write(80);  
  servodelta.write(0);    
}

void poseDescanso() {
  servoalpha.write(180);   
  servobeta.write(0);    
  servocharlie.write(0);   
  servodelta.write(45);   
}