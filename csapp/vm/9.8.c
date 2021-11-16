
/* Search a free block which fit asize */
static void *find_fit(size_t asize)
{
    void *bp = (void *)heap_listp;
    while (!(GET_ALLOC(HDRP(bp)) && (GET_SIZE(HDRP(bp)) == 0))) {
        if (!GET_ALLOC(HDRP(bp)) && (GET_SIZE(HDRP(bp)) >= asize))
            return bp;
        else
            bp = NEXT_BLKP(bp);
    }

    return NULL;
}
