#include <cstdio>
#include <ctime>
#include <cstdlib>
// TASK 1
// ACCOMPLISH QUICK_SORT

void swap_int(int *a, int *b)
{
    int t;
    t = *a;
    *a = *b;
    *b = t;
}

int rand_int(int l, int r) // [l,r]
{
    return (rand() % (r - l + 1)) + l;
}

int partition(int *A, int p, int r)
{
    int x = A[r];
    int i = p - 1;
    for (int j = p; j <= r - 1; ++j)
    {
        if (A[j] <= x)
        {
            i = i + 1;
            swap_int(A + i, A + j);
        }
    }
    swap_int(A + i + 1, A + r);
    return i + 1;
}

int ramdon_partition(int *A, int p, int r)
{
    int i = rand_int(p, r);
    swap_int(A + r, A + i);
    return partition(A, p, r);
}

void random_quicksort(int *A, int p, int r)
{
    if (p < r)
    {
        int q = ramdon_partition(A, p, r);
        random_quicksort(A, p, q - 1);
        random_quicksort(A, q + 1, r);
    }
}

const int MAX_LEN = 123456;

int main()
{
    clock_t start, end;
    printf("%d\n", 888);
    FILE *fp_in = fopen("./data.txt", "r");
    printf("%d\n", 999);
    FILE *fp_out = fopen("./out.txt", "w");
    printf("%d\n", 111);
    int num;
    int *A = (int *)malloc(sizeof(int) * MAX_LEN);
    printf("%d\n", 222);
    fscanf(fp_in, "%d", &num);
    printf("%d\n", num);
    for (int k = 0; k < num; ++k)
    {
        //printf("%d\n",k);
        fscanf(fp_in, "%d", &A[k]);
    }
    printf("%d\n", 111111);
    start = clock();
    random_quicksort(A, 0, num - 1);
    end = clock();
    for (int k = 0; k < num; ++k)
    {
        fprintf(fp_out, "%d ", A[k]);
    }
    printf("TIME: %d", end - start);
}