#include <ArduinoBLE.h>

#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

BLEService sensorService(SERVICE_UUID);
BLECharacteristic sensorCharacteristic(CHARACTERISTIC_UUID, BLERead | BLENotify);

// FSR-402와 MUX 핀 설정
const int muxS0 = D2; // GPIO 5 == D2
const int muxS1 = D3; // GPIO 6 == D3
const int muxAnalogPin = A1; // 아날로그 입력 핀

void setup() {
  // 시리얼 통신을 설정합니다.
  Serial.begin(115200);

  // MUX 제어 핀을 출력 모드로 설정
  pinMode(muxS0, OUTPUT);
  pinMode(muxS1, OUTPUT);

  Serial.println("MUX와 FSR 센서 초기화 완료");
}

void loop() {
  // 4개의 FSR 센서 값을 읽습니다.
  for (int i = 0; i < 4; i++) {
    selectMuxChannel(i);
    delay(5);
    int fsrReading = analogRead(muxAnalogPin);
    Serial.print("FSR ");
    Serial.print(i);
    Serial.print(" Reading: ");
    Serial.println(fsrReading);
  }

  // 100ms마다 값을 읽습니다.
  delay(100);
}

void selectMuxChannel(int channel) {
  // MUX 채널 선택을 위해 디지털 핀을 설정
  digitalWrite(muxS0, bitRead(channel, 0));
  digitalWrite(muxS1, bitRead(channel, 1));
}
