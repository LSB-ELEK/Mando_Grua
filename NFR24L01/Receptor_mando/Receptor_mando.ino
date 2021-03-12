#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
 
//Declaremos los pines CE y el CSN
#define CE_PIN 9
#define CSN_PIN 10
 
//Variable con la dirección del canal que se va a leer
byte direccion[5] ={'M','a','n','d','o'}; 

//creamos el objeto radio (NRF24L01)
RF24 radio(CE_PIN, CSN_PIN);

bool recivido[12];

void setup() {
  //inicializamos el NRF24L01 
  radio.begin();
  //inicializamos el puerto serie
  Serial.begin(9600); 
  
  //Abrimos el canal de Lectura
  radio.openReadingPipe(1, direccion);
  
    //empezamos a escuchar por el canal
  radio.startListening();
}

void loop() {
    while(!radio.available()){
      
    }
    //if(radio.available()){
        radio.read(recivido, sizeof(recivido));
        
        Serial.print(recivido[0]);
        Serial.print(recivido[1]);
        Serial.print(recivido[2]);
        Serial.print(recivido[3]);
        Serial.print(recivido[4]);
        Serial.print(recivido[5]);
        Serial.print(recivido[6]);
        Serial.print(recivido[7]);
        Serial.print(recivido[8]);
        Serial.print(recivido[9]);
        Serial.print(recivido[10]);
        Serial.println(recivido[11]);
    //}else{
        //Serial.println("no hay datos");
    //}
//delay(1000);
}
