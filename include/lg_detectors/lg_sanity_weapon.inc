#if defined _lg_sanity_weapon_included
    #endinput
#endif
#define _lg_sanity_weapon_included

stock LG_DetectorSanityWeaponByValue(playerid, weaponid)
{
    if (weaponid < LG_WEAPON_ID_MIN || weaponid > LG_WEAPON_ID_MAX)
    {
        LG_DetectorRaise(playerid, LG_SCORE_SANITY, LG_SANITY_SCORE_AMOUNT, "sanity weapon invalid");
    }

    LG_LastWeapon[playerid] = weaponid;
    LG_LastWeaponReady[playerid] = true;
    return 1;
}

stock LG_DetectorSanityWeapon(playerid)
{
    return LG_DetectorSanityWeaponByValue(playerid, GetPlayerWeapon(playerid));
}
