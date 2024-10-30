#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>

// Replace with your network credentials
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

// Flight plan structure
struct FlightPlan {
  String departure;
  String destination;
  String waypoints[5]; // Example: up to 5 waypoints
  int waypointCount;
};

// Flight plan storage
FlightPlan currentPlan;
ESP8266WebServer server(80);

// Function to initialize hardware
void initializeHardware() {
  Serial.begin(115200);
  EEPROM.begin(512);
}

// Function to connect to Wi-Fi
void connectWiFi() {
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");
  
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 10) {
    delay(500);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println(" Connected!");
  } else {
    Serial.println(" Failed to connect.");
  }
}

// Function to load a flight plan from EEPROM
void loadFlightPlan() {
  EEPROM.get(0, currentPlan);
}

// Function to save a flight plan to EEPROM
void saveFlightPlan() {
  EEPROM.put(0, currentPlan);
  EEPROM.commit();
}

// Function to get the HTML for the web interface
String getHTML() {
  String html = "<html><body><h1>Flight Management System</h1>";
  
  // Display current flight plan
  html += "<h2>Current Flight Plan</h2>";
  html += "<p>Departure: " + currentPlan.departure + "</p>";
  html += "<p>Destination: " + currentPlan.destination + "</p>";
  html += "<h3>Waypoints:</h3><ul>";
  for (int i = 0; i < currentPlan.waypointCount; i++) {
    html += "<li>" + currentPlan.waypoints[i] + "</li>";
  }
  html += "</ul>";

  // Form to update the flight plan
  html += "<h2>Load New Flight Plan</h2>";
  html += "<form action=\"/update\" method=\"POST\">";
  html += "Departure: <input type=\"text\" name=\"departure\" required><br>";
  html += "Destination: <input type=\"text\" name=\"destination\" required><br>";
  for (int i = 0; i < 5; i++) {
    html += "Waypoint " + String(i + 1) + ": <input type=\"text\" name=\"waypoint" + String(i) + "\"><br>";
  }
  html += "<input type=\"submit\" value=\"Update Flight Plan\">";
  html += "</form></body></html>";
  
  return html;
}

// Handle root URL
void handleRoot() {
  server.send(200, "text/html", getHTML());
}

// Handle flight plan update
void handleUpdate() {
  if (server.hasArg("departure") && server.hasArg("destination")) {
    currentPlan.departure = server.arg("departure");
    currentPlan.destination = server.arg("destination");
    currentPlan.waypointCount = 0;

    // Load waypoints
    for (int i = 0; i < 5; i++) {
      String waypoint = server.arg("waypoint" + String(i));
      if (waypoint.length() > 0) {
        currentPlan.waypoints[currentPlan.waypointCount++] = waypoint;
      }
    }

    saveFlightPlan();
    Serial.println("Flight plan updated:");
    Serial.println("Departure: " + currentPlan.departure);
    Serial.println("Destination: " + currentPlan.destination);
    for (int i = 0; i < currentPlan.waypointCount; i++) {
      Serial.println("Waypoint " + String(i + 1) + ": " + currentPlan.waypoints[i]);
    }

    server.send(200, "text/html", "<h1>Flight Plan Updated!</h1><a href=\"/\">Back</a>");
  } else {
    server.send(400, "text/html", "<h1>Bad Request</h1>");
  }
}

// Setup function
void setup() {
  initializeHardware();
  connectWiFi();

  // Load existing flight plan from EEPROM
  loadFlightPlan();
  
  server.on("/", handleRoot);
  server.on("/update", HTTP_POST, handleUpdate);
  server.begin();
  Serial.println("HTTP server started");
}

// Loop function
void loop() {
  server.handleClient();
}
