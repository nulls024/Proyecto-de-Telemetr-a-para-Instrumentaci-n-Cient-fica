#include <SPI.h>       // Librería para el protocolo de comunicación Serial Peripheral Interface.
#include <nRF24L01.h>   // Definiciones de registros del chip de radio.
#include <RF24.h>      // Librería principal para controlar el módulo.

// Creamos el objeto 'radio'. Los números (9, 10) corresponden a los pines CE y CSN.
// CE (Chip Enable): Activa el modo de transmisión/recepción.
// CSN (Chip Select Not): Le dice al módulo cuándo el Arduino le va a hablar por SPI.
RF24 radio(9, 10); 

// La 'dirección' es como el nombre de un canal de radio o una IP. 
// Ambos dispositivos deben tener la misma para escucharse.
const byte direccion[6] = "00001";

void setup() {
  radio.begin();               // Inicializa el hardware del módulo.
  
  // Abre un 'túnel' de escritura hacia la dirección que definimos arriba.
  radio.openWritingPipe(direccion); 
  
  // Define la potencia de transmisión. 
  // RF24_PA_MIN usa poca energía, ideal para pruebas en escritorio.
  // RF24_PA_MAX sería para cuando pongas el 'telescopio' en otra habitación.
  radio.setPALevel(RF24_PA_MIN); 
  
  // Apaga la escucha para que el módulo se concentre solo en transmitir.
  radio.stopListening(); 
}

void loop() {
  // El mensaje que vamos a enviar. En una práctica real, aquí pondrías 
  // los datos de tus sensores de temperatura o humedad.
  const char texto[] = "Señal INAOE OK";
  
  // 'radio.write' envía el paquete. Necesita la dirección del mensaje (&texto) 
  // y el tamaño en bytes (sizeof) para saber cuánto transmitir.
  radio.write(&texto, sizeof(texto));
  
  delay(1000); // Espera un segundo entre envíos.
}
