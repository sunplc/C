
static void place(void *bp, size_t asize)
{
    /* The size of free block */
    size_t size = GET_SIZE(bp);

    if (asize > size)
        return;

    /* remainder size */
    size_t rsize = size - asize;

    /* Split the free block */
    if (rsize >= DSIZE) {
        PUT(HDRP(bp), pack(asize, 1));
        PUT(FTRP(bp), pack(asize, 1));
        bp = NEXT_BLKP(bp);
        PUT(HDRP(bp), pack(rsize, 0));
        PUT(FTRP(bp), pack(rsize, 0));
    }
    /* Set the free block as allocated */
    else {
        PUT(HDRP(bp), pack(size, 1));
        PUT(FTRP(bp), pack(size, 1));
    }
}
