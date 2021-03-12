
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

String msg;

bool datos[12];
bool estado_pulsa = false;

void setup() {
    Serial.begin(9600);
    msg = "";
}


void loop() {


    if(MANDO.getKeys())
    {
        for(int i=0; i<LIST_MAX; i++)
        {
            if(MANDO.key[i].stateChanged)
            {
                switch (MANDO.key[i].kstate) {
                    case PRESSED:
                    msg = " PRESSED.";
                    estado_pulsa = true;
                break;
                    case HOLD:
                    msg = " HOLD.";
                    estado_pulsa = true;
                break;
                    case RELEASED:
                    msg = " RELEASED.";
                    estado_pulsa = false;
                break;
                    case IDLE:
                    msg = " IDLE.";
                }
                //Serial.print("Key ");
                //Serial.print(MANDO.key[i].kchar);
                //Serial.println(msg);
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
        }
    }
}
