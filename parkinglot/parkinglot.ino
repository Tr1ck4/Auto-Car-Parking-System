#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// WiFi hotspot information (phone hotspot)
const char* WIFI_SSID     = "vivo X200 Pro";
const char* WIFI_PASSWORD = "xiaolian";

// MQTT broker information (IP address of your laptop)
const char* MQTT_HOST = "192.168.155.109";
const uint16_t MQTT_PORT = 1883;

// MQTT client ID (must be unique in the broker)
const char* MQTT_CLIENT_ID = "esp8266-parking";

// MQTT topic used for communication
const char* TOPIC = "lab/parking";

// Create WiFi client and MQTT client
WiFiClient wifiClient;
PubSubClient mqtt(wifiClient);


// Parking slot state array
// 0 = free
// 1 = occupied
//2 = omw
int parkingSlots[] = {1, 0, 1, 0, 0, 1, 1, 0};
String instructions[] = {"2","02","002","0002","00002","000002","0000002","00000002"};

// Calculate the number of parking slots
const int SLOT_COUNT = sizeof(parkingSlots) / sizeof(parkingSlots[0]);


// Function to connect to WiFi
void connectWiFi() {

  // Set ESP8266 to station mode
  WiFi.mode(WIFI_STA);

  // Start connecting to the WiFi network
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  // Wait until the connection is established
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("[WIFI] Connected");
}


// Function to connect to the MQTT broker
void connectMQTT() {

  mqtt.setServer(MQTT_HOST, MQTT_PORT);

  while (!mqtt.connected()) {
    Serial.println("[MQTT] Connecting...");

    if (mqtt.connect(MQTT_CLIENT_ID)) {
      mqtt.subscribe(TOPIC);
      Serial.println("[MQTT] Connected and subscribed");
    } else {
      Serial.print("[MQTT] Failed, rc = ");
      Serial.println(mqtt.state());
      delay(1000);
    }
  }
}


// Function to find the nearest empty parking slot
int findNearestEmptySlot() {

  // Scan the parkingSlots array from the beginning
  for (int i = 0; i < SLOT_COUNT; i++) {

    // If the slot is free
    if (parkingSlots[i] == 0) {

      // Return the slot index
      return instructions[i];
    }
  }

  // If no empty slot exists, return -1
  return -1;
}


// MQTT callback function
// This function is triggered whenever a message is received
void mqttCallback(char* topic, byte* payload, unsigned int length) {

  // Convert MQTT payload to String
  String msg;

  for (unsigned int i = 0; i < length; i++) {
    msg += (char)payload[i];
  }

  msg.trim();

  Serial.print("[MQTT] Message arrived: ");
  Serial.println(msg);


  // Check whether the message is a parking request
  // Request format: req+mqttid
  if (msg.startsWith("req+")) {

    // Extract the vehicle mqtt ID
    String mqttid = msg.substring(4);
    mqttid.trim();

    // Find the nearest empty parking slot
    int num = findNearestEmptySlot();

    // Construct the response message
    // Format: res+slotNumber+mqttid
    String reply = "res+" + String(num) + "+" + mqttid;

    // Publish the response
    mqtt.publish(TOPIC, reply.c_str());

    Serial.print("[PUB] ");
    Serial.println(reply);
  }
}


void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.println("[BOOT] ESP8266 parking start");

  // Connect to WiFi
  connectWiFi();

  // Set MQTT message callback function
  mqtt.setCallback(mqttCallback);

  // Connect to MQTT broker
  connectMQTT();
}


void loop() {

  // Reconnect WiFi if disconnected
  if (WiFi.status() != WL_CONNECTED) {

    Serial.println("[WIFI] Disconnected, reconnecting...");
    connectWiFi();
  }

  // Reconnect MQTT if disconnected
  if (!mqtt.connected()) {

    Serial.println("[MQTT] Disconnected, reconnecting...");
    connectMQTT();
  }

  // Keep MQTT client running
  // This function processes incoming messages and maintains connection
  mqtt.loop();
}