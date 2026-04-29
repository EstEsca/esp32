// Session 0: Project bootstrap
// 빌드/업로드/시리얼 모니터 파이프라인이 동작하는지 확인하는 최소 스케치.
// 1초마다 "Hello World" + 누적 카운터를 시리얼에 찍는다.
// 카운터를 함께 찍는 이유: 똑같은 줄만 반복되면 시리얼이 멈춘 건지
// 정상 출력 중인지 한눈에 분간이 안 되기 때문.

#include <Arduino.h>

// delay() 금지 원칙에 따라 millis() 기반으로 주기 출력.
static const uint32_t PRINT_INTERVAL_MS = 1000;

uint32_t lastPrintMs = 0;
uint32_t tick = 0;

void setup() {
    Serial.begin(115200);

    // USB-CDC가 연결될 때까지 잠깐 기다림 (보드에 따라 첫 줄을 놓치는 것을 방지).
    // delay() 금지 원칙은 "메인 루프"에 적용. setup()의 일회성 대기는 허용.
    delay(500);

    Serial.println();
    Serial.println(F("=== ESP32 Retro Console — Session 0 bootstrap ==="));
    Serial.printf("Chip: %s, Cores: %d, Flash: %luKB, PSRAM: %luKB\n",
                  ESP.getChipModel(),
                  ESP.getChipCores(),
                  ESP.getFlashChipSize() / 1024UL,
                  ESP.getPsramSize() / 1024UL);
}

void loop() {
    const uint32_t now = millis();
    if (now - lastPrintMs >= PRINT_INTERVAL_MS) {
        lastPrintMs = now;
        Serial.printf("[%lu] Hello World — tick=%lu\n", now, ++tick);
    }
}
