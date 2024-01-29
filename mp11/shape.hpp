// Partners: KP38, SIRAPOP3
// This program consists of the the Shape class that has child objects: circle, rectangle,
// sphere, and rectprism. It also contains funtions that calculate the area and volume,
// and return the dimensions of each shape. The function createShape() is also important, 
// because it reads the input file and takes in all the inout dimension of each shapes. 
// The function MaxArea() and MaxVolume() are for determining the object(shape) that has 
// the greatest area or volume.

#ifndef SHAPE_H_
#define SHAPE_H_

#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
#include <list>
#include <fstream>
#include <iomanip>

using namespace std;

// Base class
// Please implement Shape's member functions
// constructor, getName()
class Shape
{
public:
 // Base class' constructor should be called in derived classes'
 // constructor to initizlize Shape's private variable
 Shape(string name)
 {
  name_ = name;
 }

 string getName()
 {
  return name_;
 }

 virtual double getArea() const = 0;
 virtual double getVolume() const = 0;

private:
 string name_;
};

// Rectangle
// Please implement the member functions of Rectangle:
// constructor, getArea(), getVolume(), operator+, operator-

template <class T>
class Rectangle : public Shape
{
public:
 Rectangle<T>(T width = 0, T length = 0) : Shape("Rectangle")
 {
  width_ = width;   // Assign width value into the private variable width_ of the Rectangle object
  length_ = length; // Assign length value into the private variable length_ of the Rectangle object
 }

 double getArea() const
 {
  return (width_ * length_); // return the rectangle's area
 }

 double getVolume() const
 {
  return 0.0; // return 0 because it is a 2-D shape
 }

 Rectangle<T> operator+(const Rectangle<T> &rec)
 {
  double new_width = width_ + rec.getWidth();    // Declare a new_width variable to be the width of the new Rectangle object
  double new_length = length_ + rec.getLength(); // Declare a new_length variable to be the length of the new Rectangle object
  return Rectangle(new_width, new_length);    // return a new thrid Rectangle object created by adding two objects together
 }

 Rectangle<T> operator-(const Rectangle<T> &rec)
 {
  double new_width = fmax(0, width_ - rec.getWidth());  // Declare a new_width variable to be the width of the new Rectangle object (if < 0, is 0)
  double new_length = fmax(0, length_ - rec.getLength()); // Declare a new_length variable to be the length of the new Rectangle object (if < 0, is 0)
  return Rectangle(new_width, new_length);     // return a new thrid Rectangle object created by subtracting two objects together
 }

 T getWidth() const
 {
  return width_; // return the rectangle's width
 }

 T getLength() const
 {
  return length_; // return the rectangle's height
 }

private:
 T width_;
 T length_;
};

// Circle
// Please implement the member functions of Circle:
// constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

class Circle : public Shape
{
public:
 Circle(double radius) : Shape("Circle")
 {
  radius_ = radius; // Assign the radius value into the private radius_ when a Circle object is declared
 }

 double getArea() const
 {
  return (M_PI * radius_ * radius_); // return the area of the circle
 }

 double getVolume() const
 {
  return 0.0; // return 0 since a circle is a 2-D shape
 }

 Circle operator+(const Circle &cir)
 {
  double new_radius = radius_ + cir.getRadius(); // Declaring new_radius as the sum of the radius of 2 Circle objects to be a radius for a new Circle
  return Circle(new_radius);        // return a new Circle object with new radius
 }

 Circle operator-(const Circle &cir)
 {
  double new_radius = fmax(0, radius_ - cir.getRadius()); // subtract the current object's radius with the inputed Circle's radius (if < 0, is 0)
  return Circle(new_radius);        // return a new Circle object with new radius
 }

 double getRadius() const
 {
  return radius_; // return the radius of the circle
 }

private:
 double radius_;
};

// Sphere
// Please implement the member functions of Sphere:
// constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

class Sphere : public Shape
{
public:
 Sphere(double radius) : Shape("Sphere")
 {
  radius_ = radius; // Assign the input value of radius into the private value radius_
 }

 double getVolume() const
 {
  return ((4.0 / 3.0) * M_PI * radius_ * radius_ * radius_); // return the sphere's volume
 }

 double getArea() const
 {
  return (4 * M_PI * radius_ * radius_); // return the sphere's surface area
 }

 Sphere
 operator+(const Sphere &sph)
 {
  double new_radius = radius_ + sph.getRadius(); // Assign the sum of the radius of 2 Sphere objects to be the new radius of a new sphere
  return Sphere(new_radius);        // return a new Sphere with the new radius
 }

 Sphere operator-(const Sphere &sph)
 {
  double new_radius = fmax(0, radius_ - sph.getRadius()); // the new_radius is the subtraction of current Sphere's radius and the inputed Sphere's radius (if < 0, is 0)
  return Sphere(new_radius);        // return a new Sphere with the new radius
 }

 double getRadius() const
 {
  return radius_; // return radius_ value
 }

private:
 double radius_;
};

// Rectprism
// Please implement the member functions of RectPrism:
// constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
class RectPrism : public Shape
{
public:
 RectPrism(double width, double length, double height) : Shape("RectPrism")
 {
  width_ = width;   // Assign the width value to the private value width_
  length_ = length; // Assign the length value to the private value length_
  height_ = height; // Assign the height value to the private value height_
 }

 double getVolume() const
 {
  return (width_ * length_ * height_); // return rectangle prism volume
 }

 double getArea() const
 {
  return ((2 * (width_ * length_)) + (2 * (width_ * height_)) + (2 * (length_ * height_))); // return rectagle surface area
 }

 RectPrism
 operator+(const RectPrism &rectp)
 {
  double new_width = width_ + rectp.getWidth();   // Assign the new_width of the new prism to be the sum of the width of 2 objects
  double new_length = length_ + rectp.getLength();  // Assign the new_length of the new prism to be the sum of the length of 2 objects
  double new_height = height_ + rectp.getHeight();  // Assign the new_height of the new prism to be the sum of the height of 2 objects
  return RectPrism(new_width, new_length, new_height); // return a new rectangular prism with new dimensions
 }

 RectPrism operator-(const RectPrism &rectp)
 {
  double new_width = fmax(0, width_ - rectp.getWidth());   // Assign the new_width of the new prism to be the difference of the width of 2 objects (if < 0, is 0)
  double new_length = fmax(0, length_ - rectp.getLength()); // Assign the new_length of the new prism to be the difference of the length of 2 objects (if < 0, is 0)
  double new_height = fmax(0, height_ - rectp.getHeight()); // // Assign the new_height of the new prism to be the difference of the height of 2 objects (if < 0, is 0)
  return RectPrism(new_width, new_length, new_height);   // return a new rectangular prism with new dimensions
 }

 double getWidth() const
 {
  return width_; // return width_ value
 }

 double getLength() const
 {
  return length_; // return length_ value
 }

 double getHeight() const
 {
  return height_; // return height_ value
 }

private:
 double length_;
 double width_;
 double height_;
};

// Read shapes from test.txt and initialize the objects
// Return a vector of pointers that points to the objects
static list<Shape *> CreateShapes(char *file_name)
{
 //@@Insert your code here
 ifstream in_file(file_name); // create a variable to hold the file from the input stream
 int obj_count;     // the number of shapes from the input text file
 in_file >> obj_count;   // read the top-most number in the input text file and assign it into the obj_count
 list<Shape *> objects;   // a vector pointer for holding different type of shapes
 Shape *newObject;

 int i = obj_count;
 while (i > 0)
 {
  string shape_name;
  in_file >> shape_name;
  if (shape_name == "Rectangle")
  {
   double w, l;
   in_file >> w >> l;
   newObject = new Rectangle<double>(w, l);
  }
  else if (shape_name == "Circle")
  {
   double r;
   in_file >> r;
   newObject = new Circle(r);
  }
  else if (shape_name == "Sphere")
  {
   double r;
   in_file >> r;
   newObject = new Sphere(r);
  }
  else if (shape_name == "RectPrism")
  {
   double w, l, h;
   in_file >> w >> l >> h;
   newObject = new RectPrism(w, l, h);
  }
  objects.push_back(newObject); // push the object onto the vector list
  i--;
 }
 in_file.close(); // close the file and stop reading
 return objects;  // return the vector list of shape objects
 ;
}

// call getArea() of each object
// return the max area
static double MaxArea(list<Shape *> shapes)
{
 double max_area = 0;
 //@@Insert your code here
 for (Shape *shape : shapes)
 {           // Traverse through the inputed list "shapes"
  double current_area = shape->getArea(); // Variable for holding the current object's area
  if (max_area < current_area)
  { // If the current area is greater than the max, then max = current area
   max_area = current_area;
  }
 }

 return max_area;
}

// call getVolume() of each object
// return the max volume
static double MaxVolume(list<Shape *> shapes)
{
 double max_volume = 0;
 //@@Insert your code here
 for (Shape *shape : shapes)
 {            // Traverse through the inputed list "shapes"
  double current_vol = shape->getVolume(); // Variable for holding the current object's volume
  if (max_volume < current_vol)    // If current volume > max, then max = current volume
  {
   max_volume = current_vol;
  }
 }

 return max_volume;
}
#endif