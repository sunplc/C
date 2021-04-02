
/*

(gdb) x/6gx 0x4006f8
0x4006f8: 0x00000000004005a1 0x00000000004005c3
0x400708: 0x00000000004005a1 0x00000000004005aa
0x400718: 0x00000000004005b2 0x00000000004005bf

long switch_prob(long x, long n)
x in %rdi, n in %rsi
0000000000400590 <switch_prob>:
    400590: 48 83 ee 3c             sub $0x3c,%rsi
    400594: 48 83 fe 05             cmp $0x5,%rsi
    400598: 77 29                   ja 4005c3 <switch_prob+0x33>
    40059a: ff 24 f5 f8 06 40 00    jmpq *0x4006f8(,%rsi,8)
    4005a1: 48 8d 04 fd 00 00 00    lea 0x0(,%rdi,8),%rax
    4005a8: 00
    4005a9: c3                      retq
    4005aa: 48 89 f8                mov %rdi,%rax
    4005ad: 48 c1 f8 03             sar $0x3,%rax
    4005b1: c3                      retq
    4005b2: 48 89 f8                mov %rdi,%rax
    4005b5: 48 c1 e0 04             shl $0x4,%rax
    4005b9: 48 29 f8                sub %rdi,%rax
    4005bc: 48 89 c7                mov %rax,%rdi
    4005bf: 48 0f af ff             imul %rdi,%rdi
    4005c3: 48 8d 47 4b             lea 0x4b(%rdi),%rax
    4005c7: c3                      retq
 */
long switch_prob_goto(long x, long n) {
    long result = x;

    n -= 60;

    if (n > 5)
        goto loc_def;

    static void *jt[6] = {
        &&loc_A,
        &&loc_def,
        &&loc_A,
        &&loc_C,
        &&loc_D,
        &&loc_E,
    };

    goto *jt[n];

    loc_A:
        result = 8 * x;
        goto done;

    loc_C:
        result = x >> 3;
        goto done;

    loc_D:
        x = (x << 4) - x;

    loc_E:
        x = x * x;

    loc_def:
        result = x + 0x4b;
    done:

    return result;
}

long switch_prob(long x, long n) {
    long result = x;

    switch (n) {
    case 60:
    case 62:
        result = 8 * x;
        break;
    case 63:
        result = x >> 3;
        break;
    case 64:
        x = (x << 4) - x;
    case 65:
        x = x * x;

    case 61:
    default:
        result = x + 0x4b;
    }

    return result;
}
