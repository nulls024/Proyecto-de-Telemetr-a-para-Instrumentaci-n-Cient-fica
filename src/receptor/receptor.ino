#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// En el ESP32 usamos pines distintos (4 y 5) por la distribución de su hardware.
RF24 radio(4, 5); 

const byte direccion[6] = "00001";

void setup() {
  // Iniciamos la comunicación serial a 115200 para ver los datos en la laptop.
  Serial.begin(115200); 
  
  radio.begin();
  
  // Abrimos el túnel de lectura en la posición 1 con nuestra dirección.
  radio.openReadingPipe(1, direccion); 
  
  radio.setPALevel(RF24_PA_MIN);
  
  // IMPORTANTE: Aquí le decimos que empiece a escuchar el aire.
  radio.startListening(); 
}

void loop() {
  // 'radio.available' es un método que devuelve 'true' si hay datos en el aire
  // esperando a ser leídos por nosotros.
  if (radio.available()) {
    
    // Creamos un contenedor (buffer) de 32 bytes para guardar el mensaje recibido.
    char texto[32] = ""; 
    
    // 'radio.read' saca el mensaje del módulo y lo mete en nuestra variable 'texto'.
    radio.read(&texto, sizeof(texto));
    
    // Imprimimos el resultado en el monitor serie.
    Serial.print("Recibido: ");
    Serial.println(texto);
  }
}
