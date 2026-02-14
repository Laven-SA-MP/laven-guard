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

stock LG_MovementPushSnapshot(playerid, now, Float:x, Float:y, Float:z, bool:onFoot, interior, vw)
{
    new index = LG_MoveIdx[playerid];

    new Float:speedSq = 0.0;
    new bool:grounded = false;

    if (LG_MoveCount[playerid] > 0)
    {
        new prevIndex = (index + LG_MOVEMENT_WINDOW - 1) % LG_MOVEMENT_WINDOW;
        new dt = now - LG_MoveTS[playerid][prevIndex];

        if (dt > 0)
        {
            new Float:dx = x - LG_MoveX[playerid][prevIndex];
            new Float:dy = y - LG_MoveY[playerid][prevIndex];
            new Float:dz = z - LG_MoveZ[playerid][prevIndex];
            new Float:hDistSq = (dx * dx) + (dy * dy);
            new Float:timeSq = float(dt * dt);

            speedSq = (hDistSq * 1000000.0) / timeSq;
            grounded = (LG_MovementAbs(dz) < 0.08 && speedSq < 4.0);
        }
    }

    LG_MoveX[playerid][index] = x;
    LG_MoveY[playerid][index] = y;
    LG_MoveZ[playerid][index] = z;
    LG_MoveTS[playerid][index] = now;
    LG_MoveOnFoot[playerid][index] = onFoot;
    LG_MoveInterior[playerid][index] = interior;
    LG_MoveVW[playerid][index] = vw;
    LG_MoveGrounded[playerid][index] = grounded;
    LG_MoveSpeedSq[playerid][index] = speedSq;

    LG_MoveIdx[playerid] = (index + 1) % LG_MOVEMENT_WINDOW;

    if (LG_MoveCount[playerid] < LG_MOVEMENT_WINDOW)
    {
        LG_MoveCount[playerid]++;
    }

    if (LG_MoveCount[playerid] >= LG_MOVEMENT_WINDOW)
    {
        LG_MoveReady[playerid] = true;
    }

    return 1;
}

stock LG_MovementSkipAndReset(playerid, now)
{
    LG_MovementSkipUntil[playerid] = now + LG_MOVEMENT_SKIP_AFTER_TELEPORT_MS;
    LG_MoveIdx[playerid] = 0;
    LG_MoveCount[playerid] = 0;
    LG_MoveReady[playerid] = false;
    return 1;
}

stock LG_MovementAnalyzeWindow(playerid)
{
    if (!LG_MoveReady[playerid])
    {
        return 0;
    }

    new latest = (LG_MoveIdx[playerid] + LG_MOVEMENT_WINDOW - 1) % LG_MOVEMENT_WINDOW;

    new speedIndex0 = latest;
    new speedIndex1 = (latest + LG_MOVEMENT_WINDOW - 1) % LG_MOVEMENT_WINDOW;
    new speedIndex2 = (latest + LG_MOVEMENT_WINDOW - 2) % LG_MOVEMENT_WINDOW;

    if (
        LG_MoveOnFoot[playerid][speedIndex0] &&
        LG_MoveOnFoot[playerid][speedIndex1] &&
        LG_MoveOnFoot[playerid][speedIndex2] &&
        LG_MoveSpeedSq[playerid][speedIndex0] > LG_MOVEMENT_ONFOOT_SPEED_LIMIT_SQ &&
        LG_MoveSpeedSq[playerid][speedIndex1] > LG_MOVEMENT_ONFOOT_SPEED_LIMIT_SQ &&
        LG_MoveSpeedSq[playerid][speedIndex2] > LG_MOVEMENT_ONFOOT_SPEED_LIMIT_SQ
    )
    {
        LG_DetectorRaise(playerid, LG_SCORE_MOVEMENT, LG_MOVEMENT_SCORE_AMOUNT, "movement sustained speed");
    }

    new zSpikeCount = 0;
    new zSpikeBest = 0;
    new hoverCount = 0;
    new hoverBest = 0;

    for (new step = 0; step < (LG_MOVEMENT_WINDOW - 1); step++)
    {
        new current = (LG_MoveIdx[playerid] + step) % LG_MOVEMENT_WINDOW;
        new next = (current + 1) % LG_MOVEMENT_WINDOW;

        new Float:dz = LG_MoveZ[playerid][next] - LG_MoveZ[playerid][current];

        if (LG_MovementAbs(dz) > LG_MOVEMENT_Z_SPIKE)
        {
            zSpikeCount++;
            if (zSpikeCount > zSpikeBest)
            {
                zSpikeBest = zSpikeCount;
            }
        }
        else
        {
            zSpikeCount = 0;
        }

        if (
            LG_MoveOnFoot[playerid][next] &&
            LG_MovementAbs(dz) < LG_MOVEMENT_HOVER_DZ_EPS &&
            LG_MoveSpeedSq[playerid][next] > LG_MOVEMENT_HOVER_MIN_HSPEED_SQ
        )
        {
            hoverCount++;
            if (hoverCount > hoverBest)
            {
                hoverBest = hoverCount;
            }
        }
        else
        {
            hoverCount = 0;
        }
    }

    if (zSpikeBest >= LG_MOVEMENT_Z_SPIKE_COUNT)
    {
        LG_DetectorRaise(playerid, LG_SCORE_MOVEMENT, LG_MOVEMENT_SCORE_AMOUNT, "movement z spike");
    }

    if (hoverBest >= LG_MOVEMENT_HOVER_COUNT)
    {
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
        #if !LG_MOVEMENT_CHECK_IN_VEHICLE
            if (inVehicle)
            {
                continue;
            }
        #endif

        new Float:x;
        new Float:y;
        new Float:z;
        GetPlayerPos(playerid, x, y, z);

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

        LG_MovementPushSnapshot(playerid, now, x, y, z, !inVehicle, interior, vw);
        LG_MovementAnalyzeWindow(playerid);
    }

    return 1;
}
