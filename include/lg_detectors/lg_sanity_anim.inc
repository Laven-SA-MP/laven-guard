#if defined _lg_sanity_anim_included
    #endinput
#endif
#define _lg_sanity_anim_included

stock LG_DetectorSanityAnim(playerid)
{
    #if defined GetPlayerAnimationIndex
        new animIndex = GetPlayerAnimationIndex(playerid);

        if (animIndex < LG_ANIM_INDEX_MIN || animIndex > LG_ANIM_INDEX_MAX)
        {
            LG_DetectorRaise(playerid, LG_SCORE_SANITY, LG_SANITY_SCORE_AMOUNT, "sanity anim invalid");
        }

        LG_LastAnimIndex[playerid] = animIndex;
        LG_LastAnimReady[playerid] = true;
    #endif

    return 1;
}
