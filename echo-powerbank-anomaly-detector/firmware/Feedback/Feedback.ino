/*
  Echo Powerbank — Anomaly Detector (STALKER)
  Firmware v1.0
  Author: B-ton

  Description:
    This firmware controls two operating modes:
    1) Motion detection using RCWL‑0516
    2) Battery voltage monitoring using analog input

    RGB LED indicates motion or battery level.
    Buzzer provides audible feedback in detection mode.
*/

// --- Pin Definitions ---
const uint8_t BTN_TYPE_PIN  = 10;   // Mode switch
const uint8_t LED_RED_PIN   = 8;    // RGB Red
const uint8_t LED_GREEN_PIN = 7;    // RGB Green
const uint8_t LED_BLUE_PIN  = 6;    // RGB Blue
const uint8_t VOLTAGE_PIN   = A5;   // Battery voltage sense
const uint8_t RCWL_PIN      = 9;    // Motion sensor
const uint8_t BUZZER_PIN    = 2;    // Buzzer

float voltage;
float volts;

void setup() {
  Serial.begin(115200);

  pinMode(RCWL_PIN, INPUT);
  pinMode(BTN_TYPE_PIN, INPUT);

  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(LED_BLUE_PIN, OUTPUT);

  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  int motion = digitalRead(RCWL_PIN);
  int btnTypeState = digitalRead(BTN_TYPE_PIN);

  voltage = analogRead(VOLTAGE_PIN);
  volts = voltage / 1023.0 * 5.0;

  Serial.println("btn " + String(btnTypeState));
  Serial.println("volts " + String(volts));

  // --- Mode 1: Motion Detection ---
  if (btnTypeState == HIGH) {
    if (motion == HIGH) {
      Serial.println("motion ON");

      digitalWrite(LED_RED_PIN, LOW);
      digitalWrite(LED_GREEN_PIN, LOW);
      digitalWrite(LED_BLUE_PIN, HIGH);

      tone(BUZZER_PIN, 4000, 10);
    } else {
      Serial.println("motion OFF");

      digitalWrite(LED_RED_PIN, LOW);
      digitalWrite(LED_GREEN_PIN, LOW);
      digitalWrite(LED_BLUE_PIN, LOW);

      noTone(BUZZER_PIN);
    }
  }

  // --- Mode 2: Battery Level ---
  else {
    if (volts < 3.4) {
      digitalWrite(LED_RED_PIN, HIGH);
      digitalWrite(LED_GREEN_PIN, LOW);
      digitalWrite(LED_BLUE_PIN, LOW);
    } else if (volts >= 3.4 && volts < 3.8) {
      digitalWrite(LED_RED_PIN, HIGH);
      digitalWrite(LED_GREEN_PIN, HIGH);
      digitalWrite(LED_BLUE_PIN, LOW);
    } else {
      digitalWrite(LED_RED_PIN, LOW);
      digitalWrite(LED_GREEN_PIN, HIGH);
      digitalWrite(LED_BLUE_PIN, LOW);
    }
  }

  delay(10);
}
