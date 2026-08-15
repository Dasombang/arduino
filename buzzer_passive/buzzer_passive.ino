const int buzzerPin = 8;

#define REST      0

#define NOTE_G5   784
#define NOTE_GS5  831
#define NOTE_A5   880
#define NOTE_AS5  932

#define NOTE_G6   1568
#define NOTE_GS6  1661
#define NOTE_A6   1760
#define NOTE_AS6  1865

int melody[] = {
  // 도입부의 빠른 고음 장식
  NOTE_AS6, NOTE_A6, NOTE_GS6, NOTE_G6, REST,

  // 트럼펫 멜로디
  NOTE_GS5, NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_GS5,
  NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_AS5, NOTE_A5,
  NOTE_GS5, NOTE_G5
};

int noteDurations[] = {
  // 고음 장식
  85, 30, 80, 25, 110,

  // 실제 멜로디의 음 길이
  80, 80, 80, 230, 90,
  630, 50, 180, 140, 255,
  920, 215
};

void setup() {
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  const int size = sizeof(melody) / sizeof(melody[0]);

  for (int i = 0; i < size; i++) {
    int duration = noteDurations[i];

    if (melody[i] == REST) {
      noTone(buzzerPin);
      delay(duration);
    } else {
      tone(buzzerPin, melody[i], duration);
      delay(duration * 1.03); // 음을 거의 붙여 연주
      noTone(buzzerPin);
    }
  }

  delay(1500);
}