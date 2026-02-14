# Changelog

Tüm önemli değişiklikler bu dosyada tutulur.

## [0.0.3]

### Added
- Sanity detector modülleri eklendi: health, armor, weapon, skin, anim ve ortak sanity tick.
- Yeni config define grubu eklendi: sanity grace/skip/tick/range/jump/policy değerleri.
- Yeni score kategorisi `LG_SCORE_SANITY` eklendi.

### Changed
- `LG_Core_TickSpeed` içinde speed + sanity tek döngü akışına taşındı (ek timer yok).
- Speed detector, interior değişimi ve absürt delta durumlarında sanity skip süresi set etmeye başladı.
- Policy çözümleme ve soft action akışı sanity kategorisini kapsayacak şekilde genişletildi.
- Dokümantasyon dosyaları v0.0.3 kapsamına göre güncellendi.

## [0.0.2.1]

### Changed
- Speed detector mesafe hesabı karekök yerine squared distance ile optimize edildi (`LG_SPEED_LIMIT_SQ`, `LG_SPEED_ABSURD_DISTANCE_SQ`).
- Speed timer intervali konfigürasyona taşındı (`LG_SPEED_TICK_MS`).
- Log fonksiyonunda log-level gate formatlama öncesine alındı (`LG_LOG_LEVEL_DEFAULT=LG_LOG_WARN`).
- Score artış log spamı default kapatıldı (`LG_DEBUG_SCORE_LOG=0`).
- Speed tick döngüsünde erken çıkış sırası yeniden düzenlendi (connected/ready/skip/vehicle/interior).

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
