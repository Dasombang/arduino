const int cdsPin = A0;   // 조도센서 중간 연결 핀
const int ledPin = 3;    // LED가 연결된 디지털 핀 (PWM 가능 핀)
const int threshold = 200; // LED가 켜지고 꺼지는 기준 밝기 값 (0 ~ 1023)

void setup() {
  Serial.begin(9600);    // 시리얼 통신 시작
  pinMode(ledPin, OUTPUT); // LED 핀을 출력으로 설정
}

void loop() {
  int sensorValue = analogRead(cdsPin); // 조도센서 값 읽기 (0 ~ 1023)

  // 시리얼 모니터로 현재 센서값 확인
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);

  // 주변이 어두워지면 (센서 값이 설정한 기준치보다 낮아지면)
  if (sensorValue < threshold) {
    digitalWrite(ledPin, HIGH); // LED 켜기
    Serial.println(" -> 어두워져서 LED를 켭니다.");
  } 
  // 주변이 밝아지면
  else {
    digitalWrite(ledPin, LOW);  // LED 끄기
    Serial.println(" -> 밝아져서 LED를 끕니다.");
  }

  delay(500); // 0.5초마다 상태 확인
}