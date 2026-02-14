# Kurulum

Bu doküman Laven Guard v0.0.4 için manual entegrasyon, modül yapısı ve policy/score ayarlarını açıklar.

## 1) Dosya Yapısı

- `include/laven_guard.inc` → public API
- `include/lg_core.inc` → init + timer + state
- `include/lg_score.inc` → score işlemleri + decay
- `include/lg_policy.inc` → eşik ve aksiyon kararları
- `include/lg_detectors/lg_flood.inc` → chat flood detector
- `include/lg_detectors/lg_speed.inc` → speed detector
- `include/lg_detectors/lg_movement.inc` → movement anomaly detector
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
> v0.0.4 ile movement ve sanity kontrolleri aynı speed tick içinde çalışır, yeni timer açılmaz.

## 3) Policy ve Score Mantığı

Akış:

1. Detector anomaly yakalar
2. `LG_ScoreAdd` ile category score artar
3. `LG_PolicyEvaluate` eşikleri kontrol eder
4. Policy aksiyonu uygulanır

Yeni kategoriler:

- `LG_SCORE_SANITY` (RP-safe default: soft warn)
- `LG_SCORE_MOVEMENT` (RP-safe default: soft warn)

## 4) Önemli Config Define'ları

### Movement

- `LG_MOVEMENT_ENABLE` (default `1`)
- `LG_MOVEMENT_TICK_EVERY_N_TICKS` (default `2`)
- `LG_MOVEMENT_WINDOW` (default `5`)
- `LG_MOVEMENT_GRACE_MS` (default `8000`)
- `LG_MOVEMENT_SKIP_AFTER_TELEPORT_MS` (default `5000`)
- `LG_MOVEMENT_CHECK_IN_VEHICLE` (default `0`)
- `LG_MOVEMENT_ONFOOT_SPEED_LIMIT` / `_SQ`
- `LG_MOVEMENT_Z_SPIKE` / `LG_MOVEMENT_Z_SPIKE_COUNT`
- `LG_MOVEMENT_HOVER_DZ_EPS`
- `LG_MOVEMENT_HOVER_MIN_HSPEED` / `_SQ`
- `LG_MOVEMENT_HOVER_COUNT`
- `LG_MOVEMENT_ABSURD_DISTANCE` / `_SQ`
- `LG_MOVEMENT_ABSURD_WARN_THROTTLE_MS`
- `LG_MOVEMENT_SCORE_AMOUNT` (default `3`)

### Movement Policy

- `LG_MOVEMENT_THRESHOLD_SOFT`
- `LG_MOVEMENT_THRESHOLD_KICK`
- `LG_MOVEMENT_THRESHOLD_BAN`
- `LG_SOFT_ACTION_MOVEMENT` (default `LG_SOFT_ACTION_WARN`)
- `LG_DECAY_AMOUNT_MOVEMENT`

### Sanity

- `LG_SANITY_ENABLE` (default `1`)
- `LG_SANITY_TICK_EVERY_N_TICKS` (default `2`)
- `LG_SANITY_GRACE_MS` (default `8000`)
- `LG_SANITY_SKIP_AFTER_TELEPORT_MS` (default `4000`)
- `LG_SANITY_SCORE_AMOUNT` (default `2`)
- `LG_SANITY_ANIM_ENABLE` (default `0`)

## 5) Performans Notları

- Tek döngü yaklaşımı korunur: speed tick içinde movement + sanity tick tetiklenir.
- Movement detector ring buffer dolmadan analiz yapmaz (window hazır olmadan raise yok).
- Tüm mesafe karşılaştırmaları squared distance ile yapılır, `sqrt` çağrısı yoktur.
- Teleport/interior/VW benzeri sıçramalarda movement kontrolü skip + reset alır.
- Debug score log default kapalıdır (`LG_DEBUG_SCORE_LOG=0`).
