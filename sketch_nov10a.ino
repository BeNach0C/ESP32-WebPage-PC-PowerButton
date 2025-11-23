#include <WiFi.h>
#include <WebServer.h>

// ===== CONFIGURACIÓN DE RED =====
const char* ssid = "Wifiname";          // Cambia por el nombre de tu WiFi
const char* password = "WifiPassword";  // Cambia por la clave tu WiFi
// ===== IP Fija =====
IPAddress local_IP(192, 168, 1, 130);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

// ===== CONFIGURACIÓN DEL LOGIN =====
const String accessPassword = "PASSWORD"; // Cambia si quieres otra contraseña

// ===== CONFIGURACIÓN DE PINES =====
const int signalPin = 4;   // GPIO4 para activar el transistor
const int pulseTime = 500; // ms de pulso

// ===== SERVIDOR WEB =====
WebServer server(8080);

// ===== HTML LOGIN =====
String loginPage = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <title>ESP32 Login</title>
  <style>
    body {
      display: flex;
      justify-content: center;
      align-items: center;
      height: 100vh;
      background-color: #121212;
      color: white;
      font-family: Arial, sans-serif;
    }
    .login-box {
      background-color: #1f1f1f;
      padding: 40px;
      border-radius: 20px;
      text-align: center;
      box-shadow: 0 0 20px rgba(0,0,0,0.5);
    }
    input[type="password"] {
      width: 250px;
      padding: 15px;
      margin: 10px 0;
      border: none;
      border-radius: 10px;
      font-size: 16px;
      text-align: center;
    }
    button {
      padding: 15px 30px;
      border: none;
      border-radius: 10px;
      background-color: #4CAF50;
      color: white;
      font-size: 16px;
      cursor: pointer;
    }
    button:hover {
      background-color: #45a049;
    }
  </style>
</head>
<body>
  <div class="login-box">
    <h2>Iniciar PC</h2>
    <form action="/login" method="POST">
      <input type="password" name="password" placeholder="Contraseña"><br>
      <button type="submit">Entrar</button>
    </form>
  </div>
</body>
</html>
)rawliteral";

// ===== FUNCIONES WEB =====
void handleRoot() {
  server.send(200, "text/html", loginPage);
}

void handleLogin() {
  if (server.hasArg("password")) {
    String pass = server.arg("password");
    if (pass == accessPassword) {
      Serial.println("Contraseña correcta. Enviando pulso...");
      digitalWrite(signalPin, HIGH);
      delay(pulseTime);
      digitalWrite(signalPin, LOW);
      server.send(200, "text/html", "<html><body><h2>PC Encendido</h2><a href='/'>Volver</a></body></html>");
      return;
    }
  }
  Serial.println("Intento con contraseña incorrecta.");
  server.send(200, "text/html", "<html><body><h2>Contraseña incorrecta</h2><a href='/'>Intentar de nuevo</a></body></html>");
}

// ===== COMANDOS SERIAL =====
void handleSerialCommands(String cmd) {
  cmd.trim();
  cmd.toLowerCase();

  if (cmd == "help") {
    Serial.println("\nComandos disponibles:");
    Serial.println("  showip   - Muestra la IP actual");
    Serial.println("  ipconfig - Estado de red y señal");
    Serial.println("  scan     - Escanear redes WiFi cercanas");
    Serial.println("  restart  - Reinicia el ESP32");
    Serial.println("  help     - Lista de comandos");
  }
  else if (cmd == "showip") {
    Serial.print("IP actual: ");
    Serial.println(WiFi.localIP());
  }
  else if (cmd == "ipconfig") {
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("Estado: Conectado");
      Serial.print("SSID: ");
      Serial.println(WiFi.SSID());
      Serial.print("RSSI: ");
      Serial.println(WiFi.RSSI());
      Serial.print("IP: ");
      Serial.println(WiFi.localIP());
    } else {
      Serial.println("Estado: No conectado");
    }
  }
  else if (cmd == "scan") {
    Serial.println("Escaneando redes...");
    int n = WiFi.scanNetworks();
    if (n == 0) {
      Serial.println("No se encontraron redes");
    } else {
      for (int i = 0; i < n; i++) {
        Serial.print(i + 1);
        Serial.print(": ");
        Serial.print(WiFi.SSID(i));
        Serial.print(" (");
        Serial.print(WiFi.RSSI(i));
        Serial.println(" dBm)");
      }
    }
  }
  else if (cmd == "restart") {
    Serial.println("Reiniciando ESP32...");
    ESP.restart();
  }
  else if (cmd.length() > 0) {
    Serial.println("Comando no reconocido. Usa 'help'.");
  }
}

// ===== SETUP =====
void setup() {
  Serial.begin(115200);
  delay(1500);
  Serial.println("\n===== Iniciando ESP32 =====");

  pinMode(signalPin, OUTPUT);
  digitalWrite(signalPin, LOW);

  // Config IP estática
  Serial.println("Configurando IP estática...");
  if (!WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("Error al configurar IP estática");
  }

  // Conexión WiFi
  Serial.print("Conectando a WiFi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  unsigned long startAttemptTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000) {
    Serial.print(".");
    delay(500);
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi conectado correctamente");
    Serial.print("IP asignada: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nNo se pudo conectar a WiFi");
  }

  // Rutas web
  server.on("/", handleRoot);
  server.on("/login", HTTP_POST, handleLogin);

  server.begin();
  Serial.println("Servidor web iniciado en el puerto 80");
  Serial.println("Escribe 'help' en el monitor serial para ver comandos.");
}

// ===== LOOP =====
void loop() {
  server.handleClient();

  // Leer comandos del serial
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    handleSerialCommands(cmd);
  }
}