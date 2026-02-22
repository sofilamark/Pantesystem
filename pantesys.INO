// ============================================
// Pantemaskin Simulator - Arduino
// ============================================
// Kobling:
//   Knapp      → Pin 2 (+ 10kΩ pulldown til GND)
//   Grønn LED  → Pin 8 (+ 220Ø motstand)
//   Rød LED    → Pin 9 (+ 220Ø motstand)
// ============================================

const int BUTTON_PIN = 2;
const int GREEN_LED  = 8;
const int RED_LED    = 9;

int itemCount     = 0;
int lastButton    = LOW;
bool ledActive    = false;
unsigned long ledOnTime = 0;
const int LED_DURATION = 1000;

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  blinkBoth(3);
  Serial.println("{\"status\":\"ready\",\"msg\":\"Pantemaskin klar\"}");
}

void loop() {
  int buttonState = digitalRead(BUTTON_PIN);

  if (buttonState == HIGH && lastButton == LOW) {
    delay(50);
    if (digitalRead(BUTTON_PIN) == HIGH) {
      itemCount++;
      bool accepted = (itemCount % 3 != 0);
      handleItem(accepted);
    }
  }

  lastButton = buttonState;

  if (ledActive && (millis() - ledOnTime > LED_DURATION)) {
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, LOW);
    ledActive = false;
  }
}

void handleItem(bool accepted) {
  if (accepted) {
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);
  } else {
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
  }
  ledActive = true;
  ledOnTime = millis();

  Serial.print("{");
  Serial.print("\"item_id\":");   Serial.print(itemCount);   Serial.print(",");
  Serial.print("\"accepted\":");  Serial.print(accepted ? "true" : "false"); Serial.print(",");
  Serial.print("\"timestamp\":"); Serial.print(millis());
  Serial.println("}");
}

void blinkBoth(int times) {
  for (int i = 0; i < times; i++) {
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, HIGH);
    delay(200);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, LOW);
    delay(200);
  }
}