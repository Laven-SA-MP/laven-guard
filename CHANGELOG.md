# Changelog

Tüm önemli değişiklikler bu dosyada tutulur.

## [0.0.2]

### Added
- Modüler include mimarisi eklendi (`core`, `score`, `policy`, `detectors`).
- Score category sistemi eklendi: flood, speed, weapon placeholder, total.
- Global decay timer eklendi.
- Policy engine eklendi (soft/kick/ban).
- Speed detector eklendi (vehicle/interior skip ve cooldown).

### Changed
- Chat flood kontrolü detector + score + policy akışına taşındı.
- Public API stabil tutuldu: `LG_Init`, `LG_OnPlayerConnect`, `LG_OnPlayerText`.

### Hotfix Notes (v0.0.2)
- `LG_OnPlayerDisconnect` public API eklendi, disconnect anında player state tamamen resetlenir.
- Soft action policy category bazlı hale getirildi (flood=mute, speed=warn, weapon=warn) ve define override desteği eklendi.
- Speed detector için absürt mesafe kill switch eklendi (`LG_SPEED_ABSURD_DISTANCE`).

## [Unreleased]

### Added
- İleri sürüm modülleri için dokümantasyon güncellemeleri devam edecek.
