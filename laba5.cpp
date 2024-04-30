#include <iostream>
#include <fstream>
#include <cstring>
#include <Windows.h>
#include <string>
#include <iomanip>

using namespace std;


struct Profile
{
    string full_name; // Фамилия Имя Отчество
    bool sex;         // Пол: M/W
    int group;        // Номер группы
    int id;               // Номер студента в списке 
    char grades[8];    // Оценки за экзамены и диф. зачёты
    char depart[9];   // Форма обучения    
};

Profile* addStudent(Profile* studArr, int num) {
    Profile newStud;
    int t;
    Profile* way = new Profile[num];
    for (int i = 0; i < num; i++) {
        way[i] = studArr[i];
    }
    studArr = new Profile[num + 1];
    for (int i = 0; i < num; i++) {
        studArr[i] = way[i];
    }

    cout << "Full name: ";
    cin.ignore();
    getline(cin, newStud.full_name); // Через оператор "." инициализируем ФИО
    cout << "Group: ";
    cin >> newStud.group;     // Через оператор "." инициализируем номер группы
    cout << "Index: ";
    cin >> newStud.id;        // Через оператор "." инициализируем номер в списке группы
    cout << "Sex (F/M): ";
    cin >> t;
    (t == 1) ? newStud.sex = true : newStud.sex = false;      // Через оператор "." инициализируем пол
    cout << "Department (day/evening/distance): ";
    cin >> newStud.depart;    // Через оператор "." инициализируем форму обучения
    cout << "Term grades: ";
    for (int i = 0; i < 8; i++)  cin >> newStud.grades[i];



    int temp = 0;
    for (int i = 0; i < 8; i++) // Так оценка 2 не может стоять в ведомости, идёт проверка
    {
        if (newStud.grades[i] == 2)
            temp++; // Найдена оценка 2, увеличиваем счётчик
    }
    if (temp == 0) // Если двоек не обнаружено
    {
        ofstream database; // Создаем поток записи в файл 
        // Открываем файл student с флагом записи в конец файла с сохранением содержимого файла
        database.open("D:\\text\\name.txt", ios::app);
        if (!database.is_open()) // Если файл открыть не удалось 
            cout << '\n' << "Saving error!"; // Выдаём соответсвующее сообщение
        else // Если файл успешно был открыт поочереди записываем всю информацию в файл.
        {
            database << newStud.full_name << " ";
            database << newStud.group << " " << newStud.id << " " << newStud.sex << " ";
            database << newStud.depart << " ";
            for (int i = 0; i < 8; i++)
                database << newStud.grades[i] << " ";
            database << '\n';
            database.close();

            cout << '\n' << "Profile is saved in the database.";

        }
    }
    else // Если у студента есть неуд, информация о нем, не может быть сохранена, т.к. он должен быть отчислен
        cout << '\n' << "This student will be expelled. The profile will not be saved in the database.";
    return studArr;
}

void editData(Profile* studArr, int num) {
    cout << "\nВведите номер записи, которую нужно изменить: ";
    int k, t;
    cin >> k;
    Profile* p = studArr + k - 1; //??
    cout << "Введите ФИО студента: ";
    cin.ignore();
    getline(cin, p->full_name);
    cout << "Введите номер группы студента: ";
    cin >> p->group;
    cout << "Введите номер студента в группе: ";
    cin >> p->id;
    cout << "Sex (F/M): ";
    cin >> t;
    (t == 1) ? p->sex = true : p->sex = false;
    cout << "Очка или че ? ";
    cin >> p->depart;
    cout << "Введите оценки студента через пробел: ";
    for (int i = 0; i < 8; i++) {
        cin >> p->grades[i];
    }
    ofstream database;
    database.open("D:\\text\\name.txt");
    if (!database.is_open()) {
        cout << "Открыть файл не удалось! \n";
        return;
    }
    for (int i = 0; i < num; i++) {
        database << studArr[i].full_name << " " << studArr[i].group << " " << studArr[i].id << " " << studArr[i].sex << " " << studArr[i].depart;
        for (int j = 0; j < 8; j++) database << " " << studArr[i].grades[j];
        database << '\n';

    }

    database.close();
    cout << "\nДанные изменены.\n";
}

int countStudents() // Функция посчёта количества студентов
{
    ifstream database("D:\\text\\name.txt");
    if (database.is_open())
    {
        int temp = 0;
        string data;
        while (!database.eof())
        {
            getline(database, data);
            temp++;
        }
        database.close();
        return temp;
    }
    else return 0;
}
void showData()
{
    ifstream database("D:\\text\\name.txt"); // Создаем поток считывания информации из файла и открываем файл student
    if (!database.is_open()) // Если файл открыть не удалось 
        cout << "File opening error";
    else
    {
        int temp;
        temp = countStudents();
        if (temp == 0)
            cout << "The File is empty" << temp;
        else
        {
            string data;
            while (!database.eof())
            {
                getline(database, data); // Считываем очередную строчку
                cout << data << '\n';    // Выводим строку на экран
            }
        }
        database.close();
    }
}

void showGroup()
{
    int n; // Переменная, которая будет содержать информацию о введенном пользователем номере группы
    cout << "Enter the group number:" << endl;
    cin >> n;
    ifstream database("D:\\text\\name.txt");
    if (!database.is_open())
        cout << "Error!";
    else
    {
        int size;
        size = countStudents();
        if (size == 0)
            cout << "The database is empty." << endl;
        else
        {
            Profile* student = new Profile[size]; // В примере показан случай неопределенной размерности, от вас этого не требуется
            for (int i = 0; i < size; i++) // Считываем данные всех студентов в массив структур
            {
                database >> student[i].full_name;
                database >> student[i].group >> student[i].id >> student[i].sex;
                database >> student[i].depart;
                for (int j = 0; j < 8; j++)
                    database >> student[i].grades[j];
            }
            database.close(); // Закрываем файл
            int temp = 0;
            for (int i = 0; i < size; i++) // Проходим по всем студентам
            {
                if (student[i].group == n) // Фильтруем данные по необходимому признаку
                {
                    cout << student[i].id << " " << student[i].full_name << '\n';
                    cout << student[i].sex << '\n' << student[i].depart << "\n";
                    cout << "Term grades: ";
                    for (int j = 0; j < 8; j++)
                        cout << student[i].grades[j] << " ";
                    cout << "\n\n";
                    temp++;
                }
            }
            if (temp == 0) // Если ни одной записи не найдено 
                cout << "No records were found" << endl;
            delete[] student; // Освобождаем динамическую память 
        }
    }
}

void showGender(Profile* studArr, int num)
{
    int M = 0, F = 0;
    for (Profile* p = studArr; p < studArr + num; p++)
    {
        if (p->sex) M++;
        else F++;
    }
    cout << "Количество студентов мужского пола:  " << M << "\n Количество студентов женского пола " << F << endl;
}

void showId()
{
    int n; // Переменная, которая будет содержать информацию о введенном пользователем номере группы
    cout << "Enter the id student:" << endl;
    cin >> n;
    ifstream database("D:\\text\\name.txt");
    if (!database.is_open())
        cout << "Error!";
    else
    {
        int size;
        size = countStudents();
        if (size == 0)
            cout << "The database is empty." << endl;
        else
        {
            Profile* student = new Profile[size]; // В примере показан случай неопределенной размерности, от вас этого не требуется
            for (int i = 0; i < size; i++) // Считываем данные всех студентов в массив структур
            {
                database >> student[i].full_name;
                database >> student[i].group >> student[i].id >> student[i].sex;
                database >> student[i].depart;
                for (int j = 0; j < 8; j++)
                    database >> student[i].grades[j];
            }
            database.close(); // Закрываем файл
            int temp = 0;
            for (int i = 0; i < size; i++) // Проходим по всем студентам
            {
                if (student[i].id == n) // Фильтруем данные по необходимому признаку
                {
                    cout << student[i].group << '\n' << student[i].full_name << '\n';
                    cout << student[i].sex << '\n' << student[i].depart << "\n";
                    cout << "Term grades: ";
                    for (int j = 0; j < 8; j++)
                        cout << student[i].grades[j] << " ";
                    cout << "\n\n";
                    temp++;
                }
            }
            if (temp == 0) // Если ни одной записи не найдено 
                cout << "No records were found" << endl;
            delete[] student; // Освобождаем динамическую память 
        }
    }
}




int main() {
    setlocale(LC_CTYPE, ".1251");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    string nametemp1, nametemp2;
    ifstream database;
    database.open("D:\\text\\name.txt");
    if (!database.is_open()) {
        cout << "Открыть файл не удалось! \n";
        return 0;
    }
    int num = 0;
    while (!database.eof()) {
        getline(database, nametemp1);
        num++;
    }
    database.close();
    Profile* studArr = new Profile[num];

    database.open("D:\\text\\name.txt");
    if (!database.is_open()) {
        cout << "Открыть файл не удалось! \n";
        return 0;
    }
    for (int i = 0; i < num; i++) {
        database >> studArr[i].full_name >> nametemp1 >> nametemp2 >> studArr[i].sex >> studArr[i].group >> studArr[i].id;
        studArr[i].full_name = studArr[i].full_name + " " + nametemp1 + " " + nametemp2;
        for (int j = 0; j < 8; j++) database >> studArr[i].grades[j];
    }
    database.close();
    int lol;
    while (true) {
        cout << "1. Cоздать новую запись о студенте\n2. Внести изменения в уже имеющуюся запись\n3. Вывести все данные о студентах\n4. Вывод информации обо всех студентах конкретной группы\n5. Вывести топ самых успешных студентов с наивысшим по рейтингу средним баллом за прошедшую сессию\n6. Вывести количество студентов мужского и женского пола\n7. Вывести данные о студентах, которые не получают стипендию; учатся только на «4» и «5»; учатся только на «5»\n8. Вывод данных о студентах, имеющих конкретный номер в списке\n\nВведите номер команды: ";
        cin >> lol;
        while (lol < 1 || lol > 8) {
            cout << "Неверно введен номер команды. Попробуйте еще раз: ";
            cin >> lol;
        }
        switch (lol) {
        case 1:
            studArr = addStudent(studArr, num);
            num++;
            break;
        case 2:
            system("cls");
            editData(studArr, num);
            system("Pause");
            system("cls");
            break;
        case 3:
            system("cls");
            showData();
            system("Pause");
            system("cls");
            break;
        case 4:
            system("cls");
            showGroup();
            system("Pause");
            system("cls");
            break;
        case 5:
            system("cls");
            showGender(studArr, num);
            system("Pause");
            system("cls");
            break;
        case 6:
            system("cls");
            showId();
            system("Pause");
            system("cls");
            break;
        default:
            break;
        }
        system("Pause");
    }
}