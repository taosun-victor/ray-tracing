#include <glm/vec3.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/ext.hpp>
#include <iostream>
#include <Magick++.h>

using namespace std;
using namespace Magick;

int main(int argc, char **argv){

    int nx = 602;
    int ny = 602;

    int pix[nx*ny*3];


    for (int j = ny-1; j>= 0; j--){
        for (int i = 0; i< nx; i++){

	    pix[(ny-j-1)*nx*3 + 3*i] = 200;
            pix[(ny-j-1)*nx*3 + 3*i + 1] = 100;
            pix[(ny-j-1)*nx*3 + 3*i + 2] = 1;

	}
    }

    for (int i=0; i<nx*ny*3; i++)
        cout << pix[i] << " ";
    InitializeMagick(*argv);
    Image image;
    image.read(ny, nx, "RGB", CharPixel, pix);
    image.write("test.png");

    return 0;
}
