# Ray Tracing Practice
This project involves some basic practices for ray tracing algorithms. The fundamentals are implemented with C++.

## Shapes, Materials, Shadows
The basic shapes (spheres, triangles and planes) and materials (lambertian and metal) and shadows are implemented. To test a flavor of the basics,
```
cd ./basic
clang++ main-orth.cpp -o main-orth
./main-orth > basic.ppm
```
would generate the snapshot of the basic shapes and effects as the following.
![Alt text](./images/basic.png?raw=true "Basics")


## Bounding Volume Hierarchy
In order to accelerate the ray tracing process with sub-linear time complexity, the bounding volume hierarchy (BVH) is implemented. The performance of BVH is compared with naive array-based containers with total number of objects as of 100, 1,000 and 10,000. The images and the time spent are listed as the following.
![Alt text](./images/bvh.png?raw=true "bvh")

| object count  | 108  | 1,000  | 10,000|
| :-----:       | :-:  | :-:    | :-:   |
| array seconds | 143  | 1210   | 13278 |
| bvh seconds   |  35  |   66   |   187 |

It is shown that the bvh based container improves the time complexity from O(n) to O(logn) compared with native array-based containers.

## Rendering obj files
The OBJ format is a simple text file format for 3D surface meshes. By taking advantage of the triangle shape implementation in Part1, it is possible to parse and render objects represented by the .OBJ format.
![Alt text](./images/obj.png?raw=true "Objs")


## Reference
[ref-url]: https://raytracing.github.io/
