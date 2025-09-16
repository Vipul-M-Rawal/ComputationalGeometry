//We have to create basic structure for performing the computational geommetry algorithms/operations

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <set>

//First structure for the point 
//Fundamental 3-D geometry structures 

struct Point3D {
	double x, y, z;
	//Constructure 
	Point3D(double x = 0, double y = 0, double z = 0) :x(x), y(y), z(z) {};
	
	//Overload the operator+
	Point3D operator +(const Point3D& other) {
		return Point3D(x + other.x, y + other.y, z + other.z);
	}

	//Overload the operator - 
	Point3D operator- (const Point3D& other) const {
		return Point3D(x - other.x, y - other.y, z - other.z);
	}

	//Overload the operator *
	Point3D operator *(const Point3D& other) {
		return Point3D(x * other.x, y * other.y, z * other.z);
	}

	//Dot product 
	Point3D dot(const Point3D& other) {
		return Point3D(x * other.x + y * other.y + z * other.z);
	}

	//Cross product
	Point3D cross(const Point3D& other) {
		return Point3D(
			y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x
		);
	}

	//Magnitude of a vector
	double maginitude() const {
		return sqrt(x * x + y * y + z * z);
	}

	//Normalize the vector
	Point3D normalize() const {
		double mag = maginitude();
		return Point3D(x / mag, y / mag, z / mag);
	}

	//Distance between two points 
	double DistanceTp(const Point3D& other) {
		return (*this - other).maginitude();
	}

};


//Structure for Triangle 

struct Triangle
{
	Point3D a, b, c;
	//Constructor 
	Triangle(Point3D& a, Point3D& b, Point3D& c) :a(a), b(b), c(c) {};

	//Normal of the trianlgle const member function
	Point3D Normal() const {
		Point3D ab = b - a;
		Point3D bc = c - b;
		return ab.cross(bc).normalize();
	}

	double area() const {
		Point3D ab = a - b;
		Point3D bc = c - b;
		return 0.5 * ab.cross(bc).maginitude();
	}

	Point3D Centroid() const{
		
		return ((a.x + b.x + c.x)/3 , 
				(a.y + b.y + c.y)/3 , 
				(a.z + b.z + c.z)/3);
	}
};


//Structure of plane 
struct Plane {

	Point3D normal;
	double d;

	//Constructor 
	Plane(const Point3D& normal, double d) : normal(normal.normalize()), d(d) {};

	//
};