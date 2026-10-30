
#include <WiFi.h>
#include <WiFiManager.h>

// Wi-Fi Manager Configuration
const char* AP_NAME = "BCA188-ESP32-2024-2026";

// BOOT Button Configuration
#define BOOT_PIN 0
#define RESET_HOLD_TIME 3000

WiFiManager wm;

unsigned long buttonPressTime = 0;

void setup() {
  Serial.begin(115200);
  pinMode(BOOT_PIN, INPUT_PULLUP);

  WiFi.mode(WIFI_STA);

  Serial.println();
  Serial.println("BCA188 - ESP32 Wi-Fi Manager");
  Serial.println("-----------------------------");

  // Set configuration portal timeout to 180 seconds
  wm.setConfigPortalTimeout(180);

  Serial.println("Starting Wi-Fi Manager...");

  // Connect to saved Wi-Fi or start setup portal
  if (!wm.autoConnect(AP_NAME)) {
    Serial.println("Connection failed or timed out.");
    Serial.println("Restarting ESP32...");
    delay(1000);
    ESP.restart();
  }

  Serial.println();
  Serial.println("Wi-Fi Connected Successfully!");

  Serial.print("Connected SSID: ");
  Serial.println(WiFi.SSID());

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  Serial.println();
  Serial.println("Hold BOOT for 3 seconds to reset Wi-Fi.");
}

void loop() {
  // Check if BOOT button is pressed
  if (digitalRead(BOOT_PIN) == LOW) {

    if (buttonPressTime == 0) {
      buttonPressTime = millis();
    }

    // Reset Wi-Fi settings after 3 seconds
    if (millis() - buttonPressTime >= RESET_HOLD_TIME) {
      Serial.println();
      Serial.println("Resetting Wi-Fi settings...");

      wm.resetSettings();

      Serial.println("Wi-Fi settings cleared.");
      Serial.println("Restarting ESP32...");

      delay(500);
      ESP.restart();
    }

  } else {
    buttonPressTime = 0;
  }
}

