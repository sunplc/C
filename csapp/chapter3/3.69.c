
typedef struct {
  int first;
  a_struct a[CNT];
  int last;
} b_struct;

void test(long i, b_struct *bp) {
  int n = bp->first + bp->last;
  a_struct *ap = &bp->a[i];
  ap->x[ap->idx] = n;
}

/*

n = *(bp + 120) + *bp
ap->x = bp + 40*i
ap->idx = *(ap->x + 8)
*(ap->x + 16 + 8*ap->idx) = n

A:
0x120 is 288, 288 - 8 => 280
CNT = 280/40 = 7

B:
struct {
    long idx;
    long x[4];
} a_struct;

*/
