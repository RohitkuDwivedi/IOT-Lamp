#include <WiFi.h>
#include <PubSubClient.h>

#define LED 16
const char* ssid     = "<wifi ssid>";
const char* password = "<wifi password>";
const char* mqttServer = "io.adafruit.com";
const int mqttPort = 1883;
const char* mqttUser = "<your adafruit id>";
const char* mqttPassword = "<your key>";
 
WiFiClient espClient;
PubSubClient client(espClient);
 
void callback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  
  Serial.print("Message:");
  char reply = *(char*)payload;
  if(reply == '1'){
    digitalWrite(LED,HIGH);
    }
  if(reply == '0'){
    digitalWrite(LED,LOW);
    }
    
  Serial.println(reply);
  Serial.println("-----------------------");
 
}
 
void setup() {
 
  Serial.begin(115200);
  pinMode(LED,OUTPUT);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
 
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP32Client", mqttUser, mqttPassword )) {
 
      Serial.println("connected");  
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }
  }
  // feed name is the topic
  client.subscribe("rohitd/feeds/lamp");
 
}
 
void loop() {
  client.loop();
}
