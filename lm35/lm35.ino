const int lm35Pin = A1; // LM35 OUT 핀이 연결된 아날로그 핀

void setup() {
  Serial.begin(9600); // 시리얼 통신 속도 설정
}

void loop() {
  int sensorValue = analogRead(lm35Pin); // 아날로그 값 읽기 (0 ~ 1023)
  
  // 아두이노 기본 5V 기준 전압을 실제 전압(mV)으로 변환
  float voltage = (sensorValue / 1023.0) * 5000.0; 
  
  // 10mV 당 1°C이므로, 전압(mV)을 10으로 나누어 섭씨 온도 계산
  float temperature = voltage / 10.0; 

  // 시리얼 모니터에 출력
  Serial.print("sensorValue: ");
  Serial.print(sensorValue);
  Serial.print(" / ");
  
  Serial.print("Current Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  delay(1000); // 1초마다 측정
}