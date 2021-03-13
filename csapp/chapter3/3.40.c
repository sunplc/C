#include <stdio.h>

#define N 16

typedef int fix_matrix[N][N];

void fix_set_diag_opt(fix_matrix A, int val) {

    int a = 0;

    do {

        *((int *)A + a) = val;
        a += (N + 1);

    } while (a != (N + 1) * N);
}

int main()
{
    fix_matrix A;

    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            A[i][j] = 0;
        }
    }

    fix_set_diag_opt(A, 3);


    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }
}
