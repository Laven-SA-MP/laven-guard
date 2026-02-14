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
