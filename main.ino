#include <WiFi.h>
#include <WebServer.h>
#include <SPIFFS.h>

const char *ssid = "pv10";
const char *password = "12345678";

WebServer server(80);

  void handleRoot() {
    Serial.println("logging");
    File file = SPIFFS.open("/index.html", "r");
    if (!file) {
      server.send(404, "text/plain", "File not found");
      return;
    }

    server.streamFile(file, "text/html");
    file.close();
  }


  void handleCustomCSS() {
    File file = SPIFFS.open("/css/style.css", "r");
    if (!file) {
      server.send(404, "text/plain", "File not found");
      return;
    }

    server.streamFile(file, "text/css");
    file.close();
  }


  void handleDashboardJS() {
    File file = SPIFFS.open("/js/dashboard.js", "r");
    if (!file) {
      server.send(404, "text/plain", "File not found");
      return;
    }
    server.streamFile(file, "application/javascript");
    file.close();
  }



  void handleMISCJS() {
    File file = SPIFFS.open("/js/misc.js", "r");
    if (!file) {
      server.send(404, "text/plain", "File not found");
      return;
    }
    server.streamFile(file, "application/javascript");
    file.close();
  }


  void handleTODOJS() {
    File file = SPIFFS.open("/js/todolist.js", "r");
    if (!file) {
      server.send(404, "text/plain", "File not found");
      return;
    }
    server.streamFile(file, "application/javascript");
    file.close();
  }



  void handleVendorBundleCSS() {
    File file = SPIFFS.open("/vendors/css/vendor.bundle.base.css", "r");
    if (!file) {
      server.send(404, "text/plain", "File not found");
      return;
    }

    server.streamFile(file, "text/css");
    file.close();
  }



  void handleVendorBundleJS() {
    File file = SPIFFS.open("/vendors/js/vendor.bundle.base.js", "r");
    if (!file) {
      server.send(404, "text/plain", "File not found");
      return;
    }

    server.streamFile(file, "application/javascript");
    file.close();
  }



  void handleJVectorWMEJS() {
    File file = SPIFFS.open("/vendors/jvectormap/jquery-jvectormap-world-mil-en.js", "r");
    if (!file) {
      server.send(404, "text/plain", "File not found");
      return;
    }

    server.streamFile(file, "application/javascript");
    file.close();
  }




  void handleJVMCSS() {
    File file = SPIFFS.open("/vendors/jvectormap/jquery-jvectormap.css", "r");
    if (!file) {
      server.send(404, "text/plain", "File not found");
      return;
    }

    server.streamFile(file, "text/css");
    file.close();
  }




  void handleJVectorJS() {
    File file = SPIFFS.open("/vendors/jvectormap/jquery-jvectormap.js", "r");
    if (!file) {
      server.send(404, "text/plain", "File not found");
      return;
    }

    server.streamFile(file, "application/javascript");
    file.close();
  }









void setup() {
  Serial.begin(115200);
  WiFi.softAP(ssid, password);
  delay(100);
  // Initialize SPIFFS
  if (!SPIFFS.begin(true)) {
    Serial.println("An error occurred while mounting SPIFFS");
    return;
  }
  Serial.println("SPIFFS mounted successfully");
server.on("/", handleRoot);
  server.on("/css/style.css", handleCustomCSS);
  server.on("/js/dashboard.js", handleDashboardJS);
  server.on("/js/misc.js", handleMISCJS);
  server.on("/js/todolist.js", handleTODOJS);
  server.on("/vendors/css/vendor.bundle.base.css", handleVendorBundleCSS);
  server.on("/vendors/js/vendor.bundle.base.js", handleVendorBundleJS);
  server.on("/vendors/jvectormap/jquery-jvectormap-world-mil-en.js", handleJVectorWMEJS);
    server.on("/vendors/jvectormap/jquery-jvectormap.css", handleJVMCSS);
    server.on("/vendors/jvectormap/jquery-jvectormap.js", handleJVectorJS);

  



  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
