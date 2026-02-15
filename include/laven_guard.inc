#if defined _laven_guard_included
    #endinput
#endif
#define _laven_guard_included

// Laven Guard v0.0.5
// SAMP 0.3.7 Pawn uyumlu
// Not: Manual integration required.

#include <a_samp>

#define LG_VERSION "0.0.5"

// --------------------------------------------------
// Konfigürasyon
// --------------------------------------------------

#if !defined LG_CHAT_FLOOD_ENABLED
    #define LG_CHAT_FLOOD_ENABLED 1
#endif

#if !defined LG_CHAT_FLOOD_LIMIT
    #define LG_CHAT_FLOOD_LIMIT 4
#endif

#if !defined LG_CHAT_WINDOW_MS
    #define LG_CHAT_WINDOW_MS 3000
#endif

#if !defined LG_FLOOD_SCORE_AMOUNT
    #define LG_FLOOD_SCORE_AMOUNT 10
#endif

#if !defined LG_SPEED_CHECK_ENABLED
    #define LG_SPEED_CHECK_ENABLED 1
#endif

#if !defined LG_SPEED_TICK_MS
    #define LG_SPEED_TICK_MS 1000
#endif

#if !defined LG_SPEED_CHECK_INTERVAL_MS
    #define LG_SPEED_CHECK_INTERVAL_MS LG_SPEED_TICK_MS
#endif

#if !defined LG_SPEED_LIMIT
    #define LG_SPEED_LIMIT 50.0
#endif

#if !defined LG_SPEED_LIMIT_SQ
    #define LG_SPEED_LIMIT_SQ (LG_SPEED_LIMIT * LG_SPEED_LIMIT)
#endif

#if !defined LG_SPEED_DISTANCE_LIMIT
    #define LG_SPEED_DISTANCE_LIMIT LG_SPEED_LIMIT
#endif

#if !defined LG_SPEED_SCORE_AMOUNT
    #define LG_SPEED_SCORE_AMOUNT 20
#endif

#if !defined LG_SPEED_ABSURD_DISTANCE
    #define LG_SPEED_ABSURD_DISTANCE 500.0
#endif

#if !defined LG_SPEED_ABSURD_DISTANCE_SQ
    #define LG_SPEED_ABSURD_DISTANCE_SQ (LG_SPEED_ABSURD_DISTANCE * LG_SPEED_ABSURD_DISTANCE)
#endif

#if !defined LG_SPEED_ABSURD_WARN_THROTTLE_MS
    #define LG_SPEED_ABSURD_WARN_THROTTLE_MS 5000
#endif

#if !defined LG_SPEED_SKIP_MS
    #define LG_SPEED_SKIP_MS 5000
#endif

#if !defined LG_MOVEMENT_ENABLE
    #define LG_MOVEMENT_ENABLE 1
#endif

#if !defined LG_MOVEMENT_TICK_EVERY_N_TICKS
    #define LG_MOVEMENT_TICK_EVERY_N_TICKS 2
#endif

#if !defined LG_MOVEMENT_WINDOW
    #define LG_MOVEMENT_WINDOW 5
#endif

#if !defined LG_MOVEMENT_CHECK_IN_VEHICLE
    #define LG_MOVEMENT_CHECK_IN_VEHICLE 0
#endif

#if !defined LG_MOVEMENT_SKIP_AFTER_TELEPORT_MS
    #define LG_MOVEMENT_SKIP_AFTER_TELEPORT_MS 5000
#endif

#if !defined LG_MOVEMENT_GRACE_MS
    #define LG_MOVEMENT_GRACE_MS 8000
#endif

#if !defined LG_MOVEMENT_ONFOOT_SPEED_LIMIT
    #define LG_MOVEMENT_ONFOOT_SPEED_LIMIT 50.0
#endif

#if !defined LG_MOVEMENT_ONFOOT_SPEED_LIMIT_SQ
    #define LG_MOVEMENT_ONFOOT_SPEED_LIMIT_SQ (LG_MOVEMENT_ONFOOT_SPEED_LIMIT * LG_MOVEMENT_ONFOOT_SPEED_LIMIT)
#endif

#if !defined LG_MOVEMENT_Z_SPIKE
    #define LG_MOVEMENT_Z_SPIKE 6.0
#endif

#if !defined LG_MOVEMENT_Z_SPIKE_COUNT
    #define LG_MOVEMENT_Z_SPIKE_COUNT 2
#endif

#if !defined LG_MOVEMENT_HOVER_DZ_EPS
    #define LG_MOVEMENT_HOVER_DZ_EPS 0.15
#endif

#if !defined LG_MOVEMENT_HOVER_MIN_HSPEED
    #define LG_MOVEMENT_HOVER_MIN_HSPEED 8.0
#endif

#if !defined LG_MOVEMENT_HOVER_MIN_HSPEED_SQ
    #define LG_MOVEMENT_HOVER_MIN_HSPEED_SQ (LG_MOVEMENT_HOVER_MIN_HSPEED * LG_MOVEMENT_HOVER_MIN_HSPEED)
#endif

#if !defined LG_MOVEMENT_FAST_EPS_DIST_SQ
    #define LG_MOVEMENT_FAST_EPS_DIST_SQ 4.0
#endif

#if !defined LG_MOVEMENT_FAST_EPS_DZ
    #define LG_MOVEMENT_FAST_EPS_DZ 0.08
#endif

#if !defined LG_MOVEMENT_SUSTAIN_COUNT
    #define LG_MOVEMENT_SUSTAIN_COUNT 3
#endif

#if !defined LG_MOVEMENT_HOVER_COUNT
    #define LG_MOVEMENT_HOVER_COUNT 3
#endif

#if !defined LG_MOVEMENT_ABSURD_DISTANCE
    #define LG_MOVEMENT_ABSURD_DISTANCE 500.0
#endif

#if !defined LG_MOVEMENT_ABSURD_DISTANCE_SQ
    #define LG_MOVEMENT_ABSURD_DISTANCE_SQ (LG_MOVEMENT_ABSURD_DISTANCE * LG_MOVEMENT_ABSURD_DISTANCE)
#endif

#if !defined LG_MOVEMENT_ABSURD_WARN_THROTTLE_MS
    #define LG_MOVEMENT_ABSURD_WARN_THROTTLE_MS 60000
#endif

#if !defined LG_MOVEMENT_SCORE_AMOUNT
    #define LG_MOVEMENT_SCORE_AMOUNT 3
#endif

#if !defined LG_SANITY_ENABLE
    #define LG_SANITY_ENABLE 1
#endif

#if !defined LG_ENABLE_SPEED
    #define LG_ENABLE_SPEED 1
#endif

#if !defined LG_ENABLE_SANITY
    #define LG_ENABLE_SANITY 1
#endif

#if !defined LG_ENABLE_MOVEMENT
    #define LG_ENABLE_MOVEMENT 1
#endif

#if !defined LG_DEBUG_DEFAULT
    #define LG_DEBUG_DEFAULT 0
#endif

#if !defined LG_SANITY_TICK_EVERY_N_TICKS
    #define LG_SANITY_TICK_EVERY_N_TICKS 2
#endif

#if !defined LG_SANITY_ANIM_ENABLE
    #define LG_SANITY_ANIM_ENABLE 0
#endif

#if !defined LG_SANITY_GRACE_MS
    #define LG_SANITY_GRACE_MS 8000
#endif

#if !defined LG_SANITY_SKIP_AFTER_TELEPORT_MS
    #define LG_SANITY_SKIP_AFTER_TELEPORT_MS 4000
#endif

#if !defined LG_SANITY_SCORE_AMOUNT
    #define LG_SANITY_SCORE_AMOUNT 2
#endif

#if !defined LG_HEALTH_MIN
    #define LG_HEALTH_MIN 0.0
#endif

#if !defined LG_HEALTH_MAX
    #define LG_HEALTH_MAX 100.0
#endif

#if !defined LG_ARMOR_MIN
    #define LG_ARMOR_MIN 0.0
#endif

#if !defined LG_ARMOR_MAX
    #define LG_ARMOR_MAX 100.0
#endif

#if !defined LG_HEALTH_JUMP_MAX
    #define LG_HEALTH_JUMP_MAX 35.0
#endif

#if !defined LG_ARMOR_JUMP_MAX
    #define LG_ARMOR_JUMP_MAX 50.0
#endif

#if !defined LG_WEAPON_ID_MIN
    #define LG_WEAPON_ID_MIN 0
#endif

#if !defined LG_WEAPON_ID_MAX
    #define LG_WEAPON_ID_MAX 46
#endif

#if !defined LG_SKIN_ID_MIN
    #define LG_SKIN_ID_MIN 0
#endif

#if !defined LG_SKIN_ID_MAX
    #define LG_SKIN_ID_MAX 311
#endif

#if !defined LG_ANIM_INDEX_MIN
    #define LG_ANIM_INDEX_MIN 0
#endif

#if !defined LG_ANIM_INDEX_MAX
    #define LG_ANIM_INDEX_MAX 20000
#endif

#if !defined LG_SOFT_MUTE_MS
    #define LG_SOFT_MUTE_MS 5000
#endif

#define LG_SOFT_ACTION_MUTE 1
#define LG_SOFT_ACTION_WARN 2

#if !defined LG_SOFT_ACTION_FLOOD
    #define LG_SOFT_ACTION_FLOOD LG_SOFT_ACTION_MUTE
#endif

#if !defined LG_SOFT_ACTION_SPEED
    #define LG_SOFT_ACTION_SPEED LG_SOFT_ACTION_WARN
#endif

#if !defined LG_SOFT_ACTION_WEAPON
    #define LG_SOFT_ACTION_WEAPON LG_SOFT_ACTION_WARN
#endif

#if !defined LG_SOFT_ACTION_SANITY
    #define LG_SOFT_ACTION_SANITY LG_SOFT_ACTION_WARN
#endif

#if !defined LG_SOFT_ACTION_MOVEMENT
    #define LG_SOFT_ACTION_MOVEMENT LG_SOFT_ACTION_WARN
#endif

#if !defined LG_FLOOD_THRESHOLD_SOFT
    #define LG_FLOOD_THRESHOLD_SOFT 20
#endif

#if !defined LG_FLOOD_THRESHOLD_KICK
    #define LG_FLOOD_THRESHOLD_KICK 60
#endif

#if !defined LG_FLOOD_THRESHOLD_BAN
    #define LG_FLOOD_THRESHOLD_BAN 100
#endif

#if !defined LG_SPEED_THRESHOLD_SOFT
    #define LG_SPEED_THRESHOLD_SOFT 40
#endif

#if !defined LG_SPEED_THRESHOLD_KICK
    #define LG_SPEED_THRESHOLD_KICK 80
#endif

#if !defined LG_SPEED_THRESHOLD_BAN
    #define LG_SPEED_THRESHOLD_BAN 140
#endif

#if !defined LG_WEAPON_THRESHOLD_SOFT
    #define LG_WEAPON_THRESHOLD_SOFT 30
#endif

#if !defined LG_WEAPON_THRESHOLD_KICK
    #define LG_WEAPON_THRESHOLD_KICK 70
#endif

#if !defined LG_WEAPON_THRESHOLD_BAN
    #define LG_WEAPON_THRESHOLD_BAN 100
#endif

#if !defined LG_SANITY_THRESHOLD_SOFT
    #define LG_SANITY_THRESHOLD_SOFT 20
#endif

#if !defined LG_SANITY_THRESHOLD_KICK
    #define LG_SANITY_THRESHOLD_KICK 80
#endif

#if !defined LG_SANITY_THRESHOLD_BAN
    #define LG_SANITY_THRESHOLD_BAN 120
#endif

#if !defined LG_MOVEMENT_THRESHOLD_SOFT
    #define LG_MOVEMENT_THRESHOLD_SOFT 25
#endif

#if !defined LG_MOVEMENT_THRESHOLD_KICK
    #define LG_MOVEMENT_THRESHOLD_KICK 70
#endif

#if !defined LG_MOVEMENT_THRESHOLD_BAN
    #define LG_MOVEMENT_THRESHOLD_BAN 120
#endif

#if !defined LG_DECAY_INTERVAL_SECONDS
    #define LG_DECAY_INTERVAL_SECONDS 60
#endif

#if !defined LG_DECAY_AMOUNT_FLOOD
    #define LG_DECAY_AMOUNT_FLOOD 5
#endif

#if !defined LG_DECAY_AMOUNT_SPEED
    #define LG_DECAY_AMOUNT_SPEED 5
#endif

#if !defined LG_DECAY_AMOUNT_WEAPON
    #define LG_DECAY_AMOUNT_WEAPON 0
#endif

#if !defined LG_DECAY_AMOUNT_SANITY
    #define LG_DECAY_AMOUNT_SANITY 5
#endif

#if !defined LG_DECAY_AMOUNT_MOVEMENT
    #define LG_DECAY_AMOUNT_MOVEMENT 5
#endif

#if !defined LG_SCORE_LOG_ENABLED
    #define LG_SCORE_LOG_ENABLED 1
#endif

#if !defined LG_DEBUG_SCORE_LOG
    #define LG_DEBUG_SCORE_LOG 0
#endif

#if !defined LG_SCORE_LOG_THROTTLE_MS
    #define LG_SCORE_LOG_THROTTLE_MS 1000
#endif

#if !defined LG_POLICY_LOG_THROTTLE_MS
    #define LG_POLICY_LOG_THROTTLE_MS 1000
#endif

// --------------------------------------------------
// Enum ve global state
// --------------------------------------------------

enum E_LG_LOG_LEVEL
{
    LG_LOG_INFO,
    LG_LOG_WARN,
    LG_LOG_ERROR
}

#if !defined LG_LOG_LEVEL_DEFAULT
    #define LG_LOG_LEVEL_DEFAULT LG_LOG_WARN
#endif

enum E_LG_SCORE_CATEGORY
{
    LG_SCORE_FLOOD,
    LG_SCORE_SPEED,
    LG_SCORE_WEAPON,
    LG_SCORE_SANITY,
    LG_SCORE_MOVEMENT,
    LG_SCORE_TOTAL,
    LG_SCORE_CATEGORY_COUNT
}

enum E_LG_PENALTY_TYPE
{
    LG_PENALTY_NONE,
    LG_PENALTY_SOFT,
    LG_PENALTY_KICK,
    LG_PENALTY_BAN
}

new LG_ChatCount[MAX_PLAYERS];
new LG_ChatWindowStart[MAX_PLAYERS];
new LG_ChatMuteUntil[MAX_PLAYERS];

new LG_Score[MAX_PLAYERS][LG_SCORE_CATEGORY_COUNT];
new LG_LastScoreLogAt[MAX_PLAYERS][LG_SCORE_CATEGORY_COUNT];
new LG_LastPolicyLogAt[MAX_PLAYERS][LG_SCORE_CATEGORY_COUNT];

new Float:LG_LastPosX[MAX_PLAYERS];
new Float:LG_LastPosY[MAX_PLAYERS];
new Float:LG_LastPosZ[MAX_PLAYERS];
new LG_LastInterior[MAX_PLAYERS];
new LG_SpeedSkipUntil[MAX_PLAYERS];
new bool:LG_SpeedReady[MAX_PLAYERS];
new LG_SpeedAbsurdWarnAt[MAX_PLAYERS];

new Float:LG_LastHealth[MAX_PLAYERS];
new bool:LG_HealthReady[MAX_PLAYERS];
new Float:LG_LastArmor[MAX_PLAYERS];
new bool:LG_ArmorReady[MAX_PLAYERS];
new LG_LastWeapon[MAX_PLAYERS];
new bool:LG_LastWeaponReady[MAX_PLAYERS];
new LG_LastSkin[MAX_PLAYERS];
new bool:LG_LastSkinReady[MAX_PLAYERS];
new LG_LastAnimIndex[MAX_PLAYERS];
new bool:LG_LastAnimReady[MAX_PLAYERS];
new LG_SanitySkipUntil[MAX_PLAYERS];

new LG_MovementSkipUntil[MAX_PLAYERS];
new LG_MovementGraceUntil[MAX_PLAYERS];
new LG_MovementAbsurdWarnAt[MAX_PLAYERS];
new LG_MoveIdx[MAX_PLAYERS];
new LG_MoveCount[MAX_PLAYERS];
new bool:LG_MoveReady[MAX_PLAYERS];
new LG_MoveLastInterior[MAX_PLAYERS];
new LG_MoveLastVW[MAX_PLAYERS];
new Float:LG_MoveX[MAX_PLAYERS][LG_MOVEMENT_WINDOW];
new Float:LG_MoveY[MAX_PLAYERS][LG_MOVEMENT_WINDOW];
new Float:LG_MoveZ[MAX_PLAYERS][LG_MOVEMENT_WINDOW];
new LG_MoveTS[MAX_PLAYERS][LG_MOVEMENT_WINDOW];
new bool:LG_MoveOnFoot[MAX_PLAYERS][LG_MOVEMENT_WINDOW];

new LG_DecayTimerId = -1;
new LG_SpeedTimerId = -1;
new bool:LG_CoreStarted = false;
new LG_CoreTickCount = 0;
new bool:LG_DebugMode = false;
new bool:LG_CategoryEnabled[LG_SCORE_CATEGORY_COUNT];

forward LG_OnDetection(playerid, category, amount, newScore, reason[]);
forward LG_OnPenaltyApply(playerid, category, &penalty);
forward LG_OnPenaltyApplied(playerid, category, penalty);

#include <lg_core>
#include <lg_score>
#include <lg_policy>
#include <lg_detectors/lg_flood>
#include <lg_detectors/lg_speed>
#include <lg_detectors/lg_movement>
#include <lg_detectors/lg_sanity_health>
#include <lg_detectors/lg_sanity_armor>
#include <lg_detectors/lg_sanity_weapon>
#include <lg_detectors/lg_sanity_skin>
#include <lg_detectors/lg_sanity_anim>
#include <lg_detectors/lg_sanity>

// --------------------------------------------------
// Stabil Public API
// --------------------------------------------------

stock LG_Init()
{
    return LG_CoreInit();
}

stock LG_Shutdown()
{
    return LG_CoreShutdown();
}

stock LG_OnPlayerConnect(playerid)
{
    return LG_CoreOnPlayerConnect(playerid);
}

stock LG_OnPlayerText(playerid, const text[])
{
    return LG_DetectorFloodOnText(playerid, text);
}

stock LG_OnPlayerDisconnect(playerid)
{
    return LG_CoreOnPlayerDisconnect(playerid);
}

stock LG_SetCategoryEnabled(E_LG_SCORE_CATEGORY:category, bool:enabled)
{
    if (category < LG_SCORE_FLOOD || category >= LG_SCORE_CATEGORY_COUNT)
    {
        return 0;
    }

    // TOTAL kategori puani turetilir, disaridan kapatilmasina izin verilmez.
    if (category == LG_SCORE_TOTAL)
    {
        return 0;
    }

    LG_CategoryEnabled[category] = enabled;
    return 1;
}

stock bool:LG_IsCategoryEnabled(E_LG_SCORE_CATEGORY:category)
{
    if (category < LG_SCORE_FLOOD || category >= LG_SCORE_CATEGORY_COUNT)
    {
        return false;
    }

    // TOTAL kategori puani turetilir; daima acik kabul edilir ve disaridan degistirilemez.
    if (category == LG_SCORE_TOTAL)
    {
        return true;
    }

    return LG_CategoryEnabled[category];
}

stock LG_SetDebugMode(bool:enabled)
{
    LG_DebugMode = enabled;
    return 1;
}

stock bool:LG_IsDebugMode()
{
    return LG_DebugMode;
}
