#include <cstdio>
#include <ctime>
#include <cstdlib>

// TASK 2
// OPTIMIZE THE ALGORITHM

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

void insertion_sort(int *A, int l, int r)// [l,r]
{
    int key;
    int i;
    for (int j = l + 1; j <= r; ++j)
    {
        key = A[j];
        i = j - 1;
        while (i >= l && A[i] > key)
        {
            A[i + 1] = A[i];
            i = i - 1;
        }
        A[i + 1] = key;
    }
}

void hybird_sort(int *A, int l, int r, int k)
{
    while (l < r)
    {
        if (r - l + 1 < k)
        {
            insertion_sort(A, l, r);
            break;
        }
        else
        {
            int pivot = ramdon_partition(A, l, r);
            if (pivot - l < r - pivot)
            {
                hybird_sort(A, l, pivot - 1, k);
                l = pivot + 1;
            }
            else
            {
                hybird_sort(A, pivot + 1, r, k);
                r = pivot - 1;
            }
        }
    }
}

int main()
{
    clock_t start, end;
    FILE *fp_in = fopen("./data.txt", "r");
    FILE *fp_out = fopen("./out.txt", "w");
    int num;
    int *A = (int *)malloc(sizeof(int) * MAX_LEN);
    int *B = (int *)malloc(sizeof(int) * MAX_LEN);
    fscanf(fp_in, "%d", &num);
    printf("TOTAL NUMBER: %d\n", num);
    for (int k = 0; k < num; ++k)
    {
        //printf("%d\n",k);
        fscanf(fp_in, "%d", &A[k]);
    }
    for (int k = 0; k < num; ++k)
    {
        B[k] = A[k];
    }
    start = clock();
    random_quicksort(B, 0, num - 1);
    end = clock();
    printf("random quicksort: time: %d\n", end - start);
    fprintf(fp_out, "random quicksort: ");
    for (int k = 0; k < num; ++k)
    {
        fprintf(fp_out, "%d ", B[k]);
    }

    for (int m = 1; m <= 20; ++m)
    {
        for (int k = 0; k < num; ++k)
        {
            B[k] = A[k];
        }
        start = clock();
        hybird_sort(B, 0, num - 1, m);
        end = clock();
        fprintf(fp_out, "\nhybird: m=%d ", m);
        for (int k = 0; k < num; ++k)
        {
            fprintf(fp_out, "%d ", B[k]);
        }
        printf("hybird: m=%d time: %d\n", m, end - start);
    }

    for (int k = 0; k < num; ++k)
    {
        B[k] = A[k];
    }

    start = clock();
    insertion_sort(B, 0, num - 1);
    end = clock();
    printf("insertition sort: time: %d\n", end - start);
    fprintf(fp_out, "insertition sort: ");
    for (int k = 0; k < num; ++k)
    {
        fprintf(fp_out, "%d ", B[k]);
    }
}