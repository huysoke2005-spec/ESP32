#include <Arduino.h>
#include <OneButton.h>

#define LED1_PIN 2       
#define LED2_PIN 18      
#define BUTTON_PIN 19    

OneButton btn(BUTTON_PIN, true, true);

enum ActiveLED { SELECT_LED1, SELECT_LED2 };
ActiveLED currentLED = SELECT_LED1;

bool led1State = false;
bool led2State = false;

bool led1Blinking = false;
bool led2Blinking = false;

unsigned long led1LastBlink = 0;
unsigned long led2LastBlink = 0;
const unsigned long blinkInterval = 200; 

void handleDoubleClick() {
  currentLED = (currentLED == SELECT_LED1) ? SELECT_LED2 : SELECT_LED1;
  Serial.print("[Chế độ] Đang điều khiển: ");
  Serial.println(currentLED == SELECT_LED1 ? "LED 1 (GPIO 2 - Built-in)" : "LED 2 (GPIO 18 - Ngoài)");
}

void handleClick() {
  if (currentLED == SELECT_LED1) {
    if (led1Blinking) {
      led1Blinking = false;
      led1State = false; // Đang nháy thì bấm 1 cái sẽ dừng nháy và tắt hẳn
    } else {
      led1State = !led1State;
    }
    digitalWrite(LED1_PIN, led1State ? HIGH : LOW);
    Serial.printf("[Single Click] LED1: %s\n", led1State ? "ON" : "OFF");
  } else {
    if (led2Blinking) {
      led2Blinking = false;
      led2State = false;
    } else {
      led2State = !led2State;
    }
    digitalWrite(LED2_PIN, led2State ? HIGH : LOW);
    Serial.printf("[Single Click] LED2: %s\n", led2State ? "ON" : "OFF");
  }
}

void handleLongPressStart() {
  if (currentLED == SELECT_LED1) {
    led1Blinking = !led1Blinking;
    if (led1Blinking) {
      led1LastBlink = millis();
      led1State = true;
      digitalWrite(LED1_PIN, HIGH);
      Serial.println("[Long Press] Bật nhấp nháy 200ms cho LED 1");
    } else {
      led1State = false;
      digitalWrite(LED1_PIN, LOW);
      Serial.println("[Long Press] Tắt nhấp nháy LED 1");
    }
  } else {
    led2Blinking = !led2Blinking;
    if (led2Blinking) {
      led2LastBlink = millis();
      led2State = true;
      digitalWrite(LED2_PIN, HIGH);
      Serial.println("[Long Press] Bật nhấp nháy 200ms cho LED 2");
    } else {
      led2State = false;
      digitalWrite(LED2_PIN, LOW);
      Serial.println("[Long Press] Tắt nhấp nháy LED 2");
    }
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);

  digitalWrite(LED1_PIN, LOW);
  digitalWrite(LED2_PIN, LOW);

  btn.attachDoubleClick(handleDoubleClick);
  btn.attachClick(handleClick);
  btn.attachLongPressStart(handleLongPressStart);
  
  btn.setPressTicks(800);

  Serial.println("Hệ thống sẵn sàng!");
}

void loop() {
  btn.tick();

  unsigned long currentMillis = millis();

  if (led1Blinking && (currentMillis - led1LastBlink >= blinkInterval)) {
    led1LastBlink = currentMillis;
    led1State = !led1State;
    digitalWrite(LED1_PIN, led1State ? HIGH : LOW);
  }

  if (led2Blinking && (currentMillis - led2LastBlink >= blinkInterval)) {
    led2LastBlink = currentMillis;
    led2State = !led2State;
    digitalWrite(LED2_PIN, led2State ? HIGH : LOW);
  }
}