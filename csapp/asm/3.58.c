
long decode2(long x, long y, long z)
{
    y = y - z;
    x = x * y;
    y = (y << 63) >> 63;
    return y ^ x;
}
