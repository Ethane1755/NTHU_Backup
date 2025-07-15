#include <iostream>
#include <string>
#include "11443.h"
using namespace std;

namespace oj
{   
    void Shape3D::setVolume(double v)
    {
        volume = v;
    }

    double Shape3D::getVolume()
    {
        return volume;
    }
    Sphere::Sphere(double r, double pi) {
        if (r <= 0 || pi <= 0) {
            setVolume(0.0);
            return;
        }
        double v = (4.0 / 3.0) * pi * r * r * r;
        setVolume(v);
    }
    Cone::Cone(double r, double h, double pi) {
        if (r <= 0 || pi <= 0 || h <= 0) {
            setVolume(0.0);
            return;
        }
        double v = (1.0 / 3.0) * pi * r * r * h;
        setVolume(v);
    }
    Cuboid::Cuboid(double a, double b, double c) {
        if (a <= 0 || b <= 0 || c <= 0) {
            setVolume(0.0);
            return;
        }
        double v = a * b * c;
        setVolume(v);
    }
    Cube::Cube(double a) : Cuboid(a, a, a) {
        // Cube is a special case of Cuboid with all sides equal
    }

}


int main(void)
{   
    using namespace oj;

    string s;
    double a, b, c;
    double totalVolume = 0.0, totalPerimeter = 0.0;

    while(cin >> s) {
        if(s == "Sphere") {
            cin >> a >> b;
            Sphere sphere(a, b);
            totalVolume += sphere.getVolume();
            //cout << "Ball: " << sphere.getVolume() << endl;
        }
        if(s == "Cone") {
            cin >> a >> b >> c;
            Cone cone(a, b, c);
            totalVolume += cone.getVolume();
            //cout << "Cone: " << cone.getVolume() << endl;
        }
        if(s == "Cuboid") {
            cin >> a >> b >> c;
            Cuboid cuboid(a, b, c);
            totalVolume += cuboid.getVolume();
            //cout << "Cuboid: " << cuboid.getVolume() << endl;
        }
        if(s == "Cube") {
            cin >> a;
            Cube cube(a);
            totalVolume += cube.getVolume();
            //cout << "Cube: " << cube.getVolume() << endl;
        }
    }

    cout << totalVolume << endl;

    return 0;
}