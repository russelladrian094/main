#include <WiFi.h>
#include <SPIFFS.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

const char *ssid = "pv10";
const char *password = "12345678";
const int sensorPin = 2; // Pin connected to the voltage sensor
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

void setup()
{
  Serial.begin(115200);
  WiFi.softAP(ssid, password);
  delay(100);
  // Initialize SPIFFS
  if (!SPIFFS.begin(true))
  {
    Serial.println("An error occurred while mounting SPIFFS");
    return;
  }
  Serial.println("SPIFFS mounted successfully");
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/index.html", "text/html"); });
  server.on("/css/style.css", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/css/style.css", "text/css"); });
  server.on("/js/dashboard.js", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/js/dashboard.js", "application/javascript"); });
  server.on("/js/misc.js", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/js/misc.js", "application/javascript"); });
  server.on("/js/todolist.js", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/js/todolist.js", "application/javascript"); });
  server.on("/vendors/css/vendor.bundle.base.css", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/vendors/css/vendor.bundle.base.css", "text/css"); });
  server.on("/vendors/js/vendor.bundle.base.js", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/vendors/js/vendor.bundle.base.js", "application/javascript"); });
  server.on("/vendors/jvectormap/jquery-jvectormap-world-mil-en.js", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/vendors/jvectormap/jquery-jvectormap-world-mil-en.js", "application/javascript"); });
  server.on("/vendors/jvectormap/jquery-jvectormap.css", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/vendors/jvectormap/jquery-jvectormap.css", "text/css"); });
  server.on("/vendors/jvectormap/jquery-jvectormap.js", handleJVectorJS);
  server.on("/vendors/jvectormap/jquery-jvectormap.js", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/vendors/jvectormap/jquery-jvectormap.js", "application/javascript"); });
  ws.onEvent(onEvent);
  server.addHandler(&ws);
  server.begin();
  Serial.println("HTTP server started");
}

void loop()
{
  server.handleClient();
  int sensorValue = analogRead(sensorPin);           // Read the voltage sensor
  float voltage = sensorValue * (3.3 / 4095.0) * 10; // Convert ADC value to voltage (3.3V is ESP32 maximum voltage)
  Serial.print("Voltage: ");
  Serial.print(voltage, 1); // Print voltage with 2 decimal places
  Serial.println(" V");
  // Send battery data to connected clients
  ws.textAll(String(voltage));
  ws.cleanupClients();

  delay(50); // Update interval
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
{
  // Handle WebSocket events
}
