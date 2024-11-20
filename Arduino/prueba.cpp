#include Arduino.h
#include <BluetoothSerial.h>  

BluetoothSerial SerialBT;  

const int motorPins[3][2] = {
  {3, 4},  // Dirección-Step del motor 1
  {5, 6},  // Dirección-Step del motor 2
  {7, 8}   // Dirección-Step del motor 3
};

int motorSeleccionado = -1; 

void setup() {
  Serial.begin(9600);        
  SerialBT.begin("ESP32_SCARA");  

  for (int i = 0; i < 3; i++) {
    pinMode(motorPins[i][0], OUTPUT);
    pinMode(motorPins[i][1], OUTPUT);
  }

  Serial.println("ESP32 listo para conectar por Bluetooth...");
}

void loop() {
  if (SerialBT.available()) { 
    char command = SerialBT.read(); 

    if (motorSeleccionado != -1) {
      switch (command) {
        case 'F': 
          moverMotor(true);
          break;
        case 'B':  
          moverMotor(false); 
          break;
        default:
          Serial.println("Comando no reconocido para movimiento");
          break;
      }
    } else {
      switch (command) {
        case '1': 
          motorSeleccionado = 0;  
          Serial.println("Motor 1 seleccionado");
          break;
        case '2':
          motorSeleccionado = 1;  
          Serial.println("Motor 2 seleccionado");
          break;
        case '3':
          motorSeleccionado = 2;  
          Serial.println("Motor 3 seleccionado");
          break;
        default:
          Serial.println("Comando no reconocido para selección de motor");
          break;
      }
    }
  }
}

void moverMotor(bool adelante) {
  if (motorSeleccionado < 0) {
    Serial.println("Ningún motor seleccionado");
    return;
  }

  int dirPin = motorPins[motorSeleccionado][0];
  int stepPin = motorPins[motorSeleccionado][1];

  
  digitalWrite(dirPin, adelante ? HIGH : LOW); 
  
  Serial.print("Moviendo Motor ");
  Serial.print(motorSeleccionado + 1); 
  Serial.print(adelante ? " hacia adelante" : " hacia atrás");
  
 
  for (int i = 0; i < 200; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000);
  }
}

*/