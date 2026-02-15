# ROADMAP

---

## ✅ v0.0.2 — Core Policy / Score / Decay
Durum: Tamamlandı  
Hedef: Detector, score ve policy katmanlarını ayırarak modüler anti-abuse çekirdeği kurmak.  
Açıklama: Flood + Speed detector, category score, global decay ve soft/kick/ban policy akışı eklendi.

---

## ✅ v0.0.3 — Sanity Checks
Durum: Tamamlandı  
Hedef: RP bütünlüğünü bozan anormal oyuncu durumlarını yakalamak.  
Açıklama: Weapon, skin, anim, health ve armor kontrolleri; speed tick içinde sanity doğrulama; policy entegrasyonu.

---

## ✅ v0.0.4 — Movement Anomaly (RP Safe)
Durum: Tamamlandı  
Hedef: RP akışını bozmadan teleport delta ve hareket anomalilerini filtrelemek.  
Açıklama: 3-5 tick pattern analizi, movement score/policy/decay entegrasyonu ve RP-safe skip kuralları eklendi.

---

## 🚧 v0.5 — Observability & Control Layer
Durum: Planlandı  
Hedef: Guard’ı kontrol edilebilir ve izlenebilir hale getirmek.  
Açıklama:

- LG_OnDetection hook  
- LG_OnPenaltyApply hook (override desteği)  
- LG_OnPenaltyApplied hook  
- Category bazlı enable/disable (Speed, Sanity, Movement)  
- Debug toggle ve runtime kontrol seçenekleri  
- Internal state inspect yardımcıları  

---

## 🚧 v0.6 — Profile System
Durum: Planlandı  
Hedef: Farklı RP sunucular için esnek güvenlik profilleri sunmak.  
Açıklama:

- LG_PROFILE_RELAXED  
- LG_PROFILE_RP (default)  
- LG_PROFILE_STRICT  
- Threshold ve tolerance override mekanizması  
- Profile bazlı movement ve sanity tuning  
- Profile bazlı policy tuning (soft-first / strict-first)  

---

## 🚧 v0.7 — Stability & Memory Audit
Durum: Planlandı  
Hedef: Uzun süreli üretim ortamı için sistem sağlamlaştırması.  
Açıklama:

- Tüm array ve state sınır kontrollerinin gözden geçirilmesi  
- Timer lifecycle audit  
- Score saturation cap (örn: max score limiti)  
- Integer overflow ve edge-case kontrolü  
- Reset ve skip mantıklarının tekrar validasyonu  
- Uzun süreli uptime testleri  

---

## 🚧 v0.8 — Performance Benchmark
Durum: Planlandı  
Hedef: Guard performansını ölçülebilir hale getirmek.  
Açıklama:

- 50 / 150 / 300 oyuncu test senaryosu  
- Sanity sampling karşılaştırması  
- Movement sampling karşılaştırması  
- Log seviyesi performans etkisi  
- CPU tick impact ölçümü  
- Benchmark sonuçlarının dokümante edilmesi  

---

## 🚧 v0.9 — API Freeze Candidate
Durum: Planlandı  
Hedef: v1.0 öncesi public API stabilizasyonu.  
Açıklama:

- Public API freeze  
- Breaking change listesi  
- Config stabilizasyonu  
- Dokümantasyon temizliği ve netleştirme  
- Geriye dönük uyumluluk garantisi  

---

# 🚀 v1.0 — Stable RP Edition
Hedef: Üretimde sürdürülebilir, dokümantasyonu tamamlanmış stabil sürüm.  
Açıklama:

- Modüllerin olgunlaştırılması  
- Profil sistemi aktif  
- Hook sistemi stabil  
- Benchmark sonuçları yayımlanmış  
- API sabit ve geriye dönük uyumlu  
- Production-ready RP güvenlik çekirdeği  

---

# 🔒 Post-v1 — Anti-Cheat Expansion Phase

> Not: Bu faz v1 stabil yayınlandıktan sonra başlatılacaktır.

---

## 🚧 v1.1 — Anti-Cheat Foundations
Hedef: Anti-cheat kategorilerini mevcut score/policy sistemine entegre etmek.  
Açıklama:

- AC_CATEGORY_AIM  
- AC_CATEGORY_LOS  
- AC_CATEGORY_COMBAT  
- Evidence log yapısı  
- Anti-cheat score + decay entegrasyonu  
- Shadow mode (enforce kapalı izleme modu)  

---

## 🚧 v1.2 — Aim Anomaly Engine
Hedef: Aimlock ve aimbot davranışlarını davranışsal analiz ile tespit etmek.  
Açıklama:

- Aim angle delta sampling  
- Reaction time analizi  
- Hit ratio spike detection  
- Headshot pattern analizi  
- Distance-normalized accuracy kontrolü  
- Score tabanlı enforcement  

---

## 🚧 v1.3 — Line of Sight & Wallhack Heuristics
Hedef: Wallhack ve pre-aim davranışlarını heuristik olarak yakalamak.  
Açıklama:

- Server-side line-of-sight kontrolü  
- Duvar arkası target tracking analizi  
- Pre-fire pattern detection  
- Visibility vs aim correlation analizi  
- Kanıt bazlı policy tetikleme  

---

## 🚧 v1.4 — Advanced Movement & Vehicle Exploit Detection
Hedef: Gelişmiş speed, airbreak ve vehicle physics exploitlerini engellemek.  
Açıklama:

- Z-axis uçuş analizi  
- Araç fizik sapma kontrolü  
- Interior/world uyumsuzluğu  
- Ping toleranslı teleport modeli  
- Macro rapid-fire detection  

---

## 🎯 v2.0 — Full Spectrum Guard
Hedef: Anti-abuse + Anti-cheat birleşik, davranış temelli tam koruma katmanı.  
Açıklama:

- Unified scoring engine  
- Adaptive tolerance sistemi  
- False-positive minimize edilmiş enforcement  
- Production-grade anti-cheat stabilization  
- RP-safe aggressive security modeli