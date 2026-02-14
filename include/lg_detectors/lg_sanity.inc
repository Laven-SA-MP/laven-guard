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

        // Speed cooldown devam ederken sanity tamamen atlanir.
        if (LG_SpeedSkipUntil[playerid] > now)
        {
            continue;
        }

        // Connect/teleport grace sirasinda cache dahi guncellenmez.
        if (LG_SanitySkipUntil[playerid] > now)
        {
            continue;
        }

        // Ucuz nativeler once: weapon + skin.
        LG_DetectorSanityWeaponByValue(playerid, GetPlayerWeapon(playerid));
        LG_DetectorSanitySkinByValue(playerid, GetPlayerSkin(playerid));

        // Float nativeler ikinci sirada: health + armor.
        new Float:health;
        GetPlayerHealth(playerid, health);
        LG_DetectorSanityHealthByValue(playerid, health);

        new Float:armor;
        GetPlayerArmour(playerid, armor);
        LG_DetectorSanityArmorByValue(playerid, armor);

        // En pahali kontrol en sonda ve default kapali.
        #if defined GetPlayerAnimationIndex
            #if LG_SANITY_ANIM_ENABLE
                LG_DetectorSanityAnimByValue(playerid, GetPlayerAnimationIndex(playerid));
            #endif
        #endif
    }

    return 1;
}
