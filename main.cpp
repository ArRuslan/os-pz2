#include <algorithm>
#include <iostream>
#include <unistd.h>

const int MAX_ARR_SIZE = 1024;

void check_cin_int() {
    if (std::cin.good())
        return;
    std::cin.clear();
    std::string ignore;
    std::cin >> ignore;
}

int readInt(const char *prompt) {
    int result = 0;
    while (true) {
        printf(prompt);
        std::cin >> result;
        check_cin_int();
        if (result >= 1)
            break;
        printf("     Number must be greater than 1!\n");
    }

    return result;
}

void printArr(const int arr[], const int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1)
            printf(", ");
    }
    printf("]\n");
}

void printMat(int **arr, const int rows, const int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%6d ", arr[i][j]);
        }
        printf("\n");
    }
}

void printMat(int **arr, const int size) {
    printMat(arr, size, size);
}

int maxInt(const int arr[], const int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max)
            max = arr[i];
    }

    return max;
}

void task_1_search(const int arr[], const int size) {
    int found = -1;
    for (int i = 0; i < size; i++) {
        if (arr[i] % 2 == 0) {
            found = arr[i];
            printf("     Took %d comparisons\n", i + 1);
            break;
        }
    }
    if (found >= 0)
        printf("     Found: %d\n", found);
    else
        printf("     Not found\n");
}

void task_1() {
    int *arr = new int[MAX_ARR_SIZE];

    int n = readInt("2.1. Enter array length (greater than 1): ");

    for (int i = 0; i < n; i++)
        arr[i] = rand() % 32767;

    printf("     Array: ");
    printArr(arr, n);

    int max = maxInt(arr, n);

    int new_len = n, move = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == max) {
            new_len--;
            move++;
        }
        if (!move || i + move >= n)
            continue;
        arr[i] = arr[i + move];
    }
    n = new_len;

    printf("     Max: %d\n", max);
    printf("     Array: ");
    printArr(arr, n);

    int k = readInt("     Enter K: ");

    std::copy(arr, arr + n, arr + k);
    for (int i = 0; i < k; i++)
        arr[i] = readInt("     Enter int: ");


    n = n + k;

    printf("     Array: ");
    printArr(arr, n);

    for (int i = 0; i < n / 2; i++) {
        int tmp = arr[i];
        arr[i] = arr[n - i - 1];
        arr[n - i - 1] = tmp;
    }

    printf("     Array (recersed): ");
    printArr(arr, n);

    task_1_search(arr, n);
    std::sort(arr, arr + n);
    printf("     Array (after sorting): ");
    printArr(arr, n);
    task_1_search(arr, n);

    delete[] arr;
}

void task_2() {
    int *arr = new int[MAX_ARR_SIZE];
    int n = readInt("2.2. Enter array length (greater than 2): ");
    for (int i = 0; i < n; i++)
        arr[i] = rand() % 32767;

    int max = arr[1];
    int min = arr[0];
    for (int i = 1; i < n; i++) {
        if (i % 2 != 0 && arr[i] > max) max = arr[i];
        if (i % 2 == 0 && arr[i] < min) min = arr[i];
    }

    printf("     Array: ");
    printArr(arr, n);
    printf("     Max: %d, Min: %d\n", max, min);
    printf("     max + min = %d\n", max + min);

    delete[] arr;
}

void task_3() {
    int **mat = new int *[MAX_ARR_SIZE];
    for (int i = 0; i < MAX_ARR_SIZE; i++) {
        mat[i] = new int[MAX_ARR_SIZE];
    }

    int n = readInt("2.3. Enter matrix size: ");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            mat[i][j] = rand() % 65534 - 32767;

    printf("     Matrix: \n");
    printMat(mat, n);

    int result = 1;
    for (int i = 0; i < n; i++) {
        if (mat[i][i] < 0)
            result *= mat[i][i];
    }

    printf("     Result: %d\n", result);

    for(int i = 0; i < MAX_ARR_SIZE; i++)
        delete[] mat[i];
    delete[] mat;
}

void task_4_array() {
    int *arr = new int[MAX_ARR_SIZE];
    int n = readInt("2.4. Enter array length (greater than 1): ");

    for (int i = 0; i < n; i++)
        arr[i] = rand() % 32767;

    printf("     Array: ");
    printArr(arr, n);

    int new_len = n, move = 0;
    for (int i = 0; i < n; i++) {
        if (!move && arr[i] % 2 == 0) {
            new_len--;
            move++;
        }
        if (!move || i + move >= n)
            continue;
        arr[i] = arr[i + move];
    }
    n = new_len;
    printf("     Array: ");
    printArr(arr, n);

    delete[] arr;
}

void task_4_matrix() {
    int **mat = new int *[MAX_ARR_SIZE];
    for (int i = 0; i < MAX_ARR_SIZE; i++) {
        mat[i] = new int[MAX_ARR_SIZE];
    }

    int n = readInt("2.4. Enter matrix size: ");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            mat[i][j] = rand() % 65534 - 32767;

    printf("     Matrix: \n");
    printMat(mat, n);

    int idx = readInt("2.4. Enter new matrix row index: ");

    int* s = mat[n];
    std::copy(mat+idx, mat + n, mat + idx + 1);
    delete[] s;
    mat[idx] = new int[MAX_ARR_SIZE];

    for (int j = 0; j < n; j++)
        mat[idx][j] = rand() % 65534 - 32767;

    printMat(mat, n+1, n);

    for(int i = 0; i < MAX_ARR_SIZE; i++)
        delete[] mat[i];
    delete[] mat;
}

void task_5_1() {
    printf("2.5 Enter string: ");
    std::string str;
    std::cin >> str;
    for(int i = 0; i < str.length(); i++) {
        if(str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u' || str[i] == 'y')
            str = str.replace(i, 1, std::string(" "));
    }
    printf("    Result: %s\n", str.c_str());
}

void task_5_2() {
    auto *arr = new std::string[MAX_ARR_SIZE];
    int n = readInt("2.5 Enter string count: ");
    std::cin.ignore();
    for(int i = 0; i < n; i++) {
        printf("    Enter string: ");
        std::getline(std::cin, arr[i]);
    }

    auto *result = new std::string[MAX_ARR_SIZE];
    int result_idx = 0;

    for(int i = 1; i < n; i++) {
        if(arr[i].find(arr[0]) != std::string::npos) {
            arr[i].erase(std::remove_if(arr[i].begin(), arr[i].end(), isspace), arr[i].end());
            result[result_idx++] = arr[i];
        }
    }

    printf("    Result: \n");

    for(int i = 0; i < result_idx+1; i++)
        printf("      %s\n", result[i].c_str());

    delete[] arr;
    delete[] result;
}

int main() {
    task_1(); // 2.1
    task_2(); // 2.2
    task_3(); // 2.3
    task_4_array(); // 2.4
    task_4_matrix(); // 2.4
    task_5_1(); // 2.5
    task_5_2(); // 2.5

    return 0;
}
