libmymath
=========

A great linear algebra lib.

--- Readme of mymath library ---

Welcome!

Let me introduce the mymath library.
Mymath is a 3d maths library created with the intention to modernize 3d maths libraries, and meanwhile preserve simplicity and flexibility.
Mymath is written in C++, it follows the GLSL conventions. Therefore the syntax
and implementation is the same, if not it's a bug.
It includes a camera class, which you can use for camera handling.

Mymath contains 2, 3, and 4 component vector classes and many functions using these classes. Mymath also contains 2x2, 3x3 and 4x4 matrix classes.

Some important things to mention:
- matrices are stored in COLUMN-MAJOR order (compatible with OpenGL) see: http://en.wikipedia.org/wiki/Column-major_order#Column-major_order
- vectors are COLUMN-MAJOR vectors
- all functions use RADIANS, if you need to convert use radians() or degrees()
- the whole library follows the GLSL conventions

Contributors:
Artur Kovacs
