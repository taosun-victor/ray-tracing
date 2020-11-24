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





one would be able to set up the streaming job and let every worker filter the incoming string with the specified KEY.

When one wants to do transform for the streaming job, he/she should go to every node's local directory and type the following:
```
./transform -fpath=FILE_PATH -word=KEY$'\t'KEY_REPLACEMENT -numWorker=NUM_WORKERS
```
one would be able to set up the streaming job and let every worker transform the corresponding KEY of the incoming string with the specified KEY_REPLACEMENT.

The last API is join, one needs to go to the corresponding directory and type:
```
./join -fpath=FILE_PATH -word=KEY$'\t'FILE_NAME -numWorker=NUM_WORKERS
```
one would be able to set up the streaming job and let every worker join the incoming string to the specified file according to the KEY.

This directory includes the working version of MP4. There is another directory MP4-experient, which is used to conduct the experiments required by the report. One could also take a look if feel interested. The directory of MP4-old is a batch system which does not satisfy the streaming requirement.
