#if defined _lg_score_included
    #endinput
#endif
#define _lg_score_included

stock LG_ScoreAdd(playerid, E_LG_SCORE_CATEGORY:category, amount, const reason[])
{
    if (!IsPlayerConnected(playerid) || amount <= 0)
    {
        return 0;
    }

    LG_Score[playerid][category] += amount;

    if (category != LG_SCORE_TOTAL)
    {
        LG_Score[playerid][LG_SCORE_TOTAL] += amount;
    }

    #if LG_SCORE_LOG_ENABLED
        new currentTick = GetTickCount();
        new lastLogTick = LG_LastScoreLogAt[playerid][category];

        if (
            LG_SCORE_LOG_THROTTLE_MS <= 0 ||
            lastLogTick == 0 ||
            currentTick < lastLogTick ||
            (currentTick - lastLogTick) >= LG_SCORE_LOG_THROTTLE_MS
        )
        {
            LG_LastScoreLogAt[playerid][category] = currentTick;

            new logMessage[144];
            format(
                logMessage,
                sizeof(logMessage),
                "Score eklendi p:%d c:%d +%d (%s)",
                playerid,
                _:category,
                amount,
                reason
            );
            LG_Log(LG_LOG_INFO, logMessage);
        }
    #endif

    return 1;
}

stock LG_ScoreGet(playerid, E_LG_SCORE_CATEGORY:category)
{
    if (!IsPlayerConnected(playerid))
    {
        return 0;
    }
    return LG_Score[playerid][category];
}

stock LG_ScoreDecayAll(playerid)
{
    if (!IsPlayerConnected(playerid))
    {
        return 0;
    }

    LG_Score[playerid][LG_SCORE_FLOOD] -= LG_DECAY_AMOUNT_FLOOD;
    if (LG_Score[playerid][LG_SCORE_FLOOD] < 0)
    {
        LG_Score[playerid][LG_SCORE_FLOOD] = 0;
    }

    LG_Score[playerid][LG_SCORE_SPEED] -= LG_DECAY_AMOUNT_SPEED;
    if (LG_Score[playerid][LG_SCORE_SPEED] < 0)
    {
        LG_Score[playerid][LG_SCORE_SPEED] = 0;
    }

    LG_Score[playerid][LG_SCORE_WEAPON] -= LG_DECAY_AMOUNT_WEAPON;
    if (LG_Score[playerid][LG_SCORE_WEAPON] < 0)
    {
        LG_Score[playerid][LG_SCORE_WEAPON] = 0;
    }

    LG_Score[playerid][LG_SCORE_TOTAL] =
        LG_Score[playerid][LG_SCORE_FLOOD] +
        LG_Score[playerid][LG_SCORE_SPEED] +
        LG_Score[playerid][LG_SCORE_WEAPON];

    return 1;
}
