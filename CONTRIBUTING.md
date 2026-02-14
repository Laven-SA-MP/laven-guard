# Katkı Rehberi

Laven Guard, sade ve üretim odaklı katkıları hedefler.

## Temel İlkeler

- Değişiklikleri küçük ve odaklı tutun.
- RP odaklı kullanım senaryolarını gözetin.
- Performans maliyetini artıran eklemelerde gerekçe belirtin.
- Türkçe dokümantasyon standardını koruyun.

## Geliştirme Akışı

1. Sorunu veya geliştirmeyi Issue ile tanımlayın.
2. İlgili kapsamı netleştirin (modül, callback, log davranışı).
3. Değişikliği minimal diff ile uygulayın.
4. Örnek kullanım ve dokümantasyonu güncelleyin.

## Kod Standartları

- SAMP 0.3.7 Pawn uyumluluğu zorunludur.
- Dış bağımlılık minimum olmalıdır (`a_samp` temel).
- Manual entegrasyon her zaman çalışmalıdır.
- Y_HOOKS entegrasyonu opsiyonel ve çakışmasız olmalıdır.

## Sürüm ve Değişiklik Kaydı

- Kullanıcıya etkili değişiklikleri `CHANGELOG.md` dosyasına ekleyin.
- Yol haritası dışı değişikliklerde teknik gerekçe belirtin.
