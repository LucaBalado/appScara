#include Arduino.h
#include SoftwareSerial.h

SoftwareSerial Bluetooth(10, 11); // RX, TX para Bluetooth

// Definimos los pines para los motores
const int motorPins[3][2] = {
  {3, 4},  // Motor 1: {Dirección, Step}
  {5, 6},  // Motor 2: {Dirección, Step}
  {7, 8}   // Motor 3: {Dirección, Step}
};


int motorSeleccionado = -1;

void setup() {
  Serial.begin(9600);       // Para monitorear en el Serial Monitor
  Bluetooth.begin(9600);    // Inicializar comunicación Bluetooth

  // Definir los pines de los motores como salidas
  for (int i = 0; i < 3; i++) {
    pinMode(motorPins[i][0], OUTPUT); // Pin de dirección
    pinMode(motorPins[i][1], OUTPUT); // Pin de paso
  }
}

void loop() {
  if (Bluetooth.available()) {
    char command = Bluetooth.read();  // Leer el comando desde el Bluetooth

    // Mover motor solo si se ha seleccionado uno
    if (motorSeleccionado != -1) {
      switch (command) {
        case 'F':  // Comando para mover hacia adelante
          moverMotor(true);  // Mover el motor seleccionado hacia adelante
          break;
        case 'B':  // Comando para mover hacia atrás
          moverMotor(false); // Mover el motor seleccionado hacia atrás
          break;
        default:
          Serial.println("Comando no reconocido para movimiento");
          break;
      }
    } else {
      // Selección de motor
      switch (command) {
        case '1': 
          motorSeleccionado = 0;  // Seleccionar motor 1
          Serial.println("Motor 1 seleccionado");
          break;
        case '2':
          motorSeleccionado = 1;  // Seleccionar motor 2
          Serial.println("Motor 2 seleccionado");
          break;
        case '3':
          motorSeleccionado = 2;  // Seleccionar motor 3
          Serial.println("Motor 3 seleccionado");
          break;
        default:
          Serial.println("Comando no reconocido para selección de motor");
          break;
      }
    }
  }
}

// Función para mover el motor seleccionado
void moverMotor(bool adelante) {
  if (motorSeleccionado < 0) {
    Serial.println("Ningún motor seleccionado");
    return; // Salir de la función si no hay motor seleccionado
  }

  int dirPin = motorPins[motorSeleccionado][0];  
  int stepPin = motorPins[motorSeleccionado][1]; 

  // Configurar la dirección
  digitalWrite(dirPin, adelante ? HIGH : LOW); 
  
  Serial.print("Moviendo Motor ");
  Serial.print(motorSeleccionado + 1); 
  Serial.print(adelante ? " hacia adelante" : " hacia atrás");
  
  // Hacer el número de pasos deseados
  for (int i = 0; i < 200; i++) { // En este caso son 200 pasos
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000);
  }
}