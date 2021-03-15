//  PANTALLA LCD
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd (0x27, 20, 4);
//  EJE Y
#define P1 42
#define P2 43
#define FCY1 36
#define FCY2 35
#define VY1 12
#define VY2 11
#define VY3 10
#define VY4 9
int fcy1 = LOW;
int fcy2 = LOW;
int p1 = LOW;
int cp1 = 0;
int p2 = LOW;
int cp2 = 0;
int abajo;
int arriba;
//  EJE X
#define P3 40
#define P4 41
#define FCX1 34
#define FCX2 33
#define VX1 8
#define VX2 7
#define VX3 6
#define VX4 5
int fcx1 = LOW;
int fcx2 = LOW;
int p3 = LOW;
int cp3 = 0;
int p4 = LOW;
int cp4 = 0;
int izquierda;
int derecha;
//  EJE Z
#define P5 38
#define P6 39
#define FCZ1 32
#define FCZ2 31
#define VZ1 4
#define VZ2 3
#define VZ3 2
#define VZ4 22
int fcz1 = LOW;
int fcz2 = LOW;
int p5 = LOW;
int cp5 = 0;
int p6 = LOW;
int cp6 = 0;
int atras;
int adelante;
//  COMÚN
#define PS 37
#define LED1 49
#define LED2 48
#define LED3 47
#define LEDS 46
int ps = HIGH;
int estado;
int contador;

//  MANDO INALAMBRICO
const bool SW = 53;
bool SWITCH = 0;
bool datos[12];
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define CE_PIN 9
#define CSN_PIN 10
byte direccion[5] ={'M','a','n','d','o'};
RF24 mando(CE_PIN, CSN_PIN);

void setup() {
//  EJE Y
  pinMode (FCY1, INPUT_PULLUP);
  pinMode (FCY2, INPUT_PULLUP);
  pinMode (VY1, OUTPUT);
  pinMode (VY2, OUTPUT);
  pinMode (VY3, OUTPUT);
  pinMode (VY4, OUTPUT);
  pinMode (P1, INPUT_PULLUP);
  pinMode (P2, INPUT_PULLUP);
//  EJE X
  pinMode (FCX1, INPUT_PULLUP);
  pinMode (FCX2, INPUT_PULLUP);
  pinMode (VX1, OUTPUT);
  pinMode (VX2, OUTPUT);
  pinMode (VX3, OUTPUT);
  pinMode (VX4, OUTPUT);
  pinMode (P3, INPUT_PULLUP);
  pinMode (P4, INPUT_PULLUP);
//  EJE Z
  pinMode (FCZ1, INPUT_PULLUP);
  pinMode (FCZ2, INPUT_PULLUP);
  pinMode (VZ1, OUTPUT);
  pinMode (VZ2, OUTPUT);
  pinMode (VZ3, OUTPUT);
  pinMode (VZ4, OUTPUT);
  pinMode (P5, INPUT_PULLUP);
  pinMode (P6, INPUT_PULLUP);
// COMÚN
  pinMode (LED1, OUTPUT);
  pinMode (LED2, OUTPUT);
  pinMode (LED3, OUTPUT);
  pinMode (LEDS, OUTPUT);
  pinMode (PS, INPUT_PULLUP);
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(1, 0);
  estado = 0;
// MANDO INALAMBRICO
  pinMode(SW, INPUT_PULLUP);
  mando.begin();
  mando.openReadingPipe(1, direccion);
  mando.startListening();
}

void loop() {
  SWITCH = digitalRead(SW);
  MANDO();
  if(SWITCH){
    p1 = digitalRead (P1);
    p2 = digitalRead (P2);
    p3 = digitalRead (P3);
    p4 = digitalRead (P4);
    p5 = digitalRead (P5);
    p6 = digitalRead (P6);
  }else{
    p1 = datos[0];
    p2 = datos[1];
    p3 = datos[2];
    p4 = datos[3];
    p5 = datos[4];
    p6 = datos[5];
  }
  ps = digitalRead (PS);
  fcy1 = digitalRead (FCY1);
  fcy2 = digitalRead (FCY2);
  fcx1 = digitalRead (FCX1);
  fcx2 = digitalRead (FCX2);
  fcz1 = digitalRead (FCZ1);
  fcz2 = digitalRead (FCZ2);
  if (ps == LOW){
    estado = 0;
  }
  switch (estado){
    case 0:
      digitalWrite (LED1, LOW);
      digitalWrite (LED2, LOW);
      digitalWrite (LED3, LOW);
      digitalWrite (VY1, LOW);
      digitalWrite (VY2, LOW);
      digitalWrite (VY3, LOW);
      digitalWrite (VY4, LOW);
      digitalWrite (VX1, LOW);
      digitalWrite (VX2, LOW);
      digitalWrite (VX3, LOW);
      digitalWrite (VX4, LOW);
      digitalWrite (VZ1, LOW);
      digitalWrite (VZ2, LOW);
      digitalWrite (VZ3, LOW);
      digitalWrite (VZ4, LOW);
      abajo = LOW;
      arriba = LOW;
      derecha = LOW;
      izquierda = LOW;
      adelante = LOW;
      atras = LOW;
      if (ps == HIGH) {
        digitalWrite (LEDS, LOW);
        if (p1 == LOW) {
          estado = 1;
        }
        if (p2 == LOW) {
          estado = 2;
        }
        if (p3 == LOW) {
          estado = 3;
        }
        if (p4 == LOW) {
          estado = 4;
        }
        if (p5 == LOW) {
          estado = 5;
        }
        if (p6 == LOW) {
          estado = 6;
        }
      }
      break;
    
    case 1:
      digitalWrite (LED1, HIGH);
      abajo = HIGH;
      if (cp1 < 15) {
      digitalWrite (VY1, HIGH);
        cp1++;
      }
      if (cp1 >= 15) {
        digitalWrite (VY1, LOW);
        digitalWrite (VY2, HIGH);
      }
      if (fcy1 == LOW) {
        digitalWrite (VY1, LOW);
        digitalWrite (VY2, LOW);
        estado = 0;
      }
      if (p3 == LOW) {
        estado = 7;
      }
      if (p4 == LOW) {
        estado = 9;
      }
      if (p5 == LOW) {
        estado = 11;
      }
      if (p6 == LOW) {
        estado = 15;
      }
      delay (200);
      break;

    case 2:
      digitalWrite (LED1, HIGH);
      arriba = HIGH;
      if (cp2 < 15) {
        digitalWrite (VY3, HIGH);
        cp2++;
      }
      if (cp2 >= 15) {
        digitalWrite (VY3, LOW);
        digitalWrite (VY4, HIGH);
      }
      if (fcy2 == LOW) {
        digitalWrite (VY3, LOW);
        digitalWrite (VY4, LOW);
        estado = 0;
      }
      if (p3 == LOW) {
        estado = 8;
      }
      if (p4 == LOW) {
        estado = 10;
      }
      if (p5 == LOW) {
        estado = 12;
      }
      if (p6 == LOW) {
        estado = 16;
      }
      delay (200);
      break;
    case 3:
      digitalWrite (LED2, HIGH);
      derecha = HIGH;
      if (cp3 < 15) {
        digitalWrite (VX1, HIGH);
        cp3++;
      }
      if (cp3 >= 15) {
        digitalWrite (VX1, LOW);
        digitalWrite (VX2, HIGH);
      }
      if (fcx2 == LOW) {
        digitalWrite (VX1, LOW);
        digitalWrite (VX2, LOW);
        estado = 0;
      }
      if (p1 == LOW) {
        estado = 7;
      }
      if (p2 == LOW) {
        estado = 8;
      }
      if (p5 == LOW) {
        estado = 13;
      }
      if (p6 == LOW) {
        estado = 17;
      }
      delay (200);
      break;
    case 4:
      digitalWrite (LED2, HIGH);
      izquierda = HIGH;
      if (cp4 < 15) {
        digitalWrite (VX3, HIGH);
        cp4++;
      }
      if (cp4 >= 15) {
        digitalWrite (VX3, LOW);
        digitalWrite (VX4, HIGH);
      }
      if (fcx1 == LOW) {
        digitalWrite (VX3, LOW);
        digitalWrite (VX4, LOW);
        estado = 0;
      }
      if (p1 == LOW) {
        estado = 9;
      }
      if (p2 == LOW) {
        estado = 10;
      }
      if (p5 == LOW) {
        estado = 14;
      }
      if (p6 == LOW) {
        estado = 18;
      }
      delay (200);
      break;
    case 5:
      digitalWrite (LED3, HIGH);
      adelante = HIGH;
      if (cp5 < 15) {
        digitalWrite (VZ1, HIGH);
        cp5++;
      }
      if (cp5 >= 15) {
        digitalWrite (VZ1, LOW);
        digitalWrite (VZ2, HIGH);
      }
      if (fcz1 == LOW) {
        digitalWrite (VZ1, LOW);
        digitalWrite (VZ2, LOW);
        estado = 0;
      }
      if (p1 == LOW) {
        estado = 11;
      }
      if (p2 == LOW) {
        estado = 12;
      }
      if (p3 == LOW) {
        estado = 13;
      }
      if (p4 == LOW) {
        estado = 14;
      }
      delay (200);
      break;
    case 6:
      digitalWrite (LED3, HIGH);
      atras = HIGH;
      if (cp6 < 15) {
        digitalWrite (VZ3, HIGH);
        cp6++;
      }
      if (cp6 >= 15) {
        digitalWrite (VZ3, LOW);
        digitalWrite (VZ4, HIGH);
      }
      if (fcz2 == LOW) {
        digitalWrite (VZ3, LOW);
        digitalWrite (VZ4, LOW);
        estado = 0;
      }
      if (p1 == LOW) {
        estado = 15;
      }
      if (p2 == LOW) {
        estado = 16;
      }
      if (p3 == LOW) {
        estado = 17;
      }
      if (p4 == LOW) {
        estado = 18;
      }
      delay (200);
      break;
    case 7:
      digitalWrite (LED1, HIGH);
      digitalWrite (LED2, HIGH);
      abajo = HIGH;
      derecha = HIGH;
      if (cp1 < 15) {
        digitalWrite (VY1, HIGH);
        cp1++;
      }
      if (cp3 < 15) {
        digitalWrite (VX1, HIGH);
        cp3++;
      }
      if (cp1 >= 15) {
        digitalWrite (VY1, LOW);
        digitalWrite (VY2, HIGH);
      }
      if (cp3 >= 15) {
        digitalWrite (VX1, LOW);
        digitalWrite (VX2, HIGH);
      }
      if (fcy1 == LOW) {
        digitalWrite (VY1, LOW);
        digitalWrite (VY2, LOW);
        estado = 3;
      }
      if (fcx2 == LOW) {
        digitalWrite (VX1, LOW);
        digitalWrite (VX2, LOW);
        estado = 1;
      }
      if (p5 == LOW) {
        estado = 19;
      }
      if (p6 == LOW) {
        estado = 20;
      }
      delay (200);
      break;
    case 8:
      digitalWrite (LED1, HIGH);
      digitalWrite (LED2, HIGH);
      arriba = HIGH;
      derecha = HIGH;
      if (cp2 < 15) {
        digitalWrite (VY3, HIGH);
        cp2++;
      }
      if (cp3 < 15) {
        digitalWrite (VX1, HIGH);
        cp3++;
      }
      if (cp2 >= 15) {
        digitalWrite (VY3, LOW);
        digitalWrite (VY4, HIGH);
      }
      if (cp3 >= 15) {
        digitalWrite (VX1, LOW);
        digitalWrite (VX2, HIGH);
      }
      if (fcy2 == LOW) {
        digitalWrite (VY3, LOW);
        digitalWrite (VY4, LOW);
        estado = 3;
      }
      if (fcx2 == LOW) {
        digitalWrite (VX1, LOW);
        digitalWrite (VX2, LOW);
        estado = 2;
      }
      if (p5 == LOW) {
        estado = 23;
      }
      if (p6 == LOW) {
        estado = 24;
      }
      delay (200);
      break;
    case 9:
      digitalWrite (LED1, HIGH);
      digitalWrite (LED2, HIGH);
      abajo = HIGH;
      izquierda = HIGH;
      if (cp1 < 15) {
        digitalWrite (VY1, HIGH);
        cp1++;
      }
      if (cp4 < 15) {
        digitalWrite (VX3, HIGH);
        cp4++;
      }
      if (cp1 >= 15) {
        digitalWrite (VY1, LOW);
        digitalWrite (VY2, HIGH);
      }
      if (cp4 >= 15) {
        digitalWrite (VX3, LOW);
        digitalWrite (VX4, HIGH);
      }
      if (fcy1 == LOW) {
        digitalWrite (VY1, LOW);
        digitalWrite (VY2, LOW);
        estado = 4;
      }
      if (fcx1 == LOW) {
        digitalWrite (VX3, LOW);
        digitalWrite (VX4, LOW);
        estado = 1;
      }
      if (p5 == LOW) {
        estado = 21;
      }
      if (p6 == LOW) {
        estado = 22;
      }
      delay (200);
      break;
    case 10:
      digitalWrite (LED1, HIGH);
      digitalWrite (LED2, HIGH);
      arriba = HIGH;
      izquierda = HIGH;
      if (cp2 < 15) {
        digitalWrite (VY3, HIGH);
        cp2++;
      }
      if (cp4 < 15) {
        digitalWrite (VX3, HIGH);
        cp4++;
      }
      if (cp2 >= 15) {
        digitalWrite (VY3, LOW);
        digitalWrite (VY4, HIGH);
      }
      if (cp4 >= 15) {
        digitalWrite (VX3, LOW);
        digitalWrite (VX4, HIGH);
      }
      if (fcy2 == LOW) {
        digitalWrite (VY3, LOW);
        digitalWrite (VY4, LOW);
        estado = 4;
      }
      if (fcx1 == LOW) {
        digitalWrite (VX3, LOW);
        digitalWrite (VX4, LOW);
        estado = 2;
      }
      if (p5 == LOW) {
        estado = 25;
      }
      if (p6 == LOW) {
        estado = 26;
      }
      delay (200);
      break;
    case 11:
      digitalWrite (LED1, HIGH);
      digitalWrite (LED3, HIGH);
      abajo = HIGH;
      adelante = HIGH;
      if (cp1 < 15) {
        digitalWrite (VY1, HIGH);
        cp1++;
      }
      if (cp5 < 15) {
        digitalWrite (VZ1, HIGH);
        cp5++;
      }
      if (cp1 >= 15) {
        digitalWrite (VY1, LOW);
        digitalWrite (VY2, HIGH);
      }
      if (cp5 >= 15) {
        digitalWrite (VZ1, LOW);
        digitalWrite (VZ2, HIGH);
      }
      if (fcy1 == LOW) {
        digitalWrite (VY1, LOW);
        digitalWrite (VY2, LOW);
        estado = 5;
      }
      if (fcz1 == LOW) {
        digitalWrite (VZ1, LOW);
        digitalWrite (VZ2, LOW);
        estado = 1;
      }
      if (p3 == LOW) {
        estado = 19;
      }
      if (p4 == LOW) {
        estado = 21;
      }
      delay (200);
      break;
    case 12:
      digitalWrite (LED1, HIGH);
      digitalWrite (LED3, HIGH);
      arriba = HIGH;
      adelante = HIGH;
      if (cp2 < 15) {
        digitalWrite (VY3, HIGH);
        cp2++;
      }
      if (cp5 < 15) {
        digitalWrite (VZ1, HIGH);
        cp5++;
      }
      if (cp2 >= 15) {
        digitalWrite (VY3, LOW);
        digitalWrite (VY4, HIGH);
      }
      if (cp5 >= 15) {
        digitalWrite (VZ1, LOW);
        digitalWrite (VZ2, HIGH);
      }
      if (fcy2 == LOW) {
        digitalWrite (VY3, LOW);
        digitalWrite (VY4, LOW);
        estado = 5;
      }
      if (fcz1 == LOW) {
        digitalWrite (VZ1, LOW);
        digitalWrite (VZ2, LOW);
        estado = 2;
      }
      if (p3 == LOW) {
        estado = 23;
      }
      if (p4 == LOW) {
        estado = 25;
      }
      delay (200);
      break;
    case 13:
      digitalWrite (LED2, HIGH);
      digitalWrite (LED3, HIGH);
      derecha = HIGH;
      adelante = HIGH;
      if (cp3 < 15) {
        digitalWrite (VX1, HIGH);
        cp3++;
      }
      if (cp5 < 15) {
        digitalWrite (VZ1, HIGH);
        cp5++;
      }
      if (cp3 >= 15) {
        digitalWrite (VX1, LOW);
        digitalWrite (VX2, HIGH);
      }
      if (cp5 >= 15) {
        digitalWrite (VZ1, LOW);
        digitalWrite (VZ2, HIGH);
      }
      if (fcx2 == LOW) {
        digitalWrite (VX1, LOW);
        digitalWrite (VX2, LOW);
        estado = 5;
      }
      if (fcz1 == LOW) {
        digitalWrite (VZ1, LOW);
        digitalWrite (VZ2, LOW);
        estado = 3;
      }
      if (p1 == LOW) {
        estado = 19;
      }
      if (p2 == LOW) {
        estado = 23;
      }
      delay (200);
      break;
    case 14:
      digitalWrite (LED2, HIGH);
      digitalWrite (LED3, HIGH);
      izquierda = HIGH;
      adelante = HIGH;
      if (cp4 < 15) {
        digitalWrite (VX3, HIGH);
        cp4++;
      }
      if (cp5 < 15) {
        digitalWrite (VZ1, HIGH);
        cp5++;
      }
      if (cp4 >= 15) {
        digitalWrite (VX3, LOW);
        digitalWrite (VX4, HIGH);
      }
      if (cp5 >= 15) {
        digitalWrite (VZ1, LOW);
        digitalWrite (VZ2, HIGH);
      }
      if (fcx1 == LOW) {
        digitalWrite (VX3, LOW);
        digitalWrite (VX4, LOW);
        estado = 5;
      }
      if (fcz1 == LOW) {
        digitalWrite (VZ1, LOW);
        digitalWrite (VZ2, LOW);
        estado = 4;
      }
      if (p1 == LOW) {
        estado = 21;
      }
      if (p2 == LOW) {
        estado = 25;
      }
      delay (200);
      break;
    case 15:
      digitalWrite (LED1, HIGH);
      digitalWrite (LED3, HIGH);
      abajo = HIGH;
      atras = HIGH;
      if (cp1 < 15) {
        digitalWrite (VY1, HIGH);
        cp1++;
      }
      if (cp6 < 15) {
        digitalWrite (VZ3, HIGH);
        cp6++;
      }
      if (cp1 >= 15) {
        digitalWrite (VY1, LOW);
        digitalWrite (VY2, HIGH);
      }
      if (cp6 >= 15) {
        digitalWrite (VZ3, LOW);
        digitalWrite (VZ4, HIGH);
      }
      if (fcy1 == LOW) {
        digitalWrite (VY1, LOW);
        digitalWrite (VY2, LOW);
        estado = 6;
      }
      if (fcz2 == LOW) {
        digitalWrite (VZ3, LOW);
        digitalWrite (VZ4, LOW);
        estado = 1;
      }
      if (p3 == LOW) {
        estado = 20;
      }
      if (p4 == LOW) {
        estado = 22;
      }
      delay (200);
      break;
    case 16:
      digitalWrite (LED1, HIGH);
      digitalWrite (LED3, HIGH);
      arriba = HIGH;
      atras = HIGH;
      if (cp2 < 15) {
        digitalWrite (VY3, HIGH);
        cp2++;
      }
      if (cp6 < 15) {
        digitalWrite (VZ3, HIGH);
        cp6++;
      }
      if (cp2 >= 15) {
        digitalWrite (VY3, LOW);
        digitalWrite (VY4, HIGH);
      }
      if (cp6 >= 15) {
        digitalWrite (VZ3, LOW);
        digitalWrite (VZ4, HIGH);
      }
      if (fcy2 == LOW) {
        digitalWrite (VY3, LOW);
        digitalWrite (VY4, LOW);
        estado = 6;
      }
      if (fcz2 == LOW) {
        digitalWrite (VZ3, LOW);
        digitalWrite (VZ4, LOW);
        estado = 2;
      }
      if (p3 == LOW) {
        estado = 24;
      }
      if (p4 == LOW) {
        estado = 26;
      }
      delay (200);
      break;
    case 17:
      digitalWrite (LED2, HIGH);
      digitalWrite (LED3, HIGH);
      derecha = HIGH;
      atras = HIGH;
      if (cp3 < 15) {
        digitalWrite (VX1, HIGH);
        cp3++;
      }
      if (cp6 < 15) {
        digitalWrite (VZ3, HIGH);
        cp6++;
      }
      if (cp3 >= 15) {
        digitalWrite (VX1, LOW);
        digitalWrite (VX2, HIGH);
      }
      if (cp6 >= 15) {
        digitalWrite (VZ3, LOW);
        digitalWrite (VZ4, HIGH);
      }
      if (fcx2 == LOW) {
        digitalWrite (VX1, LOW);
        digitalWrite (VX2, LOW);
        estado = 6;
      }
      if (fcz2 == LOW) {
        digitalWrite (VZ3, LOW);
        digitalWrite (VZ4, LOW);
        estado = 3;
      }
      if (p1 == LOW) {
        estado = 20;
      }
      if (p2 == LOW) {
        estado = 24;
      }
      delay (200);
      break;
    case 18:
      digitalWrite (LED2, HIGH);
      digitalWrite (LED3, HIGH);
      izquierda = HIGH;
      atras = HIGH;
      if (cp4 < 15) {
        digitalWrite (VX3, HIGH);
        cp4++;
      }
      if (cp6 < 15) {
        digitalWrite (VZ3, HIGH);
        cp6++;
      }
      if (cp4 >= 15) {
        digitalWrite (VX3, LOW);
        digitalWrite (VX4, HIGH);
      }
      if (cp6 >= 15) {
        digitalWrite (VZ3, LOW);
        digitalWrite (VZ4, HIGH);
      }
      if (fcx1 == LOW) {
        digitalWrite (VX3, LOW);
        digitalWrite (VX4, LOW);
        estado = 6;
      }
      if (fcz2 == LOW) {
        digitalWrite (VZ3, LOW);
        digitalWrite (VZ4, LOW);
        estado = 4;
      }
      if (p1 == LOW) {
        estado = 22;
      }
      if (p2 == LOW) {
        estado = 26;
      }
      delay (200);
      break;
    case 19:
      digitalWrite (LED1, HIGH);
      digitalWrite (LED2, HIGH);
      digitalWrite (LED3, HIGH);
      abajo = HIGH;
      derecha = HIGH;
      adelante = HIGH;
      if (cp1 < 15) {
        digitalWrite (VY1, HIGH);
        cp1 ++;
      }
      if (cp3 < 15) {
        digitalWrite (VX1, HIGH);
        cp3 ++;
      }
      if (cp5 < 15) {
        digitalWrite (VZ1, HIGH);
        cp5 ++;
      }
      if (cp1 >= 15) {
        digitalWrite (VY1, LOW);
        digitalWrite (VY2, HIGH);
      }
      if (cp3 >= 15) {
        digitalWrite (VX1, LOW);
        digitalWrite (VX2, HIGH);
      }
      if (cp5 >= 15) {
        digitalWrite (VZ1, LOW);
        digitalWrite (VZ2, HIGH);
      }
      if (fcy1 == LOW) {
        digitalWrite (VY1, LOW);
        digitalWrite (VY2, LOW);
        estado = 13;
      }
      if (fcx2 == LOW) {
        digitalWrite (VX1, LOW);
        digitalWrite (VX2, LOW);
        estado = 11;
      }
      if (fcz1 == LOW) {
        digitalWrite (VZ1, LOW);
        digitalWrite (VZ2, LOW);
        estado = 7;
      }
      delay (200);
      break;
    case 20:
      digitalWrite (LED1, HIGH);
      digitalWrite (LED2, HIGH);
      digitalWrite (LED3, HIGH);
      abajo = HIGH;
      derecha = HIGH;
      atras = HIGH;
      if (cp1 < 15) {
        digitalWrite (VY1, HIGH);
        cp1 ++;
      }
      if (cp3 < 15) {
        digitalWrite (VX1, HIGH);
        cp3 ++;
      }
      if (cp6 < 15) {
        digitalWrite (VZ3, HIGH);
        cp6 ++;
      }
      if (cp1 >= 15) {
        digitalWrite (VY1, LOW);
        digitalWrite (VY2, HIGH);
      }
      if (cp3 >= 15) {
        digitalWrite (VX1, LOW);
        digitalWrite (VX2, HIGH);
      }
      if (cp6 >= 15) {
        digitalWrite (VZ3, LOW);
        digitalWrite (VZ4, HIGH);
      }
      if (fcy1 == LOW) {
        digitalWrite (VY1, LOW);
        digitalWrite (VY2, LOW);
        estado = 17;
      }
      if (fcx2 == LOW) {
        digitalWrite (VX1, LOW);
        digitalWrite (VX2, LOW);
        estado = 15;
      }
      if (fcz2 == LOW) {
        digitalWrite (VZ3, LOW);
        digitalWrite (VZ4, LOW);
        estado = 7;
      }
      delay (200);
      break;
    case 21:
      digitalWrite (LED1, HIGH);
      digitalWrite (LED2, HIGH);
      digitalWrite (LED3, HIGH);
      abajo = HIGH;
      izquierda = HIGH;
      adelante = HIGH;
      if (cp1 < 15) {
        digitalWrite (VY1, HIGH);
        cp1 ++;
      }
      if (cp4 < 15) {
        digitalWrite (VX3, HIGH);
        cp4 ++;
      }
      if (cp5 < 15) {
        digitalWrite (VZ1, HIGH);
        cp5 ++;
      }
      if (cp1 >= 15) {
        digitalWrite (VY1, LOW);
        digitalWrite (VY2, HIGH);
      }
      if (cp4 >= 15) {
        digitalWrite (VX3, LOW);
        digitalWrite (VX4, HIGH);
      }
      if (cp5 >= 15) {
        digitalWrite (VZ1, LOW);
        digitalWrite (VZ2, HIGH);
      }
      if (fcy1 == LOW) {
        digitalWrite (VY1, LOW);
        digitalWrite (VY2, LOW);
        estado = 14;
      }
      if (fcx1 == LOW) {
        digitalWrite (VX3, LOW);
        digitalWrite (VX4, LOW);
        estado = 11;
      }
      if (fcz1 == LOW) {
        digitalWrite (VZ1, LOW);
        digitalWrite (VZ2, LOW);
        estado = 9;
      }
      delay (200);
      break;
    case 22:
      digitalWrite (LED1, HIGH);
      digitalWrite (LED2, HIGH);
      digitalWrite (LED3, HIGH);
      abajo = HIGH;
      izquierda = HIGH;
      atras = HIGH;
      if (cp1 < 15) {
        digitalWrite (VY1, HIGH);
        cp1 ++;
      }
      if (cp4 < 15) {
        digitalWrite (VX3, HIGH);
        cp4 ++;
      }
      if (cp6 < 15) {
        digitalWrite (VZ3, HIGH);
      }
      if (cp1 >= 15) {
        digitalWrite (VY1, LOW);
        digitalWrite (VY2, HIGH);
      }
      if (cp4 >= 15) {
        digitalWrite (VX3, LOW);
        digitalWrite (VX4, HIGH);
      }
      if (cp6 >= 15) {
        digitalWrite (VZ3, LOW);
        digitalWrite (VZ4, HIGH);
      }
      if (fcy1 == LOW) {
        digitalWrite (VY1, LOW);
        digitalWrite (VY2, LOW);
        estado = 18;
      }
      if (fcx1 == LOW) {
        digitalWrite (VX3, LOW);
        digitalWrite (VX4, LOW);
        estado = 15;
      }
      if (fcz2 == LOW) {
        digitalWrite (VZ3, LOW);
        digitalWrite (VZ4, LOW);
        estado = 9;
      }
      delay (200);
      break;
    case 23:
      digitalWrite (LED1, HIGH);
      digitalWrite (LED2, HIGH);
      digitalWrite (LED3, HIGH);
      arriba = HIGH;
      derecha = HIGH;
      adelante = HIGH;
      if (cp2 < 15) {
        digitalWrite (VY3, HIGH);
        cp2 ++;
      }
      if (cp3 < 15) {
        digitalWrite (VX1, HIGH);
        cp3 ++;
      }
      if (cp5 < 15) {
        digitalWrite (VZ1, HIGH);
        cp5 ++;
      }
      if (cp2 >= 15) {
        digitalWrite (VY3, LOW);
        digitalWrite (VY4, HIGH);
      }
      if (cp3 >= 15) {
        digitalWrite (VX1, LOW);
        digitalWrite (VX2, HIGH);
      }
      if (cp5 >= 15) {
        digitalWrite (VZ1, LOW);
        digitalWrite (VZ2, HIGH);
      }
      if (fcy2 == LOW) {
        digitalWrite (VY3, LOW);
        digitalWrite (VY4, LOW);
        estado = 13;
      }
      if (fcx2 == LOW) {
        digitalWrite (VX1, LOW);
        digitalWrite (VX2, LOW);
        estado = 12;
      }
      if (fcz1 == LOW) {
        digitalWrite (VZ1, LOW);
        digitalWrite (VZ2, LOW);
        estado = 8;
      }
      delay (200);
      break;
    case 24:
      digitalWrite (LED1, HIGH);
      digitalWrite (LED2, HIGH);
      digitalWrite (LED3, HIGH);
      arriba = HIGH;
      derecha = HIGH;
      atras = HIGH;
      if (cp2 < 15) {
        digitalWrite (VY3, HIGH);
        cp2 ++;
      }
      if (cp3 < 15) {
        digitalWrite (VX1, HIGH);
        cp3 ++;
      }
      if (cp6 < 15) {
        digitalWrite (VZ3, HIGH);
        cp6 ++;
      }
      if (cp2 >= 15) {
        digitalWrite (VY3, LOW);
        digitalWrite (VY4, HIGH);
      }
      if (cp3 >= 15) {
        digitalWrite (VX1, LOW);
        digitalWrite (VX2, HIGH);
      }
      if (cp6 >= 15) {
        digitalWrite (VZ3, LOW);
        digitalWrite (VZ4, HIGH);
      }
      if (fcy2 == LOW) {
        digitalWrite (VY3, LOW);
        digitalWrite (VY4, LOW);
        estado = 17;
      }
      if (fcx2 == LOW) {
        digitalWrite (VX1, LOW);
        digitalWrite (VX2, LOW);
        estado = 16;
      }
      if (fcz2 == LOW) {
        digitalWrite (VZ3, LOW);
        digitalWrite (VZ4, LOW);
        estado = 8;
      }
      delay (200);
      break;
    case 25:
      digitalWrite (LED1, HIGH);
      digitalWrite (LED2, HIGH);
      digitalWrite (LED3, HIGH);
      arriba = HIGH;
      izquierda = HIGH;
      adelante = HIGH;
      if (cp2 < 15) {
        digitalWrite (VY3, HIGH);
        cp2 ++;
      }
      if (cp4 < 15) {
        digitalWrite (VX3, HIGH);
        cp4 ++;
      }
      if (cp5 < 15) {
        digitalWrite (VZ1, HIGH);
        cp5 ++;
      }
      if (cp2 >= 15) {
        digitalWrite (VY3, LOW);
        digitalWrite (VY4, HIGH);
      }
      if (cp4 >= 15) {
        digitalWrite (VX3, LOW);
        digitalWrite (VX4, HIGH);
      }
      if (cp5 >= 15) {
        digitalWrite (VZ1, LOW);
        digitalWrite (VZ2, HIGH);
      }
      if (fcy2 == LOW) {
        digitalWrite (VY3, LOW);
        digitalWrite (VY4, LOW);
        estado = 14;
      }
      if (fcx1 == LOW) {
        digitalWrite (VX3, LOW);
        digitalWrite (VX4, LOW);
        estado = 12;
      }
      if (fcz1 == LOW) {
        digitalWrite (VZ1, LOW);
        digitalWrite (VZ2, LOW);
        estado = 10;
      }
      delay (200);
      break;
    case 26:
      digitalWrite (LED1, HIGH);
      digitalWrite (LED2, HIGH);
      digitalWrite (LED3, HIGH);
      arriba = HIGH;
      izquierda = HIGH;
      atras = HIGH;
      if (cp2 < 15) {
        digitalWrite (VY3, HIGH);
        cp2 ++;
      }
      if (cp4 < 15) {
        digitalWrite (VX3, HIGH);
        cp4 ++;
      }
      if (cp6 <15) {
        digitalWrite (VZ3, HIGH);
        cp6 ++;
      }
      if (cp2 >= 15) {
        digitalWrite (VY3, LOW);
        digitalWrite (VY4, HIGH);
      }
      if (cp4 >= 15) {
        digitalWrite (VX3, LOW);
        digitalWrite (VX4, HIGH);
      }
      if (cp6 >= 15) {
        digitalWrite (VZ3, LOW);
        digitalWrite (VZ4, HIGH);
      }
      if (fcy2 == LOW) {
        digitalWrite (VY3, LOW);
        digitalWrite (VY4, LOW);
        estado = 18;
      }
      if (fcx1 == LOW) {
        digitalWrite (VX3, LOW);
        digitalWrite (VX4, LOW);
        estado = 16;
      }
      if (fcz2 == LOW) {
        digitalWrite (VZ3, LOW);
        digitalWrite (VZ4, LOW);
        estado = 10;
      }
      delay (200);
      break;
  }
  if (abajo == HIGH) {
    lcd.setCursor (1, 0);
    lcd.print ("Abajo");
  }
  if (arriba == HIGH) {
    lcd.setCursor (1, 0);
    lcd.print ("Arriba");
  }
  if (izquierda == HIGH) {
    lcd.setCursor (7, 0);
    lcd.print ("Izquierda");
  }
  if (derecha == HIGH) {
    lcd.setCursor (9, 0);
    lcd.print ("Derecha");
  }
  if (adelante == HIGH) {
    lcd.setCursor (1, 1);
    lcd.print ("Adelante");
  }
  if (atras == HIGH) {
    lcd.setCursor (1, 1);
    lcd.print ("Atras");
  }
  if (abajo == LOW && arriba == LOW) {
    if (ps == LOW) {
      lcd.setCursor (1, 0);
      lcd.print ("M1Paro");
    }
  }
  if (ps == LOW) {
    if (derecha == LOW && izquierda == LOW) {
      lcd.setCursor (10, 0);
      lcd.print ("M2Paro");
    }
  }
  if (ps == LOW) {
   if (adelante == LOW && atras == LOW) {
     lcd.setCursor (1, 1);
     lcd.print ("M3Paro");
    }
  }
  if (ps == HIGH) {
    lcd.clear ();
    lcd.setCursor (1, 0);
    lcd.print ("EMERGENCIA");
    digitalWrite (LEDS, HIGH);
    delay (1000);
  }
}


void MANDO(){
  mando.read(datos, sizeof(datos));
  for(int i=0; i <= ((sizeof(datos))-1); i++){
        Serial.print(datos[i]);
  }
}
