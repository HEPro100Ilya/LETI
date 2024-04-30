#include <iostream>
#include <fstream> 
#include <string>

using namespace std;

string text;

void DeleteSpace(string txt) {
    for (int i = 0; i < txt.size(); i++) {
        if (txt[i] == ' ' && txt[i + 1] == ' ')
            while (txt[i + 1] == ' ')
                txt.erase((i + 1), 1);
    }
    text = txt;
}

void DeleteSign(string txt) {
    for (int i = 0; i <= txt.size(); i++) {
        if ((txt[i] == '.' || txt[i] == ',' || txt[i] == ';' || txt[i] == ':' || txt[i] == '!' || txt[i] == '?') && (txt[i + 1] == '.' || txt[i + 1] == ',' || txt[i + 1] == ';' || txt[i + 1] == ':' || txt[i + 1] == '!' || txt[i + 1] == '?'))
            if (txt[i] == '.' && txt[i + 1] == '.' && txt[i + 2] == '.' && txt[i + 3] == ' ')
                i += 3;
            else {
                while (txt[i + 1] == '.' || txt[i + 1] == ',' || txt[i + 1] == ';' || txt[i + 1] == ':' || txt[i + 1] == '!' || txt[i + 1] == '?')
                    txt.erase((i + 1), 1);
            }
    }
    text = txt;
}

void Register(string txt) {
    for (int i = 0; i < txt.size(); i++) {
        if (txt[i] == ' ')
            i += 2;
        txt[i] = tolower(txt[i]);
    }
    text = txt;
}

void UpFirst(string txt) {
    txt[0] = toupper(txt[0]);
    for (int i = 0; i < txt.size(); i++) {
        if (txt[i] == ' ')
            txt[i + 1] = toupper(txt[i + 1]);
    }
    text = txt;
}

int main()
{
    setlocale(0, "");

    /*  1 задание  */ {
        int input;
    Menu: {
        cout << "Записать текст или прочитать его с файла?\n"
            "1. Записать\n"
            "2. Прочитать с файла\n";
        cin >> input;
        }
    if (input == 1) { // Пользоватеть сам вводит текст
        cin.ignore();
        getline(cin, text);
    }
    else if (input == 2) { // Пользователь считывает файл
        ifstream file("D:\\text\\IDZ");
        if (file.is_open())
            getline(file, text);
        file.close();
    }
    else
        goto Menu;

    cout << "1) Исходная строка: " << text << "\n";
    }

    /*  2 задание  */ {
        DeleteSpace(text);
        DeleteSign(text);
        Register(text);

        cout << "2) Отредактированная строка: " << text << "\n";
    }

    /*  3 задание  */ {
        cout << "3) Cтрока в обратном порядке: ";
        int a = 0;
        text += " ";

        for (int i = text.length(); i >= 0; i--) {
            if (text[i] == ' ') {
                for (int k = i + 1; k <= (i + a); k++) {
                    cout << text[k];
                }
                a = 0;
            }
            a++;
        }
        for (int i = 0; i < text.length(); i++) {
            if (text[i] == ' ') break;
            cout << text[i];
        }
    }

    /*  4 задание  */ {
        UpFirst(text);

        cout << "\n4) Все слова с заглавной буквы: " << text << "\n";
    }
}