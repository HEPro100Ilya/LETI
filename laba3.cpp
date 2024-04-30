#include <iostream>
#include <thread>
#include <iomanip>

using namespace std;

void printMatrix(int**, int, bool = 1);

void clearMatrix(int**, int);

void spiralMatrix(int**, int);

void snakeMatrix(int**, int);

void rotateMatrix(int**, int, char);

void sortMatrix(int**, int);

void increaseMatrix(int**, int, int);

void decreaseMatrix(int**, int, int);

void multiplyMatrix(int**, int, int);

void divideMatrix(int**, int, int);

int main() {
    srand(time(0));
    setlocale(0, "");
    int N;
    cout << "Выберите размерность матрицы: 6, 8, 10:" << "\n";
    cin >> N;
    while (N != 6 && N != 8 && N != 10) {
        cout << "Неправильно введены данные, повторите попытку " << "\n";
        cin >> N;
    }
    int** matrix = new int* [N]; // пустой массив указателей на N элементов 
    for (int** cur = matrix, **end = cur + N - 1; cur <= end; cur++) *cur = new int[N]; // пустая матрица
    string fillType;
    cout << "Выберите вид заполнения матрицы:\n1. \"Спиралью\"\n2. \"Змейкой\"" << endl;
    cin >> fillType;
    while (fillType != "1" && fillType != "2") {
        cout << "Неправильно введены данные, повторите попытку:" << endl;
        cin >> fillType;
    }
    clearMatrix(matrix, N);
    if (fillType == "1") {
        spiralMatrix(matrix, N);
    }
    else snakeMatrix(matrix, N);

    string rotateOption;
    cout << "Выберите как изменить положение элементов матрицы:\n1. Переместить четверти по часовой стрелке\n2. Переместить четверти по диагонали\n3. Переместить четверти по вертикали\n4. Переместить четверти по горизонтали" << endl;
    cin >> fillType;
    while (fillType != "1" && fillType != "2" && fillType != "3" && fillType != "4") {
        cout << "Неправильно введены данные, повторите попытку" << endl;
        cin >> fillType;
    }
    cout << "Матрица после изменения: " << '\n';
    rotateMatrix(matrix, N, fillType[0]);
    cout << '\n' << "Отсортированная матрица: " << '\n';
    sortMatrix(matrix, N);
    cout << '\n' << "Выберите какую операцию выполнить с каждым элементом матрицы:\n1. Сложение\n2. Вычитание\n3. Умножение\n4. Деление (нацело)\n";
    int operation;
    cin >> operation;
    cout << "Введите число, с которым провести операцию:";
    int k;
    cin >> k;
    switch (operation) {
    case 1:
        increaseMatrix(matrix, N, k);
        break;
    case 2:
        decreaseMatrix(matrix, N, k);
        break;
    case 3:
        multiplyMatrix(matrix, N, k);
        break;
    case 4:
        divideMatrix(matrix, N, k);
        break;
    default:
        break;
    }
    system("Pause");
}

void printMatrix(int** matrix, int N, bool clear) {
    if (clear) system("cls");
    for (int** curi = matrix, **endi = curi + N - 1; curi <= endi; curi++) {
        for (int* curj = *curi, *endj = curj + N - 1; curj <= endj; curj++) {
            cout << setw(3) << *curj;
            if (curj != endj) cout << " ";
        }
        cout << "\n";
    }
    std::this_thread::sleep_for(0.1s);
}

void clearMatrix(int** matrix, int N) {
    for (int** curi = matrix, **endi = curi + N - 1; curi <= endi; curi++)
        for (int* curj = *curi, *endj = curj + N - 1; curj <= endj; curj++) *curj = 0;
}

void spiralMatrix(int** matrix, int N) {
    printMatrix(matrix, N);
    int lineNum = 0;
    for (int j = 0; j < N / 2; ++j) {
        for (int* curi = *(matrix + lineNum) + lineNum, *endi = curi + N - 2 * lineNum; curi < endi; curi++) {
            *curi = rand() % (N * N) + 1;
            printMatrix(matrix, N);
        }
        for (int** curi = matrix + lineNum + 1, **endi = matrix + N - 2 - lineNum; curi <= endi; curi++) {
            *(*curi + N - lineNum - 1) = rand() % (N * N) + 1;
            printMatrix(matrix, N);
        }
        for (int* curi = *(matrix + N - lineNum - 1) + N - lineNum - 1, *endi = curi - N + 1 + 2 * lineNum; curi > endi; curi--) {
            *curi = rand() % (N * N) + 1;
            printMatrix(matrix, N);
        }
        for (int** curi = matrix + N - 1 - lineNum, **endi = matrix + lineNum + 1; curi >= endi; curi--) {
            *(*curi + lineNum) = rand() % (N * N) + 1;
            printMatrix(matrix, N);
        }
        lineNum++;
    }
}

void snakeMatrix(int** matrix, int N) {
    printMatrix(matrix, N);
    for (int lineNum = 0; lineNum < N / 2; ++lineNum) {
        for (int** curi = matrix, **endi = matrix + N - 1; curi <= endi; curi++) { //заполняет нечетные столбцы сверху вниз
            *(*curi + lineNum * 2) = rand() % (N * N) + 1;
            printMatrix(matrix, N);
        }
        for (int** curi = matrix + N - 1, **endi = matrix; curi >= endi; curi--) { // заполняет четные столбцы снизу вверх
            *(*curi + lineNum * 2 + 1) = rand() % (N * N) + 1;
            printMatrix(matrix, N);
        }
    }
}

void rotateMatrix(int** matrix, int N, char option) {
    int** a = new int* [N / 2], ** b = new int* [N / 2], ** c = new int* [N / 2], ** d = new int* [N / 2], *** arr = new int** [4];
    arr[0] = a; arr[1] = b; arr[2] = c; arr[3] = d;
    for (int*** i = arr, ***iEnd = arr + 3; i <= iEnd; i++)
        for (int** cur = *i, **end = cur + N / 2 - 1; cur <= end; cur++) *cur = new int[N / 2];

    for (int** curi = matrix, **endi = curi + N / 2 - 1, **curArray = a; curi <= endi; curi++, curArray++)
        for (int* curj = *curi, *endj = curj + N / 2 - 1, *curArrayJ = *curArray; curj <= endj; curj++, curArrayJ++)
            *curArrayJ = *curj;

    for (int** curi = matrix, **endi = curi + N / 2 - 1, **curArray = b; curi <= endi; curi++, curArray++)
        for (int* curj = *curi + N / 2, *endj = curj + N / 2 - 1, *curArrayJ = *curArray; curj <= endj; curj++, curArrayJ++)
            *curArrayJ = *curj;

    for (int** curi = matrix + N / 2, **endi = curi + N / 2 - 1, **curArray = c; curi <= endi; curi++, curArray++)
        for (int* curj = *curi, *endj = curj + N / 2 - 1, *curArrayJ = *curArray; curj <= endj; curj++, curArrayJ++)
            *curArrayJ = *curj;

    for (int** curi = matrix + N / 2, **endi = curi + N / 2 - 1, **curArray = d; curi <= endi; curi++, curArray++)
        for (int* curj = *curi + N / 2, *endj = curj + N / 2 - 1, *curArrayJ = *curArray; curj <= endj; curj++, curArrayJ++)
            *curArrayJ = *curj;

    int** pa, ** pb, ** pc, ** pd;
    if (option == '1') {
        pa = c; pb = a; pc = d; pd = b;
    }
    else if (option == '2') {
        pa = d; pb = c; pc = b; pd = a;
    }
    else if (option == '3') {
        pa = c; pb = d; pc = a; pd = b;
    }
    else {
        pa = b; pb = a; pc = d; pd = c;
    }
    for (int** curi = matrix, **endi = curi + N / 2 - 1, **curArray = pa; curi <= endi; curi++, curArray++)
        for (int* curj = *curi, *endj = curj + N / 2 - 1, *curArrayJ = *curArray; curj <= endj; curj++, curArrayJ++)
            *curj = *curArrayJ;

    for (int** curi = matrix, **endi = curi + N / 2 - 1, **curArray = pb; curi <= endi; curi++, curArray++)
        for (int* curj = *curi + N / 2, *endj = curj + N / 2 - 1, *curArrayJ = *curArray; curj <= endj; curj++, curArrayJ++)
            *curj = *curArrayJ;

    for (int** curi = matrix + N / 2, **endi = curi + N / 2 - 1, **curArray = pc; curi <= endi; curi++, curArray++)
        for (int* curj = *curi, *endj = curj + N / 2 - 1, *curArrayJ = *curArray; curj <= endj; curj++, curArrayJ++)
            *curj = *curArrayJ;

    for (int** curi = matrix + N / 2, **endi = curi + N / 2 - 1, **curArray = pd; curi <= endi; curi++, curArray++)
        for (int* curj = *curi + N / 2, *endj = curj + N / 2 - 1, *curArrayJ = *curArray; curj <= endj; curj++, curArrayJ++)
            *curj = *curArrayJ;

    printMatrix(matrix, N, 0);
}

void sortMatrix(int** matrix, int N) {
    int* arr = new int[N * N];
    int i = 0;
    for (int** curi = matrix, **endi = curi + N - 1; curi <= endi; curi++) {
        for (int* curj = *curi, *endj = curj + N - 1; curj <= endj; curj++) {
            *(arr + i) = *curj;
            i++;
        }
    }
    bool isChanged = 1;
    while (isChanged) {
        isChanged = 0;
        for (int* j = arr, *jEnd = j + (N * N) - 2; j <= jEnd; j++) {
            if (*j > *(j + 1)) {
                isChanged = 1;
                int t = *(j + 1);
                *(j + 1) = *j;
                *j = t;
            }
        }
    }

    i = 0;
    for (int** curi = matrix, **endi = curi + N - 1; curi <= endi; curi++) {
        for (int* curj = *curi, *endj = curj + N - 1; curj <= endj; curj++) {
            *curj = *(arr + i);
            i++;
        }
    }
    printMatrix(matrix, N, 0);
}

void increaseMatrix(int** matrix, int N, int k) {
    for (int** curi = matrix, **endi = curi + N - 1; curi <= endi; curi++)
        for (int* curj = *curi, *endj = curj + N - 1; curj <= endj; curj++) *curj += k;
    printMatrix(matrix, N, 0);
}
void decreaseMatrix(int** matrix, int N, int k) {
    for (int** curi = matrix, **endi = curi + N - 1; curi <= endi; curi++)
        for (int* curj = *curi, *endj = curj + N - 1; curj <= endj; curj++) *curj -= k;
    printMatrix(matrix, N, 0);
}
void multiplyMatrix(int** matrix, int N, int k) {
    for (int** curi = matrix, **endi = curi + N - 1; curi <= endi; curi++)
        for (int* curj = *curi, *endj = curj + N - 1; curj <= endj; curj++) *curj *= k;
    printMatrix(matrix, N, 0);
}
void divideMatrix(int** matrix, int N, int k) {
    for (int** curi = matrix, **endi = curi + N - 1; curi <= endi; curi++)
        for (int* curj = *curi, *endj = curj + N - 1; curj <= endj; curj++) *curj /= k;
    printMatrix(matrix, N, 0);
}

