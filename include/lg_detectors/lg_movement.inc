#if defined _lg_movement_included
    #endinput
#endif
#define _lg_movement_included

stock LG_DetectorMovementResetPlayer(playerid)
{
    LG_MovementSkipUntil[playerid] = GetTickCount() + LG_MOVEMENT_SKIP_AFTER_TELEPORT_MS;
    LG_MovementGraceUntil[playerid] = GetTickCount() + LG_MOVEMENT_GRACE_MS;
    LG_MovementAbsurdWarnAt[playerid] = 0;
    LG_MoveIdx[playerid] = 0;
    LG_MoveCount[playerid] = 0;
    LG_MoveReady[playerid] = false;
    LG_MoveLastInterior[playerid] = -1;
    LG_MoveLastVW[playerid] = -1;
    return 1;
}

stock LG_MovementAbs(Float:value)
{
    if (value < 0.0)
    {
        return -value;
    }
    return value;
}

stock bool:LG_MovementIsAbsurdDelta(playerid, index, Float:x, Float:y, Float:z)
{
    if (LG_MoveCount[playerid] <= 0)
    {
        return false;
    }

    new prevIndex = (index + LG_MOVEMENT_WINDOW - 1) % LG_MOVEMENT_WINDOW;
    new Float:dx = x - LG_MoveX[playerid][prevIndex];
    new Float:dy = y - LG_MoveY[playerid][prevIndex];
    new Float:dz = z - LG_MoveZ[playerid][prevIndex];
    new Float:distSq = (dx * dx) + (dy * dy) + (dz * dz);
    return distSq > LG_MOVEMENT_ABSURD_DISTANCE_SQ;
}

stock LG_MovementPushSnapshot(playerid, now, Float:x, Float:y, Float:z, bool:onFoot)
{
    new index = LG_MoveIdx[playerid];

    LG_MoveX[playerid][index] = x;
    LG_MoveY[playerid][index] = y;
    LG_MoveZ[playerid][index] = z;
    LG_MoveTS[playerid][index] = now;
    LG_MoveOnFoot[playerid][index] = onFoot;

    LG_MoveIdx[playerid] = (index + 1) % LG_MOVEMENT_WINDOW;

    if (LG_MoveCount[playerid] < LG_MOVEMENT_WINDOW)
    {
        LG_MoveCount[playerid]++;
    }

    if (LG_MoveCount[playerid] >= LG_MOVEMENT_WINDOW)
    {
        LG_MoveReady[playerid] = true;
    }

    return index;
}

stock LG_MovementSkipAndReset(playerid, now)
{
    LG_MovementSkipUntil[playerid] = now + LG_MOVEMENT_SKIP_AFTER_TELEPORT_MS;
    LG_MoveIdx[playerid] = 0;
    LG_MoveCount[playerid] = 0;
    LG_MoveReady[playerid] = false;
    return 1;
}

stock bool:LG_MovementFastPass(playerid, index)
{
    if (LG_MoveCount[playerid] < 2)
    {
        return true;
    }

    new prevIndex = (index + LG_MOVEMENT_WINDOW - 1) % LG_MOVEMENT_WINDOW;
    new prevPrevIndex = (index + LG_MOVEMENT_WINDOW - 2) % LG_MOVEMENT_WINDOW;

    new Float:dx = LG_MoveX[playerid][prevIndex] - LG_MoveX[playerid][prevPrevIndex];
    new Float:dy = LG_MoveY[playerid][prevIndex] - LG_MoveY[playerid][prevPrevIndex];
    new Float:dz = LG_MoveZ[playerid][prevIndex] - LG_MoveZ[playerid][prevPrevIndex];
    new Float:distSq = (dx * dx) + (dy * dy);

    if (distSq <= LG_MOVEMENT_FAST_EPS_DIST_SQ && LG_MovementAbs(dz) <= LG_MOVEMENT_FAST_EPS_DZ)
    {
        return false;
    }

    return true;
}

stock LG_MovementAnalyzeWindow(playerid)
{
    if (!LG_MoveReady[playerid] || LG_MoveCount[playerid] < 3)
    {
        return 0;
    }

    new latest = (LG_MoveIdx[playerid] + LG_MOVEMENT_WINDOW - 1) % LG_MOVEMENT_WINDOW;
    new middle = (latest + LG_MOVEMENT_WINDOW - 1) % LG_MOVEMENT_WINDOW;
    new oldest = (latest + LG_MOVEMENT_WINDOW - 2) % LG_MOVEMENT_WINDOW;

    new speedLimitCount = 0;
    new zSpikeCount = 0;
    new hoverCount = 0;
    new bool:hoverReady = (LG_MoveCount[playerid] >= 4);

    new current = oldest;

    for (new step = 0; step < 2; step++)
    {
        new next;
        if (step == 0)
        {
            next = middle;
        }
        else
        {
            next = latest;
        }

        new Float:dx = LG_MoveX[playerid][next] - LG_MoveX[playerid][current];
        new Float:dy = LG_MoveY[playerid][next] - LG_MoveY[playerid][current];
        new Float:dz = LG_MoveZ[playerid][next] - LG_MoveZ[playerid][current];

        new Float:hDistSq = (dx * dx) + (dy * dy);

        if (LG_MoveOnFoot[playerid][next] && hDistSq > LG_MOVEMENT_ONFOOT_SPEED_LIMIT_SQ)
        {
            speedLimitCount++;
        }

        if (LG_MovementAbs(dz) > LG_MOVEMENT_Z_SPIKE)
        {
            zSpikeCount++;
        }

        current = next;
    }

    if (hoverReady)
    {
        new hoverOldest = (latest + LG_MOVEMENT_WINDOW - 3) % LG_MOVEMENT_WINDOW;
        current = hoverOldest;

        for (new step = 0; step < 3; step++)
        {
            new next;
            if (step == 0)
            {
                next = (hoverOldest + 1) % LG_MOVEMENT_WINDOW;
            }
            else if (step == 1)
            {
                next = (hoverOldest + 2) % LG_MOVEMENT_WINDOW;
            }
            else
            {
                next = latest;
            }

            new Float:dx = LG_MoveX[playerid][next] - LG_MoveX[playerid][current];
            new Float:dy = LG_MoveY[playerid][next] - LG_MoveY[playerid][current];
            new Float:dz = LG_MoveZ[playerid][next] - LG_MoveZ[playerid][current];
            new Float:hDistSq = (dx * dx) + (dy * dy);

            if (
                LG_MoveOnFoot[playerid][next] &&
                LG_MovementAbs(dz) < LG_MOVEMENT_HOVER_DZ_EPS &&
                hDistSq > LG_MOVEMENT_HOVER_MIN_HSPEED_SQ
            )
            {
                hoverCount++;
            }

            current = next;
        }
    }

    new sustainNeed = LG_MOVEMENT_SUSTAIN_COUNT - 1;
    if (sustainNeed < 1)
    {
        sustainNeed = 1;
    }
    if (sustainNeed > 2)
    {
        sustainNeed = 2;
    }

    if (speedLimitCount >= sustainNeed)
    {
        LG_DetectorRaise(playerid, LG_SCORE_MOVEMENT, LG_MOVEMENT_SCORE_AMOUNT, "movement sustained speed");
    }

    if (zSpikeCount >= LG_MOVEMENT_Z_SPIKE_COUNT)
    {
        LG_DetectorRaise(playerid, LG_SCORE_MOVEMENT, LG_MOVEMENT_SCORE_AMOUNT, "movement z spike");
    }

    if (hoverCount >= LG_MOVEMENT_HOVER_COUNT)
    {
        // Teorik olarak hoverCount artik 0..3 araligina cikabilir (4 snapshot => 3 delta).
        LG_DetectorRaise(playerid, LG_SCORE_MOVEMENT, LG_MOVEMENT_SCORE_AMOUNT, "movement hover");
    }

    return 1;
}

stock LG_DetectorMovementTick()
{
    new now = GetTickCount();

    for (new playerid = 0; playerid < MAX_PLAYERS; playerid++)
    {
        if (!IsPlayerConnected(playerid))
        {
            continue;
        }

        #if !LG_MOVEMENT_ENABLE
            continue;
        #endif

        if (LG_MovementGraceUntil[playerid] > now)
        {
            continue;
        }

        if (LG_MovementSkipUntil[playerid] > now)
        {
            continue;
        }

        // Speed tarafinda cooldown aktifse hareket analizi RP-safe icin bekletilir.
        if (LG_SpeedSkipUntil[playerid] > now)
        {
            continue;
        }

        new bool:inVehicle = IsPlayerInAnyVehicle(playerid);

        new Float:x;
        new Float:y;
        new Float:z;
        GetPlayerPos(playerid, x, y, z);

        #if !LG_MOVEMENT_CHECK_IN_VEHICLE
            if (inVehicle)
            {
                LG_MovementPushSnapshot(playerid, now, x, y, z, false);
                continue;
            }
        #endif

        new interior = GetPlayerInterior(playerid);
        new vw = GetPlayerVirtualWorld(playerid);

        if (LG_MoveLastInterior[playerid] == -1)
        {
            LG_MoveLastInterior[playerid] = interior;
            LG_MoveLastVW[playerid] = vw;
        }

        if (interior != LG_MoveLastInterior[playerid] || vw != LG_MoveLastVW[playerid])
        {
            LG_MoveLastInterior[playerid] = interior;
            LG_MoveLastVW[playerid] = vw;
            LG_MovementSkipAndReset(playerid, now);
            continue;
        }

        new index = LG_MoveIdx[playerid];
        if (LG_MovementIsAbsurdDelta(playerid, index, x, y, z))
        {
            LG_MovementSkipAndReset(playerid, now);
            if ((now - LG_MovementAbsurdWarnAt[playerid]) >= LG_MOVEMENT_ABSURD_WARN_THROTTLE_MS)
            {
                new warnMessage[120];
                format(warnMessage, sizeof(warnMessage), "movement absurd skip p:%d", playerid);
                LG_Log(LG_LOG_WARN, warnMessage);
                LG_MovementAbsurdWarnAt[playerid] = now;
            }
            continue;
        }

        index = LG_MovementPushSnapshot(playerid, now, x, y, z, true);

        if (!LG_MovementFastPass(playerid, index))
        {
            continue;
        }

        LG_MovementAnalyzeWindow(playerid);
    }

    return 1;
}
