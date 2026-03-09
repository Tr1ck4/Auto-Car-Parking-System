#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// WiFi hotspot information
const char* WIFI_SSID     = "vivo X200 Pro";
const char* WIFI_PASSWORD = "xiaolian";

// MQTT broker information
const char* MQTT_HOST = "192.168.155.109";
const uint16_t MQTT_PORT = 1883;

// MQTT client ID for this car-side ESP8266
const char* MQTT_CLIENT_ID = "car001";

// Shared topic
const char* TOPIC = "lab/parking";

WiFiClient wifiClient;
PubSubClient mqtt(wifiClient);

// Buffer for serial command from Arduino
String serialCmd = "";

void connectWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("[WIFI] Connected");
}

void connectMQTT() {
  mqtt.setServer(MQTT_HOST, MQTT_PORT);

  while (!mqtt.connected()) {
    //Serial.println("[MQTT] Connecting...");

    if (mqtt.connect(MQTT_CLIENT_ID)) {
      mqtt.subscribe(TOPIC);
      //Serial.println("[MQTT] Connected and subscribed");
    } else {
      //Serial.print("[MQTT] Failed, rc = ");
      //Serial.println(mqtt.state());
      delay(1000);
    }
  }
}

void sendParkingRequest() {
  String msg = "req+" + String(MQTT_CLIENT_ID);
  mqtt.publish(TOPIC, msg.c_str());

  //Serial.print("[PUB] ");
  //Serial.println(msg);
}

void updateOccupied(int slotNum) {
  String msg = "update+" + String(slotNum) /*+ "+1"*/;
  mqtt.publish(TOPIC, msg.c_str());

  //Serial.print("[PUB] ");
  //Serial.println(msg);
}

void mqttCallback(char* topic, byte* payload, unsigned int length) {
  String msg;

  for (unsigned int i = 0; i < length; i++) {
    msg += (char)payload[i];
  }
  msg.trim();

  //Serial.print("[MQTT] Message arrived: ");
  //Serial.println(msg);

  // Expected format: res+num+mqttid
  if (msg.startsWith("res+")) {
    int firstPlus = msg.indexOf('+');
    int secondPlus = msg.indexOf('+', firstPlus + 1);

    if (secondPlus == -1) return;

    String numStr = msg.substring(firstPlus + 1, secondPlus);
    String idStr  = msg.substring(secondPlus + 1);

    numStr.trim();
    idStr.trim();

    // Only process the response for this car
    if (idStr == String(MQTT_CLIENT_ID)) {
      String serialReply = "SLOT+" + numStr;

      // Send slot number to Arduino through serial
      Serial.println(serialReply);

      // Debug output
      //Serial.print("[SERIAL->UNO] ");
      //Serial.println(serialReply);
    }
  }
}

void handleSerialCommand(String cmd) {
  cmd.trim();

  if (cmd == "REQ") {
    sendParkingRequest();
  }
  else if (cmd.startsWith("OCCUPY+")) {
    String numStr = cmd.substring(7);
    numStr.trim();

    int slotNum = numStr.toInt();
    updateOccupied(slotNum);
  }
}

void setup() {
  Serial.begin(9600);
  delay(200);

  //Serial.println();
  //Serial.println("[BOOT] Car ESP8266 start");

  connectWiFi();

  mqtt.setCallback(mqttCallback);
  connectMQTT();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    //Serial.println("[WIFI] Disconnected, reconnecting...");
    connectWiFi();
  }

  if (!mqtt.connected()) {
    //Serial.println("[MQTT] Disconnected, reconnecting...");
    connectMQTT();
  }

  mqtt.loop();

  // Read serial command from Arduino
  while (Serial.available()) {
    char c = Serial.read();

    if (c == '\n') {
      handleSerialCommand(serialCmd);
      serialCmd = "";
    } else if (c != '\r') {
      serialCmd += c;
    }
  }
}