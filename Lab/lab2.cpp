#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

class Rational {
public:
    Rational(int a = 0, int b = 1) {
        if (b < 0) {
            numerator = -a;
            denominator = -b;
        }
        else {
            numerator = a;
            denominator = b;
        }
        reduce();
    }
    Rational add(const Rational& b) const {
        Rational new_Rational(numerator*b.denominator + denominator*b.numerator, denominator*b.denominator);
        return new_Rational;
    }
    Rational subtract(const Rational& b) const {
        Rational new_Rational(numerator*b.denominator - denominator*b.numerator, denominator*b.denominator);
        return new_Rational;
    }
    Rational multiply(const Rational& b) const {
        Rational new_Rational(numerator*b.numerator, denominator*b.denominator);
        return new_Rational;
    }
    Rational divide(const Rational& b) const {
        Rational new_Rational(numerator*b.denominator, denominator*b.numerator);
        return new_Rational;
    }
    string toRationalString() const {
        ostringstream output;
        output << numerator << '/' << denominator;
        return output.str();
    }      // return a string in the format x/y
    double toDouble() const {
        return numerator/(double)denominator;
    }              // return a rational as double
private:
    int numerator;   // numerator
    int denominator; // denominator; positive integer
    void reduce() {
        int a{numerator > 0 ? numerator : -numerator};
        int limit{a > denominator ? denominator :  a};
        int i{2};
        while (i <= limit) {
            if (numerator % i == 0 && denominator % i == 0) {
                numerator /= i;
                denominator /= i;
            }
            else {
                i++;
            }
        }
    }   // convert to irreducible fraction with positive denominator
};

int main() {
    int a, b;

    cout << "Enter the first rational: ";
    cin >> a >> b;
    Rational first(a, b);

    cout << "First rational: " << first.toRationalString() << "\nEnter the second rational: ";
    cin >> a >> b;
    Rational second(a, b);

    cout << fixed << setprecision(2);
    cout << "Second rational: " << second.toRationalString() << endl;
    cout << first.toRationalString()  << " + " << second.toRationalString() << " = " << first.add(second).toRationalString() << " = " << first.add(second).toDouble() << endl;
    cout << first.toRationalString()  << " - " << second.toRationalString() << " = " << first.subtract(second).toRationalString() << " = " << first.subtract(second).toDouble() << endl;
    cout << first.toRationalString()  << " * " << second.toRationalString() << " = " << first.multiply(second).toRationalString() << " = " << first.multiply(second).toDouble() << endl;
    cout << first.toRationalString()  << " / " << second.toRationalString() << " = " << first.divide(second).toRationalString() << " = " << first.divide(second).toDouble() << endl;
}
