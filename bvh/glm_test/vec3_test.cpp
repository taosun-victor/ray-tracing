#include <glm/vec3.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/ext.hpp>
#include <iostream>

using namespace std;

int main() {
    glm::vec3 a(2.0, 3.0, 4.0);
    glm::vec3 b(0.5, 0.5, 0.1);

    //a += b;
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

    return 0;
}	
