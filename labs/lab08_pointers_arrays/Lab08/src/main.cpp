#include <iostream>
using std::cout;
using std::cin;
//Задание 1: m = 456, n = 53.14
//Задание 2
int links_indicator(int n, int m) {
    // ссылка
    int links = n * n;
    int &reflinks = links;
    // указатель
    int indic = m * m;
    int *ref = &indic;
    cout << "5 ->" << reflinks << "| 10 ->" << *ref << "\n";
    return 0;
}
int un_arr(int* arr1, int* arr2) {
    int i = 0, j = 0, k = 0;
    int* big_arr;
    big_arr = new int[10];
    while ((i < 5) && (j < 5)) {
        if (arr1[i] < arr2[j]) {
            big_arr[k] = arr1[i];
            i++;
        }
        else {
            big_arr[k] = arr2[j];
            j++;
        }
        k++;
    while (i < 5) {
        big_arr[k] = arr1[i];
        i++;
        k++;
        }
    while (j < 5) {
        big_arr[k] = arr2[j];
        j++;
        k++;
    }
    }
    for (i = 0; i < 10; i++) {
        cout << big_arr[i] << " ";
    }
    delete[] big_arr;
    return 0;
}

struct Node {
    int id;
    Node* prev;
    Node* next;

};

void Exercise4()// упражнение 4
{
    cout << "task 4";

    Node* head = NULL;
    Node* tail = NULL;

    for (int i = 0; i < 10; i++)
    {
        Node* newItem = new Node;
        newItem->id = i;
        newItem->next = NULL;

        if (head == NULL)
        {
            newItem->prev = NULL;
            head = newItem;
            tail = newItem;
        }
        else
        {
            tail->next = newItem;
            newItem->prev = tail;
            tail = newItem;
        }
    }

    cout << "list output " << "\n";

    Node* current = head;
    while (current != NULL)
    {
        cout << current->id << " ";
        current = current->next;
    }
}

int main() {
    setlocale(LC_ALL, "rus");
    cout << "task 2" << "\n";
    int links = 5, indic = 10;
    links_indicator(links, indic);
    cout << "task 3" << "\n";
    // Статический с индексами
    int n1 = 10, n2 = 10, n3, n4;
    cout << "Static with indexes" << "\n" << "Enter the size of the array 1 = ";
    int nums1[10];
    for (int i = 0; i < 10; i++) {
        nums1[i] = i * i;
        cout << nums1[i] << " ";
    }
    // Статический с указателями
    cout << "\n" << "Static with pointers" << "\n" << "Enter the size of the array 2 = ";
    int nums2[10];
    for (int i = 0; i < 10; i++) {
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
    cout << "\n" << "merging arrays with even and odd numbers:" << "\n";
    // слияние массивов

    int* arr1;
    arr1 = new int[5] {0, 2, 4, 6, 8};
    int* arr2;
    arr2 = new int[5] {1, 3, 5, 7, 9};
    un_arr(arr1, arr2);
    delete[] arr1;
    delete[] arr2;
    // Двусвязный список
    cout << "\n" << "task 4" << "\n";
    Exercise4();
    return 0;
}
    
