#if defined _lg_sanity_included
    #endinput
#endif
#define _lg_sanity_included

stock LG_DetectorSanityTick()
{
    new now = GetTickCount();

    for (new playerid = 0; playerid < MAX_PLAYERS; playerid++)
    {
        if (!IsPlayerConnected(playerid))
        {
            continue;
        }

        if (LG_SanitySkipUntil[playerid] > now)
        {
            continue;
        }

        LG_DetectorSanityHealth(playerid);
        LG_DetectorSanityArmor(playerid);
        LG_DetectorSanityWeapon(playerid);
        LG_DetectorSanitySkin(playerid);
        LG_DetectorSanityAnim(playerid);
    }

    return 1;
}
