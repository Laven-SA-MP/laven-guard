#if defined _lg_core_included
    #endinput
#endif
#define _lg_core_included

forward LG_Core_TickDecay();
forward LG_Core_TickSpeed();

stock LG_Log(E_LG_LOG_LEVEL:level, const message[])
{
    if (level < LG_LOG_LEVEL_DEFAULT)
    {
        return 1;
    }

    new levelText[8];
    switch (level)
    {
        case LG_LOG_INFO: format(levelText, sizeof(levelText), "INFO");
        case LG_LOG_WARN: format(levelText, sizeof(levelText), "WARN");
        case LG_LOG_ERROR: format(levelText, sizeof(levelText), "ERROR");
        default: format(levelText, sizeof(levelText), "INFO");
    }

    new output[192];
    format(output, sizeof(output), "[LavenGuard][%s] %s", levelText, message);
    printf("%s", output);
    return 1;
}

stock LG_CoreResetPlayer(playerid)
{
    LG_ChatCount[playerid] = 0;
    LG_ChatWindowStart[playerid] = 0;
    LG_ChatMuteUntil[playerid] = 0;

    for (new category = 0; category < LG_SCORE_CATEGORY_COUNT; category++)
    {
        LG_Score[playerid][category] = 0;
        LG_LastScoreLogAt[playerid][category] = 0;
    }

    LG_LastPosX[playerid] = 0.0;
    LG_LastPosY[playerid] = 0.0;
    LG_LastPosZ[playerid] = 0.0;
    LG_LastInterior[playerid] = 0;
    LG_SpeedSkipUntil[playerid] = GetTickCount() + LG_SPEED_SKIP_MS;
    LG_SpeedReady[playerid] = false;
    LG_SpeedAbsurdWarnAt[playerid] = 0;

    LG_LastHealth[playerid] = 0.0;
    LG_LastHealthReady[playerid] = false;
    LG_LastArmor[playerid] = 0.0;
    LG_LastArmorReady[playerid] = false;
    LG_LastWeapon[playerid] = 0;
    LG_LastWeaponReady[playerid] = false;
    LG_LastSkin[playerid] = 0;
    LG_LastSkinReady[playerid] = false;
    LG_LastAnimIndex[playerid] = 0;
    LG_LastAnimReady[playerid] = false;
    LG_SanitySkipUntil[playerid] = GetTickCount() + LG_SANITY_GRACE_MS;
    return 1;
}

stock LG_CoreInit()
{
    if (LG_CoreStarted)
    {
        LG_Log(LG_LOG_WARN, "Init tekrar cagrildi, mevcut timerlar korunuyor.");
        return 1;
    }

    LG_DecayTimerId = SetTimer("LG_Core_TickDecay", LG_DECAY_INTERVAL_SECONDS * 1000, true);

    #if LG_SPEED_CHECK_ENABLED
        // SA-MP timerlari tam isabetli degildir; RP sunucularda maliyet/denge icin konfig edilebilir interval kullanilir.
        LG_SpeedTimerId = SetTimer("LG_Core_TickSpeed", LG_SPEED_TICK_MS, true);
    #endif

    LG_CoreStarted = true;
    LG_Log(LG_LOG_INFO, "Core init tamamlandi.");
    return 1;
}

stock LG_CoreShutdown()
{
    if (LG_DecayTimerId != -1)
    {
        KillTimer(LG_DecayTimerId);
        LG_DecayTimerId = -1;
    }

    #if LG_SPEED_CHECK_ENABLED
        if (LG_SpeedTimerId != -1)
        {
            KillTimer(LG_SpeedTimerId);
            LG_SpeedTimerId = -1;
        }
    #endif

    LG_CoreStarted = false;
    LG_Log(LG_LOG_INFO, "Core shutdown tamamlandi.");
    return 1;
}

stock LG_CoreOnPlayerConnect(playerid)
{
    LG_CoreResetPlayer(playerid);
    LG_DetectorSpeedInitPlayer(playerid);
    return 1;
}

stock LG_CoreOnPlayerDisconnect(playerid)
{
    // Disconnect aninda tum state temizlenir.
    LG_CoreResetPlayer(playerid);
    return 1;
}

public LG_Core_TickDecay()
{
    for (new playerid = 0; playerid < MAX_PLAYERS; playerid++)
    {
        if (!IsPlayerConnected(playerid))
        {
            continue;
        }

        LG_ScoreDecayAll(playerid);
    }
    return 1;
}

public LG_Core_TickSpeed()
{
    #if LG_SPEED_CHECK_ENABLED
        LG_DetectorSpeedTick();

        #if LG_SANITY_ENABLE
            LG_CoreSpeedTickCount++;
            if (LG_SANITY_TICK_EVERY_N_TICKS <= 1 || (LG_CoreSpeedTickCount % LG_SANITY_TICK_EVERY_N_TICKS) == 0)
            {
                LG_DetectorSanityTick();
            }
        #endif
    #endif
    return 1;
}
