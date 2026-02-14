# Kurulum

Bu doküman Laven Guard v0.0.2 için manual entegrasyon, modül yapısı ve policy/score ayarlarını açıklar.

## 1) Dosya Yapısı

- `include/laven_guard.inc` → public API
- `include/lg_core.inc` → init + timer + state
- `include/lg_score.inc` → score işlemleri + decay
- `include/lg_policy.inc` → eşik ve aksiyon kararları
- `include/lg_detectors/lg_flood.inc` → chat flood detector
- `include/lg_detectors/lg_speed.inc` → speed detector

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

public OnPlayerDisconnect(playerid, reason)
{
    LG_OnPlayerDisconnect(playerid);
    return 1;
}
```

> Not: `LG_Init()` çağrısı core timerları başlatır (score decay + speed tick).

## 3) Policy ve Score Mantığı

Akış:

1. Detector anomaly yakalar
2. `LG_ScoreAdd` ile category score artar
3. `LG_PolicyEvaluate` eşikleri kontrol eder
4. Policy aksiyonu uygulanır

Penalty tipleri:

- `LG_PENALTY_NONE`
- `LG_PENALTY_SOFT`
- `LG_PENALTY_KICK`
- `LG_PENALTY_BAN`

Varsayılan RP-safe yaklaşım:

- Flood: soft odak
- Speed: kick odak
- Weapon: ban odak (detector placeholder)

## 4) Önemli Config Define'ları

Threshold:

- `LG_FLOOD_THRESHOLD_SOFT/KICK/BAN`
- `LG_SPEED_THRESHOLD_SOFT/KICK/BAN`

Decay:

- `LG_DECAY_INTERVAL_SECONDS`
- `LG_DECAY_AMOUNT_FLOOD`
- `LG_DECAY_AMOUNT_SPEED`

Detector:

- `LG_CHAT_FLOOD_LIMIT`
- `LG_CHAT_WINDOW_MS`
- `LG_SPEED_DISTANCE_LIMIT`
- `LG_SPEED_ABSURD_DISTANCE`
- `LG_SPEED_SKIP_MS`

Score loglama:

- `LG_SCORE_LOG_ENABLED` (`1`: aktif, `0`: tamamen sessiz)
- `LG_SCORE_LOG_THROTTLE_MS` (aynı oyuncu + kategori logları için minimum bekleme süresi)

Soft aksiyon override:

- `LG_SOFT_ACTION_FLOOD` (default: mute)
- `LG_SOFT_ACTION_SPEED` (default: warn)
- `LG_SOFT_ACTION_WEAPON` (default: warn)

## 5) Opsiyonel Auto Hook (İleri Aşama)

Y_HOOKS entegrasyonu opsiyonel plan olarak durur.
Varsayılan akış her zaman manual integration ile stabil çalışır.

## 6) Sık Sorulan

### Gamemode içinde zaten OnPlayerText varsa?

Mevcut callback içine `LG_OnPlayerText(playerid, text)` çağrısı eklenir.
Dönüş `0` ise mesaj engellenir, `1` ise normal akış sürer.

### Speed detector yanlış pozitif üretir mi?

Riski azaltmak için:

- Araç içindeyse kontrol atlanır
- Interior değişiminde cooldown uygulanır
- Eşik ve decay değerleri sunucuya göre ayarlanmalıdır
