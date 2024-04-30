#include <iostream>
#include <ctime>
#include <vector>
#include <fstream>
#include <queue>
#include <string>
using namespace std;

struct Node {         // Структура данных для хранения узла бинарного дерева
    int Key;        //ключ-значение узла, типа инт 
    Node* Left;        // указатель на левого потомка
    Node* Right;        // указатель на правого потомка
    Node(int key) {
        this->Key = key;
        this->Left = this->Right = NULL;
    }
};
struct Trunk {
    Trunk* prev;
    string str;
    Trunk(Trunk* prev, string str) {
        this->prev = prev;
        this->str = str;
    }
};

struct BinTree {        //стуктура бинарного дерева, тут все функции по дереву
    Node* Root = NULL;  //корневой узел
    int Size = 0;        //размер бинарного дерева
    void insert(int key) //функция добавления элемента
    {                        // сначала проверим корневой элемент
        if (Root != NULL)                //Если он не инициализирован,
            insert(key, Root);            //то вызовется рекурсивная функция для добавления элемента
        else {                            //Иначе Функция поместит новое значение:
            Root = new Node(key);            //инициализируется корневой элемент 
            Root->Key = key;            // поместится ключевое значение в соответствующую ячейку структуры. 
            Root->Left = NULL;            //Инициализируется указатель на левый и правый элемент как NULL
            Root->Right = NULL;
        }
    }

    void Destroy() {            //фунция удаления дерева
        DestroyTree(Root);
    }

    void Show() {            //Функция вывода дерева
        printTree(Root, NULL, false);
    }

    void ReadFromFile() {            //функция чтения из файла
        ifstream Massiv;
        Massiv.open("Massiv.txt");
        if (Massiv.is_open()) {
            int i;
            vector<int> arr;
            while (!Massiv.eof()) {
                Massiv >> i;
                arr.push_back(i);
            }
            for (int n : arr)
                insert(n);
        }
        Massiv.close();
    }

    int Search(int key) {            //поиск элемента
        Search(key, Root);
        if (Search(key, Root) != NULL) {
            cout << "Данное число есть в дереве" << '\n';
            return 1;
        }
        cout << "Данного числа нет в дереве" << '\n';
        return 0;
    }

    void FindMin() {        //функция поиска минимального значения
        cout << "Минимальное значение: " << FindMin(Root)->Key << '\n';
    }

    void FindMax() {            //функция поиска максимального значения
        cout << "Максимальное значение: " << FindMax(Root)->Key << '\n';
    }

    void DeleteKey(int Item) {                //функция удаления определенного элемента
        DeleteKey(Root, Item);
    }

    void SizeTree() {
        SizeTree(Root);
        cout << "Размер бинарного дерева: " << Size << '\n';
    }

    void DirectBypass() {
        DirectBypass(Root);
    }

    void ReverseBypass() {
        ReverseBypass(Root);
    }

    void WidthBypass() {
        WidthBypass(Root);
    }

    void PrintInFile(string R) {
        ofstream Output(R);
        PrintTree(Root, NULL, false, Output);
        Output.close();
    }

    void insert(int key, Node* Leaf) {
        if (key < Leaf->Key) {
            if (Leaf->Left != NULL)
                insert(key, Leaf->Left);
            else {
                Leaf->Left = new Node(key);
                Leaf->Left->Key = key;
                Leaf->Left->Left = NULL;
                Leaf->Left->Right = NULL;
            }
        }
        else {
            if (Leaf->Right != NULL)
                insert(key, Leaf->Right);
            else {
                Leaf->Right = new Node(key);
                Leaf->Right->Key = key;
                Leaf->Right->Left = NULL;
                Leaf->Right->Right = NULL;
            }
        }
    }

    void DestroyTree(Node* Leaf) {            //Если узел дерева существует
        if (Leaf) {                            //Функция вызовет сама себя
            DestroyTree(Leaf->Left);        //сначала для левого потомка
            DestroyTree(Leaf->Right);        //после для правого потомка
            delete Leaf;            // Если потомков нет, она удалит Узел, полученный в качестве параметра функции
        }
    }

    Node* DeleteKey(Node* Leaf, int Item) {
        if (Leaf->Key == Item) {
            if (Leaf->Left == NULL && Leaf->Right == NULL)
                return NULL;
            if (Leaf->Left == NULL)
                return Leaf->Right;
            if (Leaf->Right == NULL)
                return Leaf->Left;

            const Node* MinNodeInRightTree = FindMin(Leaf->Right);
            Leaf->Key = MinNodeInRightTree->Key;
            Leaf->Right = DeleteKey(Leaf->Right, MinNodeInRightTree->Key);
            return Leaf;
        }
        if (Item < Leaf->Key) {
            if (Leaf->Left == NULL) {
                cout << "Элемента нет в дереве " << "\n";
                return Leaf;
            }
            Leaf->Left = DeleteKey(Leaf->Left, Item);
            return Leaf;
        }
        if (Item > Leaf->Key) {
            if (Leaf->Right == NULL) {
                cout << "Элемента нет в дереве" << '\n';
                return Leaf;
            }
            Leaf->Right = DeleteKey(Leaf->Right, Item);
            return Leaf;
        }
    }

    Node* Search(int key, Node* Leaf) {            // поиск элемента с заданным ключевым значением:(Ключевое значение, //указатель ну узел)
        if (Leaf != NULL) {        //Если узел //инициализирован
            if (key == Leaf->Key) {    // И ключевое значение //узла совпадает с //искомым ключевым //значением.

                return Leaf;            //Возвращается указатель на найденный элемент.
            }
            if (key < Leaf->Key)            //Иначе, если искомое ключевое значение меньше ключевого значения узла
                return Search(key, Leaf->Left);        //Вызывается эта же функция для левого потомка
            else
                return Search(key, Leaf->Right); //Вызывается эта же функция для правого потомка
        }
        else {

            return NULL;        //Иначе возвращается NULL
        }
    }

    Node* FindMin(Node* Leaf) {            //получение узла с наименьшим значением
        if (Leaf->Left == NULL) {
            return Leaf;
        }
        return FindMin(Leaf->Left);
    }

    Node* FindMax(Node* Leaf) {        //получение узла с наибольшим значением 
        if (Leaf->Right == NULL) {
            return Leaf;
        }
        return FindMax(Leaf->Right);
    }

    void SizeTree(Node* Leaf) {        //размерность дерева
        if (Leaf) {
            Size++;
            SizeTree(Leaf->Left);
            SizeTree(Leaf->Right);
        }
    }

    void DirectBypass(Node* Leaf) {            //прямой обход - сверху внизу
        if (Leaf) {
            cout << Leaf->Key << ' ';
            DirectBypass(Leaf->Left);
            DirectBypass(Leaf->Right);
        }
    }

    void ReverseBypass(Node* Leaf) {    //Обратный обход – снизу-вверх
        if (Leaf) {
            ReverseBypass(Leaf->Left);
            ReverseBypass(Leaf->Right);
            cout << Leaf->Key << ' ';
        }
    }

    void WidthBypass(Node* Leaf) {        //обход в ширину
        queue<Node*> nodeQueue;
        nodeQueue.push(Leaf);
        while (!nodeQueue.empty()) {
            Leaf = nodeQueue.front();
            cout << Leaf->Key << ' ';
            nodeQueue.pop();
            if (Leaf->Left) {
                nodeQueue.push(Leaf->Left);
            }
            if (Leaf->Right) {
                nodeQueue.push(Leaf->Right);
            }
        }
    }

    void showTrunks(Trunk* p) {             //функция вывода связи дерева - стебли
        if (p == NULL) {
            return;
        }
        showTrunks(p->prev);
        cout << p->str;
    }

    void printTree(Node* Leaf, Trunk* prev, bool IsRight) {        //функция выводит узлы дерева, вызывает функцию вывода связей
        if (Leaf == NULL) {                //пустое дерево
            return;
        }
        string prev_str = "    ";            //отступ по уровням (длина как для стрелки)
        Trunk* trunk = new Trunk(prev, prev_str);            //новая связь
        printTree(Leaf->Right, trunk, true);            //новая связь
        if (!prev) {        //если нет предыдущего узла (предка) -> корень дерева

            trunk->str = "——>";            //связь корня дерева
        }
        else if (IsRight) {                //если правое поддерево
            trunk->str = ".——>";        //связь правого поддерева
            prev_str = "   |";            //в отступ по уровням добавляем черту (дерево идет вширь)
        }
        else {                            //в противном случае - левое поддерево
            trunk->str = "`-—>";        //левое поддерево
            prev->str = prev_str;        //отступ по уровням не меняется
        }
        showTrunks(trunk);                //выводим связи дерева - стебли
        cout << " " << Leaf->Key << '\n';            //выводим значение узла
        if (prev) {                                    // задаем строку отступов для узла, если есть поддеревья
            prev->str = prev_str;
        }
        trunk->str = "   |";                            //в отступ по уровням добавляем черту (дерево идет вширь)
        printTree(Leaf->Left, trunk, false);            //левое поддерево
    }

    void ShowTrunk(Trunk* p, ofstream& File) {            //функция вывода связей дерева
        if (p == NULL)                                    //если нет поддеревьев
            return;
        ShowTrunk(p->prev, File);                        //выводим предыдущий узел
        File << p->str;                                    //выводим отступы и связи
    }

    void PrintTree(Node* Leaf, Trunk* prev, bool IsRight, ofstream& File) {            //функция выводит узлы дерева, вызывает функцию вывода связей( только теперь для файла)
        if (Leaf == NULL)
            return;
        string prev_str = "    ";
        Trunk* trunk = new Trunk(prev, prev_str);
        PrintTree(Leaf->Right, trunk, true, File);
        if (!prev) {
            trunk->str = "-->";
        }
        else if (IsRight) {
            trunk->str = ".-->";
            prev_str = "   |";
        }
        else {
            trunk->str = "`-->";
            prev->str = prev_str;
        }

        ShowTrunk(trunk, File);
        File << Leaf->Key << '\n';

        if (prev) {
            prev->str = prev_str;
        }
        trunk->str = "   |";
        PrintTree(Leaf->Left, trunk, false, File);
    }
};
int main() {
    setlocale(0, "");
    int Variant;
    BinTree Tree;
    BinTree BinTree1;
    int N;
    int Var;
    vector<int> Numb;
    vector<int> Numbers;
    cout << "1. Самостоятельно заполнить дерево" << '\n';
    cout << "2. Автоматически заполнить дерево" << '\n';
    cout << "3. Заполнить дерево элементами из файла" << '\n';
    cin >> Var;
    switch (Var) {
    case 1:
        int Number;
        cout << "Вводите числа в массив, для окончания напишите 1985" << '\n';
        cin >> Number;
        while (Number != 1985) {
            Numbers.push_back(Number);
            cin >> Number;
        }
        for (int i : Numbers) {
            BinTree1.insert(i);
        }
        break;
    case 2:
        cout << "Введите размер дерева: ";
        cin >> N;
        cout << '\n';
        for (int i = 0; i < N; i++) {
            int data = rand() % (199) - 99;
            BinTree1.insert(data);
        }
        break;
    case 3:
        BinTree1.ReadFromFile();
        break;
    }
    do {
        system("cls");
        cout << "Что выхотите сделать?" << '\n';
        cout << "1. Вывести в консоль и файл бинарное дерево" << '\n';
        cout << "2. Добавить новый элемент в дерево" << '\n';
        cout << "3. Удалить элемент дерева" << '\n';
        cout << "4. Найти элемент дерева" << '\n';
        cout << "5. Прямой обход дерева" << '\n';
        cout << "6. Обратный обход дерева" << '\n';
        cout << "7. Обход в ширину дерева" << '\n';
        cout << "8. Выйти из программы" << '\n';
        int Value;
        cin >> Variant;
        switch (Variant) {
        case 1:
            BinTree1.Show();
            BinTree1.PrintInFile("Output.txt");
            break;
        case 2:
            cout << '\n' << "Введите значение которое хотите добавить в дерево: ";
            cin >> Value;
            BinTree1.insert(Value);
            break;
        case 3:
            cout << '\n' << "Введите значение которое хотите удалить из дерева: ";
            cin >> Value;
            BinTree1.DeleteKey(Value);
            break;
        case 4:
            cout << '\n' << "Введите значение которое хотите найти в дереве: ";
            cin >> Value;
            BinTree1.Search(Value);
            break;
        case 5:
            cout << "Прямой обход дерева: " << '\n';
            BinTree1.DirectBypass();
            break;
        case 6:
            cout << "Обратный обход дерева: " << '\n';
            BinTree1.ReverseBypass();
            break;
        case 7:
            cout << "Обход дерева в ширину: " << '\n';
            BinTree1.WidthBypass();
            break;

        }
        if (Variant != 8)
            system("pause");
    } while (Variant != 8);
    BinTree1.Destroy();
    Tree.Destroy();

}