#include <glm/vec3.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/ext.hpp>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

vector<glm::vec3> read_obj(const string &filename) {

    std::vector<glm::vec3> Points;

    ifstream in(filename, ios::in);
    if (!in)
    {
        cerr << "Cannot open " << filename << endl; exit(1);
    }

    string line;
    while (getline(in, line))
    {
        if (line.substr(0,2) == "v ")
        {
            istringstream s(line.substr(2));
            glm::vec3 v; s >> v.x; s >> v.y; s >> v.z;
            Points.push_back(v);
        }
	/*
        else if (line.substr(0,2) == "f ")
        {
            istringstream s(line.substr(2));
            GLushort a,b,c;
            s >> a; s >> b; s >> c;
            a--; b--; c--;
           elements.push_back(a); elements.push_back(b); elements.push_back(c);
        }
        else if (line[0] == '#')
        {
        }
        else
        {
        }
	*/
    }

    return Points;

}

int main() {
    glm::vec3 a(2.0, 3.0, 4.0);
    glm::vec3 b(0.5, 0.5, 0.1);

    vector<glm::vec3> points = read_obj("simple.obj");

    for (unsigned i=0; i<points.size(); i++)
        cout << glm::to_string(points[i]) << "->";
    cout << endl;
    //a += b;
    /*
    double t = 1.0;

    cout << "a: " << glm::to_string(a) << endl;
    cout << "b: " << glm::to_string(b) << endl;
    cout << glm::length(a) << endl;
    cout << glm::length2(a) << endl;
    cout << glm::to_string(glm::normalize(a)) << endl;
    cout << glm::to_string(a + float(t)) << endl;
    cout << glm::to_string(a * float(t)) << endl;
    cout << (a+b).x << endl;
    cout << (a+b).r << endl;
    */
    return 0;
}	
