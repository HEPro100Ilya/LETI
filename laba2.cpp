#include <iostream> 
#include <ctime> 
#include <chrono> // создаем библиотеку для определения времени затраченного на действия 
using namespace std;

void bubbleSort(int* arr, int n) {  // создаем пузырьковую сортировку массива
    for (; n != 1; n--)
        for (int i = 0; i < n - 1; i++) {
            if (arr[i] > arr[i + 1])
                swap(arr[i], arr[i + 1]);
        }
}
void shakerSort(int* arr, int n) {  // создаем шейкер-сортировку массива 
    for (; n != 1; n--)
        for (int i = 0; i < n - 1; i++) {
            if (arr[i] > arr[i + 1])
                swap(arr[i], arr[i + 1]);
        }
    for (int i = n - 2; i > 0; i--) {
        if (arr[i] < arr[i - 1])
            swap(arr[i], arr[i - 1]);
    }
}
void insertSort(int* arr, int n) {  // создаем сортировку массива вставками 
    for (int i = 1; i < n; i++) {
        int current = arr[i];
        int j = i - 1;
        while (j >= 0 && current < arr[j]) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = current;
    }
}
void combSort(int* arr, int n) { // создаем сортировку массива расческой 
    int gap = n;
    while (gap != 1) {
        gap = int(gap / 1.3);
        if (gap < 1)
            gap = 1;
        for (int i = 0; i < n - gap; i++) {
            if (arr[i] > arr[i + gap])
                swap(arr[i], arr[i + gap]);
        }
    }
}
void quicksort(int* arr, int  end, int begin) // создаем быструю сортировку массива
{
    int mid;
    int f = begin;
    int l = end;
    mid = arr[(f + l) / 2];
    while (f < l)
    {
        while (arr[f] < mid) f++;
        while (arr[l] > mid) l--;
        if (f <= l)
        {
            swap(arr[f], arr[l]);
            f++;
            l--;
        }
    }
    if (begin < l) quicksort(arr, l, begin);
    if (f < end) quicksort(arr, end, f);
}

void time()
{
    srand(time(0));
    const int N = 100;
    int arr[N];
    for (int i = 0; i < N; i++)
    {
        arr[i] = rand() % 199 - 99;
    }
    int end = N - 1, begin = 0;
    quicksort(arr, end, begin);
    for (int i = 0; i < N; i++)
        getchar();
}

void createNewArray(int* arr) { // создаем массив из 100 элементов
    int const n = 100;
    cout << "Ваш массив: ";
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 199 - 99;
        cout << arr[i] << " ";
    }
    cout << endl;
}
int binarySearch(int* arr, int start, int end, int x)
{
    if (start <= end) {
        int mid = (end - start) / 2 + start;
        if (arr[mid] == x) // если центральный элемент и есть число x
            return 1;
        if (arr[mid] > x) // если центр. элемент больше x, то число x находится слева
            return binarySearch(arr, start, mid - 1, x);
        return binarySearch(arr, mid + 1, end, x); // значит центральный элемент больше x, то есть число x находится справа
    }
    return -1;
}
int answer = 0;

int main() {
    setlocale(0, "");
    srand(time(0));

    int const n = 100;
    int arr[n];
    int unsortedArr[n];
    cout << "Ваш массив: ";
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 199 - 99;
        unsortedArr[i] = arr[i];
        cout << arr[i] << " ";
    }
    cout << endl << endl;
    int minnum, maxnum, meannum, counter, result, index1, index2;
    auto start = chrono::high_resolution_clock::now();
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<float> durationMinMaxUnsorted = end - start;
    while (true) {
        cout << "Выберите действие с массивом:\n1. Создать новый массив\n2. Отсортировать массив\n3. Найти максимальный и минимальный элемент массива\n4. Вывести среднее значение\n5. Вывести количество элементов в отсортированном массиве, которые меньше введенного числа\n6. Вывести количество элементов в отсортированном массиве, которые больше введенного числа\n7. Вывести информацию о том, есть ли введенное число в массиве\n8. Поменять местами элементы массива\n";
        int answer = 0;
        cin >> answer;
        switch (answer) {
        case 1:
            createNewArray(arr);
            cout << endl;
            break;
        case 2:
            cout << "Выберите тип сортировки:" << endl << "1. Bubble sort" << endl << "2. Shaker sort" << endl << "3. Insertion sort" << endl << "4. Comb sort" << endl << "5. Quick sort" << endl;
            cin >> answer;
            switch (answer)
            {
            case 1:
                start = chrono::high_resolution_clock::now();
                bubbleSort(arr, n);
                end = chrono::high_resolution_clock::now();
                break;
            case 2:
                start = chrono::high_resolution_clock::now();
                shakerSort(arr, n);
                end = chrono::high_resolution_clock::now();
                break;
            case 3:
                start = chrono::high_resolution_clock::now();
                insertSort(arr, n);
                end = chrono::high_resolution_clock::now();
                break;
            case 4:
                start = chrono::high_resolution_clock::now();
                combSort(arr, n);
                end = chrono::high_resolution_clock::now();
                break;
            case 5:
                start = chrono::high_resolution_clock::now();
                quicksort(arr, 0, n - 1);
                end = chrono::high_resolution_clock::now();
                break;
            default:
                break;
            }
            chrono::duration<float> duration = end - start;
            for (int i = 0; i < n; i++)
                cout << arr[i] << " ";
            cout << "\nотсортировано за " << fixed << duration.count() << " сек." << endl << endl;
            break;
        case 3:
            start = chrono::high_resolution_clock::now();
            minnum = arr[0];
            maxnum = arr[n - 1];
            end = chrono::high_resolution_clock::now();
            duration = end - start;
            cout << "\nНайдены минимальные и максимальные числа: " << minnum << ", " << maxnum << endl;
            cout << "В отсортированном за " << fixed << duration.count() * 1000 << " мс. (" << defaultfloat << duration.count() << " сек.)" << endl;
            start = chrono::high_resolution_clock::now();
            minnum = 100;
            maxnum = 0;
            for (int i = 0; i < n; i++) {
                if (unsortedArr[i] > maxnum) maxnum = arr[i];
                if (unsortedArr[i] < minnum) minnum = arr[i];
            }
            end = chrono::high_resolution_clock::now();
            duration = end - start;
            cout << "В неотсортированном за " << fixed << duration.count() * 1000 << " мс. (" << defaultfloat << duration.count() << " сек.)" << endl << endl;
            break;
        case 4:
            minnum = arr[0];
            maxnum = arr[n - 1];
            meannum = round((maxnum + minnum) / 2);
            counter = 0;
            for (int i = 0; i < n; i++)
                if (arr[i] == meannum)
                    counter++;
            cout << "\nСреднее значение = " << meannum << ". Раз встречается в массиве: " << counter << endl << endl;
            break;
        case 5:
            cout << "Введите число: ";
            cin >> answer;
            counter = 0;
            for (int i = 0; i < n; i++) {
                if (arr[i] < answer)
                    counter++;
                else
                    break;
            }
            cout << "\nЭлементов меньше " << answer << ": " << counter << endl << endl;
            break;
        case 6:
            cout << "Введите число: ";
            cin >> answer;
            counter = 0;
            for (int i = n - 1; i >= 0; i--) {
                if (arr[i] > answer)
                    counter++;
                else
                    break;
            }
            cout << "\nЭлементов больше " << answer << ": " << counter << endl << endl;
            break;
        case 7:
            cout << "Введите число, чтобы проверить его наличие: ";
            cin >> answer;
            start = chrono::high_resolution_clock::now();
            result = binarySearch(arr, 0, n - 1, answer);
            end = chrono::high_resolution_clock::now();
            duration = end - start;
            (result == -1) ? cout << "\nЧисло " << answer << " не существует в массиве" << endl : cout << "\nЧисло " << answer << " существует в массиве" << endl;
            cout << "Высчитано бинарным поиском за " << fixed << duration.count() * 1000 << " мс. (" << defaultfloat << duration.count() << " сек.)" << endl;
            start = chrono::high_resolution_clock::now();
            for (int i = 0; i < n; i++)
                if (arr[i] == answer)
                    break;
            end = chrono::high_resolution_clock::now();
            duration = end - start;
            cout << "Высчитано обычным перебором за " << fixed << duration.count() * 1000 << " мс. (" << defaultfloat << duration.count() << " сек.)" << endl << endl;
            break;
        case 8:
            while (true) {
                cout << "Введите два индекса элементов, чтобы поменять их местами: ";
                cin >> index1 >> index2;
                if (index1 < 0 || index1 > n - 1 || index2 < 0 || index2 > n - 1)
                    cout << "Индексы указаны неверно, попробуйте еще раз." << endl;
                else
                    break;
            }
            start = chrono::high_resolution_clock::now();
            swap(arr[index1], arr[index2]);
            end = chrono::high_resolution_clock::now();
            duration = end - start;
            for (int i = 0; i < n; i++)
                cout << arr[i] << " ";
            cout << "\nперемещены за " << fixed << duration.count() * 1000 << " мс. (" << defaultfloat << duration.count() << " сек.)" << endl << endl;
            break;
        default:
            return 0;
        }
    }
}