#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Point {
public:
    Point(int px=0, int py=0) {
        x = px;
        y = py;
    }
    int getX() const {
        return x;
    }
    int getY() const {
        return y;
    }
    void setX(int px) {
        x = px;
    }
    void setY(int py) {
        y = py;
    }
protected:
    int x;
    int y;
};

class Square : public Point {
public:
    Square(const string pname, int px, int py, unsigned int side = 0) {
        name = pname;
        setX(px);
        setY(py);
        this-> side = side;
        setArea(side*side);
    }
    unsigned int getSide() const {
        return side;
    }
    unsigned int getArea() const {
        return area;
    }
    string getName() const {
        return name;
    }
    void setSide(unsigned int side) {
        this-> side = side;
    }
    void setArea(unsigned int area) {
        this-> area = area;
    }
    void setName(string pname) {
        name = pname;
    }
private:
    unsigned int side;
    unsigned int area{ 0 };
    string name;
};

bool compareArea(const Square& c1, const Square& c2) {
    return c1.getArea() < c2.getArea();
}
bool compareX(const Square& c1, const Square& c2) {
    return c1.getX() < c2.getX();
}
bool compareY(const Square& c1, const Square& c2) {
    return c1.getY() < c2.getY();
}

int main() {
    string name;
    int x, y;
    unsigned int side;
    vector<Square> v;

    cout << "Enter the name, lower left corner and side of a square (EOF to end): ";

    while (cin >> name) {
        cin >> x >> y >> side;
        Square s(name, x, y, side);
        v.push_back(s);
    }

    sort(v.begin(), v.end(), compareArea);
    cout << "\n\nSquares in increasing order of area\n";
    for (int i{0}; i<v.size(); i++) {
        cout << v[i].getName() << "(" << v[i].getX() << ", " << v[i].getY() << ") side=" << v[i].getSide() << endl;
    }
    sort(v.begin(), v.end(), compareX);
    cout << "\nSquares in increasing order of x-coordinate\n";
    for (int i{0}; i<v.size(); i++) {
        cout << v[i].getName() << "(" << v[i].getX() << ", " << v[i].getY() << ") side=" << v[i].getSide() << endl;
    }
    sort(v.begin(), v.end(), compareY);
    cout << "\nSquares in increasing order of y-coordinate\n";
    for (int i{0}; i<v.size(); i++) {
        cout << v[i].getName() << "(" << v[i].getX() << ", " << v[i].getY() << ") side=" << v[i].getSide() << endl;
    }

    return 0;
}
