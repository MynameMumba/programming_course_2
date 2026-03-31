#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include <cmath>
using namespace std;
const float EPS = 1e-9;

void gauss(float** matrix, int M, int Col) {
    // сортируем матрицу (на первую позицию ставим строку с наибольшим числом в первом столбце)
    for (int n = 0; n < M && n < Col; n++) {
        int index = n;
        float max = fabsf(matrix[n][n]), temp;
        for (int i = n+1; i < M; i++) {
            if (fabsf(matrix[i][n]) > max){
                max = fabsf(matrix[i][n]);
                index = i;
            }
        }
        for (int r = 0; r < Col; r++) {
            temp = matrix[n][r];
            matrix[n][r] = matrix[index][r];
            matrix[index][r] = temp;
        }
        //делим первую строку на её первый элемент
        if (fabsf(matrix[n][n]) < EPS) {
            continue;
        }
        float pivot = matrix[n][n];
        for (int i = n; i < Col; i++) {
            matrix[n][i] /= pivot;
        }
        //вычитаем n-ю тройку из остальных
        for (int i = n+1; i < M; i++) {
            float factor = matrix[i][n];
            for (int j = n; j < Col; j++) {
                matrix[i][j] -= matrix[n][j] * factor;
            }
        }
    }

}


int main() {
    // чтение txt файла
    string line;
    ifstream in("Test.txt");
    getline(in, line);

    int M, N;
    istringstream iss(line);
    iss >> M;
    iss >> N;
    int Col = count(line.begin(), line.end(), ' ') + 1;
    
    //создаём и заполняем матрицу
    float **matrix = new float*[M];
    for (int i = 0; i < M; i++) {
        matrix[i] = new float[Col]{};
    }
    for (int i = 0; i < M; i++) {
        getline(in, line);
        istringstream iss(line);
        for (int j = 0; j < Col; j++) {
            iss >> matrix[i][j];
        }
    }
    // считываем x1,x2,x3...
    getline(in, line);
    in.close();

    //алгоритм превердения матрицы к ступенчатому виду
    gauss(matrix, M, Col);


    // вывод результата в txt файл
    ofstream out("Test.txt", ios::app);
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < Col; j++) {
            out << matrix[i][j] << " ";
        }
        out << endl;
    }
    out << endl;
    // удаление матрицы
    for (int i = 0; i < M; i++) {
        delete [] matrix[i];
    }
    delete[] matrix;
    return 0;
}
