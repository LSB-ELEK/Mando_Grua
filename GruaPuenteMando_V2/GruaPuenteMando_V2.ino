// EJE Y
#define P1 42
#define P2 43
#define LED1 49
#define VY1 12
#define VY2 11
#define VY3 10
#define VY4 9
#define FCY1 36
#define FCY2 35
int p1;
int cp1;
int p2;
int cp2;
int fcy1;
int fcy2;
int contadory;

// EJE X
#define P3 40
#define P4 41
#define LED2 48
#define VX1 8
#define VX2 7
#define VX3 6
#define VX4 5
#define FCX1 34
#define FCX2 33
int p3;
int cp3;
int p4;
int cp4;
int fcx1;
int fcx2;
int contadorx;

// EJE Z
#define P5 38
#define P6 39
#define LED3 47
#define VZ1 4
#define VZ2 3
#define VZ3 2
#define VZ4 22
#define FCZ1 32
#define FCZ2 31
int p5;
int cp5;
int p6;
int cp6;
int fcz1;
int fcz2;
int contadorz;

// GENERAL
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd (0x27, 16, 2);
#define PS 37
#define LED4 46
int ps;
int estadoy;
int estadox;
int estadoz;

//  MANDO INALAMBRICO
#define SW 13
bool SWITCH = 0;
bool datos[12];
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define CE_PIN 44
#define CSN_PIN 45
byte direccion[5] ={'M','a','n','d','o'};
RF24 mando(CE_PIN, CSN_PIN);

#define SERIAL

void setup() {
// EJE Y
  pinMode (P1, INPUT_PULLUP);
  pinMode (P2, INPUT_PULLUP);
  pinMode (LED1, OUTPUT);
  pinMode (VY1, OUTPUT);
  pinMode (VY2, OUTPUT);
  pinMode (VY3, OUTPUT);
  pinMode (VY4, OUTPUT);
  pinMode (FCY1, INPUT_PULLUP);
  pinMode (FCY2, INPUT_PULLUP);
  
// EJE X
  pinMode (P3, INPUT_PULLUP);
  pinMode (P4, INPUT_PULLUP);
  pinMode (LED2, OUTPUT);
  pinMode (VX1, OUTPUT);
  pinMode (VX2, OUTPUT);
  pinMode (VX3, OUTPUT);
  pinMode (VX4, OUTPUT);
  pinMode (FCX1, INPUT_PULLUP);
  pinMode (FCX2, INPUT_PULLUP);
  
// EJE Z
  pinMode (P5, INPUT_PULLUP);
  pinMode (P6, INPUT_PULLUP);
  pinMode (LED3, OUTPUT);
  pinMode (VZ1, OUTPUT);
  pinMode (VZ2, OUTPUT);
  pinMode (VZ3, OUTPUT);
  pinMode (VZ4, OUTPUT);
  pinMode (FCZ1, INPUT_PULLUP);
  pinMode (FCZ2, INPUT_PULLUP);
  
// GENERAL
  pinMode (PS, INPUT_PULLUP);
  pinMode (LED4, OUTPUT);
  lcd.begin();
  lcd.clear ();
  lcd.home ();
  lcd.backlight ();
  estadoy = 0;
  estadox = 0;
  estadoz = 0;
// MANDO INALAMBRICO
  pinMode(SW, INPUT_PULLUP);
  mando.begin();
  mando.openReadingPipe(1, direccion);
  mando.startListening();
  #ifdef SERIAL
    Serial.begin(9600);
    Serial.println("Serial Activo");
  #endif
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
    #ifdef SERIAL
      Serial.println("Pulsas");
    #endif
  }else{
    p1 = datos[0];
    p2 = datos[1];
    p3 = datos[2];
    p4 = datos[3];
    p5 = datos[4];
    p6 = datos[5];
    #ifdef SERIAL
      Serial.println("Mando");
    #endif
  }
  #ifdef SERIAL
    Serial.println(SWITCH);
  #endif
  ps = digitalRead (PS);
  fcy1 = digitalRead (FCY1);
  fcy2 = digitalRead (FCY2);
  fcx1 = digitalRead (FCX1);
  fcx2 = digitalRead (FCX2);
  fcz1 = digitalRead (FCZ1);
  fcz2 = digitalRead (FCZ2);
  if (ps == HIGH) {
      estadoy = 0;
      estadox = 0;
      estadoz = 0;
      lcd.clear ();
      lcd.setCursor (1, 0);
      lcd.print ("EMERGENCIA");
      digitalWrite (LED4, HIGH);
      delay (100);
    }
    if (ps == LOW) {
        digitalWrite (LED4, LOW);
      }

  switch (estadoy) {
    case 0:
    digitalWrite (LED1, LOW);
    digitalWrite (VY1, LOW);
    digitalWrite (VY2, LOW);
    digitalWrite (VY3, LOW);
    digitalWrite (VY4, LOW);
    lcd.setCursor (1, 0);
    lcd.print ("M1Paro  ");
    cp1 = 0;
    cp2 = 0;
    if (ps == LOW) {
      if (fcy1 == HIGH) {
        if (p1 == LOW && p2 == HIGH) {
          estadoy = 1;
          cp1 = millis ();
        }
      }
      if (fcy2 == HIGH) {
        if (p2 == LOW && p1 == HIGH) {
          estadoy = 2;
          cp2 = millis ();
        }
      }
    }
    break;

    case 1:
    digitalWrite (LED1, HIGH);
    contadory = millis () - cp1;
    if (contadory < 3000) {
    digitalWrite (VY1, HIGH);
    lcd.setCursor  (1, 0);
    lcd.print ("abajo   ");
    }
    if (contadory > 3000) {
      digitalWrite (VY2, HIGH);
      lcd.setCursor  (1, 0);
      lcd.print ("ABAJO   ");
    }
    if (p2 == LOW) {
      estadoy = 0;
    }
    if (fcy1 == LOW) {
      estadoy = 0;
    }
    if (p1 == HIGH) {
      estadoy = 0;
    }
    break;

    case 2:
    digitalWrite (LED1, HIGH);
    contadory = millis () - cp2;
    if (contadory < 3000) {
    digitalWrite (VY3, HIGH);
    lcd.setCursor (1, 0);
    lcd.print ("arriba  ");
    }
    if (contadory > 3000) {
      digitalWrite (VY4, HIGH);
      lcd.setCursor (1, 0);
      lcd.print ("ARRIBA  ");
    }
    if (p1 == LOW) {
      estadoy = 0;
    }
    if (fcy2 == LOW) {
      estadoy = 0;
    }
    if (p2 == HIGH) {
      estadoy = 0;
    }
    break;
  }
  
  switch (estadox) {
    case 0:
    digitalWrite (LED2, LOW);
    digitalWrite (VX1, LOW);
    digitalWrite (VX2, LOW);
    digitalWrite (VX3, LOW);
    digitalWrite (VX4, LOW);
    lcd.setCursor (9, 0);
    lcd.print (" M2Paro");
    cp3 = 0;
    cp4 = 0;
    if (ps == HIGH) {
      estadox = 0;
      lcd.clear ();
      lcd.setCursor (1, 0);
      lcd.print ("EMERGENCIA");
    }
    if (ps == LOW) {
      if (fcx2 == HIGH) {
        if (p3 == LOW && p4 == HIGH) {
          estadox = 1;
          cp3 = millis ();
        }
      }
      if (fcx1 == HIGH) {
        if (p4 == LOW && p3 == HIGH) {
          estadox = 2;
          cp4 = millis ();
        }
      }
    }
    break;

    case 1:
    digitalWrite (LED2, HIGH);
    contadorx = millis () - cp3;
    if (contadorx < 3000) {
      digitalWrite (VX1, HIGH);
      lcd.setCursor  (8, 0);
      lcd.print ("derecha ");
    }
    if (contadorx > 3000) {
      digitalWrite (VX2, HIGH);
      lcd.setCursor  (8, 0);
      lcd.print ("DERECHA ");
    }
    if (p4 == LOW) {
      estadox = 0;
    }
    if (fcx2 == LOW) {
      estadox = 0;
    }
    if (p3 == HIGH) {
      estadox = 0;
    }
    break;

    case 2:
    digitalWrite (LED2, HIGH);
    contadorx = millis () - cp4;
    if (contadorx < 3000) {
      digitalWrite (VX3, HIGH);
      lcd.setCursor (7, 0);
      lcd.print ("izquierda");
    }
    if (contadorx > 3000) {
      digitalWrite (VX4, HIGH);
      lcd.setCursor (7, 0);
      lcd.print ("IZQUIERDA");
    }
    if (p3 == LOW) {
      estadox = 0;
    }
    if (fcx1 == LOW) {
      estadox = 0;
    }
    if (p4 == HIGH) {
      estadox = 0;
    }
    break;
  }


  switch (estadoz) {
    case 0:
    digitalWrite (LED3, LOW);
    digitalWrite (VZ1, LOW);
    digitalWrite (VZ2, LOW);
    digitalWrite (VZ3, LOW);
    digitalWrite (VZ4, LOW);
    lcd.setCursor (1, 1);
    lcd.print ("M3Paro  ");
    cp5 = 0;
    cp6 = 0;
    if (ps == HIGH) {
      estadoz = 0;
      lcd.clear ();
      lcd.setCursor (1, 0);
      lcd.print ("EMERGENCIA");
    }
    if (ps == LOW) {
      if (fcz1 == HIGH) {
        if (p5 == LOW && p6 == HIGH) {
          estadoz = 1;
          cp5 = millis ();
        }
      }
      if (fcz2 == HIGH) {
        if (p6 == LOW && p5 == HIGH) {
          estadoz = 2;
          cp6 = millis ();
        }
      }
    }
    break;

    case 1:
    digitalWrite (LED3, HIGH);
    contadorz = millis () - cp5;
    if (contadorz < 3000) {
      digitalWrite (VZ1, HIGH);
      lcd.setCursor  (1, 1);
      lcd.print ("adelante");
    }
    if (contadorz > 3000) {
      digitalWrite (VZ2, HIGH);
      lcd.setCursor  (1, 1);
      lcd.print ("ADELANTE");
    }
    if (p6 == LOW) {
      estadoz = 0;
    }
    if (fcz1 == LOW) {
      estadoz = 0;
    }
    if (p5 == HIGH) {
      estadoz = 0;
    }
    break;

    case 2:
    digitalWrite (LED3, HIGH);
    contadorz = millis () - cp6;
    if (contadorz < 3000) {
      digitalWrite (VZ3, HIGH);
      lcd.setCursor (1, 1);
      lcd.print ("atras   ");
    }
    if (contadorz > 3000) {
      digitalWrite (VZ4, HIGH);
      lcd.setCursor (1, 1);
      lcd.print ("ATRAS   ");
    }
    if (p5 == LOW) {
      estadoz = 0;
    }
    if (fcz2 == LOW) {
      estadoz = 0;
    }
    if (p6 == HIGH) {
      estadoz = 0;
    }
    break;
  }
}
void MANDO(){
  if(mando.available()){
    mando.read(datos, sizeof(datos));
    #ifdef SERIAL
    for(int i=0; i <= ((sizeof(datos))-1); i++){
        Serial.print(datos[i]);
    }
    Serial.print("\n");
    #endif
  }
}
