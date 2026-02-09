#include <iostream>
#include <cmath>
using namespace std;

int Fib(long long Max)
{
    long long S{1};
    int x1{ 0 }, x2{ 1 }, nextnum, N{ 2 };
    cout << "\n";
    while (S <= Max)
    {
        nextnum = x1 + x2;
        x1 = x2;
        x2 = nextnum;
        N++;
        S += nextnum;
    }
    cout << N << "  " << S << endl;
    return 0;
}

int F(double x0)
{
    double t;
    if ((x0 > 4) || (x0 <= 1)) {
        cout << "Недопустимое значение";
        return 0;
    }

    t = (4 - x0) / 10;
    for (double x{ x0 }; x <= 4; x += t)
    {
        cout << sin(x) / x << " ";
    }
    return 0;
}

int main() {
    setlocale(LC_ALL, "Russian");
    double x1;
    long long Mx;
    cout << "Задание 1" << "\n" << "Введите число Max = ";
    cin >> Mx;
    Fib(Mx);

    cout << "\n" << "--------------------------------------------";

    cout << "Задание 2" << "\n";
    cout << "Введите мин число = ";
    cin >> x1;
    F(x1);
    cout << "\n";
    return 0;
}
