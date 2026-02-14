# Kurulum

Bu doküman Laven Guard v0.0.3 için manual entegrasyon, modül yapısı ve policy/score ayarlarını açıklar.

## 1) Dosya Yapısı

- `include/laven_guard.inc` → public API
- `include/lg_core.inc` → init + timer + state
- `include/lg_score.inc` → score işlemleri + decay
- `include/lg_policy.inc` → eşik ve aksiyon kararları
- `include/lg_detectors/lg_flood.inc` → chat flood detector
- `include/lg_detectors/lg_speed.inc` → speed detector
- `include/lg_detectors/lg_sanity.inc` → sanity ortak tick akışı
- `include/lg_detectors/lg_sanity_health.inc` → health doğrulama
- `include/lg_detectors/lg_sanity_armor.inc` → armor doğrulama
- `include/lg_detectors/lg_sanity_weapon.inc` → weapon doğrulama
- `include/lg_detectors/lg_sanity_skin.inc` → skin doğrulama
- `include/lg_detectors/lg_sanity_anim.inc` → anim doğrulama

## 2) Manual Entegrasyon (Zorunlu Taban)

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

public OnPlayerDisconnect(playerid, reason)
{
    LG_OnPlayerDisconnect(playerid);
    return 1;
}
```

> Not: `LG_Init()` çağrısı core timerları başlatır (score decay + speed tick).
> v0.0.3 ile sanity kontrolleri aynı speed tick içinde çalışır, yeni timer açılmaz.

## 3) Policy ve Score Mantığı

Akış:

1. Detector anomaly yakalar
2. `LG_ScoreAdd` ile category score artar
3. `LG_PolicyEvaluate` eşikleri kontrol eder
4. Policy aksiyonu uygulanır

Yeni kategori:

- `LG_SCORE_SANITY` (RP-safe default: soft warn)

## 4) Önemli Config Define'ları

### Sanity

- `LG_SANITY_ENABLE` (default `1`)
- `LG_SANITY_TICK_EVERY_N_TICKS` (default `2`)
- `LG_SANITY_GRACE_MS` (default `8000`)
- `LG_SANITY_SKIP_AFTER_TELEPORT_MS` (default `4000`)
- `LG_SANITY_SCORE_AMOUNT` (default `2`)
- `LG_SANITY_ANIM_ENABLE` (default `0`)

### Sanity Aralıkları

- `LG_HEALTH_MIN` / `LG_HEALTH_MAX`
- `LG_ARMOR_MIN` / `LG_ARMOR_MAX`
- `LG_HEALTH_JUMP_MAX`
- `LG_ARMOR_JUMP_MAX`
- `LG_WEAPON_ID_MIN` / `LG_WEAPON_ID_MAX`
- `LG_SKIN_ID_MIN` / `LG_SKIN_ID_MAX`
- `LG_ANIM_INDEX_MIN` / `LG_ANIM_INDEX_MAX`

### Policy

- `LG_SANITY_THRESHOLD_SOFT`
- `LG_SANITY_THRESHOLD_KICK`
- `LG_SANITY_THRESHOLD_BAN`
- `LG_SOFT_ACTION_SANITY` (default `LG_SOFT_ACTION_WARN`)
- `LG_POLICY_LOG_THROTTLE_MS` (default `1000`)

## 5) Performans Notları

- Tek döngü yaklaşımı korunur: speed tick içinde sanity tick tetiklenir.
- Teleport/interior benzeri sıçramalarda sanity kontrolü geçici skip alır.
- Debug score log default kapalıdır (`LG_DEBUG_SCORE_LOG=0`).
