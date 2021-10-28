
typedef enum range_t {NEG, ZERO, POS, OTHER} range_t;

range_t find_range(float x)
{
    if (x < 0)
        return NEG;
    else if (x == 0)
        return ZERO;
    else if (x > 0)
        return POS;
    else
        return OTHER;
}
