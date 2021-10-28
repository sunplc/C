/*

long A[R][S][T];

long store_ele(long i, long j, long k, long *dest)
{
    *dest = A[i][j][k];
    return sizeof(A);
}

long store_ele(long i, long j, long k, long *dest)
i in %rdi, j in %rsi, k in %rdx, dest in %rcx

store_ele:
    leaq (%rsi,%rsi,2), %rax
    leaq (%rsi,%rax,4), %rax
    movq %rdi, %rsi
    salq $6, %rsi
    addq %rsi, %rdi
    addq %rax, %rdi
    addq %rdi, %rdx
    movq A(,%rdx,8), %rax
    movq %rax, (%rcx)
    movl $3640, %eax
    ret

A:
for array declared as T D[X][Y][Z], L is the size of data type T in bytes.
an array element D[i][j][k] is at memory address:
&D[i][j][k] = XD + L(i * Y * Z + j * Z + k)

B:
rax = 13*j
rdi = 65*i
rdi = rdi + rax

address = A + 8(65*i + 13*j + k)
sizeof(A) is 3640

So, we can get:
Y*Z = 65;
Z = 13;
X*Y*Z = 3640;

we Get:
X = 56, Y = 5, Z = 13

*/
