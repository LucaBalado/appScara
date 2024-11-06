const express = require('express');
const path = require('path');

const app = express();
const port = 3000; // Puerto en el que el servidor escuchará

// Sirve los archivos estáticos (HTML, CSS, JS) desde la carpeta "public"
app.use(express.static(path.join(__dirname, 'public')));

// Ruta principal que devuelve el archivo HTML
app.get('/', (req, res) => {
  res.sendFile(path.join(__dirname, 'index.html'));
});

// Inicia el servidor en el puerto 3000
app.listen(port, () => {
  console.log(`Servidor en http://localhost:${port}`);
});
