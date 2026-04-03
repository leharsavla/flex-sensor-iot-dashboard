#include <WiFi.h>
#include <PubSubClient.h>
#include <ESP32Servo.h>
#include <WiFiClientSecure.h>

const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
const char* mqtt_server = "YOUR_HIVEMQ_URL";
const char* mqtt_user = "YOUR_HIVEMQ_USERNAME";
const char* mqtt_pass = "YOUR_HIVEMQ_PASSWORD";

WiFiClientSecure espClient;
PubSubClient client(espClient);
Servo myServo;
int flexPin = 34;

void connectWiFi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
}
void connectMQTT() {
  espClient.setInsecure();
  client.setServer(mqtt_server, 8883);
  int attempts = 0;
  while (!client.connected() && attempts < 5) {
    Serial.print("Attempting MQTT connection... state: ");
    Serial.println(client.state());
    client.connect("ESP32Client", mqtt_user, mqtt_pass);
    attempts++;
    delay(2000);
  }
  if (client.connected()) {
    Serial.println("MQTT connected");
  } else {
    Serial.println("MQTT failed after 5 attempts");
  }
}

void setup() {
  Serial.begin(115200);
  myServo.attach(13);
  connectWiFi();
  connectMQTT();
}

void loop() {
  int flexValue = analogRead(flexPin);
  int angle = map(flexValue, 1700, 2000, 0, 90);
  angle = constrain(angle, 0, 90);
  myServo.write(angle);

  String payload = String(angle);
  client.publish("flex/angle", payload.c_str());
  client.loop();

  Serial.println(angle);
  delay(200);
}
