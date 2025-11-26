#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define MIN_PARALLEL_SIZE 50000
#define MAX_DEPTH 3

// =============================
// Merge Sort Sequential
// =============================

void merge(int arr[], int left, int mid, int right, int temp[]) {
    int i = left, j = mid + 1, k = left;

    while (i <= mid && j <= right) {
        temp[k++] = (arr[i] <= arr[j]) ? arr[i++] : arr[j++];
    }
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];

    for (i = left; i <= right; i++)
        arr[i] = temp[i];
}

void mergeSortSeq(int arr[], int left, int right, int temp[]) {
    if (left >= right) return;

    int mid = (left + right) / 2;

    mergeSortSeq(arr, left, mid, temp);
    mergeSortSeq(arr, mid + 1, right, temp);

    merge(arr, left, mid, right, temp);
}

void mergeSortSequential(int arr[], int n) {
    int* temp = (int*)malloc(sizeof(int) * n);
    mergeSortSeq(arr, 0, n - 1, temp);
    free(temp);
}


// =============================
// Merge Sort Parallel (WinAPI)
// =============================

typedef struct {
    int* arr;
    int* temp;
    int left;
    int right;
    int depth;
} ThreadArgs;

DWORD WINAPI mergeSortThread(LPVOID arg);

DWORD WINAPI mergeSortThread(LPVOID arg) {
    ThreadArgs* args = (ThreadArgs*)arg;
    int left = args->left;
    int right = args->right;

    if (left >= right) return 0;

    int mid = (left + right) / 2;
    int size = right - left + 1;

    if (args->depth < MAX_DEPTH && size >= MIN_PARALLEL_SIZE) {
        HANDLE t1, t2;

        ThreadArgs leftArgs = { args->arr, args->temp, left, mid, args->depth + 1 };
        ThreadArgs rightArgs = { args->arr, args->temp, mid + 1, right, args->depth + 1 };

        t1 = CreateThread(NULL, 0, mergeSortThread, &leftArgs, 0, NULL);
        t2 = CreateThread(NULL, 0, mergeSortThread, &rightArgs, 0, NULL);

        WaitForSingleObject(t1, INFINITE);
        WaitForSingleObject(t2, INFINITE);

        CloseHandle(t1);
        CloseHandle(t2);
    }
    else {
        mergeSortSeq(args->arr, left, right, args->temp);
        return 0;
    }

    merge(args->arr, left, mid, right, args->temp);
    return 0;
}

void mergeSortParallel(int arr[], int n) {
    int* temp = (int*)malloc(sizeof(int) * n);
    ThreadArgs args = { arr, temp, 0, n - 1, 0 };
    mergeSortThread(&args);
    free(temp);
}


// =============================
// Unique Random Array (Fisher–Yates shuffle)
// =============================

void generateUniqueRandom(int arr[], int n) {
    for (int i = 0; i < n; i++)
        arr[i] = i;

    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int t = arr[i];
        arr[i] = arr[j];
        arr[j] = t;
    }
}

void printArray(int arr[], int n, int maxPrint) {
    int limit = (n < maxPrint) ? n : maxPrint;
    for (int i = 0; i < limit; i++)
        printf("%d ", arr[i]);
    printf("\n");
}


// =============================
// MAIN MENU
// =============================

int main() {
    // Thiết lập UTF-8 cho console Windows
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    srand((unsigned)time(NULL));

    while (1) {
        int choice;
        printf("\n===== MENU MERGE SORT =====\n");
        printf("1. Chạy CẢ tuần tự và song song\n");
        printf("2. Chỉ chạy merge sort tuần tự\n");
        printf("3. Chỉ chạy merge sort song song\n");
        printf("0. Thoát\n");
        printf("Chọn: ");
        scanf("%d", &choice);

        if (choice == 0) {
            printf("Thoát chương trình.\n");
            return 0;
        }

        int n;
        printf("Nhập số lượng phần tử (>= 2): ");
        scanf("%d", &n);

        int* arrSeq = (int*)malloc(n * sizeof(int));
        int* arrPar = (int*)malloc(n * sizeof(int));

        // Sinh mảng KHÔNG TRÙNG
        generateUniqueRandom(arrSeq, n);
        for (int i = 0; i < n; i++) arrPar[i] = arrSeq[i];

        printf("\nMảng ban đầu (10 phần tử đầu): ");
        printArray(arrSeq, n, 10);

        double timeSeq = 0, timePar = 0;

        // CASE 1 + 2 → chạy tuần tự
        if (choice == 1 || choice == 2) {
            clock_t start = clock();
            mergeSortSequential(arrSeq, n);
            clock_t end = clock();
            timeSeq = (double)(end - start) / CLOCKS_PER_SEC;

            printf("\n⏳ Thời gian tuần tự: %.6f giây\n", timeSeq);
        }

        // CASE 1 + 3 → chạy song song
        if (choice == 1 || choice == 3) {
            clock_t start = clock();
            mergeSortParallel(arrPar, n);
            clock_t end = clock();
            timePar = (double)(end - start) / CLOCKS_PER_SEC;

            printf("Thời gian song song: %.6f giây\n", timePar);
        }

        // Nếu chọn 1 → in speedup
        if (choice == 1) {
            printf("\nTăng tốc (Seq / Par): %.2fx\n", timeSeq / timePar);
        }

        printf("\nMảng sau khi sắp xếp (10 phần tử đầu): ");
        printArray((choice == 2) ? arrSeq : arrPar, n, 10);

        free(arrSeq);
        free(arrPar);
    }

    return 0;
}
