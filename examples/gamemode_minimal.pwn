#include <a_samp>
#include <laven_guard>

main()
{
    return 1;
}

public OnGameModeInit()
{
    // LG_Init core timerlarini baslatir (decay + speed tick).
    LG_Init();
    return 1;
}

public OnPlayerConnect(playerid)
{
    LG_OnPlayerConnect(playerid);
    return 1;
}

public OnPlayerText(playerid, text[])
{
    if (!LG_OnPlayerText(playerid, text))
    {
        return 0;
    }
    return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
    LG_OnPlayerDisconnect(playerid);
    return 1;
}

public LG_OnDetection(playerid, category, amount, newScore, reason[])
{
    // Varsayilan kullanimda debug log kapali oldugu icin sadece WARN/ERROR akisina odaklanin.
    // Bu callback'i audit/telemetry kaydi icin kullanabilirsiniz.
    return 1;
}

public LG_OnPenaltyApply(playerid, category, &penalty)
{
    // Override ornekleri (default davranis degismesin diye yorumlu):
    // if (category == LG_SCORE_MOVEMENT && penalty > LG_PENALTY_SOFT) penalty = LG_PENALTY_SOFT;
    // if (penalty == LG_PENALTY_BAN) penalty = LG_PENALTY_KICK;
    // if (category == LG_SCORE_SANITY) penalty = LG_PENALTY_NONE;
    return 1;
}

public LG_OnPenaltyApplied(playerid, category, penalty)
{
    // Cezadan sonra metrics/log toplama icin kullanin.
    // Default policy akisi bu callback'te degistirilmez.
    return 1;
}
