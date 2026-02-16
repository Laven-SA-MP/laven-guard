# Changelog

Tüm önemli değişiklikler bu dosyada tutulur.

## [Unreleased]

### Added
- LAVEN COMMUNITY LICENSE v1 metni eklendi ve lisans koşulları netleştirildi.
- Build signature üretimi için `scripts/generate_build_id.sh` ve `include/generated/lg_build_signature.inc` akışı eklendi.
- Startup sırasında tek seferlik lisans/attribution banner çıktısı eklendi.
- Hidden signature sabiti (`lvn_guard_core_sig_26x_decay`) core init akışına loglanmadan referanslandı.
- Güvenlik süreçleri için `SECURITY.md` eklendi.
- Kod sahipliği takibi için `.github/CODEOWNERS` eklendi.

### Changed
- README üst kısmına ticari kullanım uyarısı ve zorunlu Attribution bölümü eklendi.
- `LG_Log` çıktısına build id bilgisi entegre edildi.
- CONTRIBUTING dokümanı lisans ve attribution zorunluluklarıyla güncellendi.

## [0.0.5]

### Optimize Sprint (Observability Control Layer)
- Hook callback maliyeti optimize edildi: hook olmayan derlemelerde detection/penalty hook path'i ekstra is yapmaz.
- Penalty evaluate akisinda `LG_OnPenaltyApply` sonrasi `LG_PENALTY_NONE` erken cikisi sertlestirildi; ceza uygulanmadan akistan donulur.
- Runtime category enable kontrolleri detector entry noktalarina ve core tick dispatch katmanina alindi; disabled moduller detector/native call calistirmaz.
- `LG_Log` icinde log-level + debug gate format oncesine alinarak debug kapaliyken INFO format maliyeti sifirlandi.
- `LG_SetCategoryEnabled` ve `LG_SetDebugMode` degisiklik yoksa early-return yapacak sekilde hafifletildi.

### Added
- Observability hook forward'ları eklendi: `LG_OnDetection`, `LG_OnPenaltyApply`, `LG_OnPenaltyApplied`.
- Category bazlı runtime kontrol API'si eklendi: `LG_SetCategoryEnabled`.
- Debug runtime kontrol API'si eklendi: `LG_SetDebugMode`, `LG_IsDebugMode`.

### Changed
- `LG_VERSION` değeri `0.0.5` olarak güncellendi.
- Policy akışına ceza uygulama öncesi hook entegre edildi; hook içinde penalty by-ref değiştirilebilir hale geldi.
- `LG_PENALTY_NONE` override durumunda ceza uygulanmama davranışı eklendi.
- Detection raise akışına category enable/disable kontrolü ve detection event hook çağrısı eklendi.
- `LG_Log` davranışı debug moduna bağlandı: debug kapalıyken INFO loglar susar, WARN/ERROR her zaman basılır.
- Yeni timer eklenmeden observability/control katmanı mevcut mimariye entegre edildi.

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

### Hotfix (v0.0.4 - Hover Pattern Fix)
- Hover pattern analizi son 4 snapshot (3 delta) uzerinden hesaplanacak sekilde duzeltildi.
- `LG_MOVEMENT_HOVER_COUNT` default `3` korunarak hover tetikleme tekrar calisir hale getirildi.
- Fast filter (son 2 snapshot) ve z-spike/sustained speed akislarinin mevcut davranisi korundu.

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
