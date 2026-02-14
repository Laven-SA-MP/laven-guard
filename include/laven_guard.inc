#if defined _laven_guard_included
    #endinput
#endif
#define _laven_guard_included

// Laven Guard minimal foundation
// SAMP 0.3.7 Pawn uyumlu
// Not: Manual integration required.

#include <a_samp>

#define LG_VERSION "0.0.1"

// Konfigürasyon (örnek)
#if !defined LG_CHAT_FLOOD_ENABLED
    #define LG_CHAT_FLOOD_ENABLED 1
#endif

#if !defined LG_CHAT_FLOOD_LIMIT
    #define LG_CHAT_FLOOD_LIMIT 4
#endif

#if !defined LG_CHAT_WINDOW_MS
    #define LG_CHAT_WINDOW_MS 3000
#endif

#if !defined LG_CHAT_MUTE_MS
    #define LG_CHAT_MUTE_MS 5000
#endif

enum E_LG_PLAYER_STATE
{
    LG_ChatCount,
    LG_ChatWindowStart,
    LG_ChatMuteUntil
}

static LG_PlayerState[MAX_PLAYERS][E_LG_PLAYER_STATE];

stock LG_Log(const message[])
{
    printf("[LavenGuard] %s", message);
    return 1;
}

stock LG_Init()
{
    LG_Log("Init tamamlandi.");
    return 1;
}

stock LG_OnPlayerConnect(playerid)
{
    LG_PlayerState[playerid][LG_ChatCount] = 0;
    LG_PlayerState[playerid][LG_ChatWindowStart] = 0;
    LG_PlayerState[playerid][LG_ChatMuteUntil] = 0;
    return 1;
}

stock LG_OnPlayerText(playerid, const text[])
{
    #if LG_CHAT_FLOOD_ENABLED
        new now = GetTickCount();

        if (LG_PlayerState[playerid][LG_ChatMuteUntil] > now)
        {
            LG_Log("Chat engellendi: aktif mute.");
            return 0;
        }

        if ((now - LG_PlayerState[playerid][LG_ChatWindowStart]) > LG_CHAT_WINDOW_MS)
        {
            LG_PlayerState[playerid][LG_ChatWindowStart] = now;
            LG_PlayerState[playerid][LG_ChatCount] = 0;
        }

        LG_PlayerState[playerid][LG_ChatCount]++;

        if (LG_PlayerState[playerid][LG_ChatCount] > LG_CHAT_FLOOD_LIMIT)
        {
            LG_PlayerState[playerid][LG_ChatMuteUntil] = now + LG_CHAT_MUTE_MS;
            LG_PlayerState[playerid][LG_ChatCount] = 0;
            LG_Log("Chat flood limiti asildi, mesaj engellendi.");
            return 0;
        }
    #endif

    // text parametresi placeholder icin tutulur.
    #pragma unused text
    return 1;
}
