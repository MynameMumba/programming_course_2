#include <iostream>
using namespace std;
//123
int main() {
    setlocale(LC_ALL, "rus");
    // Статический с индексами
    int n1, n2, n3, n4;
    cout << "Static with indexes" << "\n" << "Enter the size of the array 1 = ";
    cin >> n1;
    int nums1[100];
    if ((size(nums1) < n1) || (n1 < 0)) {
        return 0;
    }

    for (int i = 0; i < n1; i++) {
        nums1[i] = i * i;
        cout << nums1[i] << " ";
    }
    // Статический с указателями
    cout << "\n" << "Static with pointers" << "\n" << "Enter the size of the array 2 = ";
    cin >> n2;
    int nums2[100];
    if ((size(nums2) < n2) || (n2 < 0)) {
        return 0;
    }
    for (int i = 0; i < n2; i++) {
        *(nums2 + i) = i * i;
        cout << *(nums2 + i) << " ";
    }
    // Динамический с индексами
    cout << "\n" << "Dynamic with indexes" << "\n" << "Enter the size of the array 3 = ";
    cin >> n3;
    int* nums3;
    nums3 = new int[n3];
    for (int i = 0; i < n3; i++) {
        nums3[i] = i * i;
        cout << nums3[i] << " ";
    }
    // Динамический с указателями
    cout << "\n" << "Dynamic with pointers" << "\n" << "Enter the size of the array 4 = ";
    cin >> n4;
    int* nums4;
    nums4 = new int[n4];
    for (int i = 0; i < n4; i++) {
        *(nums4 + i) = i * i;
        cout << *(nums4 + i) << " ";
    }
    //----
    int a, b, t1, t2;
    cout << "\n" <<  "number 1 array -> ";
    cin >> a;
    cout << "number 2 array -> ";
    cin >> b;
    if (a == 1) { t1 = n1; }
    if (a == 2) { t1 = n2; }
    if (a == 3) { t1 = n3; }
    if (a == 4) { t1 = n4; }
    //----
    if (b == 1) { t2 = n1; }
    if (b == 2) { t2 = n2; }
    if (b == 3) { t2 = n3; }
    if (b == 4) { t2 = n4; }
    if ((a == b) || (a < 1) || (a > 4) || (b < 1) || (b > 4)) {delete[] nums3; delete[] nums4; return 0;}
    //--
    int c = 0;
    int* un_arr;
    un_arr = new int[t1 + t2];
    if (a == 1) {
        for (int i = 0; i < t1; i++) {
            un_arr[i] = nums1[i];
            c++;
        }
    }
    if (a == 2) {
        for (int i = 0; i < t1; i++) {
            un_arr[i] = nums2[i];
            c ++ ;
        }
    }
    if (a == 3) {
        for (int i = 0; i < t1; i++) {
            un_arr[i] = nums3[i];
            c++;
        }
    }
    if (a == 4) {
        for (int i = 0; i < t1; i++) {
            un_arr[i] = nums4[i];
            c++;
        }
    }
    //----
    if (b == 1) {
        for (int i = 0; i < (t2); i++) {
            un_arr[c + i] = nums1[i];
        }
    }
    if (b == 2) {
        for (int i = 0; i < (t2); i++) {
            un_arr[c + i] = nums2[i];
        }
    }
    if (b == 3) {
        for (int i = 0; i < (t2); i++) {
            un_arr[c + i] = nums3[i];
        }
    }
    if (b == 4) {
        for (int i = 0; i < (t2); i++) {
            un_arr[c + i] = nums4[i];
        }
    }
    cout << "Сombined array:" << "\n";

    for (int i = 0; i < t1 + t2; i++) {
        cout << un_arr[i] << " ";
    }
    delete[] nums3;
    delete[] nums4;
    delete[] un_arr;
    return 0;
}
