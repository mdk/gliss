# Gliss

Gliss is a OpenGL/GLES library for resolution-independent rendering of hardware-accelerated vector graphics directly on the GPU. The core functionality of the package is a suite of tools allowing to render cubic curves (third-degree polynomials) directly on the hardware using fragment shaders. The core optimisation comes from the fact that the CPU-intensive geometry generation step (and tessellation) can be skipped entirely from the rendering process.

![Curves image](http://mdk.org.pl/assets/cubic-examples.png)
![Curves image](http://mdk.org.pl/assets/cubic-triangle.png)

Gliss also provides direct support for quadratics (second-degree polynomials) which are interesting being a part of the SVG standard and the basis of TrueType font rendering.

## Example

    glissBegin (GLISS_CUBIC_PATH);
    glissMoveTo2d (0, 0);
    glissCubicTo6d (-200, -100, -200, -150, -200.0, -200.0);
    glissCubicTo6d (0, -150, 0, -100, 0.0, 0.0);
    glissCubicTo6d (200, -100, 200, -150, 200.0, -200.0);
    glissCubicTo6d (0, -150, 0, -100, 0.0, 0.0);
    glissCubicTo6d (200, 100, 200, 150, 200.0, 200.0);
    glissCubicTo6d (0, 150, 0, 100, 0.0, 0.0);
    glissCubicTo6d (-200, 100, -200, 150, -200.0, 200.0);
    glissCubicTo6d (0, 150, 0, 100, 0.0, 0.0);
    glissEnd ();

## Reference

This works is based on a research paper ["Resolution Independent Curve Rendering using
Programmable Graphics Hardware"](https://www.microsoft.com/en-us/research/wp-content/uploads/2005/01/p1000-loop.pdf) by Charles Loop and Jim Blinn from Microsoft Research.

You can find more details and some examples in my (very old) [blog post](http://mdk.org.pl/2007/10/27/curvy-blues).