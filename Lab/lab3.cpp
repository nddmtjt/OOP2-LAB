#include <iostream>
#include <cmath>
#include <sstream>
#include <stdexcept>
#include <iomanip>

using namespace std;

class Quadratic {
    friend Quadratic add(Quadratic& q1, Quadratic& q2);
    friend Quadratic subtract(Quadratic& q1, Quadratic& q2);
public:
    Quadratic(double a, double b, double c) {
        this-> a = a;
        this-> b = b;
        this-> c = c;
    }
    string toString() const {
        ostringstream output;
        output << a << "x^2" << (b >= 0 ? "+" : "") << b << "x" << (c >= 0 ? "+" : "") << c << "=0";
        return output.str();
    }       // ax^2+bx+c=0 format의 string 리턴
    void solve() {
        double D{b*b - 4*a*c};
        cout << fixed << setprecision(2);
        cout << "Solution of " << toString() << ": ";
        if (D > 0) {
            cout << "x=" << (-b+sqrt(D))/(2*a) << " or " << (-b-sqrt(D))/(2*a) << endl;
        }
        else if (D == 0) {
            cout << "x=" << -b/(2*a) << endl;
        }
        else {
            cout << "No real roots\n";
        }
    }                // 이차방정식의 해를 구해서 출력
private:
    double a{ 1 };
    double b{ 0 };
    double c{ 0 };
};

Quadratic add(Quadratic& q1, Quadratic& q2) {
    return Quadratic(
        q1.a + q2.a,
        q1.b + q2.b,
        q1.c + q2.c
    );
}

Quadratic subtract(Quadratic& q1, Quadratic& q2) {
    return Quadratic(
        q1.a - q2.a,
        q1.b - q2.b,
        q1.c - q2.c
    );
}

int main() {
    double a, b, c;

    while (true) {
        cout << "Enter 3 coefficients of the first quadratic equation: ";
        cin >> a >> b >> c;
        try {
            if (a == 0) {
                throw invalid_argument("The coefficient of the quadratic term must be non-zero. Enter again.");
            }
        }
        catch (invalid_argument& e) {
            cout << e.what() << endl;
        }
        if (a != 0) {
            break;
        }
    }

    Quadratic q1(a, b, c);
    cout << "First equation: " << q1.toString() << endl;

    while (true) {
        cout << "Enter 3 coefficients of the second quadratic equation: ";
        cin >> a >> b >> c;
        try {
            if (a == 0) {
                throw invalid_argument("The coefficient of the quadratic term must be non-zero. Enter again.");
            }
        }
        catch (invalid_argument& e) {
            cout << e.what() << endl;
        }
        if (a != 0) {
            break;
        }
    }
    Quadratic q2(a, b, c);
    cout << "Second equation: " << q2.toString() << endl;
    cout << endl;
    q1.solve();
    q2.solve();
    cout << endl;

    cout << "(" << q1.toString() << ")+(" << q2.toString() << ")=" << add(q1, q2).toString() << endl;
    cout << "(" << q1.toString() << ")-(" << q2.toString() << ")=" << subtract(q1, q2).toString() << endl;
}
