document.addEventListener("deviceready", () => {
  bluetoothSerial.isEnabled(
      () => {
          console.log("Bluetooth está habilitado");
      },
      () => {
          alert("Por favor, habilita Bluetooth");
      }
  );
});

// Conectar al módulo Bluetooth (debes poner la dirección de tu módulo Bluetooth)
function connectBluetooth() {
  bluetoothSerial.connect(
      "direccion_del_modulo", // Aquí va la dirección del módulo Bluetooth, ej: "00:11:22:33:44:55"
      () => console.log("Conectado al módulo Bluetooth"),
      () => alert("No se pudo conectar al módulo Bluetooth")
  );
}

// Función para mover el motor según el número de motor y la dirección
function moveMotor(motorNumber, direction) {
  let command = "";
  switch (motorNumber) {
      case 1:
          command = direction === 'F' ? 'F' : 'B'; // Adelante o atrás
          break;
      case 2:
          command = direction === 'F' ? 'F' : 'B';
          break;
      case 3:
          command = direction === 'F' ? 'F' : 'B';
          break;
      default:
          console.error("Motor no válido");
          return;
  }

  // Enviar el comando vía Bluetooth al Arduino
  bluetoothSerial.write(command, 
      () => console.log(`Comando ${command} enviado para el motor ${motorNumber}`),
      () => alert("Error enviando comando")
  );
}

// Función para manejar el click en los botones de dirección para cada motor
function setMotorControl() {
  // Agregar eventos a los botones de control de los motores
  document.getElementById("motor1-forward").addEventListener("click", () => moveMotor(1, 'F'));
  document.getElementById("motor1-backward").addEventListener("click", () => moveMotor(1, 'B'));
  
  document.getElementById("motor2-forward").addEventListener("click", () => moveMotor(2, 'F'));
  document.getElementById("motor2-backward").addEventListener("click", () => moveMotor(2, 'B'));
  
  document.getElementById("motor3-forward").addEventListener("click", () => moveMotor(3, 'F'));
  document.getElementById("motor3-backward").addEventListener("click", () => moveMotor(3, 'B'));
}

// Llamar a la función de control de los motores al cargar la página
window.onload = function() {
  setMotorControl();
};
