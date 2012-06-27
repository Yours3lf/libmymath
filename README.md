libmymath
=========

A great linear algebra lib.

--- Readme of mymath library ---

Welcome!

Let me introduce the mymath library. 
Mymath is a 3d maths library created with the intention to modernize 3d maths libraries, and meanwhile preserve simplicity and flexibility. 
Mymath is written in C++, it uses a modern object-oriented approach. 
It includes a camera class, which you can use for camera handling. 
It also includes a matrix stack class, which you can use as a replacement for the OpenGL functions. 
Mymath contains 2, 3, and 4 component vector classes and many functions using these classes. Mymath also contains 2x2, 3x3 and 4x4 matrix classes. 
Mymath is based on the math3d library and contains similar functions. However these functions are modernized, and even some new functions are included. The similarity in the 2.0+ versions is minimal.

Some important things to mention:
 -matrices are stored in COLUMN-MAJOR order (compatible with OpenGL) see: http://en.wikipedia.org/wiki/Column-major_order#Column-major_order
 -vectors are COLUMN-MAJOR vectors
 -all functions use RADIANS, if you need to convert use radians() or degrees()
