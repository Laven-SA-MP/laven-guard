# Kurulum

Bu doküman, Laven Guard'ın SAMP 0.3.7 Pawn projelerine manuel ve opsiyonel auto hook yaklaşımıyla entegrasyonunu açıklar.

## 1) Manuel Entegrasyon (Önerilen ve Zorunlu Taban)

Manual entegrasyon her zaman çalışır ve varsayılan yaklaşımdır.

### Adımlar

1. `laven_guard.inc` dosyasını `include/` altında konumlandırın.
2. Gamemode dosyanızda include edin:

```pawn
#include <a_samp>
#include <laven_guard>
```

3. Callback'lerde API çağrılarını tetikleyin:

```pawn
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

## 2) Opsiyonel Auto Hook Yaklaşımı (İleri Aşama)

- Y_HOOKS desteği ilerleyen sürümlerde opsiyonel olarak sunulacaktır.
- Varsayılan durumda kapalıdır.
- Amaç, mevcut gamemode callback'leriyle çakışmasız çalışmaktır.
- Y_HOOKS olmasa dahi sistem manual integration ile tam çalışmalıdır.

## 3) Sık Sorulanlar

### Soru: Gamemode içinde zaten `OnPlayerText` var, ne olacak?

Sorun olmaz. Mevcut callback'in içinde `LG_OnPlayerText(playerid, text)` çağrısını ekleyin.

- `0` dönerse mesajı engelleyin (`return 0`).
- `1` dönerse mevcut akışı sürdürün.

### Soru: Birden fazla anti-abuse sistemi kullanıyorsam?

Çağrı sırasını net tutun ve log kaynaklarını ayırın. Laven Guard'ın dönüş değerine göre kontrolü merkezde toplayın.

## 4) Notlar

- Eşik değerlerini sunucu profilinize göre test ederek belirleyin.
- Çok agresif eşikler yanlış pozitif üretebilir.
- Performans için kontrol noktalarını sınırlı callback'lerde tutun.
