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
    // Упражнение 4
    int word_count = 0;
    cout << "Введите количество слов в массиве: " << "\n";
    cin >> word_count;
    vector<string> words;
    words.reserve(word_count);
    if ((word_count > 20) || (word_count < 0)){
        return 0;
    }

    for (int i = 0; i < word_count; ++i) {
        string word;
        cout << "Введите слово: ";
        cin >> word;
        if (word.length() > 10) { 
            i--;
            cout << "Недопустимое слово, введите другое" << "\n";
        }
        else {
            words.push_back(word);
        }
    }
    cout << "Результат работы программы:" << "\n";
    for (int i = 1; i < word_count; i += 2 ){
        cout << words[i] << " ";
    }

    return 0;
}
///
//
//
//
