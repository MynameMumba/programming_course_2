#include <iostream>
#include <vector>
using namespace std;
const int N = 3;

void backtrack(int *s, int n, int m){
    if (n == m) {
        cout << s[0] << " " << s[1] << " " << s[2] << endl;
        return;
    }

    for (int i = n; i < m; i++){
        int temp = s[n];
        s[n] = s[i];
        s[i] = temp;

        backtrack(s, n + 1, m);

        temp = s[n];
        s[n] = s[i];
        s[i] = temp;
    }
}  
bool check(int** matrix, int k, int row, int col) {
    for (int i = 0; i < row; i++) {
        if (matrix[i][col] == 1) 
            return false;
    }

    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
        if (matrix[i][j] == 1)
            return false;

        }
    for (int i = row - 1, j = col + 1; i >= 0 && j < k; i--, j++) {
        if (matrix[i][j] == 1)
            return false;
    }
    return true;
}

void matrixfunk(int row, int** matrix, int k, int* Q) {
    if (row == k) {
        for (int e = 0; e < k; e++) {
            cout << Q[e]+1 << " ";
        }
        cout << "\n";
        return;
        
    }
    for (int col = 0; col < k; col++) {
        if (check(matrix, k, row, col)) {
            matrix[row][col] = 1; // ставим ферзя
            Q[row] = col;
            matrixfunk(row + 1, matrix, k, Q);// переходим на следующую строку
            matrix[row][col] = 0; // откат 
        }
    }
}


void Queen(int j, int k, int* S, int* Q, int* R, int* L) {
    for (int i = 0; i < k; i++){
        if ((S[i] == 0) && (R[j-i + k - 1] == 0) && (L[j+i] == 0)) {
            S[i] = 1; 
            R[j - i + k - 1] = 1;
            L[j + i] = 1; 
            Q[j] = i;
            if (j == k - 1) {
                for (int e = 0; e < k; e++) {
                    cout << Q[e]+1 << " ";
                }
                cout << "\n";
            }
            else {
                Queen(j + 1, k, S, Q, R, L);
            }
            S[i] = 0; R[j - i + k - 1] = 0; L[i + j] = 0; 
        }
    }
}

int main() {
    // алгоритм ререстановки с бэктрекингом
    int s[N] {1, 2, 3};   
    backtrack(s, 0, N);

    // Ферзи через массивы
    int k;
    int c;
    cout << "Enter the board size:" << endl;
    cin >> k; // размер доски
    while (k > 10) {
        cout << "Программа будет выполняться слишком долго, вы уверены что хотите продолжить при k = " << k << "?\n" << "Введите 1 если да и 0 если хотите ввести другой размер доски: ";
        cin >> c;
        if (c == 1) { break; }
        if (c == 0) {
            cin >> k;
            cout << endl;
        }
    }

    int* S;//
    S = new int[k] {};
    int* Q;//
    Q = new int[k] {};
    int* R;//
    R = new int[(k * 2) - 1] {};
    int* L;//
    L = new int[(k * 2) - 1] {};
    //
    for (int i = 0; i < k; i++) {
        cout << "_ ";
    }
    cout << endl;
    //
    Queen(0, k, S, Q, R, L); // функция по костюку
    delete[] S;
    delete[] R;
    delete[] L;
    delete[] Q;

    //Ферзи через матрицы
    // Выделяем массив указателей на строки
    int** matrix = new int* [k];
    for (int i = 0; i < k; i++) {
        matrix[i] = new int[k] {};
    }
    int* M;
    M = new int[k] {};
    //
    for (int i = 0; i < k; i++) {
        cout << "_ ";
    }
    cout << endl;
    
    matrixfunk(0, matrix, k, M); // функция по матрицам
    
    for (int i = 0; i < k; i++) {
        cout << "_ ";
    }
    cout << endl;
    //

    for (int i = 0; i < k; i++) { // удаляем столбцы матрицы
        delete [] matrix[i];
    }
    delete[] matrix;
    delete[] M;
    return 0;
}





