//  Fuente de información
//https://www.naylampmechatronics.com/blog/16_Tutorial-b%C3%A1sico-NRF24L01-con-Arduino.html


//        Comunicación
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//Declaremos los pines CE y el CSN
#define CE_PIN A2
#define CSN_PIN A1

/*    Conexionado de los pines
/*   
*         GND = GND   
*         VCC = 3.3V
*         CE = A0
*         CSN = A1
*         SCLK = 15
*         MISO = 14
*         MOSI = 16
*/

//Variable con la dirección del canal por donde se va a transmitir
byte direccion[5] ={'M','a','n','d','o'};

//creamos el objeto radio (NRF24L01)
RF24 radio(CE_PIN, CSN_PIN);

//vector con los datos a enviar
bool datos[12];

//        Botones

#include <Keypad.h>

const byte ROWS = 6; //numero de FILAS
const byte COLS = 2; //numero de COLUMNAS

char KeyMap[ROWS][COLS] = {
  {'A','B'},
  {'C','D'},
  {'E','F'},
  {'G','H'},
  {'I','J'},
  {'K','L'}
};
byte rowPins[ROWS] = {9, 8, 7, 6, 5, 4,};  //pinout de las FILAS
byte colPins[COLS] = {3, 2};              //pinout de las COLUMNAS

Keypad MANDO = Keypad( makeKeymap(KeyMap), rowPins, colPins, ROWS, COLS); 



void setup()
{
  //inicializamos el NRF24L01 
  radio.begin();
  //inicializamos el puerto serie
  Serial.begin(9600); 
 
//Abrimos un canal de escritura
 radio.openWritingPipe(direccion);
 
}
 
void loop(){ 
      
//      Comprueba las teclas 14 veces
  /*char tecla = MANDO.getKey();
        if(tecla){
      Serial.println(tecla);*/
    for(int i = 1;i<6;i++){
       char tecla = MANDO.getKey();
       //Serial.print("hola for");
        if (tecla != NO_KEY){
           if(tecla == 'A'){
              datos[0] = true;
           }else if(tecla == 'B'){
              datos[1] = true;
           }if(tecla == 'C'){
              datos[2] = true;
           }else if(tecla == 'D'){
              datos[3] = true;
           }if(tecla == 'E'){
              datos[4] = true;
           }else if(tecla == 'F'){
              datos[5] = true;
           }if(tecla == 'G'){
              datos[6] = true;
           }else if(tecla == 'H'){
              datos[7] = true;
           }if(tecla == 'I'){
              datos[8] = true;
           }else if(tecla == 'J'){
              datos[9] = true;
           }if(tecla == 'K'){
              datos[10] = true;
           }else if(tecla == 'L'){
              datos[11] = true;
           }
        }
    }
    
       /*Serial.print("BOTON 1 = ");Serial.println(datos[0]);
       Serial.print("BOTON 2 = ");Serial.println(datos[1]);
       Serial.print("BOTON 3 = ");Serial.println(datos[2]);
       Serial.print("BOTON 4 = ");Serial.println(datos[3]);
       Serial.print("BOTON 5 = ");Serial.println(datos[4]);
       Serial.print("BOTON 6 = ");Serial.println(datos[5]);
       Serial.print("BOTON 7 = ");Serial.println(datos[6]);
       Serial.print("BOTON 8 = ");Serial.println(datos[7]);
       Serial.print("BOTON 9 = ");Serial.println(datos[8]);
       Serial.print("BOTON 10 = ");Serial.println(datos[9]);
       Serial.print("BOTON 11 = ");Serial.println(datos[10]);
       Serial.print("BOTON 12 = ");Serial.println(datos[11]);
       Serial.print("BOTON 13 = ");Serial.println(datos[12]);
       Serial.print("BOTON 14 = ");Serial.println(datos[13]);
       delay(10);
    
    /*
//        Envia y comprueba el envio
    bool ok = radio.write(datos, sizeof(datos));
//        Reportamos los datos enviados 
    if(ok)
    {
       Serial.print("BOTON 1");Serial.println(datos[0]);
       Serial.print("BOTON 2");Serial.println(datos[1]);
       Serial.print("BOTON 3");Serial.println(datos[2]);
       Serial.print("BOTON 4");Serial.println(datos[3]);
       Serial.print("BOTON 5");Serial.println(datos[4]);
       Serial.print("BOTON 6");Serial.println(datos[5]);
       Serial.print("BOTON 7");Serial.println(datos[6]);
       Serial.print("BOTON 8");Serial.println(datos[7]);
       Serial.print("BOTON 9");Serial.println(datos[8]);
       Serial.print("BOTON 10");Serial.println(datos[9]);
       Serial.print("BOTON 11");Serial.println(datos[10]);
       Serial.print("BOTON 12");Serial.println(datos[11]);
       Serial.print("BOTON 13");Serial.println(datos[12]);
       Serial.print("BOTON 14");Serial.println(datos[13]);
       Serial.println("===============");Serial.println();
    }
    else{
       Serial.println("no se ha podido enviar");
    }*/
//      Pone los 12 datos a 0
    for(int e = 0; e<=11; e++){
        Serial.print(datos[e]);
        datos[e] = false;
    }
    Serial.println();
}
