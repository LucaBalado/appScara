import React, { useEffect, useState } from 'react';
import { View, Text, Button, Alert } from 'react-native';
import { BleManager } from 'react-native-ble-plx';

const App = () => {
  const [manager] = useState(new BleManager());
  const [device, setDevice] = useState(null);

  useEffect(() => {
    return () => {
      manager.destroy();
    };
  }, [manager]);

  const connectToDevice = async () => {
    const device = await manager.connectToDevice('');  // Poner aca la direccion MAC de la ESP32
    setDevice(device);
    console.log('Conectado al dispositivo');
  };

  const sendCommand = (command) => {
    if (device) {
      device.writeCharacteristicWithResponseForService(
        '',  // Servicio Bluetooth (modificar según el ESP32)
        '',  // Característica de Bluetooth (modificar según el ESP32)
        command
      ).then(() => {
        console.log('Comando enviado:', command);
      }).catch((error) => {
        console.error('Error al enviar comando:', error);
        Alert.alert('Error', 'No se pudo enviar el comando');
      });
    }
  };

  return (
    <View>
      <Text>Control de Robot SCARA</Text>
      <Button title="Conectar al ESP32" onPress={connectToDevice} />
      <Button title="Motor 1 Adelante" onPress={() => sendCommand('1F')} />
      <Button title="Motor 1 Atrás" onPress={() => sendCommand('1B')} />
    </View>
  );
};

export default App;