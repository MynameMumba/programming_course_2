#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>


using namespace std;
void task1() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    char chr1[10] = "Hello_";
    char chr2[10] = "World!";
    char result[20];
    //char
    strcpy_s(result, chr1);// копируем 1 строку в итоговую
    cout << "strcpy_s(): " << result << "\n" << endl;
    strcat_s(result, chr2);// соединяем строки по '\0' у 1 строки 
    cout << "strcat_s(): " << result << "\n" << endl;
    cout << "strlen(): " << strlen(result) << "\n" << endl;
    cout << "String-------" << "\n" << endl;
    //string
    string str1 = "Goodbye_";
    string str2 = "World";
    string StrResult;
    StrResult.append(str1); StrResult.append(str2);
    cout << "append(): " << StrResult << "\n" << endl;
    int N = StrResult.size();
    cout << "size(): " << N << "\n" << endl;
    StrResult.replace(8, 5, "Kesha");
    cout << "replace(): " << StrResult << "\n" << endl;
}
int main() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    cout << "Задание 1" << "\n" << "Char----------" << endl;
    task1();
    // Упражнение 4 string
    int word_count = 0;
    cout << "Задание 4(str) \n" << "Введите количество слов в массиве:" << endl;
    cin >> word_count;
    if ((word_count > 20) || (word_count <= 0)) {
        cout << "Не получится <<<(-___-)/";
        return 0;
    }
    //string1
    vector<string> words;
    words.reserve(word_count);

    for (int i = 0; i < word_count; ++i) {
        string word;
        char wordc[11];
        cout << "Введите "<< i+1 << " слово: ";
        cin >> word;
        cout << "\n";
        if (word.length() > 10) { 
            i--;
            cout << "Недопустимое слово, введите другое" << "\n";
        }
        else {
            words.push_back(word);
        }
    }
    cout << "Результат работы программы(Str):" << "\n";
    for (int i = 1; i < word_count; i += 2 ){
        cout << words[i] << " ";
    }
    cout << "\n" << "Задание 4(char)" << endl;
    // char 
    char mass[20][11];
    char word2[20];
    
    for (int i = 0; i < word_count; i++) {
        cout << "Введите " << i+1 << " Слово: ";
        cin >> word2;
        cout << "\n";
        if (strlen(word2) > 10) {
            i--;
            cout << "Недопустимое слово, введите другое" << "\n";
        }
        else {
            strcpy_s(mass[i], word2);
        }
    }
    cout << "\n" << "Результат работы программы(Сhar):" << "\n";
    for (int i = 1; i < word_count; i += 2) {
        cout << mass[i] << " ";
    }
    return 0; 
}

