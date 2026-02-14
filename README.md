# 🛡️ Laven Guard

SAMP 0.3.7 Pawn ekosistemi için RP odaklı anti-abuse / koruma framework.

Laven Guard, roleplay sunucularında oyuncu deneyimini bozan davranışları düşük maliyetle kontrol altına almak için tasarlanmış modüler bir altyapıdır.

## 🎯 Hedefler

- ⚡ **Performans:** Hafif, öngörülebilir ve düşük overhead.
- 🧩 **Modülerlik:** İhtiyacın olan koruma katmanını aç, diğerlerini kapalı tut.
- 🔌 **Tak-çalıştır yaklaşımı:** Manual entegrasyon ile hızlı devreye alma.
- 🧾 **Temiz log akışı:** İnceleme ve operasyon için sade çıktılar.
- 🏭 **Üretime hazır yapı:** Sürdürülebilir, dokümante ve yönetilebilir temel.

## 🚀 Hızlı Başlangıç

1. `include/laven_guard.inc` dosyasını projenize ekleyin.
2. Gamemode dosyanızda include edin.
3. İlgili callback'lerde Laven Guard API çağrılarını manuel olarak çalıştırın.

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
```

## 🧱 Modüller (Yakında)

- Chat Flood Guard
- Command Spam Guard
- Dialog Spam Guard
- Sanity Checks
- Movement Anomaly Detection
- Logging Pipeline

## ⚙️ Konfigürasyon Mantığı

Laven Guard, `#define` tabanlı aç/kapa modelini benimser.

- Her modül için ayrı define.
- Varsayılan: güvenli ve minimal temel.
- İhtiyaca göre RP profilinize uygun eşik yönetimi.

Detaylar için: `docs/kurulum.md`.

## 🧭 Destek

- Hata / öneri: GitHub Issues
- Sürüm planı: `ROADMAP.md`

---

<sub>© LAVEN — Founded by Talha Çiftçi</sub>
