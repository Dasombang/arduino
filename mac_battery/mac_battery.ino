const int ledPin = 13; // 아두이노 나노 내장 LED가 연결된 13번 핀
bool isLowBattery = false; // 배터리 부족 상태 저장 변수
unsigned long previousMillis = millis(); // 비차단 깜빡임을 위한 시간 기록 변수
const long interval = 200; // 깜빡이는 속도 (밀리초 단위, 200ms = 0.2초)
bool ledState = LOW;

void setup() {
  Serial.begin(9600);      // 파이썬 통신 속도(Baud Rate) 설정
  pinMode(ledPin, OUTPUT); // 내장 LED 핀을 출력으로 설정
  digitalWrite(ledPin, LOW);
}

void loop() {
  // 1. 파이썬으로부터 새로운 시리얼 데이터가 들어왔는지 확인
  if (Serial.available() > 0) {
    char command = Serial.read();
    
    if (command == '1') {
      isLowBattery = true; // 배터리 20% 이하 상태로 설정
    } 
    else if (command == '0') {
      isLowBattery = false; // 정상 상태로 설정
      digitalWrite(ledPin, LOW); // LED 끄기
      ledState = LOW;
    }
  }

  // 2. 배터리 부족 상태가 true일 경우, 딜레이 없이 빠르게 깜빡이기
  if (isLowBattery) {
    unsigned long currentMillis = millis();
    
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis; // 마지막 변경 시간 갱신
      
      // LED 상태 반전 (켜져있으면 끄고, 꺼져있으면 켜기)
      if (ledState == LOW) {
        ledState = HIGH;
      } else {
        ledState = LOW;
      }
      digitalWrite(ledPin, ledState);
    }
  }
}