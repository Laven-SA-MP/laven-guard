#if defined _laven_guard_included
    #endinput
#endif
#define _laven_guard_included

// Laven Guard v0.0.2
// SAMP 0.3.7 Pawn uyumlu
// Not: Manual integration required.

#include <a_samp>

#define LG_VERSION "0.0.2"

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

#if !defined LG_SPEED_CHECK_INTERVAL_MS
    #define LG_SPEED_CHECK_INTERVAL_MS 1000
#endif

#if !defined LG_SPEED_DISTANCE_LIMIT
    #define LG_SPEED_DISTANCE_LIMIT 120.0
#endif

#if !defined LG_SPEED_SCORE_AMOUNT
    #define LG_SPEED_SCORE_AMOUNT 20
#endif

#if !defined LG_SPEED_ABSURD_DISTANCE
    #define LG_SPEED_ABSURD_DISTANCE 500.0
#endif

#if !defined LG_SPEED_ABSURD_WARN_THROTTLE_MS
    #define LG_SPEED_ABSURD_WARN_THROTTLE_MS 5000
#endif

#if !defined LG_SPEED_SKIP_MS
    #define LG_SPEED_SKIP_MS 5000
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

#if !defined LG_SCORE_LOG_ENABLED
    #define LG_SCORE_LOG_ENABLED 1
#endif

#if !defined LG_SCORE_LOG_THROTTLE_MS
    #define LG_SCORE_LOG_THROTTLE_MS 1000
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

enum E_LG_SCORE_CATEGORY
{
    LG_SCORE_FLOOD,
    LG_SCORE_SPEED,
    LG_SCORE_WEAPON,
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

new Float:LG_LastPosX[MAX_PLAYERS];
new Float:LG_LastPosY[MAX_PLAYERS];
new Float:LG_LastPosZ[MAX_PLAYERS];
new LG_LastInterior[MAX_PLAYERS];
new LG_SpeedSkipUntil[MAX_PLAYERS];
new bool:LG_SpeedReady[MAX_PLAYERS];
new LG_SpeedAbsurdWarnAt[MAX_PLAYERS];

new LG_DecayTimerId = -1;
new LG_SpeedTimerId = -1;
new bool:LG_CoreStarted = false;

#include <lg_core>
#include <lg_score>
#include <lg_policy>
#include <lg_detectors/lg_flood>
#include <lg_detectors/lg_speed>

// --------------------------------------------------
// Stabil Public API
// --------------------------------------------------

stock LG_Init()
{
    return LG_CoreInit();
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
