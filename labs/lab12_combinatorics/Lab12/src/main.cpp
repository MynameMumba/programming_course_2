#include <iostream>
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
void Queen(int j, int k, int* S, int* Q, int* R, int* L) {
    for (int i = 0; i < k; i++){
        if ((S[i] == 0) && (R[j-i + k - 1] == 0) && (L[j+i] == 0)) {
            S[i] = 1; 
            R[j - i + k - 1] = 1;
            L[j + i] = 1; 
            Q[j] = i;
            if (j == k - 1) {
                for (int e = 0; e < k; e++) {
                    cout << Q[e] << " ";
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
    int s[N] {1, 2, 3};   
    backtrack(s, 0, N);

    int k;
    cout << "Enter the board size:" << endl;
    cin >> k; // размер доски
    int* S;//
    S = new int[k] {};
    int* Q;//
    Q = new int[k] {};
    int* R;//
    R = new int[(k * 2) - 1] {};
    int* L;//
    L = new int[(k * 2) - 1] {};
    Queen(0, k, S, Q, R, L);
    delete[] S;
    delete[] Q;
    delete[] R;
    delete[] L;
    return 0;
}





