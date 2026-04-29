# Session 0: Project bootstrap

## Goal

PlatformIO 프로젝트를 띄우고 ESP32-S3 보드에 "Hello World"를 시리얼로 출력하는 데까지. 빌드·업로드·시리얼 모니터 파이프라인이 동작하는지 확인하는 세션.

## Tasks

- [ ] Git 저장소 초기화 (이미 `.gitignore`는 루트에 있음)
- [x] 이 세션 폴더에 PlatformIO 프로젝트 구성 (`platformio.ini` + `src/main.cpp`)
- [x] ESP32-S3 보드 설정: `board = esp32-s3-devkitc-1`, `board_build.arduino.memory_type = qio_opi`
- [x] `src/main.cpp`에서 `Serial.begin(115200)` + 1초마다 "Hello World" 출력
- [ ] `pio run` 빌드 성공
- [ ] `pio run -t upload` 업로드 성공
- [ ] `pio device monitor`에서 메시지 확인

## Done criteria

- `pio run`이 에러 없이 통과한다.
- 보드를 USB로 연결하고 시리얼 모니터(115200)에서 "Hello World"가 1초 간격으로 찍힌다.

## Tag

`v0.0-bootstrap`

## Notes

- TFT_eSPI 빌드 플래그는 이 세션에서 잡지 않는다. Session 1a(Display)에서 처음 필요해질 때 추가.
- 핀 번호는 [../../hardware/pinout.md](../../hardware/pinout.md) 참고.
- 학습 회고는 [../../docs/learning/](../../docs/learning/)에.
