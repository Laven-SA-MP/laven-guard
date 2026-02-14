# Changelog

Tüm önemli değişiklikler bu dosyada tutulur.

## [0.0.4]

### Added
- Yeni movement detector modülü eklendi: `include/lg_detectors/lg_movement.inc`.
- Yeni score kategorisi `LG_SCORE_MOVEMENT` eklendi.
- Movement pattern analizi eklendi: sustained speed, z spike ve hover.
- Movement ring buffer altyapısı eklendi (`LG_MOVEMENT_WINDOW=5`).
- Movement teleport/absurd delta için RP-safe skip + throttled warn log eklendi.

### Changed
### Optimize Sprint (Movement Anomali Maliyet Dusurme)
- Movement detector iki asamali akisla optimize edildi: hizli filtre (distSq + dz) ve tetiklenirse 3 snapshot pattern analizi.
- Sustained speed kontrolunde zaman normalize bolmesi kaldirildi; ard arda squared hiz limit asimlari sayiliyor (`LG_MOVEMENT_SUSTAIN_COUNT`).
- Hover ve z-spike hesaplari tek pass/minimum snapshot ile sadeletirildi, ekstra normalize ve sqrt benzeri maliyetler korunarak kaldirildi.
- Ring buffer state sadeletirildi: buffer sadece pos/tick/onFoot tutuyor, interior/VW son durum state disinda izleniyor.
- Movement tick early-exit sirasi sertlestirildi; skip kosullari analizden once daha agresif uygulanir hale getirildi.

- `LG_VERSION` değeri `0.0.4` olarak güncellendi.
- Core speed tick akışına movement sampling entegre edildi (ek timer açılmadı).
- Policy ve decay mimarisi movement kategorisini kapsayacak şekilde genişletildi.
- README, kurulum dokümanı ve roadmap v0.0.4 kapsamına göre güncellendi.

## [0.0.3]

### Added
- Sanity detector modülleri eklendi: health, armor, weapon, skin, anim ve ortak sanity tick.
- Yeni config define grubu eklendi: sanity grace/skip/tick/range/jump/policy değerleri.
- Yeni score kategorisi `LG_SCORE_SANITY` eklendi.

### Changed
### Optimize Sprint (Sanity Odakli)
- Sanity tick sampling default `LG_SANITY_TICK_EVERY_N_TICKS=2` yapildi; speed tick her turde, sanity modulo ile calisir.
- Sanity detector tek pass akisina alindi; native cagrilari ucuzdan pahaliya siralandi (weapon/skin -> health/armor -> anim).
- Speed cooldown aktifken sanity tamamen skip edilir; grace suresinde cache guncellemesi yapilmaz.
- Health/armor jump kontrolu cache-ready flag ile sertlestirildi (`LG_HealthReady`, `LG_ArmorReady`), ilk okumada raise yapilmaz.
- Anim sanity kontrolu config ile default kapatildi (`LG_SANITY_ANIM_ENABLE=0`).
- Policy loglari kategori bazli throttle aldi (`LG_POLICY_LOG_THROTTLE_MS=1000`) ve log spami kisitlandi.

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
