# ESP32 Retro Handheld Console

DIY 휴대용 레트로 게임 콘솔. ESP32-S3 기반, ILI9341 컬러 TFT, 8버튼 + 로터리 엔코더.
최종 목표: 7개 고전 게임 + ESP-NOW 무선 멀티플레이.

## 문서 인덱스

- 보유 부품: [hardware/parts.md](hardware/parts.md)
- 핀 할당: [hardware/pinout.md](hardware/pinout.md)
- 실배선 메모: [hardware/wiring.md](hardware/wiring.md)
- 전체 세션 인덱스: [sessions/README.md](sessions/README.md)
- **현재 활성 세션**: [sessions/CURRENT.md](sessions/CURRENT.md)
- 학습 회고: [docs/learning/](docs/learning/)
- 사용 매뉴얼: [docs/manual/](docs/manual/)
- 최초 통합 CLAUDE.md (참고용): [archive/claude.ai-initial-CLAUDE.md](archive/claude.ai-initial-CLAUDE.md)

## Development environment

- Framework: Arduino (C++) on PlatformIO (VSCode), Windows
- Display library: TFT_eSPI (1순위) / LovyanGFX
- Serial monitor: 115200 baud (디버깅 주력 도구)

## Development principles

1. **한 번에 한 가지만 바꾸기.** 코드 수정 → 빌드 → 업로드 → 확인. 여러 변경 동시 금지.
2. **Serial.print가 주력 디버깅 도구.** 의심 변수는 무조건 시리얼에 찍는다.
3. **헤드리스 검증 우선.** 게임 로직은 화면에 그리기 전에 시리얼 출력으로 먼저 확인.
4. **동작하면 커밋.** 작은 단위로 자주. 커밋 메시지는 한글 OK.
5. **delay() 금지.** 메인 루프는 millis() 기반 비동기 타이밍만.
6. **3.3V 규칙.** ILI9341은 3.3V 전용. 5V 절대 금지.
7. **GPIO 금지 구역.** 0, 3, 19, 20, 26-37, 43, 44, 45, 46번은 사용하지 않음. 상세는 [hardware/pinout.md](hardware/pinout.md).
8. **디버그 오버레이.** 개발 중 화면 구석에 FPS·게임 상태·주요 변수 항상 표시.

## Git conventions

- 브랜치: `session/0-bootstrap`, `session/1-hw-validation`, `session/3-pong` …
- 커밋 메시지: `[S0] 프로젝트 구조 생성`, `[S1] 버튼 디바운싱 구현` 형식
- 세션 완료 시: main에 머지 + 태그 (`vX.Y-name`)

## Notes for Claude Code

- 사용자(Jiwon)는 설계·의사결정, Claude는 코드 작성.
- 코드를 짤 때 "왜 이렇게 작성했는지" 핵심 주석을 단다.
- 빌드 에러는 메시지 전문을 보여주고 원인 설명 → 수정 순서로.

### 세션 트리거 동작

다음 발화에 반응한다:

- **"Session N 시작" / "새 세션 만들자"** → [sessions/_template/](sessions/_template/)을 `sessions/NN-name/`으로 복사 → [sessions/CURRENT.md](sessions/CURRENT.md)를 NN-name으로 갱신 → [sessions/README.md](sessions/README.md) 표에서 해당 행 상태를 `IN PROGRESS`로.
- **"태스크 X 완료" / "체크해줘"** → 해당 세션 README의 체크박스를 `[x]`로 갱신.
- **"Session N 완료"** → 체크박스·Done 조건 검토 → [sessions/README.md](sessions/README.md) 표에서 `DONE` 표기 → 사용자에게 `git tag vX.Y-name` 명령 제안 (실제 태깅은 사용자 승인 후).
- **"부품 추가/제거"** → [hardware/parts.md](hardware/parts.md) 편집.
- **"핀 변경"** → [hardware/pinout.md](hardware/pinout.md) 편집 + 영향받는 활성 세션의 코드/`platformio.ini` 표시.
- **"실배선 메모"** → [hardware/wiring.md](hardware/wiring.md) 편집 (스펙은 pinout.md, 실제 연결·함정은 wiring.md로 분리).

### 세션 시작 시 PlatformIO 설정 메모

`sessions/_template/platformio.ini`가 보일러플레이트.
디스플레이를 쓰는 세션(1a, 1e, 2 이후)에서 활성화할 TFT_eSPI build_flags:

- `-DILI9341_DRIVER=1`, `-DTFT_WIDTH=240`, `-DTFT_HEIGHT=320`
- SPI 핀: `TFT_MOSI=11, TFT_SCLK=12, TFT_CS=10, TFT_DC=9, TFT_RST=14, TFT_BL=21`
- `board = esp32-s3-devkitc-1`, `board_build.arduino.memory_type = qio_opi` (Octal PSRAM)
