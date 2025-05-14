//version alfa

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


enum Estado { S0_AUTO, S1_MANUAL };
Estado estadoActual = S0_AUTO;

void setup() {

  pinMode(potModo, INPUT);
  pinMode(potServo1, INPUT);
  pinMode(potServo2, INPUT);
  pinMode(potServo3, INPUT);
  pinMode(potServo4, INPUT);

  pinMode(botonizq, INPUT_PULLUP);
  pinMode(botonder, INPUT_PULLUP);

  pinMode(ledmodoa, OUTPUT);
  pinMode(ledmodob, OUTPUT);

  Serial.begin(9600);
}

void loop() {

  int pot = analogRead(potModo);
  bool btn = !digitalRead(boton);

  Serial.println(pot);

  switch(estadoActual) {
    case S0_AUTO:
      
      digitalWrite(ledmodoa, HIGH);
      digitalWrite(ledmodob, LOW);
      
      

      
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