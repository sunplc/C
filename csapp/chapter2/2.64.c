#include <stdio.h>
#include <assert.h>

/* Return 1 when any odd bit of x equals 1, 0 otherwise.
 * Assume w=32. */
int any_odd_one(unsigned x) {
    // mask's binary represention: 
    // 10101010 10101010 10101010 10101010
    int mask = 0xAAAAAAAA;
    return !!(x & mask);
}

int main(int argc, char* argv[])
{
    int x = 0xAAAAAAAC;
    assert(any_odd_one(x));

    return 0;
}

