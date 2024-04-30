#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <chrono>

using namespace std;

struct Node //Отвечает за отдельные элементы списка
{
    int data;
    Node* prev;
    Node* next; //указалатели на предыдущие и следующие элемен ты
    Node(int data)
    {
        this->data = data;
        this->prev = this->next = NULL;
    }
};

struct TipList
{
    Node* head, * tail;
    TipList()
    {
        head = tail = NULL;

    }

    ~TipList() {
        while (head != NULL)
        {
            delete_felem();

        }
    }

    Node* add_elem(int data) // добавление элемента
    {
        Node* ptr = new Node(data); //создаем временный объект
        ptr->prev = tail;
        if (tail != NULL)
            tail->next = ptr;
        if (head == NULL)
            head = ptr;
        tail = ptr;
        return ptr;
    }
    Node* add_elem2(int data) {  //добавление элемента
        Node* ptr = new Node(data);
        ptr->next = head;
        if (head != NULL)
            head->prev = ptr;
        if (tail == NULL)
            tail = ptr;
        return ptr;
    }

    void delete_felem() //удаление элемента
    {
        if (head == NULL) return;
        Node* ptr = head->next; // создаем временный указатель 
        if (ptr != NULL) // проверка
            ptr->prev = NULL;

        else   //если удаляем единственный объект, то и таил и хед = 0 
            tail = NULL;

        delete head;
        head = ptr;
    }
    void delete_lelem() // удаление последнего объекта
    {
        if (tail == NULL)return;
        Node* ptr = tail->next;
        if (ptr != NULL)
            ptr->next = NULL;

        else
            head = NULL;

        delete tail;
        tail = ptr;
    }

    void erase_elem(int index) {
        Node* ptr = get_elem(index);
        if (ptr == NULL)return;

        if (ptr->prev == NULL)
        {
            delete_felem();
            return;
        }

        if (ptr->next == NULL)
        {
            delete_lelem();
            return;
        }
        Node* left = ptr->prev;
        Node* right = ptr->next;
        left->next = right;
        right->prev = left;
        delete ptr;
    }

    Node* get_elem(int index) //Получение нужного элемента
    {
        Node* ptr = head;
        int n = 0;
        while (n != index)
        {
            if (ptr == NULL)
                return ptr;
            ptr = ptr->next;
            n++;
        }
        return ptr;
    }

    Node* operator[] (int index) { // оператор , которые возвращает элемент по определенному индексу
        return get_elem(index);
    }

    Node* insert_elem(int index, int data) { //вставка нового элемента в любое место
        Node* right = get_elem(index);
        if (right == NULL)
            return add_elem(data);
        Node* left = right->prev;
        if (left == NULL)
            return add_elem2(data);

        Node* ptr = new Node(data);

        ptr->prev = left;
        ptr->next = right;
        left->next = ptr;
        right->prev = ptr;

        return ptr;
    }

    void show() {
        Node* temp = head;
        while (temp != NULL)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
    }

    void swap(int index, int index2) {
        Node* temp = head;
        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }
        Node* temp1 = head;
        for (int i = 0; i < index2; i++) {
            temp1 = temp1->next;
        }
        int k = temp->data;
        temp->data = temp1->data;
        temp1->data = k;
    }

};

int main()
{
    srand(time(NULL));
    setlocale(LC_ALL, "RUS");
    TipList spisok;
    int choose = 0;
    int deystv = 0;
    do {
        auto start = chrono::steady_clock::now();
        auto end = chrono::steady_clock::now();
        cout << "Выберите вариант: " << endl;
        cout << "1 - Введите количество элементов в списке" << endl;
        cout << "2 - введите в консоль элементы списка" << endl;
        cout << "3 - Работа со списком" << endl;
        cout << "4 - Выход из программы" << endl;
        cin >> choose;
        int length = 0;
        switch (choose)
        {

        case 1:
            cout << "Введите длину списка: " << endl;
            cin >> length;
            cout << "Список: ";
            start = chrono::steady_clock::now();
            for (int i = 0; i < length; i++)
            {
                int data = rand() % 100;
                spisok.add_elem(data);

            }
            end = chrono::steady_clock::now();
            spisok.show();
            cout << endl << "Время создания списка: " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " наносекунд" << endl;
            system("pause");
            break;
        case 2:

            int data;
            cin >> data;
            while (data != -1)
            {
                spisok.add_elem(data);
                cin >> data;
            }
            system("pause");
            break;
        case 3:
            do
            {
                cout << endl << "Выберите действие со списком: " << endl;
                cout << "1 - Вывести элемент списка: " << endl;
                cout << "2 - Вставить элемент в любую позицию списка: " << endl;
                cout << "3 - Поменять 2 любых элемента в списке: " << endl;
                cout << "4 - Удалить любой элемент в списке: " << endl;
                cout << "5 - Выход из операций со списком: " << endl;


                cin >> deystv;
                switch (deystv)
                {
                case 1:
                    cout << "Исходный список" << endl;
                    spisok.show();
                    cout << "Введите индекс элемента, который хотите вывести" << endl;
                    int index;
                    cin >> index;
                    start = chrono::steady_clock::now();
                    cout << spisok[index]->data << endl;
                    end = chrono::steady_clock::now();

                    cout << "Время получения элемента списка: "
                        << chrono::duration_cast<chrono::nanoseconds>(end - start).count()
                        << " наносекунд" << endl;
                    system("pause");
                    break;
                case 2:
                    cout << "Исходный список" << endl;
                    spisok.show();
                    int data, head;
                    cin >> index;
                    cin >> data;
                    start = chrono::steady_clock::now();
                    spisok.insert_elem(index, data);
                    end = chrono::steady_clock::now();
                    spisok.show();
                    cout << "Время вставки элемента списка: "
                        << chrono::duration_cast<chrono::nanoseconds>(end - start).count()
                        << " наносекунд" << endl;
                    system("pause");
                    break;
                case 3:
                    cout << "Исходный список" << endl;
                    spisok.show();
                    int index2;
                    cout << "Первый индекс" << endl;
                    cin >> index;
                    cout << "Второй индекс" << endl;
                    cin >> index2;
                    start = chrono::steady_clock::now();
                    spisok.swap(index, index2);
                    end = chrono::steady_clock::now();
                    cout << "Измененный список" << endl;
                    spisok.show();
                    cout << "Время обмена элементов списка: "
                        << chrono::duration_cast<chrono::nanoseconds>(end - start).count()
                        << " наносекунд" << endl;
                    system("pause");
                    break;
                case 4:
                {
                    cout << "Исходный список" << endl;
                    spisok.show();
                    int del;
                    cin >> del;
                    start = chrono::steady_clock::now();
                    spisok.erase_elem(del);
                    end = chrono::steady_clock::now();
                    spisok.show();
                    cout << "Время удаления элементов списка: "
                        << chrono::duration_cast<chrono::nanoseconds>(end - start).count()
                        << " наносекунд" << endl;
                    system("pause");
                }
                break;
                }
            } while (deystv != 5);
            break;
        }

    } while (choose != 4);
    return 0;
}

