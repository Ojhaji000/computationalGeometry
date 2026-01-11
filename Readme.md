# Computational Geometry
- This project is about solving the below problem:
- In a 3D space, find whether a line is intersecting with a triangle or not?
- This project is on going right now

 ## How to run it
 - download the project
 - install [MSYS64](https://www.msys2.org/) and follow it's instructions 
 - install cmake
 <!-- - open terminal, make a build directory-->
 - open project directory in terminal and run the below command
```
////// need lot of testing on new system
mkdir build && cd build
cmake ..
cmake --build .
./"your chosen directory name"/run and then press tab
./1.line-triangle-intersection/run1.lineTriangleExe
```
- a "output.txt" file will be generated, whose content could be copy pasted in **[desmos3D](https://www.desmos.com/3d)** and viewed

---
[link of the below graph](https://www.desmos.com/3d/q3j0u8wrko)

---
 ![output in desmos3d](image.png)

---
!warning for debugging:
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
