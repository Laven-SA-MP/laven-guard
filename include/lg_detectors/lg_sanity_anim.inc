#if defined _lg_sanity_anim_included
    #endinput
#endif
#define _lg_sanity_anim_included

stock LG_DetectorSanityAnimByValue(playerid, animIndex)
{
    if (animIndex < LG_ANIM_INDEX_MIN || animIndex > LG_ANIM_INDEX_MAX)
    {
        LG_DetectorRaise(playerid, LG_SCORE_SANITY, LG_SANITY_SCORE_AMOUNT, "sanity anim invalid");
    }

    LG_LastAnimIndex[playerid] = animIndex;
    LG_LastAnimReady[playerid] = true;
    return 1;
}

stock LG_DetectorSanityAnim(playerid)
{
    #if defined GetPlayerAnimationIndex
        #if LG_SANITY_ANIM_ENABLE
            return LG_DetectorSanityAnimByValue(playerid, GetPlayerAnimationIndex(playerid));
        #endif
    #endif

    return 1;
}
