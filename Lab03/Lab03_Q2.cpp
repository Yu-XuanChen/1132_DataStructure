#include <iostream>
#include <cmath>
using namespace std;


class Polynomial {
private:
    int degree; //最高次數
    float* coef; //係數
public:
    Polynomial(int d);
    ~Polynomial();

    void input(); //讀取多項式
    Polynomial Add(Polynomial& other) const; //多項式的加法    
    Polynomial Mult(Polynomial& other) const; //多項式的乘法    
    float Eval(float x) const; //多項式的代入
    void print() const; //輸出    

    Polynomial::Polynomial(int d) {
        degree = d;
        coef = new float[degree + 1];
    }

    Polynomial::~Polynomial() {
        delete[] coef;
    }

    void Polynomial::input() {
        cout << "請輸入多項式最高次數: ";
        cin >> degree; //讀取最高次數
        coef = new float[degree + 1];

        cout << "請輸入多項式的係數: ";
        for (int i = degree; i >= 0; i--) { //由最高次到最低次
            cin >> coef[i]; //讀取係數
        }
    }

    Polynomial Polynomial::Add(Polynomial& other) const {
        Polynomial result(max(degree, other.degree));
        for (int i = 0; i <= result.degree; i++) {
            result.coef[i] = coef[i] + other.coef[i]; //將兩個多項式的係數相加
        }
        return result;
    }

    Polynomial Polynomial::Mult(Polynomial& other) const {
        Polynomial result(degree + other.degree);
        for (int i = 0; i <= degree; i++) {
            for (int j = 0; j <= other.degree; j++) {
                result.coef[i + j] += coef[i] * other.coef[j]; //將兩個多項式的係數相乘
            }
        }
        return result;
    }

    float Polynomial::Eval(float x) const {
        float result = 0;
        for (int i = 0; i <= degree; i++) {
            result += coef[i] * pow(x, i); //將多項式的係數代入
        }
        return result;
    }

    void Polynomial::print() const {
        int count = 0;
        for (int i = degree; i >= 0; i--) {
            if (count != 0) cout << " + ";
            cout << coef[i] << "x^" << i;
            count++;
        }
        if (count == 0) cout << "0"; 
    }
};

int main() {
    Polynomial p1, p2;
    
    cout << "請輸入第一個多項式: " << endl;
    p1.input();
    cout << "請輸入第二個多項式: " << endl;
    p2.input();

    Polynomial add = p1.Add(p2);
    cout << "Add: Polynomial 1 + Polynomail 2= ";
    add.print();
    cout << endl;

    Polynomial mult = p1.Mult(p2);
    cout << "Mult: Polynomial 1 * Polynomial 2= ";
    mult.print();
    cout << endl;

    int x;
    cout << "請輸入代入的值: ";
    cin >> x;
    cout << "Eval: Polynomial 1 = p(" << x << ")" << p1.Eval(x) << endl;
    cout << "Eval: Polynomial 2 = p(" << x << ")" << p2.Eval(x) << endl;

}
