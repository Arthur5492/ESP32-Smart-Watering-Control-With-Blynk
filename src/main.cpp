// Blynk Credentials
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL26hW63NBm"
#define BLYNK_TEMPLATE_NAME "HortaMedicinal"
#define BLYNK_AUTH_TOKEN "C9ahAkg_IwFsMfjuHkYq3gNWGGVGA8Y_"

#include <Arduino.h>
#include <BlynkSimpleEsp32.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>

// DHT11 Sensor Configuration
#define DHTPIN 14    // Pin connected to DHT11 sensor data pin
#define DHTTYPE DHT11 // Define the type of sensor
DHT dht(DHTPIN, DHTTYPE); // Initialize DHT sensor

// Soil Moisture Sensor Configuration
#define SOIL_SENSOR_PIN 32  // Analog pin connected to HW-080 soil sensor

// Wi-Fi credentials
char ssid[] = "GalaxyA52";     // Your WiFi SSID
char pass[] = "moretti123";  // Your WiFi password

void setup() {
  // Start serial communication
  Serial.begin(115200);
  Serial.println();
  Serial.println("Starting up...");

  // Initialize DHT sensor
  dht.begin();

  // Manually connect to Wi-Fi
  Serial.print("Connecting to Wi-Fi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);

  // Wait for Wi-Fi connection
  int retries = 0;
  while (WiFi.status() != WL_CONNECTED && retries < 20) {
    delay(500);
    Serial.print(".");
    retries++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println();
    Serial.println("Connected to Wi-Fi!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    // Initialize Blynk
    Blynk.config(BLYNK_AUTH_TOKEN);
    Blynk.connect(); // Manually start the Blynk connection
  } else {
    Serial.println();
    Serial.println("Failed to connect to Wi-Fi. Please check credentials or signal strength.");
  }
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    // Read temperature and humidity from DHT11
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature(); // In Celsius

    // Check if readings failed
    if (isnan(humidity) || isnan(temperature)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }

    // Print readings to the serial monitor
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print("%  Temperature: ");
    Serial.print(temperature);
    Serial.println("°C");

    // Read soil moisture from HW-080 sensor
    int soilMoistureValue = analogRead(SOIL_SENSOR_PIN); // Read analog value (0-4095)i
    // Convert to percentage (0-100%)
    int soilMoisturePercent = map(soilMoistureValue, 0, 4095, 0, 100);
    // Print soil moisture value
    Serial.print("Soil Moisture: ");
    Serial.print(soilMoisturePercent);
    Serial.println("%");

    // Send data to Blynk
    Blynk.virtualWrite(V1, temperature); // V1 is the virtual pin for temperature
    Blynk.virtualWrite(V2, humidity);    // V2 is the virtual pin for humidity
    Blynk.virtualWrite(V3, soilMoisturePercent); // V3 is the virtual pin for soil moisture

    // Run Blynk
    Blynk.run();
  } else {
    Serial.println("Wi-Fi disconnected, trying to reconnect...");
    WiFi.reconnect();  // Attempt to reconnect
  }

  // Wait 2 seconds between measurements
  delay(2000);
}
