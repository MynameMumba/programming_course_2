#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

int main() {
    // чтение txt файла
    string line;
    ifstream in("Test.txt");
    getline(in, line);

    int M, N;
    istringstream iss(line);
    iss >> M;
    iss >> N;

    //создаём и заполняем матрицу
    int **matrix = new int*[M];
    for (int i = 0; i < M; i++) {
        matrix[i] = new int[N]{};
    }
    for (int i = 0; i < M; i++) {
        getline(in, line);
        istringstream iss(line);
        for (int j = 0; j < N; j++) {
            iss >> matrix[i][j];
        }
    }
    in.close();


    // вывод результата в txt файл
    ofstream out("Test.txt", ios::app);
    out << "печенько" << endl;
    // удаление матрицы
    for (int i = 0; i < M; i++) {
        delete [] matrix[i];
    }
    delete[] matrix;
    return 0;
}
