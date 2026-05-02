#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;
void Genealogy(int k, int num_families,int **data, vector <int>& row, vector<bool>& visited){
    visited[k] = true;
    row.push_back(k);
    for (int j = 0; j < num_families; j++) {
        if (data[k][j] == 1 && !visited[j]) {
            Genealogy(j, num_families, data, row, visited);
        }
    }
}
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

    //Genealogy
    vector<vector<int>> family;
    int num_families = 0;
    num1 = 0, num2 = 0;
    ifstream file2("Test2.txt");
    file2 >> num_families;
    //создаём матрицу смежности
    int** data = new int* [num_families] {};
    for (int i = 0; i < num_families; i++) {
        data[i] = new int[num_families] {};
    }
    //заполняем её
    while (file2 >> num1 >> num2) {
        if (num1 == -1) break;
        if (num1 >= 0 && num1 < num_families && num2 >= 0 && num2 < num_families) {
            data[num1][num2] = 1;
            data[num2][num1] = 1;  // неориентированный граф
        }
    }
    file2.close();
    //Рекурсивное нахождение мамы и папы
    vector<bool> visited(num_families, false);// массив посешенных вершин
    for (int i = 0; i < num_families; i++) {
        vector <int> row;
        if (!visited[i]) {
            vector <int> row;
            Genealogy(i, num_families, data, row, visited);
            // сортируем и загружаем массив 
            sort(row.begin(), row.end());
            family.push_back(row);
        }
    }

    // вывод
    size_t Rows = family.size();
    ofstream out3;
    out3.open("Result_Genealogy.txt");

    out3 << Rows << " семей" << endl;
    for (int i = 0; i < Rows; i++) {
        size_t Columns = family[i].size();
        for (int j = 0; j < Columns; j++) {
            if (j == Columns - 1) {
                out3 << family[i][j];
                break;
            }
            out3 << family[i][j] << "-";
        }
        out3 << endl;
    }
    out3.close();
    // удаление после Генеалогии
    for (int i = 0; i < num_families; i++) {
        delete[] data[i];
    }
    delete[] data;
    return 0;
}
