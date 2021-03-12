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

//variable de datos
bool datos[12];

//variable para cada cambio de estado
bool estado_pulsa = false;
bool enviar;

unsigned long ant_millis;

void setup() {
    //inicializamos el NRF24L01 
    radio.begin();
    
    Serial.begin(9600);

    //Abrimos un canal de escritura
    radio.openWritingPipe(direccion);
    ant_millis = millis();
}


void loop() {


    if(MANDO.getKeys())
    {
        for(int i=0; i<LIST_MAX; i++){
            if(MANDO.key[i].stateChanged){
                switch(MANDO.key[i].kstate) {
                    case PRESSED:
                        estado_pulsa = true;
                        enviar = true;
                        break;
                    case HOLD:
                        estado_pulsa = true;
                        break;
                    case RELEASED:
                        estado_pulsa = false;
                        enviar = true;
                        break;
                    case IDLE:
                        estado_pulsa = false;
                        break;
                }

                switch(MANDO.key[i].kchar){
                    case 'A':
                        datos[0] = estado_pulsa;
                        break;
                    case 'B':
                        datos[1] = estado_pulsa;
                        break;
                    case 'C':
                        datos[2] = estado_pulsa;
                        break;
                    case 'D':
                        datos[3] = estado_pulsa;
                        break;
                    case 'E':
                        datos[4] = estado_pulsa;
                        break;
                    case 'F':
                        datos[5] = estado_pulsa;
                        break;
                    case 'G':
                        datos[6] = estado_pulsa;
                        break;
                    case 'H':
                        datos[7] = estado_pulsa;
                        break;
                    case 'I':
                        datos[8] = estado_pulsa;
                        break;
                    case 'J':
                        datos[9] = estado_pulsa;
                        break;
                    case 'K':
                        datos[10] = estado_pulsa;
                        break;
                    case 'L':
                        datos[11] = estado_pulsa;
                        break;
                   
                }
                for(int e = 0; e<=11; e++){
                    Serial.print(datos[e]);
                }
                Serial.print("\n\n");    
            }
            if(enviar){
                enviar = false;
                bool ok = radio.write(datos, sizeof(datos));
                if(ok){
                    Serial.println("Enviado");
                }
            }
        }
    }
}
