#include <WiFi.h>
#include <PubSubClient.h>

// — CONFIGURACIÓN WI-FI —
const char* ssid     = "network";
const char* password = "helloworld";

// — BROKER MQTT LOCAL —
const char* mqtt_server = "192.168.76.32";
const int   mqtt_port   = 1883;
const char* topic_cmd   = "josee/control/presentacion";

// — PINS —
const int pinBack = 21;  // Botón “Back”
const int pinNext = 4;   // Botón “Next”
const int pinLED  = 16;  // LED de confirmación

WiFiClient   espClient;
PubSubClient mqtt(espClient);

void setupWiFi() {
  Serial.print("Conectando a Wi-Fi ");
  Serial.print(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n¡Wi-Fi conectado!");
  Serial.print("IP local: ");
  Serial.println(WiFi.localIP());
}

void reconnectMQTT() {
  while (!mqtt.connected()) {
    Serial.print("Conectando a MQTT...");
    if (mqtt.connect("esp32_presentation")) {
      Serial.println(" ¡Conectado!");
    } else {
      Serial.print(" fallo rc=");
      Serial.print(mqtt.state());
      Serial.println(" — reintentando en 1s");
      delay(1000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(pinBack, INPUT_PULLUP);
  pinMode(pinNext, INPUT_PULLUP);
  pinMode(pinLED, OUTPUT);
  digitalWrite(pinLED, LOW);

  setupWiFi();
  mqtt.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!mqtt.connected()) {
    reconnectMQTT();
  }
  mqtt.loop();

  // Si Back está pulsado...
  if (digitalRead(pinBack) == LOW) {
    Serial.println("← PREV pulsado");
    mqtt.publish(topic_cmd, "PREV");
    digitalWrite(pinLED, HIGH);
    delay(100);
    digitalWrite(pinLED, LOW);
    // Espera a soltar el botón
    while (digitalRead(pinBack) == LOW) delay(10);
    delay(100); // antirrebote
  }

  // Si Next está pulsado...
  if (digitalRead(pinNext) == LOW) {
    Serial.println("→ NEXT pulsado");
    mqtt.publish(topic_cmd, "NEXT");
    digitalWrite(pinLED, HIGH);
    delay(100);
    digitalWrite(pinLED, LOW);
    // Espera a soltar el botón
    while (digitalRead(pinNext) == LOW) delay(10);
    delay(100); // antirrebote
  }

  // Pequeña pausa para aligerar el loop
  delay(10);
}
