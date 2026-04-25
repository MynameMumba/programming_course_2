#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

int main() {
    int M = 0, num1 = 0, num2 = 0, Max = 0;
    string line;
    //
    ifstream file("Test.txt");
    if (!file.is_open()) {
        return 0;
    }
    getline(file, line);
    while ((line != "")) {
        M++;
        getline(file, line);
    }
    file.close();
    // создаем матрицу для считывания данных из файла
    int** readmi = new int* [M] {};
    for (int i = 0; i < M; i++) {
        readmi[i] = new int[2];
    }

    //Заполняем матрицу readmi
    ifstream in("Test.txt");
    for (int i = 0; i < M; i++) {
        getline(in, line);
        istringstream iss(line);
        iss >> num1 >> num2;
        readmi[i][0] = num1;
        readmi[i][1] = num2;
        if (num1 > Max) Max = num1;
        if (num2 > Max) Max = num2;
    }
    in.close();
    // создаем пустую матрицу смежности и заполняем её
    int** matrixs = new int* [Max] {};
    for (int i = 0; i < Max; i++) {
        matrixs[i] = new int[Max] {};
    }
    for (int j = 0; j < M; j++) {
        matrixs[readmi[j][0]-1][readmi[j][1]-1] = 1;
        matrixs[readmi[j][1]-1][readmi[j][0]-1] = 1;
    }

    //выводим в файл Result Итоговую матрицу смежности
    ofstream out;
    out.open("Result1.txt");
    for (int i = 0; i < Max; i++) {
        for (int j = 0; j < Max; j++) {
            out << matrixs[i][j] << " ";
        }
        out << endl;
    }
    out.close();
    // задание 2
    // массив номеров смежных вершин
    int** adjust = new int* [Max] {};
    for (int i = 0; i < Max; i++) {
        adjust[i] = new int[Max] {};
    }
    for (int i = 0; i < Max; i++) {
        int pos = 0;
        for (int j = 0; j < Max; j++) {
            if (matrixs[i][j] != 0) {
                adjust[i][pos++] = j+1;
            }
        }
    }//вывод массива смежных вершин
    ofstream out1;
    out1.open("Result2.txt");

    for (int i = 0; i < Max; i++) {
        out1 << "Вершина " << i+1 << ": [";
        for (int j = 0; j < Max; j++) {
            if (adjust[i][j] != 0) {
                out1 << adjust[i][j] << " ";
            }
        }
        out1 << "]" << endl;     
    }
    out1.close();



    //удаление
    for (int j = 0; j < M; j++) {
        delete[] readmi[j];
    }
    for (int j = 0; j < Max; j++) {
        delete[] matrixs[j];
        delete[] adjust[j];
    }
    delete[] adjust;
    delete [] readmi;
    delete[] matrixs;
    return 0;
}
