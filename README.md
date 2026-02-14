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
- `include/lg_detectors/lg_flood.inc` → chat flood detector
- `include/lg_detectors/lg_speed.inc` → speed anomaly detector

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
```

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
- Total score

## 📌 v0.0.2 Notları

- Score decay sistemi eklendi (global timer)
- Policy engine eklendi (soft/kick/ban)
- Flood detector policy akışına taşındı
- Speed detector eklendi (vehicle/interior skip, cooldown)

## 🧭 Destek

- Hata / geliştirme: GitHub Issues
- Kurulum detayları: `docs/kurulum.md`
- Yol haritası: `ROADMAP.md`

---

<sub>© LAVEN — Founded by Talha Çiftçi</sub>
