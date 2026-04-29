# 보유 부품 목록

> 이 문서는 자주 갱신된다. 부품을 추가/제거할 때 표를 직접 수정.

## 핵심 부품

| 부품 | 스펙 | 비고 |
|---|---|---|
| MCU | ESP32-S3-DevKitC-1 (N8R8, 8MB Flash + 8MB PSRAM) | Octal SPI로 GPIO 26-37 사용 불가 |
| Display | ILI9341 2.4" 320×240 TFT (SPI, IPS 권장) | 3.3V 동작. TFT_eSPI 또는 LovyanGFX 사용 |
| D-pad | 택트 스위치 4개 (Up, Down, Left, Right) | INPUT_PULLUP, common GND |
| Action buttons | 택트 스위치 4개 (A, B, Start, Select) | INPUT_PULLUP, common GND |
| Rotary encoder | KY-040 호환 (push button 내장) | CLK 핀은 인터럽트로 읽을 것 |
| Audio | Passive piezo buzzer | PWM으로 음높이 제어. active 아님 주의 |
| Power | 18650 배터리 + TP4056 충전/보호 모듈 | VIN 또는 부스트 컨버터 경유 |

## 향후 추가 후보

- 진동 모터 (햅틱 피드백)
- 추가 LED (상태 표시)
- microSD 카드 슬롯 (세이브 데이터)
- ESP-NOW용 두 번째 ESP32-S3 (멀티플레이 페어링)

## 관련 문서

- 핀 할당: [pinout.md](pinout.md)
- 실배선 메모: [wiring.md](wiring.md)
