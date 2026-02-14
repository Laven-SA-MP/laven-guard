#if defined _lg_policy_included
    #endinput
#endif
#define _lg_policy_included

stock LG_PolicyGetSoftAction(E_LG_SCORE_CATEGORY:category)
{
    switch (category)
    {
        case LG_SCORE_FLOOD: return LG_SOFT_ACTION_FLOOD;
        case LG_SCORE_SPEED: return LG_SOFT_ACTION_SPEED;
        case LG_SCORE_WEAPON: return LG_SOFT_ACTION_WEAPON;
    }
    return LG_SOFT_ACTION_WARN;
}

stock LG_PolicyApply(playerid, E_LG_SCORE_CATEGORY:category, E_LG_PENALTY_TYPE:penalty, const reason[])
{
    if (!IsPlayerConnected(playerid) || penalty == LG_PENALTY_NONE)
    {
        return 0;
    }

    new logMessage[160];

    switch (penalty)
    {
        case LG_PENALTY_SOFT:
        {
            new softAction = LG_PolicyGetSoftAction(category);

            if (softAction == LG_SOFT_ACTION_MUTE)
            {
                LG_ChatMuteUntil[playerid] = GetTickCount() + LG_SOFT_MUTE_MS;
                format(logMessage, sizeof(logMessage), "SOFT p:%d c:%d mute uygulandi (%s)", playerid, _:category, reason);
            }
            else
            {
                format(logMessage, sizeof(logMessage), "SOFT p:%d c:%d uyari kaydi (%s)", playerid, _:category, reason);
            }

            LG_Log(LG_LOG_WARN, logMessage);
            return 1;
        }
        case LG_PENALTY_KICK:
        {
            format(logMessage, sizeof(logMessage), "KICK p:%d c:%d (%s)", playerid, _:category, reason);
            LG_Log(LG_LOG_WARN, logMessage);
            Kick(playerid);
            return 1;
        }
        case LG_PENALTY_BAN:
        {
            format(logMessage, sizeof(logMessage), "BAN p:%d c:%d (%s)", playerid, _:category, reason);
            LG_Log(LG_LOG_ERROR, logMessage);
            Ban(playerid);
            return 1;
        }
    }

    return 0;
}

stock E_LG_PENALTY_TYPE:LG_PolicyResolve(E_LG_SCORE_CATEGORY:category, score)
{
    new softThreshold;
    new kickThreshold;
    new banThreshold;

    switch (category)
    {
        case LG_SCORE_FLOOD:
        {
            softThreshold = LG_FLOOD_THRESHOLD_SOFT;
            kickThreshold = LG_FLOOD_THRESHOLD_KICK;
            banThreshold = LG_FLOOD_THRESHOLD_BAN;
        }
        case LG_SCORE_SPEED:
        {
            softThreshold = LG_SPEED_THRESHOLD_SOFT;
            kickThreshold = LG_SPEED_THRESHOLD_KICK;
            banThreshold = LG_SPEED_THRESHOLD_BAN;
        }
        case LG_SCORE_WEAPON:
        {
            softThreshold = LG_WEAPON_THRESHOLD_SOFT;
            kickThreshold = LG_WEAPON_THRESHOLD_KICK;
            banThreshold = LG_WEAPON_THRESHOLD_BAN;
        }
        default:
        {
            return LG_PENALTY_NONE;
        }
    }

    if (score >= banThreshold)
    {
        return LG_PENALTY_BAN;
    }
    if (score >= kickThreshold)
    {
        return LG_PENALTY_KICK;
    }
    if (score >= softThreshold)
    {
        return LG_PENALTY_SOFT;
    }

    return LG_PENALTY_NONE;
}

stock E_LG_PENALTY_TYPE:LG_PolicyEvaluate(playerid, E_LG_SCORE_CATEGORY:category, const reason[])
{
    new score = LG_ScoreGet(playerid, category);
    new E_LG_PENALTY_TYPE:penalty = LG_PolicyResolve(category, score);

    // RP-safe varsayilan davranis:
    // Flood = soft odakli, Speed = kick odakli, Weapon = ban odakli (detector placeholder).
    LG_PolicyApply(playerid, category, penalty, reason);
    return penalty;
}

stock E_LG_PENALTY_TYPE:LG_DetectorRaise(playerid, E_LG_SCORE_CATEGORY:category, amount, const reason[])
{
    LG_ScoreAdd(playerid, category, amount, reason);
    return LG_PolicyEvaluate(playerid, category, reason);
}
