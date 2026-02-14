#if defined _lg_sanity_armor_included
    #endinput
#endif
#define _lg_sanity_armor_included

stock LG_DetectorSanityArmorByValue(playerid, Float:armor)
{
    if (armor < LG_ARMOR_MIN || armor > LG_ARMOR_MAX)
    {
        LG_DetectorRaise(playerid, LG_SCORE_SANITY, LG_SANITY_SCORE_AMOUNT, "sanity armor out of range");
    }

    // Ilk okumada sadece cache yazilir, jump kontrolu tetiklenmez.
    if (LG_ArmorReady[playerid] && (armor - LG_LastArmor[playerid]) > LG_ARMOR_JUMP_MAX)
    {
        LG_DetectorRaise(playerid, LG_SCORE_SANITY, LG_SANITY_SCORE_AMOUNT, "sanity armor jump");
    }

    LG_LastArmor[playerid] = armor;
    LG_ArmorReady[playerid] = true;
    return 1;
}

stock LG_DetectorSanityArmor(playerid)
{
    new Float:armor;
    GetPlayerArmour(playerid, armor);
    return LG_DetectorSanityArmorByValue(playerid, armor);
}
