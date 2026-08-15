const int buttonPin = 2; // 아두이노 2번 핀에 버튼 신호선 연결

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT); // 2번 핀을 입력 모드로 설정
}

void loop() {
  int buttonState = digitalRead(buttonPin); // 버튼 상태 읽기 (HIGH 또는 LOW)

  if (buttonState == HIGH) {
    Serial.println("버튼이 눌렸습니다! (ON)");
  } else {
    Serial.println("버튼이 떼어져 있습니다. (OFF)");
  }
  
  delay(100); // 출력 속도 조절용 딜레이
}