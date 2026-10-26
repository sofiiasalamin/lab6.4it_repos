#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <windows.h>
using namespace std;

// Варіант 26, ітераційний спосіб

void Create(double*& a, const int n, const double Low, const double High); // створення та заповнення масиву
void Print(const double* a, const int n);                                  // виведення масиву в рядок
double Min(const double* a, const int n);                                  // мінімальний елемент
int FirstPositive(const double* a, const int n);                           // індекс першого додатного (або -1)
int LastPositive(const double* a, const int n);                            // індекс останнього додатного (або -1)
double SumBetween(const double* a, const int first, const int last);       // сума елементів строго між індексами
bool SumBetweenPositives(const double* a, const int n, double& sum);       // сума між першим та останнім додатними
void MoveZerosFirst(double* a, const int n);                               // нулі - на початок, порядок решти збережено


void Create(double*& a, const int n, const double Low, const double High)
{
    a = new double[n]; // виділили пам'ять (вказівник - посилання!)
    const int steps = (int)((High - Low) * 10);
    for (int i = 0; i < n; i++)
        a[i] = Low + (rand() % (steps + 1)) / 10.0; // значення з кроком 0.1
}

void Print(const double* a, const int n)
{
    for (int i = 0; i < n; i++)
        cout << setw(8) << fixed << setprecision(2) << a[i];
    cout << endl;
}

double Min(const double* a, const int n)
{
    double min = a[0];
    for (int i = 1; i < n; i++)
        if (a[i] < min)
            min = a[i];
    return min;
}

int FirstPositive(const double* a, const int n)
{
    for (int i = 0; i < n; i++)
        if (a[i] > 0)
            return i;
    return -1;
}

int LastPositive(const double* a, const int n)
{
    for (int i = n - 1; i >= 0; i--)
        if (a[i] > 0)
            return i;
    return -1;
}

double SumBetween(const double* a, const int first, const int last)
{
    double s = 0;
    for (int i = first + 1; i < last; i++)
        s += a[i];
    return s;
}

bool SumBetweenPositives(const double* a, const int n, double& sum)
{
    int f = FirstPositive(a, n);
    int l = LastPositive(a, n);
    if (f == -1 || f == l) // менше двох додатних елементів
    {
        sum = 0;
        return false;
    }
    sum = SumBetween(a, f, l);
    return true;
}

void MoveZerosFirst(double* a, const int n)
{
    int w = n - 1; // позиція запису наступного ненульового елемента
    for (int i = n - 1; i >= 0; i--)
        if (a[i] != 0)
            a[w--] = a[i];
    for (int i = w; i >= 0; i--)
        a[i] = 0;
}


int main()
{
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);

    srand((unsigned)time(NULL));
    int n;
    do {
        cout << "n = "; cin >> n;
    } while (n <= 0);

    double* a = NULL;
    Create(a, n, -10, 10);
    cout << "Початковий масив:" << endl;
    Print(a, n);

    cout << "1.1. Мінімальний елемент = " << Min(a, n) << endl;

    double sum;
    if (SumBetweenPositives(a, n, sum))
        cout << "1.2. Сума між першим і останнім додатними = " << sum << endl;
    else
        cout << "1.2. Додатних елементів менше двох - суму обчислити неможливо" << endl;

    MoveZerosFirst(a, n);
    cout << "Масив після переміщення нулів на початок:" << endl;
    Print(a, n);

    delete[] a;
    return 0;
}
