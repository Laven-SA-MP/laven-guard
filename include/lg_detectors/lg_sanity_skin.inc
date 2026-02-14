#if defined _lg_sanity_skin_included
    #endinput
#endif
#define _lg_sanity_skin_included

stock LG_DetectorSanitySkinByValue(playerid, skinid)
{
    if (skinid < LG_SKIN_ID_MIN || skinid > LG_SKIN_ID_MAX)
    {
        LG_DetectorRaise(playerid, LG_SCORE_SANITY, LG_SANITY_SCORE_AMOUNT, "sanity skin invalid");
    }

    LG_LastSkin[playerid] = skinid;
    LG_LastSkinReady[playerid] = true;
    return 1;
}

stock LG_DetectorSanitySkin(playerid)
{
    return LG_DetectorSanitySkinByValue(playerid, GetPlayerSkin(playerid));
}
