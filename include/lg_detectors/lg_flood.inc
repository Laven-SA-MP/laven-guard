#if defined _lg_flood_included
    #endinput
#endif
#define _lg_flood_included

stock LG_DetectorFloodOnText(playerid, const text[])
{
    #if LG_CHAT_FLOOD_ENABLED
        new now = GetTickCount();

        if (LG_ChatMuteUntil[playerid] > now)
        {
            LG_Log(LG_LOG_WARN, "Chat mesaji engellendi: aktif mute.");
            return 0;
        }

        if ((now - LG_ChatWindowStart[playerid]) > LG_CHAT_WINDOW_MS)
        {
            LG_ChatWindowStart[playerid] = now;
            LG_ChatCount[playerid] = 0;
        }

        LG_ChatCount[playerid]++;

        if (LG_ChatCount[playerid] > LG_CHAT_FLOOD_LIMIT)
        {
            LG_ChatCount[playerid] = 0;
            LG_DetectorRaise(playerid, LG_SCORE_FLOOD, LG_FLOOD_SCORE_AMOUNT, "Chat flood algilandi");
            return 0;
        }
    #endif

    #pragma unused text
    return 1;
}
