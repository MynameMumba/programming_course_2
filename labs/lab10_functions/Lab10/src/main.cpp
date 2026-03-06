#include <iostream>
#include <stdlib.h>
#include <ctime>
using namespace std;

// Функция распаковки массива
int* Un_mass(int M, int* mass) {
    int* un_mass = new int[M];
    int index = 0;

    for (int i = 0; i < 18; i++) {
        int count = mass[i];
        for (int j = 0; j < count; j++) {
            if (index < M) {
                un_mass[index++] = i;
            }
        }
    }
    return un_mass;
}

int *Compressed_mass(int M, int* mass) {// Функция сжатия массива
    int* compr_mass = new int[18] ();
    for (int i = 0; i < M ; i++) {
        compr_mass[mass[i]] += 1;
    }
    return compr_mass;
}

int* Origin_Mass(int M) {
    int mass [18]{ 0 };
    int t = 0, r = 0;
    // Диапазон значений элементов: 

    for (int i = 0; i < M; i++) { // 
        t = rand() % 18;
        mass[t] += 1;
    }
    int* origin_mass = Un_mass(M, mass);
    return origin_mass;
}   

void chek_Mass(int M, int* origin, int* unpaking) {
    int t = 0;
    for (int i = 0; i < M; i++) {
        if (origin[i] == unpaking[i]) {
            t++;
        }
    }
    if (t == M) {
        cout << "\n The check was successful, and the original array matches the unpacked array. \n";
    }
    return;
}



int main() {
    srand(time(NULL));
    int M = 0;
    int t = 0;
    cout << "Enter the number of characters in the array (at least 1000): ";
    cin >> M;
    if (M > 1000) {
        int* origin = Origin_Mass(M);
        int* сompressed = Compressed_mass(M, origin);
        int* unpacking = Un_mass(M, сompressed);
        cout << "\n  The size of the original array is:" << M * sizeof(int);
        cout << "\n Size of the compressed array:" << 18 * sizeof(int) << endl;
        chek_Mass(M, origin, unpacking);
        delete[] origin;
        delete[] сompressed;
        delete[] unpacking;
    }
    else {
        while (M <= 1000) {
            cout << "EROR!!! - The number of characters in the array must be > 1000 \n" << "Enter the number of characters in the array (at least 1000): " << endl;
            cin >> M;
        }
        int* origin = Origin_Mass(M);
        int* сompressed = Compressed_mass(M, origin);
        int* unpacking = Un_mass(M, сompressed);
        cout << "\n  The size of the original array is:" << M * sizeof(int);
        cout << "\n Size of the compressed array:" << 18 * sizeof(int) << endl;
        chek_Mass(M, origin, unpacking);
        delete[] origin;
        delete[] сompressed;
        delete[] unpacking;

    }
    return 0;
}
