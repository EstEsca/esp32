# GPIO 핀 할당 (ESP32-S3 N8R8)

## 사용 불가 핀

| GPIO | 이유 |
|---|---|
| 0, 3, 45, 46 | 스트래핑 핀 (부팅 모드 결정) |
| 19, 20 | USB D-/D+ (시리얼 모니터 겸용) |
| 26-37 | Octal SPI Flash/PSRAM 전용 (N8R8에서 사용 불가) |
| 43, 44 | UART0 TX/RX (시리얼 디버깅용, 가능하면 보존) |

## ILI9341 SPI 디스플레이

| 신호 | GPIO | 설명 |
|---|---|---|
| SCLK | 12 | SPI Clock |
| MOSI (SDA) | 11 | SPI Data Out |
| CS | 10 | Chip Select |
| DC | 9 | Data/Command |
| RST | 14 | Reset |
| BL | 21 | Backlight (PWM 밝기 조절 가능) |

## 버튼 (모두 INPUT_PULLUP, 누르면 LOW)

| 버튼 | GPIO |
|---|---|
| D-pad Up | 1 |
| D-pad Down | 2 |
| D-pad Left | 4 |
| D-pad Right | 5 |
| A | 6 |
| B | 7 |
| Start | 8 |
| Select | 15 |

## 로터리 엔코더

| 신호 | GPIO | 설명 |
|---|---|---|
| CLK | 16 | 인터럽트 사용 필수 |
| DT | 17 | 회전 방향 판별 |
| SW | 18 | 누름 버튼 (INPUT_PULLUP) |

## 부저

| 신호 | GPIO | 설명 |
|---|---|---|
| Buzzer | 38 | PWM (`ledcWriteTone`) |

## 예비 (향후 확장용)

| GPIO | 용도 후보 |
|---|---|
| 39 | 배터리 전압 ADC 읽기 |
| 40, 41, 42, 47, 48 | 미할당 (진동모터, LED, SD카드 등) |

## 관련 문서

- 부품 목록: [parts.md](parts.md)
- 실배선 메모: [wiring.md](wiring.md)
