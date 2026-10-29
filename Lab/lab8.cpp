#include <iostream>
#include <string>
#include <array>
#include <sstream>
#include <cmath>
#include <iomanip>

using namespace std;

class Point {
public:
Point(int x=0, int y=0, int z=0) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    virtual ~Point() = default;
    int getX() const { return x; }
    int getY() const { return y; }
    int getZ() const { return z; }
    void setX(int px) { x = px; }
    void setY(int py) { y = py; }
    void setZ(int pz) { z = pz; }
    virtual string toString() const {
        ostringstream output;
        output << "(" << x << ", " << y << ", " << z << ") ";
        return output.str();
    }
    private:
    int x, y, z;
};

class Bubble : public Point {
    public:
    Bubble(int x, int y, int z, int r=0): Point(x, y, z) {
        setRadius(r);
        setVolume(r);
    }
    virtual ~Bubble() = default;
    int getRadius() const { return radius; }
    void setRadius(int r) { radius = r;}
    double getVolume() const { return volume; }
    void setVolume(int r) { volume = 3.14*r*r*r*4/3; }
    virtual string toString() const {
        ostringstream output;
        output << "bubble " << Point::toString() << "R=" << radius;
        return output.str();
    }
    private:
    int radius{0};
    double volume;
};

int overlap (const Bubble& b1, const Bubble& b2) {
    double d{sqrt(
        (b1.getX()-b2.getX())*(b1.getX()-b2.getX()) +
        (b1.getY()-b2.getY())*(b1.getY()-b2.getY()) +
        (b1.getZ()-b2.getZ())*(b1.getZ()-b2.getZ()))
    };
    int sum_r{b1.getRadius() + b2.getRadius()};
    if (d > sum_r) {
        return 1; // disjoint
    }
    else if (d < sum_r && d > abs(b1.getRadius() - b2.getRadius())) {
        return 2; // partially overlap
    }
    else if (d <= sum_r) {
        if (b1.getRadius() >= b2.getRadius()) {
            return 3; // b1 includes b2
        }
        else {
            return 4; // b1 is included in b2
        }
    }
    else {
        return -1; // error
    }
}

int main() {
    int x, y, z, r;
    int max_i{0};
    cout << "Enter the center (x, y, z) and radius of a bubble (EOF to end): ";
    cin >> x >> y >> z >> r;
    Bubble* b = new Bubble(x, y, z, r);
    array<Bubble*, 100> arr;
    arr[0] = new Bubble(x, y, z, r);
    int i{1};
    while (cin >> x) {
        cin >> y >> z >> r;
        arr[i] = new Bubble(x, y, z, r);
        cout << arr[i-1]->toString();
        switch(overlap(*arr[i-1], *arr[i])) {
            case 1:
                cout << " and " << arr[i]->toString() << " are disjoint\n";
                break;
            case 2:
                cout << " and " << arr[i]->toString() << " are partially overlap\n";
                break;
            case 3:
                cout << " includes " << arr[i]->toString() << endl;
                break;
            case 4:
                cout << " is included in " << arr[i]->toString() << endl;
                break;
        }
        if (arr[i]->getVolume() > arr[max_i]->getVolume()) {
            max_i = i;
        }
        i++;
    }
    cout << fixed << setprecision(2);
    cout << "bubble with the largest volume: " << arr[max_i]->toString() << ", V=" << arr[max_i]->getVolume();

    for (int j{0}; j<i; j++) {
        delete arr[j];
    }
    return 0;
}
