#include <Adafruit_NeoPixel.h>

// ----- 핀 -----
const uint8_t NEOPIXEL_PIN = 6;
const uint8_t PIR_PIN = 2;
const uint8_t CDS_PIN = A0;

const uint16_t LED_COUNT = 8;

// WS2812B (WCMCU-2812B-8): GRB, 800kHz
Adafruit_NeoPixel strip(LED_COUNT, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

// ----- 동작 설정 -----
// 일반적인 분압: 5V -- CdS -- A0 -- 10kΩ -- GND
// 어두울수록 analogRead 값이 작아집니다.
// 시리얼 모니터로 cds 값을 보고 환경에 맞게 조절하세요.
const int DARK_THRESHOLD = 400;

// PIR이 LOW로 떨어진 뒤에도 이 시간(ms) 동안은 불을 유지합니다.
const unsigned long MOTION_HOLD_MS = 18000;

const uint8_t BRIGHTNESS = 80;           // 0~255 (USB 전원 부담을 줄이려면 낮게)
const unsigned long COLOR_STEP_MS = 20;  // 색 변화 속도 (작을수록 빠름)
const uint8_t HUE_STEP = 1;              // 한 프레임당 색상 진행량

uint16_t hue = 0;
unsigned long lastColorStepMs = 0;
unsigned long lastMotionMs = 0;
bool lampOn = false;

void setup() {
  pinMode(PIR_PIN, INPUT);
  strip.begin();
  strip.setBrightness(BRIGHTNESS);
  strip.clear();
  strip.show();

  Serial.begin(9600);
}

void loop() {
  const int cds = analogRead(CDS_PIN);
  const bool isDark = cds < DARK_THRESHOLD;
  const bool motion = digitalRead(PIR_PIN) == HIGH;

  if (motion) {
    lastMotionMs = millis();
  }

  const bool motionRecent = (millis() - lastMotionMs) < MOTION_HOLD_MS;
  const bool shouldLight = isDark && motionRecent;

  if (shouldLight) {
    lampOn = true;
    updateMoodColor();
  } else if (lampOn) {
    turnOff();
    lampOn = false;
  }

  static unsigned long lastPrintMs = 0;
  if (millis() - lastPrintMs >= 500) {
    lastPrintMs = millis();
    Serial.print("cds=");
    Serial.print(cds);
    Serial.print(" dark=");
    Serial.print(isDark ? "Y" : "N");
    Serial.print(" pir=");
    Serial.print(motion ? "Y" : "N");
    Serial.print(" lamp=");
    Serial.println(shouldLight ? "ON" : "OFF");
  }
}

// 빨강(0) → 초록(21845) → 파랑(43690) → 빨강, HSV 색상환을 따라 부드럽게 순환
void updateMoodColor() {
  const unsigned long now = millis();
  if (now - lastColorStepMs < COLOR_STEP_MS) {
    return;
  }
  lastColorStepMs = now;

  hue += HUE_STEP;
  const uint32_t color = strip.ColorHSV(hue);
  strip.fill(color);
  strip.show();
}

void turnOff() {
  strip.clear();
  strip.show();
}
