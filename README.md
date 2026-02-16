> ⚠️ Ticari kullanım yasaktır. Detaylar için `LICENSE` dosyasını okuyun.

# 🛡️ Laven Guard

SAMP 0.3.7 Pawn ekosistemi için RP odaklı anti-abuse / koruma framework.

Laven Guard, detector + score + policy yaklaşımıyla çalışan modüler bir altyapıdır.
Detector modülleri ceza basmaz; yalnızca event ve score üretir. Policy engine, eşiklere göre aksiyon seçer.

## 🎯 Hedefler

- ⚡ Performans: düşük overhead, sade kontrol döngüsü
- 🧩 Modülerlik: detector / score / policy katmanları ayrı
- 🔌 Tak-çalıştır: manual entegrasyon her zaman aktif
- 🧾 Temiz log: sabit format, seviyeli loglama
- 🛡️ RP-safe: yanlış pozitifte sert ceza default değil

## 🏗️ Modül Yapısı

- `include/laven_guard.inc` → ana public API
- `include/lg_core.inc` → init, timer, state yönetimi
- `include/lg_score.inc` → score add/get/decay
- `include/lg_policy.inc` → eşik/policy/aksiyon
- `include/laven_guard.inc` (observability/control layer) → hook forward + runtime toggle API
- `include/lg_detectors/lg_flood.inc` → chat flood detector
- `include/lg_detectors/lg_speed.inc` → speed anomaly detector
- `include/lg_detectors/lg_movement.inc` → movement anomaly detector (window pattern)
- `include/lg_detectors/lg_sanity.inc` → sanity ortak tick girişi
- `include/lg_detectors/lg_sanity_health.inc` → health doğrulama
- `include/lg_detectors/lg_sanity_armor.inc` → armor doğrulama
- `include/lg_detectors/lg_sanity_weapon.inc` → weapon doğrulama
- `include/lg_detectors/lg_sanity_skin.inc` → skin doğrulama
- `include/lg_detectors/lg_sanity_anim.inc` → anim doğrulama

## 🚀 Hızlı Başlangıç (Manual Integration)

```pawn
#include <a_samp>
#include <laven_guard>

public OnGameModeInit()
{
    LG_Init();
    return 1;
}

public OnPlayerConnect(playerid)
{
    LG_OnPlayerConnect(playerid);
    return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
    LG_OnPlayerDisconnect(playerid);
    return 1;
}

public OnPlayerText(playerid, text[])
{
    if (!LG_OnPlayerText(playerid, text))
    {
        return 0;
    }
    return 1;
}

public OnGameModeExit()
{
    LG_Shutdown();
    return 1;
}
```


> Not: `OnPlayerDisconnect` callback entegrasyonu zorunludur; player state reset işlemi için gereklidir.

## ⚙️ Konfigürasyon Mantığı

Framework `#define` ile yönetilir:

- Detector aç/kapa
- Category threshold değerleri
- Score decay interval ve amount
- Soft/Kick/Ban policy akışı

Örnek kategoriler:

- Flood score
- Speed score
- Weapon score (placeholder)
- Movement score
- Total score

## 📌 v0.0.5 Notları

- Observability hook katmanı eklendi: `LG_OnDetection`, `LG_OnPenaltyApply`, `LG_OnPenaltyApplied`.
- Penalty apply öncesi override desteği eklendi; `LG_PENALTY_NONE` ile ceza iptal edilebilir.
- Category bazlı runtime enable/disable API eklendi: `LG_SetCategoryEnabled`.
- Debug runtime kontrolü eklendi: `LG_SetDebugMode`, `LG_IsDebugMode`, `LG_DEBUG_DEFAULT`.
- Speed/Sanity/Movement category default kontrol define'ları eklendi: `LG_ENABLE_SPEED`, `LG_ENABLE_SANITY`, `LG_ENABLE_MOVEMENT`.
- Yeni timer eklenmeden mevcut policy mimarisi korunarak entegrasyon tamamlandı.

## 🧭 Destek

- Hata / geliştirme: GitHub Issues
- Kurulum detayları: `docs/kurulum.md`
- Yol haritası: `ROADMAP.md`

---

## Attribution

- © LAVEN — Founded by Talha Çiftçi
- Bu projeyi kullanan tüm sunucular README veya dokümanlarında bu krediyi korumalıdır.
- Bu bölümün kaldırılması lisans ihlalidir.
