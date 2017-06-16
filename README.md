# CPE 473 Distributed Ray Tracer
# By: Paula Ledgerwood 


## Final Project: Constructive Solid Geometry
For my final project additional feature, I implemented constructive solid geometry to allow the use of
boolean operators on entire objects. The parsing support I offer matches the basic POVRAY 
specifications, found [here](http://www.povray.org/documentation/view/3.6.1/304/). The three boolean
operators available are union, intersection, and difference. 

## Intersection
### Here is a simple intersection of a box and a sphere:
![](https://github.com/paledger/raytracer/blob/master/images/intersection1.png)

## Difference
### Here is a box with four spheres subtracted:
![](https://github.com/paledger/raytracer/blob/master/images/multi_difference.png)

### Here is the same "difference" shape above, rotated in two different ways. A benefit of these operators is being able to apply transformations to the entire shape.
![](https://github.com/paledger/raytracer/blob/master/images/rotated_multi.png)

![](https://github.com/paledger/raytracer/blob/master/images/rotated_multi_2.png)

## Union
### Here is a simple union of two boxes, rotated and given the same color. This differs from the POVRAY specification which lets 'child' objects' color override the parent, while I let the parent's color override specific children's colors. 
![](https://github.com/paledger/raytracer/blob/master/images/union_og.png)

![](https://github.com/paledger/raytracer/blob/master/images/union_rotate.png)

![](https://github.com/paledger/raytracer/blob/master/images/union_final.png)

### Here is a union skewed. Each child object can be transformed in any way, before being combined with boolean operators:
![](https://github.com/paledger/raytracer/blob/master/images/transformed_diamond.png)

![](https://github.com/paledger/raytracer/blob/master/images/skewed_union.png)


# Software Design Principles
Throughout my project, I highly used polymorphism to allow me to extend the functionality easily throughout the quarter. 
A great example of this is in the abstract class Shape, which extends each geometrical object as well as two other important classes, BoundingBox and BooleanOperator.

Because my project was organized using this design, extending other geometric functionality (like Bounding Volume Hierarchy and Constructive Solid Geometry) was pretty straightforward. This design also helped decouple my geometric functionality from my Color/Lighting functionality. Because all of my Shading/Reflection/Refraction code depended on a vector<Shape> associated with a Scene, my Color/Lighting code was highly flexible and virtually untouched when implementing BVH and CSG. 

A useful design choice that made CSG easily integrated into my previous code was the choice for my getIntersection() functions across all Shape classes to return a vector<float> which contained all valid 't' values where the ray intersected with the Shape.

Below is a UML diagram of my overall Shape polymorphic design. Also present is the Composite design pattern, when implementing BVH and CSG, for straightforward recursion. 

![](https://github.com/paledger/raytracer/blob/master/images/RayTracer_ShapeDesign.jpg)









