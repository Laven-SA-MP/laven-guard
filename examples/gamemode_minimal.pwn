#include <a_samp>
#include <laven_guard>

// Opsiyonel LG hook callback'leri bu ornekte bilincli olarak implement edilmiyor.
// include/laven_guard.inc callback guard'lari sayesinde derleme sorunsuz devam eder.

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
