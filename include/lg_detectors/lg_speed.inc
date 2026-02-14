#if defined _lg_speed_included
    #endinput
#endif
#define _lg_speed_included

stock LG_DetectorSpeedInitPlayer(playerid)
{
    if (!IsPlayerConnected(playerid))
    {
        return 0;
    }

    GetPlayerPos(playerid, LG_LastPosX[playerid], LG_LastPosY[playerid], LG_LastPosZ[playerid]);
    LG_LastInterior[playerid] = GetPlayerInterior(playerid);
    LG_SpeedSkipUntil[playerid] = GetTickCount() + LG_SPEED_SKIP_MS;
    LG_SpeedReady[playerid] = true;
    return 1;
}

stock LG_DetectorSpeedTick()
{
    new now = GetTickCount();

    for (new playerid = 0; playerid < MAX_PLAYERS; playerid++)
    {
        if (!IsPlayerConnected(playerid))
        {
            continue;
        }

        if (!LG_SpeedReady[playerid])
        {
            LG_DetectorSpeedInitPlayer(playerid);
            continue;
        }

        new Float:x;
        new Float:y;
        new Float:z;
        GetPlayerPos(playerid, x, y, z);

        if (IsPlayerInAnyVehicle(playerid))
        {
            LG_LastPosX[playerid] = x;
            LG_LastPosY[playerid] = y;
            LG_LastPosZ[playerid] = z;
            continue;
        }

        new interior = GetPlayerInterior(playerid);
        if (interior != LG_LastInterior[playerid])
        {
            LG_LastInterior[playerid] = interior;
            LG_SpeedSkipUntil[playerid] = now + LG_SPEED_SKIP_MS;

            LG_LastPosX[playerid] = x;
            LG_LastPosY[playerid] = y;
            LG_LastPosZ[playerid] = z;
            continue;
        }

        if (LG_SpeedSkipUntil[playerid] > now)
        {
            LG_LastPosX[playerid] = x;
            LG_LastPosY[playerid] = y;
            LG_LastPosZ[playerid] = z;
            continue;
        }

        new Float:dx = x - LG_LastPosX[playerid];
        new Float:dy = y - LG_LastPosY[playerid];
        new Float:dz = z - LG_LastPosZ[playerid];
        new Float:distance = floatsqroot((dx * dx) + (dy * dy) + (dz * dz));

        if (distance > LG_SPEED_ABSURD_DISTANCE)
        {
            // Absurt distance kill switch: score basma, cooldown baslat, pozisyonu guncelle.
            LG_SpeedSkipUntil[playerid] = now + LG_SPEED_SKIP_MS;

            if ((now - LG_SpeedAbsurdWarnAt[playerid]) >= LG_SPEED_ABSURD_WARN_THROTTLE_MS)
            {
                new logMessage[160];
                format(logMessage, sizeof(logMessage), "Speed absurt delta ignore p:%d dist:%.2f", playerid, distance);
                LG_Log(LG_LOG_WARN, logMessage);
                LG_SpeedAbsurdWarnAt[playerid] = now;
            }

            LG_LastPosX[playerid] = x;
            LG_LastPosY[playerid] = y;
            LG_LastPosZ[playerid] = z;
            continue;
        }

        if (distance > LG_SPEED_DISTANCE_LIMIT)
        {
            LG_DetectorRaise(playerid, LG_SCORE_SPEED, LG_SPEED_SCORE_AMOUNT, "Speed anomaly algilandi");
            LG_SpeedSkipUntil[playerid] = now + LG_SPEED_SKIP_MS;
        }

        LG_LastPosX[playerid] = x;
        LG_LastPosY[playerid] = y;
        LG_LastPosZ[playerid] = z;
    }

    return 1;
}
