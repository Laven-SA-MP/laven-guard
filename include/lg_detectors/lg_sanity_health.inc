#if defined _lg_sanity_health_included
    #endinput
#endif
#define _lg_sanity_health_included

stock LG_DetectorSanityHealth(playerid)
{
    new Float:health;
    GetPlayerHealth(playerid, health);

    if (health < LG_HEALTH_MIN || health > LG_HEALTH_MAX)
    {
        LG_DetectorRaise(playerid, LG_SCORE_SANITY, LG_SANITY_SCORE_AMOUNT, "sanity health out of range");
    }

    if (LG_LastHealthReady[playerid])
    {
        if ((health - LG_LastHealth[playerid]) > LG_HEALTH_JUMP_MAX)
        {
            LG_DetectorRaise(playerid, LG_SCORE_SANITY, LG_SANITY_SCORE_AMOUNT, "sanity health jump");
        }
    }

    LG_LastHealth[playerid] = health;
    LG_LastHealthReady[playerid] = true;
    return 1;
}
