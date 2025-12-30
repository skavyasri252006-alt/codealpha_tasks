#include <stdio.h>

void add(int r, int c, int a[10][10], int b[10][10]) {
    int i, j;
    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            printf("%d ", a[i][j] + b[i][j]);
        }
        printf("\n");
    }
}

void multiply(int r1, int c1, int r2, int c2, int a[10][10], int b[10][10]) {
    int i, j, k, sum;
    int res[10][10] = {0};
    for (i = 0; i < r1; i++) {
        for (j = 0; j < c2; j++) {
            sum = 0;
            for (k = 0; k < c1; k++) {
                sum += a[i][k] * b[k][j];
            }
            res[i][j] = sum;
        }
    }
    for (i = 0; i < r1; i++) {
        for (j = 0; j < c2; j++) {
            printf("%d ", res[i][j]);
        }
        printf("\n");
    }
}

void transpose(int r, int c, int a[10][10]) {
    int i, j;
    for (j = 0; j < c; j++) {
        for (i = 0; i < r; i++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int r1, c1, r2, c2, i, j;
    int a[10][10], b[10][10];
    scanf("%d %d", &r1, &c1);
    for (i = 0; i < r1; i++)
        for (j = 0; j < c1; j++)
            scanf("%d", &a[i][j]);

    scanf("%d %d", &r2, &c2);
    for (i = 0; i < r2; i++)
        for (j = 0; j < c2; j++)
            scanf("%d", &b[i][j]);

    if (r1 == r2 && c1 == c2)
        add(r1, c1, a, b);

    if (c1 == r2)
        multiply(r1, c1, r2, c2, a, b);

    transpose(r1, c1, a);

    return 0;
}
