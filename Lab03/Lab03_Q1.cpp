#include <iostream>
#include <cmath>
using namespace std;

const int MaxDegree = 1000;

class Polynomial {
private:
    int degree; //最高次數
    float coef[MaxDegree + 1]; //係數
public:
    void input() { //讀取多項式
        cout << "請輸入多項式最高次數: ";
        cin >> degree; //將輸入的數字存到degree

        cout << "請依次輸入係數和次數: ";
        for (int i = degree; i >= 0; i--) { //從最高次數開始遍歷到最低次數0
            float coeff;
            cout << "請輸入x^" << i << "的係數: ";
            cin >> coeff; //將輸入的數字存到coeff
            coef[i] = coeff; //將coeff存到coef[i]
        }
    }

    Polynomial Add(Polynomial& other) const { //多項式的加法
        Polynomial result{}; //創建多項式結果
        result.degree = max(degree, other.degree); //取出兩個多項式中最高次數

        for (int i = 0; i <= result.degree; i++) { //從0開始到結果的最高次數遍歷每一項
            result.coef[i] = 0; //初始化為0
            result.coef[i] = coef[i] + other.coef[i]; //當前多項式次數i的係數加上另外一個多項式次數i的係數，然後儲存結果
        }
        return result;
    }

    Polynomial Mult(Polynomial& other) const { //多項式的乘法
        Polynomial result{};
        result.degree = degree + other.degree; //最高次數為兩個多項式最高次數相加

        for (int i = 0; i <= degree; i++) { //從0開始遍歷當前多項式到最高次數
            for (int j = 0; j <= degree; j++) { //從0開始遍歷另一個多項式
                result.coef[i + j] += coef[i] * other.coef[j]; //當前多項式次數i的係數和另一個多項式次數j的係數相乘，然後存到result的兩個次數相乘
            }
        }
        return result;
    }

    float Eval(float x) const { //多項式的代入
        float result = 0; //宣告result，初始化為0
        for (int i = 0; i <= degree; i++) { //從0開始遍歷每一項
            result += coef[i] * pow(x, i); //次數i的係數乘上x的i次方，然後加到result
        }
        return result;
    }

    void print() const { //輸出
        int count = 0; //計算已輸出幾項

        for (int i = degree; i >= 0; i--) { //從最高次數開始遍歷到0
            if (coef[i] != 0) { //看該項係數是否為0
                if (count > 0) cout << "+"; //如果不是第一項，會在後面加上"+"
                cout << coef[i] << "x^" << i;
                count++; //計數器+1

            }
        }
        if (count == 0) cout << "0"; //計數器為0表示每項係數都是0，則輸出0
    }
};

int main() {
    Polynomial p1, p2;

    //輸入
    cout << "請輸入第一個多項式: " << endl;
    p1.input();

    cout << "請輸入第二個多項式: " << endl;
    p2.input();

    //加法
    Polynomial add = p1.Add(p2);
    cout << "Add: Polynomial 1 + Polynomial 2= ";
    add.print();
    cout << endl;

    //乘法
    Polynomial mult = p1.Mult(p2);
    cout << "Mult: Polynomial 1 * Polynomial 2= ";
    mult.print();
    cout << endl;

    //代入
    int x;
    cout << "請輸入代入的值: ";
    cin >> x;
    cout << "Eval: Polynomial 1 = p(" << x << ") =" << p1.Eval(x) << endl;
    cout << "Eval: Polynomial 2 = p(" << x << ") =" << p2.Eval(x) << endl;

}
