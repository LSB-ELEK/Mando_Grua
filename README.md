# Mando_Grua
Conversión de mando industrial en mando inalámbrico mediante Arduino y el chip de comunicación NFR24l01.

<img src="https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Ftse1.mm.bing.net%2Fth%3Fid%3DOIP.4HBfNvu16CmaQU3-s2PuDAHaHa%26pid%3DApi&f=1" width="200" height="200" />

## Funcionamiento

Para hacer funcionar el mando necesitamos 2 chips NFR, 1 el cual funcionará como emisor y el otro que funcionará como receptor. Para hacer funcionar este chip con Arduino necesitamos 3 librerias, las cuales son la libreria para la comunicacion SPI, la libreria nRF24L01.h y por ultimo RF24.h. 

## Electrónica

### Materiales


Materiales | Cantidad
------------ | -------------
Arduino Nano | x1
Chip de comunicación NFR24l01 | x2
PowerBank | x1


### Esquema eléctrico

Conexionado del arduino nano
<img src="https://github.com/LSB-ELEK/Mando_Grua/blob/main/img/NANO.png?raw=true" width="200" height="200" />
Conexionado del emisor nfr
<img src="https://github.com/LSB-ELEK/Mando_Grua/blob/main/img/NRF24L01.png?raw=true" width="250" height="300" />
Conexionado de los pulsadores del mando
<img src="https://github.com/LSB-ELEK/Mando_Grua/blob/main/img/buttons.png?raw=true" width="200" height="400" />


### Programa de Arduino
