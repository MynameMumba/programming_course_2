#include <iostream>
#include <fstream>
#include <cstdio>

using namespace std;

// Lab 11
// TODO: реализуйте решение по заданию в labs/lab11_io/README.md
//
// Рекомендация по выводу:
// - без лишнего текста
// - числа через пробел
// - если несколько строк — в фиксированном порядке
int main() {
    char words[50][26];
    int wordcount = 50;
    FILE* fp = fopen("words.txt", "r");
    if (fp == NULL) {
        printf("%s", "Fatal EROR");
        return 0;
    }

    while (!feof(fp) && (wordcount < 50)){
        if()

    }

    

    return 0;
}
