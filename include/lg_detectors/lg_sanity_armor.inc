#if defined _lg_sanity_armor_included
    #endinput
#endif
#define _lg_sanity_armor_included

stock LG_DetectorSanityArmor(playerid)
{
    new Float:armor;
    GetPlayerArmour(playerid, armor);

    if (armor < LG_ARMOR_MIN || armor > LG_ARMOR_MAX)
    {
        LG_DetectorRaise(playerid, LG_SCORE_SANITY, LG_SANITY_SCORE_AMOUNT, "sanity armor out of range");
    }

    if (LG_LastArmorReady[playerid])
    {
        if ((armor - LG_LastArmor[playerid]) > LG_ARMOR_JUMP_MAX)
        {
            LG_DetectorRaise(playerid, LG_SCORE_SANITY, LG_SANITY_SCORE_AMOUNT, "sanity armor jump");
        }
    }

    LG_LastArmor[playerid] = armor;
    LG_LastArmorReady[playerid] = true;
    return 1;
}
