#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include <cmath>
#include <iomanip>
using namespace std;
const float EPS = 1e-9;
int inappropriate = 0;
// Вспомогательная функция: превращает "+", "-", "" в числа
float parseCoeff(string raw) {
    if (raw.empty() || raw == "+") return 1.0f;
    if (raw == "-") return -1.0f;
    return stof(raw); // stod для double, stof для float
}

void universary(float* equation, string line) {
    // 1. Убираем пробелы
    string s = "";
    for (char ch : line) if (ch != ' ') s += ch;

    // 2. Ищем позиции
    size_t xPos = s.find('x');
    size_t yPos = s.find('y');
    size_t zPos = s.find('z');
    size_t eqPos = s.find('=');

    //Парсим X
    if (xPos != string::npos) {
        string xRaw = s.substr(0, xPos);
        equation[0] = parseCoeff(xRaw);
    }
    else {
        equation[0] = 0; // Нет икса
    }

    //Парсим Y
    if (yPos != string::npos) {
        string yRaw = s.substr(xPos + 1, yPos - (xPos + 1));
        equation[1] = parseCoeff(yRaw);
    }
    else {
        equation[1] = 0;
    }

    //Парсим Z
    if (zPos != string::npos) {
        string zRaw = s.substr(yPos + 1, zPos - (yPos + 1));
        equation[2] = parseCoeff(zRaw);
    }
    else {
        equation[2] = 0;
    }
    //Парсим ==
    if (eqPos != string::npos) {
        string rightRaw = s.substr(eqPos + 1);
        equation[3] = parseCoeff(rightRaw);
    }
}

void prohod(float** matrix, int M, int Col, float* x) {
    for (int i = 0; i < M; i++) {
        bool rowIsZero = true;
        for (int j = 0; j < Col - 1; j++) {
            if (fabsf(matrix[i][j]) > EPS) {
                rowIsZero = false;
                break;
            }
        }
        if (rowIsZero) {
            if (fabsf(matrix[i][Col - 1]) > EPS) {
                inappropriate = 1;
                return;
            }
            inappropriate = 2;
            return;
        }
    }

    // Проверка на нули на диагонали (после исключения нулевых строк)
    for (int i = 0; i < M; i++) {
        if (fabsf(matrix[i][i]) < EPS) {
            inappropriate = 2;
            return;
        }
    }

    for (int i = M - 1; i >= 0; i--) {
        float sum = 0;
        for (int j = i + 1; j < Col - 1; j++) {
            sum += matrix[i][j] * x[j];
        }
        x[i] = (matrix[i][Col - 1] - sum) / matrix[i][i];
    }
    return;
}

void gauss(float** matrix, int M, int Col) {
    // сортируем матрицу (на первую позицию ставим строку с наибольшим числом в первом столбце)
    for (int n = 0; n < M && n < Col; n++) { // зацикливаем алгоритм (вычеркиваем столбец с 1 и нулями и соответствующую ему строку)
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
        //Все элементы первой строки делим на верхний элемент выбранного столбца.
        if (fabsf(matrix[n][n]) < EPS) {
            continue;
        }
        float pivot = matrix[n][n];
        for (int i = n; i < Col; i++) {
            matrix[n][i] /= pivot;
        }
        /* Из оставшихся строк вычитаем первую строку, 
        умноженную на первый элемент соответствующей строки, 
        с целью получить первым элементом каждой строки (кроме первой) ноль.
        */
        for (int i = n+1; i < M; i++) {
            float factor = matrix[i][n];
            for (int j = n; j < Col; j++) {
                matrix[i][j] -= matrix[n][j] * factor;
            }
        }
    }
}


int main() {
    string line;
    ifstream in("Test.txt");
    getline(in, line);

    int M, N;
    istringstream iss(line);
    iss >> M >> N;

    getline(in, line);
    int Col = count(line.begin(), line.end(), ' ') + 1;

    // создаём матрицу
    float** matrix = new float* [M];
    for (int i = 0; i < M; i++) {
        matrix[i] = new float[Col] {};
    }

    // первая строка
    {
        istringstream iss_first(line);
        for (int j = 0; j < Col; j++) {
            iss_first >> matrix[0][j];
        }
    }

    // остальные строки
    for (int i = 1; i < M; i++) {
        getline(in, line);
        istringstream iss(line);
        for (int j = 0; j < Col; j++) {
            iss >> matrix[i][j];
        }
    }

    getline(in, line); 
    in.close();
    // приведение к ступенчатому виду
    gauss(matrix, M, Col);
    //нахождение единственного решения
    float* x = new float[M] {};

    // Если переменных больше, чем уравнений — не единственное решение
    if ((Col - 1) > M) {
        inappropriate = 2;
    }
    // Вызываем prohod только если действительно единственное решение
    if (inappropriate == 0) {
        prohod(matrix, M, Col, x);
    }

    // Задание 3
    // Массив для общего решения
    float* general = new float[Col - 1] {};
    bool* isbasic = new bool[Col - 1] {};
    // если есть свободные члены
    if ((inappropriate == 2)) {
        // Поиск базисных переменных
        for (int i = 0; i < M; i++){
            for (int j = 0; j < Col - 1; j++){
                if (fabs(matrix[i][j]) > EPS){
                    bool isLeading = true;
                    for (int k = 0; k < j; k++) {
                        if (fabs(matrix[i][k]) > EPS) {
                            isLeading = false;
                            break;
                        }
                    }
                    if (isLeading) {
                        isbasic[j] = true;
                        break;
                    }
                }
            }
        }      
        int pp = 0;
        // Свободные переменные == 2
        for (int j = 0; j < Col - 1; j++) {
            if (!isbasic[j]&& (pp == 0)) {
                general[j] = 4.0f;
                pp++;
            }
            else if (!isbasic[j] && (pp == 1)) {
                general[j] = 1.0f;
            }

        }
        //Находим базисные переменные обратным ходом
        for (int i = M - 1; i >= 0; i--) {
            int leadCol = -1;
            for (int j = 0; j < Col-1; j++) {
                if (fabsf(matrix[i][j]) > EPS) {
                    bool isLeading = true;
                    for (int k = 0; k < j; k++) {
                        if (fabsf(matrix[i][k]) > EPS) {
                            isLeading = false;
                            break;
                        }
                    }
                    if (isLeading) {
                        leadCol = j;
                        break;
                    }
                }
            }
            if (leadCol != -1) {
                float sum = 0;
                for (int j = leadCol + 1; j < Col - 1; j++) {
                    sum += matrix[i][j] * general[j];
                }
                general[leadCol] = (matrix[i][Col - 1] - sum) / matrix[i][leadCol];
            }
        }
    }

    // вывод 
    ofstream out("Test.txt", ios::app);
    out << endl;
    out << "Матрица, приведенная к ступенчатому виду:" << endl;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < Col; j++) {
            out << setw(8) << fixed << setprecision(3) << matrix[i][j] << "\t";
        }
        out << endl;
    }
    out << endl;
    if (inappropriate == 1) {
        out << "Система несовместна (нет решений)" << endl;
    }
    else if (inappropriate == 0) {
        out << "Единственное решение:" << endl;
        for (int i = 0; i < M; i++) {
            out << "x" << i + 1 << " = " << fixed << setprecision(3) << x[i] << "  ";
        }
    }
    // 3 задание
    else if (inappropriate == 2) {
        out << "Общее решение(Свободные члены == 2):" << endl;
        //
        int freeCount = 0;
        for (int i = 0; i < Col - 1; i++) {
            if (!isbasic[i]) {
                freeCount++;
            }
        }
        if (freeCount == 1) { // если свободных == 1
            for (int i = 0; i < Col - 1; i++) {
                if (!isbasic[i]){
                    out << "x" << i+1 << " - is free"<< endl;                  
                }
            }
        }
        if (freeCount > 1) { // если свободных > 1
            bool first = true;
            for (int i = 0; i < Col - 1; i++) {
                if (!isbasic[i]) {
                    if (!first) out << ", ";
                    out << "x" << i + 1;
                    first = false;
                }
            }
            out << " - are free" << endl;
        }
        // вывод общего решения для свободных членов == 1
        for (int j = 0; j < Col - 1; j++) {
            out << "x" << j + 1 << " = " << fixed << setprecision(3) << general[j] << "  ";
        }


    }
    out << endl;
    out.close();

    // удаление
    for (int i = 0; i < M; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    delete[] x;
    delete[] isbasic;
    delete[] general;

    //--------------------------------------------------------------------------------------------
    //доп. задания(1)
    inappropriate = 0;
    string ln;
    ifstream file("Ex_3.1.txt");
    getline(file, ln);
    int Q = ln.length(), colX= 0, colY =0;
    //Создаем cтроки матриц
    float equation1[4]{}, equation2[4]{}, equation3[4]{};
    //делим строку по запятой
    size_t zap1 = ln.find(',');
    size_t zap2 = ln.find(',', zap1 + 1);
    string line1 = ln.substr(0, zap1);
    string line2 = ln.substr(zap1 + 1, zap2 - zap1 - 1);
    string line3 = ln.substr(zap2 + 1);
    //для 1-й строки 
    universary(equation1, line1);
    universary(equation2, line2);
    universary(equation3, line3);
    //создаем и заполняем матрицу
    float** matrix2 = new float* [3];
    for (int i = 0; i < 3; i++) {
        matrix2[i] = new float[4] {};
    }
    for (int j = 0; j < 4; j++) {
        matrix2[0][j] = equation1[j];
        matrix2[1][j] = equation2[j];
        matrix2[2][j] = equation3[j];

    }
    // приводим к ступенчатому виду
    gauss(matrix2, 3, 4);
    float* x2 = new float[3] {};
    // ф-ция prohod
    prohod(matrix2, 3, 4, x2);
    file.close();
    ofstream out2("Ex_3.1.txt", ios::app);
    if (inappropriate == 1) out2 << "\n" << "Inconsistent system";
    else if (inappropriate == 2) out2 << "\n" << "Set of decisions";
    else {
        out2 << "x = " << x2[0] << " " << "y = " << x2[1] << " " << "z = " << x2[2] << endl;
    }
    // удаление
    for (int i = 0; i < 3; i++) {
        delete[] matrix2[i];
    }
    delete[] matrix2;
    delete[] x2;
    out2.close();
    return 0;
}
