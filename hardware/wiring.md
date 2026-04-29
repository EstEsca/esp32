# 실배선 메모

> [pinout.md](pinout.md)는 "어떤 GPIO에 무엇을 할당할 것인가"의 스펙.
> 이 문서는 "실제로 브레드보드/PCB에 어떻게 연결했는가"의 기록.
> 배선 도중 알게 된 함정·실수도 여기에 적는다.

## 전원

- ESP32-S3 DevKitC: USB 또는 5V 입력
- ILI9341: **3.3V 전용** (ESP32 3V3 핀에서 인출). 5V 절대 금지.
- TP4056 → 18650 → 부스트 컨버터(5V) → DevKitC VIN: 휴대용 전원 트리

## 공통 GND

- 모든 부품의 GND는 한 점에 모은다 (스타 그라운드).
- D-pad 4개 + Action 4개 = 8버튼 모두 common GND.

## 알게 된 함정 (TODO: 작업하면서 채워나가기)

- (예) ILI9341 IM 핀이 4-wire SPI 모드 핀에 묶여있는지 확인할 것
- (예) KY-040 풀업이 모듈에 있는지 확인 (있으면 INPUT만, 없으면 INPUT_PULLUP)

## 사진/다이어그램

- (TODO: 배선 사진 또는 Fritzing 도면 첨부)
