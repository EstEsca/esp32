# ESP32 Retro Handheld Console

DIY 휴대용 레트로 게임 콘솔. ESP32-S3 기반, ILI9341 컬러 TFT 디스플레이, 8버튼 + 로터리 엔코더 입력.
최종 목표: 7개 고전 게임 구현 + ESP-NOW 무선 멀티플레이.

## Hardware

| 부품 | 스펙 | 비고 |
|---|---|---|
| MCU | ESP32-S3-DevKitC-1 (N8R8, 8MB Flash + 8MB PSRAM) | Octal SPI로 GPIO 26-37 사용 불가 |
| Display | ILI9341 2.4" 320×240 TFT (SPI, IPS 권장) | 3.3V 동작. TFT_eSPI 또는 LovyanGFX 사용 |
| D-pad | 택트 스위치 4개 (Up, Down, Left, Right) | INPUT_PULLUP, common GND |
| Action buttons | 택트 스위치 4개 (A, B, Start, Select) | INPUT_PULLUP, common GND |
| Rotary encoder | KY-040 호환 (push button 내장) | CLK 핀은 인터럽트로 읽을 것 |
| Audio | Passive piezo buzzer | PWM으로 음높이 제어. active 아님 주의 |
| Power | 18650 배터리 + TP4056 충전/보호 모듈 | VIN 또는 부스트 컨버터 경유 |

## Pin assignments (ESP32-S3 N8R8)

**사용 불가 핀:**
- GPIO 0, 3, 45, 46: 스트래핑 핀 (부팅 모드 결정)
- GPIO 19, 20: USB D-/D+ (시리얼 모니터 겸용)
- GPIO 26-37: Octal SPI Flash/PSRAM 전용 (N8R8에서 사용 불가)
- GPIO 43, 44: UART0 TX/RX (시리얼 디버깅용, 가능하면 보존)

**ILI9341 SPI 디스플레이:**
| 신호 | GPIO | 설명 |
|---|---|---|
| SCLK | 12 | SPI Clock |
| MOSI (SDA) | 11 | SPI Data Out |
| CS | 10 | Chip Select |
| DC | 9 | Data/Command |
| RST | 14 | Reset |
| BL | 21 | Backlight (PWM 밝기 조절 가능) |

**버튼 (모두 INPUT_PULLUP, 누르면 LOW):**
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

**로터리 엔코더:**
| 신호 | GPIO | 설명 |
|---|---|---|
| CLK | 16 | 인터럽트 사용 필수 |
| DT | 17 | 회전 방향 판별 |
| SW | 18 | 누름 버튼 (INPUT_PULLUP) |

**부저:**
| 신호 | GPIO | 설명 |
|---|---|---|
| Buzzer | 38 | PWM (ledcWriteTone) |

**예비 (향후 확장용):**
- GPIO 39: 배터리 전압 ADC 읽기
- GPIO 40, 41, 42, 47, 48: 미할당 (진동모터, LED, SD카드 등)

## Development environment

- **Framework**: Arduino (C++)
- **Build system**: PlatformIO (VSCode)
- **Display library**: TFT_eSPI (1순위) 또는 LovyanGFX
- **OS**: Windows
- **Serial monitor**: 115200 baud (디버깅 주력 도구)

## Project structure

```
esp32-retro-console/
├── CLAUDE.md              ← 이 파일 (프로젝트 컨텍스트)
├── platformio.ini         ← PlatformIO 설정
├── src/
│   ├── main.cpp           ← 엔트리포인트
│   ├── config.h           ← 핀 번호, 상수 정의
│   ├── input/
│   │   ├── buttons.h / .cpp    ← 버튼 디바운싱, 상태 읽기
│   │   └── encoder.h / .cpp    ← 로터리 엔코더 인터럽트 처리
│   ├── display/
│   │   └── display.h / .cpp    ← TFT 초기화, 헬퍼 함수
│   ├── audio/
│   │   └── buzzer.h / .cpp     ← PWM 톤 재생, 멜로디
│   ├── engine/
│   │   ├── game_engine.h / .cpp  ← 게임 루프, 프레임 타이밍
│   │   └── state_machine.h / .cpp ← FSM 프레임워크
│   └── games/
│       ├── pong/
│       ├── snake/
│       ├── space_invaders/
│       ├── tetris/
│       ├── asteroids/
│       ├── fortress/
│       └── platformer/
├── assets/
│   └── sprites/           ← 비트맵 스프라이트 헤더 파일 (.h)
├── test/                  ← 부품별 단독 테스트 코드
│   ├── test_display/
│   ├── test_buttons/
│   ├── test_encoder/
│   └── test_buzzer/
└── docs/
    └── wiring.md          ← 배선 참고 메모
```

## Sessions (스프린트)

각 세션은 명확한 완료 조건(Done criteria)이 있고, 완료 시 Git 태그를 찍는다.

### Session 0: Project bootstrap
- [ ] Git 저장소 초기화 + .gitignore
- [ ] PlatformIO 프로젝트 생성 (ESP32-S3 보드 설정)
- [ ] 디렉토리 구조 생성
- [ ] config.h에 핀 번호 상수 정의
- [ ] platformio.ini에 TFT_eSPI 빌드 플래그 설정
- [ ] "Hello World" 시리얼 출력으로 빌드+업로드 확인
- **Done**: `pio run` 성공 + 시리얼에 메시지 출력
- **Tag**: `v0.0-bootstrap`

### Session 1: Hardware validation (부품별 단독 테스트)
- [ ] 1a: Display — TFT_eSPI로 컬러 사각형 + 텍스트 표시
- [ ] 1b: Buttons — 8개 버튼 각각 시리얼에 이름 출력 (디바운싱 포함)
- [ ] 1c: Encoder — 다이얼 회전 시 각도값(0~360) 시리얼 출력, 누름 감지
- [ ] 1d: Buzzer — C4~C6 음계 순서대로 재생
- [ ] 1e: Integration — 모든 부품 동시 동작 확인 (버튼 누르면 화면에 표시 + 소리)
- **Done**: 모든 부품이 동시에 정상 동작하는 통합 테스트 통과
- **Tag**: `v0.1-hw-validated`

### Session 2: Game engine foundation
- [ ] 고정 프레임레이트 게임 루프 (millis 기반, target 30 FPS)
- [ ] 더블 버퍼링 또는 스프라이트 기반 화면 갱신
- [ ] FSM 프레임워크 (MENU → PLAYING → PAUSED → GAME_OVER)
- [ ] 공통 입력 추상화 (ButtonState 구조체: pressed, released, held)
- [ ] FPS 카운터 디버그 오버레이
- **Done**: 빈 게임 루프가 안정적으로 30 FPS 유지 + 상태 전환 동작
- **Tag**: `v0.2-engine`

### Session 3: Pong
- [ ] 패들 2개 (다이얼 = P1, D-pad Up/Down = P2)
- [ ] 공 물리 (반사, 속도 점진 증가)
- [ ] 점수 표시, 승리 조건
- [ ] 발사음, 반사음, 득점음
- **Done**: 로컬 2인 플레이 가능한 Pong
- **Tag**: `v0.3-pong`

### Session 4: Snake
- [ ] D-pad 4방향 이동
- [ ] 먹이 생성, 몸 성장
- [ ] 자기 몸·벽 충돌 판정
- [ ] 점수, 게임오버, 재시작
- **Done**: 플레이 가능한 Snake + 최고점수 표시
- **Tag**: `v0.4-snake`

### Session 5: Space Invaders
- [ ] 플레이어 좌우 이동 + 발사
- [ ] 적 무리 이동 패턴 (좌→우→한칸 내려오기)
- [ ] 적 격파, 보호막, 스테이지 클리어
- [ ] 적 수 줄어들수록 이동 가속
- **Done**: 3스테이지 플레이 가능
- **Tag**: `v0.5-invaders`

### Session 6: Tetris
- [ ] 7종 테트로미노, 7-bag 랜덤
- [ ] 좌우 이동, 시계/반시계 회전 (A/B), 소프트드롭(Down), 하드드롭(Up)
- [ ] 줄 완성·소거 판정
- [ ] 레벨업 (속도 증가), 점수 시스템
- [ ] 다음 블록 미리보기
- **Done**: 레벨 10 이상 플레이 가능
- **Tag**: `v0.6-tetris`

### Session 7: Asteroids
- [ ] 다이얼로 우주선 회전, A로 가속, B로 발사
- [ ] 관성 물리 (thrust → drift)
- [ ] 소행성 분열 (대→중→소)
- [ ] 화면 랩어라운드
- **Done**: 3 웨이브 이상 플레이 가능
- **Tag**: `v0.7-asteroids`

### Session 8: Fortress (포트리스류 포격전)
- [ ] 울퉁불퉁 지형 생성 (높이 배열)
- [ ] 다이얼 = 포 각도, 버튼 = 파워 게이지 충전/발사
- [ ] 포물선 궤적 물리 (중력 + 바람)
- [ ] 지형 파괴 (폭발 반경 내 높이 배열 깎기)
- [ ] 2인 교대 플레이 (같은 기기)
- **Done**: 로컬 2인 턴제 대전 가능
- **Tag**: `v0.8-fortress`

### Session 9: Mini platformer (마리오류)
- [ ] 캐릭터 이동 + 점프 (가변 높이: 짧게/길게 누르기)
- [ ] 중력, 플랫폼 충돌 판정
- [ ] 횡스크롤 카메라
- [ ] 적 (밟으면 처치)
- [ ] 코인, 골 지점
- **Done**: 1스테이지 클리어 가능
- **Tag**: `v0.9-platformer`

### Session 10: Game selector menu
- [ ] 부팅 시 게임 목록 메뉴
- [ ] 다이얼 또는 D-pad로 선택, A로 진입
- [ ] 각 게임에서 Start+Select 동시 누르면 메뉴 복귀
- **Done**: 메뉴에서 7개 게임 모두 진입/복귀 가능
- **Tag**: `v1.0-complete`

### Session 11+: ESP-NOW 멀티플레이 (향후)
- ESP-NOW 페어링, 상태 동기화
- Pong 무선 대전, Fortress 무선 대전
- **Tag**: `v1.1-multiplayer`

## Current session

**Session 0: Project bootstrap**
Status: NOT STARTED

## Development principles

1. **한 번에 한 가지만 바꾸기.** 코드 수정 → 빌드 → 업로드 → 확인. 여러 변경을 한꺼번에 하지 않는다.
2. **Serial.print가 주력 디버깅 도구.** 의심 가는 변수는 무조건 시리얼에 찍는다.
3. **헤드리스 검증 우선.** 게임 로직은 화면에 그리기 전에 시리얼 출력으로 먼저 확인한다.
4. **동작하면 커밋.** 작은 단위로 자주 커밋한다. 커밋 메시지는 한글 OK.
5. **delay() 금지.** 메인 루프에서 delay()를 쓰지 않는다. millis() 기반 비동기 타이밍만 사용.
6. **3.3V 규칙.** ILI9341은 3.3V 전용. 5V 절대 연결 금지.
7. **GPIO 금지 구역.** 0, 3, 19, 20, 26-37, 43, 44, 45, 46번 핀은 사용하지 않는다.
8. **디버그 오버레이.** 개발 중에는 화면 구석에 FPS, 게임 상태, 주요 변수를 항상 표시한다.

## Git conventions

- 브랜치: `session/0-bootstrap`, `session/1-hw-validation`, `session/3-pong` ...
- 커밋 메시지: `[S0] 프로젝트 구조 생성`, `[S1] 버튼 디바운싱 구현` 형식
- 세션 완료 시: main에 머지 + 태그
- .gitignore: `.pio/`, `.vscode/` (선택), `build/`

## Notes for Claude Code

- 사용자(Jiwon)는 설계·의사결정을 담당하고, 코드 작성은 Claude가 한다.
- 코드를 짤 때는 해당 코드가 "왜 이렇게 작성되었는지" 핵심 주석을 달아준다.
- 새 세션을 시작할 때 이 파일의 "Current session" 섹션과 체크리스트를 업데이트한다.
- 세션 내 태스크 완료 시 체크박스를 [x]로 갱신한다.
- 빌드 에러 발생 시 에러 메시지 전문을 보여주고 원인을 설명한 뒤 수정한다.
- platformio.ini의 TFT_eSPI 설정은 Session 0에서 정확히 잡아야 한다:
  - `TFT_DRIVER=ILI9341`, `TFT_WIDTH=240`, `TFT_HEIGHT=320`
  - SPI 핀 번호를 build_flags에 명시
  - `board = esp32-s3-devkitc-1`
  - `board_build.arduino.memory_type = qio_opi` (Octal PSRAM 활성화)
