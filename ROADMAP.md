# ROADMAP

---

## ✅ v0.0.2 — Core Policy / Score / Decay
**Durum:** Tamamlandı  
**Hedef:** Detector, score ve policy katmanlarını ayırarak modüler anti-abuse çekirdeği kurmak.  
**Açıklama:** Flood + Speed detector, category score, global decay ve soft/kick/ban policy akışı eklendi.

---

## ✅ v0.0.3 — Sanity Checks
**Durum:** Tamamlandı  
**Hedef:** RP bütünlüğünü bozan anormal oyuncu durumlarını yakalamak.  
**Açıklama:** Weapon, skin, anim, health ve armor kontrolleri; speed tick içinde sanity doğrulama; policy entegrasyonu.

---

## ✅ v0.0.4 — Movement Anomaly (RP Safe)
**Durum:** Tamamlandı  
**Hedef:** RP akışını bozmadan teleport delta ve hareket anomalilerini filtrelemek.  
**Açıklama:** 3-5 tick pattern analizi, movement score/policy/decay entegrasyonu ve RP-safe skip kuralları eklendi.

---

## 🚧 v0.5 — Observability & Control Layer
**Durum:** Planlandı  
**Hedef:** Guard’ı kontrol edilebilir ve izlenebilir hale getirmek.  
**Açıklama:**
- `LG_OnDetection` hook
- `LG_OnPenaltyApply` hook (override desteği)
- `LG_OnPenaltyApplied` hook
- Category bazlı enable/disable (Speed, Sanity, Movement)
- Debug toggle ve runtime kontrol seçenekleri

---

## 🚧 v0.6 — Profile System
**Durum:** Planlandı  
**Hedef:** Farklı RP sunucular için esnek güvenlik profilleri sunmak.  
**Açıklama:**
- `LG_PROFILE_RELAXED`
- `LG_PROFILE_RP` (default)
- `LG_PROFILE_STRICT`
- Threshold ve tolerance override mekanizması
- Profile bazlı movement ve sanity tuning

---

## 🚧 v0.7 — Stability & Memory Audit
**Durum:** Planlandı  
**Hedef:** Uzun süreli üretim ortamı için sistem sağlamlaştırması.  
**Açıklama:**
- Tüm array ve state sınır kontrollerinin gözden geçirilmesi
- Timer lifecycle audit
- Score saturation cap (örn: max score limiti)
- Integer overflow ve edge-case kontrolü
- Reset ve skip mantıklarının tekrar validasyonu

---

## 🚧 v0.8 — Performance Benchmark
**Durum:** Planlandı  
**Hedef:** Guard performansını ölçülebilir hale getirmek.  
**Açıklama:**
- 50 / 150 / 300 oyuncu test senaryosu
- Sanity sampling karşılaştırması
- Movement sampling karşılaştırması
- Log seviyesi performans etkisi
- Benchmark sonuçlarının dokümante edilmesi

---

## 🚧 v0.9 — API Freeze Candidate
**Durum:** Planlandı  
**Hedef:** v1.0 öncesi public API stabilizasyonu.  
**Açıklama:**
- Public API freeze
- Breaking change listesi
- Config stabilizasyonu
- Dokümantasyon temizliği ve netleştirme
- Geriye dönük uyumluluk garantisi

---

## 🚀 v1.0 — Stable RP Edition
**Hedef:** Üretimde sürdürülebilir, dokümantasyonu tamamlanmış stabil sürüm.  
**Açıklama:**
- Modüllerin olgunlaştırılması
- Profil sistemi aktif
- Hook sistemi stabil
- Benchmark sonuçları yayımlanmış
- API sabit ve geriye dönük uyumlu