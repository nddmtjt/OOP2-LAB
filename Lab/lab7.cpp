#include <iostream>
#include <iomanip>

using namespace std;

class Shape {
public:
    Shape (int x=0, int y=0, int z=0, int r=1) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->r = r;
    }
protected:
    double pi{3.14};
    int x, y, z, r;
};

class Cylinder : public Shape {
public:
    Cylinder(int px, int py, int pz, int pr, int ph): Shape(px, py, pz, pr), h(ph) {}
    void volume() {
        cout << "Volume of the cylinder: " << pi*r*r*h << endl;
    }
    void draw() {
        cout << "Drawing of the cylinder at (" << x << ", " << y << ", " << z << ")\n";
    }
private:
    int h;
};

class Sphere : public Shape {
public:
    Sphere(int px, int py, int pz, int pr): Shape(px, py, pz, pr) {}
    void volume() {
        cout << "Volume of the sphere: " << 4/3.0*pi*r*r*r << endl;
    }
    void draw() {
        cout << "Drawing of the sphere at (" << x << ", " << y << ", " << z << ")\n";
    }
};

class Cone : public Shape {
public:
    Cone(int px, int py, int pz, int pr, int ph): Shape(px, py, pz, pr), h(ph) {}
    void volume() {
        cout << "Volume of the cone: " << 1/3.0*pi*r*r*h << endl;
    }
    void draw() {
        cout << "Drawing of the cone at (" << x << ", " << y << ", " << z << ")\n";
    }
private:
    int h;
};

int main() {
    char shape;
    int x, y, z, r, h;

    cout << "Shape type (y: cylinder, s: sphere, c: cone, EOF: to end): ";
    cout << fixed << setprecision(2);
    while (cin >> shape) {
        if (shape == 'y') {
            cout << "Center position, radius and height of the cylinder (x y z r h): ";
            cin >> x >> y >> z >> r >> h;
            Cylinder c(x, y, z, r, h);
            c.volume();
            c.draw();
        }
        else if (shape == 's') {
            cout << "Center position and radius of the sphere (x y z r): ";
            cin >> x >> y>> z >> r;
            Sphere s(x, y, z, r);
            s.volume();
            s.draw();
        }
        else {
            cout << "Center position, radius and height of the cone (x y z r h): ";
            cin >> x >> y >> z >> r >> h;
            Cone c(x, y, z, r, h);
            c.volume();
            c.draw();
        }
        cout << "\nShape type (y: cylinder, s: sphere, c: cone, EOF: to end): ";
    }

    return 0;
}
