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
        case LG_SCORE_SANITY: return LG_SOFT_ACTION_SANITY;
        case LG_SCORE_MOVEMENT: return LG_SOFT_ACTION_MOVEMENT;
    }
    return LG_SOFT_ACTION_WARN;
}


stock bool:LG_PolicyCanLog(playerid, E_LG_SCORE_CATEGORY:category, now)
{
    if (LG_POLICY_LOG_THROTTLE_MS <= 0)
    {
        return true;
    }

    new lastLog = LG_LastPolicyLogAt[playerid][category];
    if (lastLog == 0 || now < lastLog || (now - lastLog) >= LG_POLICY_LOG_THROTTLE_MS)
    {
        LG_LastPolicyLogAt[playerid][category] = now;
        return true;
    }

    return false;
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

            if (LG_PolicyCanLog(playerid, category, GetTickCount()))
            {
                LG_Log(LG_LOG_WARN, logMessage);
            }
            return 1;
        }
        case LG_PENALTY_KICK:
        {
            format(logMessage, sizeof(logMessage), "KICK p:%d c:%d (%s)", playerid, _:category, reason);
            if (LG_PolicyCanLog(playerid, category, GetTickCount()))
            {
                LG_Log(LG_LOG_WARN, logMessage);
            }
            Kick(playerid);
            return 1;
        }
        case LG_PENALTY_BAN:
        {
            format(logMessage, sizeof(logMessage), "BAN p:%d c:%d (%s)", playerid, _:category, reason);
            if (LG_PolicyCanLog(playerid, category, GetTickCount()))
            {
                LG_Log(LG_LOG_ERROR, logMessage);
            }
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
        case LG_SCORE_SANITY:
        {
            softThreshold = LG_SANITY_THRESHOLD_SOFT;
            kickThreshold = LG_SANITY_THRESHOLD_KICK;
            banThreshold = LG_SANITY_THRESHOLD_BAN;
        }
        case LG_SCORE_MOVEMENT:
        {
            softThreshold = LG_MOVEMENT_THRESHOLD_SOFT;
            kickThreshold = LG_MOVEMENT_THRESHOLD_KICK;
            banThreshold = LG_MOVEMENT_THRESHOLD_BAN;
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

    if (penalty != LG_PENALTY_NONE && LG_PolicyCanLog(playerid, category, GetTickCount()))
    {
        new logMessage[144];
        format(logMessage, sizeof(logMessage), "Threshold tetiklendi p:%d c:%d score:%d (%s)", playerid, _:category, score, reason);
        LG_Log(LG_LOG_WARN, logMessage);
    }

    #if defined LG_OnPenaltyApply
        LG_OnPenaltyApply(playerid, _:category, penalty);
    #endif

    if (penalty == LG_PENALTY_NONE)
    {
        return penalty;
    }

    // RP-safe varsayilan davranis:
    // Flood = soft odakli, Speed = kick odakli, Weapon = warn odakli, Sanity = soft warn odakli.
    LG_PolicyApply(playerid, category, penalty, reason);

    #if defined LG_OnPenaltyApplied
        LG_OnPenaltyApplied(playerid, _:category, _:penalty);
    #endif

    return penalty;
}

stock E_LG_PENALTY_TYPE:LG_DetectorRaise(playerid, E_LG_SCORE_CATEGORY:category, amount, const reason[])
{
    if (category < LG_SCORE_FLOOD || category >= LG_SCORE_CATEGORY_COUNT)
    {
        return LG_PENALTY_NONE;
    }

    if (!LG_CategoryEnabled[category])
    {
        return LG_PENALTY_NONE;
    }

    LG_ScoreAdd(playerid, category, amount, reason);

    #if defined LG_OnDetection
        new newScore = LG_ScoreGet(playerid, category);
        LG_OnDetection(playerid, _:category, amount, newScore, reason);
    #endif

    return LG_PolicyEvaluate(playerid, category, reason);
}
