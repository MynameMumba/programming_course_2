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

    //выводим в файл Result1 Итоговую матрицу смежности
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
    int edges = 0;
    for (int i = 0; i < Max; i++) {
        for (int j = 0; j < Max; j++) {
            if (matrixs[i][j] != 0) {
                edges += 1;
            }
        }
    }
    int* adjust = new int [edges] {};
    // массив длин
    int* len1 = new int[Max] {};
    // масив индексов
    int* index = new int[Max] {};
    int cc = 0, r = 0;

    //заполняем массив номеров смежных вершин
    for (int i = 0; i < Max; i++) {
        for (int j = 0; j < Max; j++) {
            if (matrixs[i][j] != 0) {
                adjust[r] = j + 1;
                r += 1;
                len1[i] += 1;
            }
        }
        index[i] = cc;
        cc += len1[i];
    }
    r = 0;
    //вывод массива смежных вершин
    ofstream out1;
    out1.open("Result2.txt");
    for (int i = 0; i < Max; i++) {
        out1 << "Вершина " << i+1 << ": [";
        for (int j = 0; j < len1[i]; j++) {
            out1 << adjust[r] << " ";
            r += 1;
        }
        out1 << "]" << endl;
    }
 
    out1.close();
    // Задание 3
    // матрица последовательности ребер 
    int** way = new int* [M] {};
    for (int i = 0; i < M; i++) {
        way[i] = new int[2];
    }
    //Заполняем массив, используя счетчик
    int edgeCount = 0;
    r = 0;
    for (int i = 0; i < Max; i++) {
        for (int k = 0; k < len1[i]; k++) {
        // Записываем ребро в текущую свободную позицию
            if ((i + 1) < adjust[r]) {
                way[edgeCount][0] = i + 1;
                way[edgeCount][1] = adjust[r];
                edgeCount++;

            }
            r++;
        }
    }
    ofstream out2;
    out2.open("Result3.txt");
    for (int i = 0; i < edgeCount; i++) {
        out2 << way[i][0] << " " << way[i][1] << endl;
    }
    out2.close();
    

    //удаление
    for (int j = 0; j < M; j++) {
        delete[] readmi[j];
    }
    for (int j = 0; j < Max; j++) {
        delete[] matrixs[j];
    }
    for (int j = 0; j < M; j++) {
        delete[] way[j];
    }
    delete[] way;
    delete[] adjust;
    delete [] readmi;
    delete[] matrixs;
    return 0;
}
