#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class Point {
public:
    Point(string pname=NULL, int px=0, int py=0) {
        setName(pname);
        setX(px);
        setY(py);
    }
    string getName() {
        return name;
    }
    int getX() {
        return x;
    }
    int getY() {
        return y;
    }
    void setName(string pname) {
        name = pname;
    }
    void setX(int px) {
        x = px;
    }
    void setY(int py) {
        y = py;
    }
private:
    string name;
    int x;
    int y;
};

int main() {
    vector<Point> v;
    int n;
    double avg_x{0},avg_y{0};

    cout << "Number of the points: ";
    cin >> n;

    for (int i{0}; i<n; i++) {
        string name;
        int x, y;
        cout << "Name of a point: ";
        cin.ignore(100, '\n');
        getline(cin, name);
        cout << "Position of a point: ";
        cin >> x >> y;
        avg_x += x;
        avg_y += y;
        Point p(name, x, y);
        v.push_back(p);
        cout << v[i].getName() << " (" << v[i].getX() << ", " << v[i].getY() << ")\n\n";
    }

    avg_x /= n;
    avg_y /= n;
    cout << fixed << setprecision(1);
    cout << "Center of " << n << " points: (" << avg_x << ", " << avg_y << ")";
    return 0;
}
