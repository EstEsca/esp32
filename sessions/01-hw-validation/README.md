# Session 1: Hardware validation

각 부품을 **단독으로** 검증한 뒤, 마지막 1e에서 통합 동작을 확인한다.
서브태스크마다 독립 PlatformIO 프로젝트로 만든다 (한 번에 한 가지만 바꾸기 원칙).

## 서브태스크

- [ ] **1a — Display** (`1a-display/`): TFT_eSPI로 컬러 사각형 + 텍스트 표시
- [ ] **1b — Buttons** (`1b-buttons/`): 8개 버튼 각각 시리얼에 이름 출력 (디바운싱 포함)
- [ ] **1c — Encoder** (`1c-encoder/`): 다이얼 회전 시 각도값(0~360) 시리얼 출력, 누름 감지
- [ ] **1d — Buzzer** (`1d-buzzer/`): C4~C6 음계 순서대로 재생
- [ ] **1e — Integration** (`1e-integration/`): 모든 부품 동시 동작 (버튼 누르면 화면에 표시 + 소리)

## 작업 방식

각 서브태스크 폴더는 그 시점에 도달했을 때 [../_template/](../_template/)을 복사해 만든다.
지금 미리 5개 폴더를 만들어두지 않는다 — 필요할 때만 생성.

## Done criteria

- 1a~1d 각각이 단독으로 정상 동작한다.
- 1e에서 모든 부품이 동시에 정상 동작한다.

## Tag

`v0.1-hw-validated`

## Notes

- TFT_eSPI 설정 (1a부터 적용):
  - `TFT_DRIVER=ILI9341`, `TFT_WIDTH=240`, `TFT_HEIGHT=320`
  - SPI 핀은 [../../hardware/pinout.md](../../hardware/pinout.md) 참고
- 엔코더(1c) CLK 핀은 인터럽트로 처리할 것.
- 부저(1d)는 passive piezo — `ledcWriteTone` PWM. active 모듈 아님 주의.
- 학습 회고는 [../../docs/learning/](../../docs/learning/)에.
