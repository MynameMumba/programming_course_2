#include <iostream>
#include <stdlib.h>
#include <ctime>
using namespace std;

void Un_mass(int M, int* mass) {
    int* un_mass = new int[M];
    int t, index = 0;
    int count = 0;
    for (int i = 0; i < 18; i++) {
        t = mass[i];
        for (int j = 0; j < t; j++) {
            if (index < M) {  // Проверка на выход за границы
                un_mass[index++] = i;
            }
        }
    }
    //Вывод распакованного массива
    cout << "The unpacked array: \n";
    for (int i = 0; i < M; i++) {
        cout << un_mass[i] << " ";
        count ++;
    }
    cout << "\n";
    cout << "The number of elements in the unpacked array: " << count << endl;
    delete[] un_mass;
}


void Mass(int M) {
    int mass[18]{0};
    int t = 0, r = 0;
    // Диапазон значений элементов: 

    for (int i = 0; i < M; i++) { // 
        t = rand() % 18;
        mass[t] += 1;
    }
    //Вывод сжатого массива
    cout << "compressed array: \n";
    for (int i = 0; i < 18 ;i++) {
        cout << mass[i] << " ";
    }
    Un_mass(M, mass);
}




int main() {
    srand(time(NULL));
    int M = 0;
    cout << "Enter the number of characters in the array (at least 1000): ";
    cin >> M;
    if (M > 1000) {
        Mass(M);
    }
    else {
        while (M <= 1000) {
            cout << "EROR!!! - The number of characters in the array must be > 1000 \n" << "Enter the number of characters in the array (at least 1000): " << endl;
            cin >> M;
        }
        Mass(M);
    }
    return 0;
}
