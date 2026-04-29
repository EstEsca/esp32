# Sessions

각 세션은 자체 폴더 + 독립 PlatformIO 프로젝트 + README(체크리스트·Done·Tag).
현재 활성 세션은 [CURRENT.md](CURRENT.md) 참고.

새 세션을 시작할 때는 [_template/](_template/)을 복사해 `NN-name/` 폴더로 사용한다.

## 세션 인덱스

| # | Session | Tag | Status |
|---|---|---|---|
| 0 | [Project bootstrap](00-bootstrap/) | `v0.0-bootstrap` | **IN PROGRESS** |
| 1 | [Hardware validation](01-hw-validation/) | `v0.1-hw-validated` | NOT STARTED |
| 2 | Game engine foundation | `v0.2-engine` | NOT STARTED |
| 3 | Pong | `v0.3-pong` | NOT STARTED |
| 4 | Snake | `v0.4-snake` | NOT STARTED |
| 5 | Space Invaders | `v0.5-invaders` | NOT STARTED |
| 6 | Tetris | `v0.6-tetris` | NOT STARTED |
| 7 | Asteroids | `v0.7-asteroids` | NOT STARTED |
| 8 | Fortress (포격전) | `v0.8-fortress` | NOT STARTED |
| 9 | Mini platformer | `v0.9-platformer` | NOT STARTED |
| 10 | Game selector menu | `v1.0-complete` | NOT STARTED |
| 11 | ESP-NOW multiplayer | `v1.1-multiplayer` | FUTURE |

상태값: `NOT STARTED` / `IN PROGRESS` / `DONE` / `FUTURE`

## 작업 흐름

1. 세션 시작 시: `_template/`을 `NN-name/`으로 복사 → [CURRENT.md](CURRENT.md) 갱신 → 위 표의 상태를 `IN PROGRESS`로
2. 태스크 완료 시: 해당 세션 README의 체크박스 `[x]` 갱신
3. 세션 완료 시: 위 표의 상태를 `DONE` + 태그 표기 → `git tag vX.Y-name`

세션 트리거 동작 상세는 [../CLAUDE.md](../CLAUDE.md)의 "Notes for Claude Code" 참고.
