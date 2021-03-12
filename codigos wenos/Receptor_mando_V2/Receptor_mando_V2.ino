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

//cantidad de datos a recivir
const int CANTIDAD = 12;  
bool recivido[CANTIDAD];


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
    while(!radio.available());  //Bloquear el codigo mientras no haya datos
//==============================    
    radio.read(recivido, sizeof(recivido));
    for(int i=0; i<=(CANTIDAD-1); i++){
        Serial.print(recivido[i]);
    }
    Serial.print("\n");
}
