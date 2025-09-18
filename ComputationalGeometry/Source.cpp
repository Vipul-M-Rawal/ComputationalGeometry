//We have to create basic structure for performing the computational geommetry algorithms/operations

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <set>
#include <cmath>

//First structure for the point 
//Fundamental 3-D geometry structures 

struct Point3D {
	double x, y, z;
	//Constructure 
	Point3D(double x = 0, double y = 0, double z = 0) :x(x), y(y), z(z) {};
	
	//Overload the operator+
	Point3D operator +(const Point3D& other) const {
		return Point3D(x + other.x, y + other.y, z + other.z);
	}

	//Overload the operator - 
	Point3D operator- (const Point3D& other) const {
		return Point3D(x - other.x, y - other.y, z - other.z);
	}

	//Overload the operator *
	Point3D operator *(const Point3D& other) const{
		return Point3D(x * other.x, y * other.y, z * other.z);
	}

	//Dot product 
	double dot(const Point3D& other) const{
		return (x * other.x + y * other.y + z * other.z);
	}

	//Cross product
	Point3D cross(const Point3D& other) const {
		return Point3D(
			y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x
		);
	}

	//Magnitude of a vector
	double magnitude() const {
		return sqrt(x * x + y * y + z * z);
	}

	//Normalize the vector
	Point3D normalize() const {
		double mag = magnitude();
		return Point3D(x / mag, y / mag, z / mag);
	}

	//Distance between two points 
	double DistanceTp(const Point3D& other) {
		return (*this - other).magnitude();
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
		return 0.5 * ab.cross(bc).magnitude();
	}

	//Overload the area function 
	static double area (const Point3D& a, const Point3D& b, const Point3D& c) {
		return 0.5 * std::abs((b - a).cross(c - a).magnitude());
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

	//Distance of a plane from a point p 
	double distanceToPoint(const Point3D& p) const {
		return std::abs(normal.dot(p) + d);
	}

	//Project the point on the plane :
	Point3D projectPoint(const Point3D& p) const {
		double dist = normal.dot(p) + d;
		return p - normal * dist;
	}
};


//Now start the algorithms 
//Algorithm -1 Point in triangle 

//So there are so many methods . i will implement here the area method
//Calaculate the main trianlge area and other 3 triangles area and check if it is same or not.
bool pointInTriangle3D(const Point3D& p, const Triangle& tri) {
	double mainTraingleArea = tri.area(tri.a , tri.b  ,tri.c);

	const double Epsilon = 1e-10;

	//Now calculate the area of small three triangles 

	double area1 = tri.area(tri.a, tri.b, p);
	double area2 = tri.area(tri.b, p, tri.c);
	double area3 = tri.area(tri.c, p, tri.a);


	return std::abs(mainTraingleArea - (area1 + area2 + area3)) < Epsilon;
}


//

void testAllMethods() {
	Point3D p1(0, 0, 0);
	Point3D p2(1, 0, 0);
	Point3D p3(0.5, 1, 0);



	Triangle tri(p1, p2, p3);
	Point3D insidePoint(0.3, 0.2, 0);
	Point3D outsidePoint(1.5, 0.5, 0);

	std::cout << "=== Point-in-Triangle Method Comparison ===" << std::endl;
	std::cout << std::boolalpha;

	std::cout << "\nTesting inside point (0.3, 0.2, 0):" << std::endl;
	std::cout << "Area Method:   " << pointInTriangle3D(outsidePoint, tri) << std::endl;


	//std::cout << "Barycentric:   " << pointInTriangleBarycentric(insidePoint, tri) << std::endl;
	//std::cout << "Same Side:     " << pointInTriangleSameSide(insidePoint, tri) << std::endl;
	//std::cout << "Angle Sum:     " << pointInTriangleAngleSum(insidePoint, tri) << std::endl;
	//std::cout << "Sign 2D:       " << pointInTriangleSign2D(insidePoint, tri) << std::endl;
	//std::cout << "Parametric:    " << pointInTriangleParametric(insidePoint, tri) << std::endl;
	//std::cout << "Edge Function: " << pointInTriangleEdgeFunction(insidePoint, tri) << std::endl;
	//std::cout << "Projection:    " << pointInTriangleProjection(insidePoint, tri) << std::endl;

	//std::cout << "\nTesting outside point (1.5, 0.5, 0):" << std::endl;
	//std::cout << "Barycentric:   " << pointInTriangleBarycentric(outsidePoint, tri) << std::endl;
	//std::cout << "Same Side:     " << pointInTriangleSameSide(outsidePoint, tri) << std::endl;
	//std::cout << "Area Method:   " << pointInTriangleArea(outsidePoint, tri) << std::endl;
	//std::cout << "Angle Sum:     " << pointInTriangleAngleSum(outsidePoint, tri) << std::endl;
	//std::cout << "Sign 2D:       " << pointInTriangleSign2D(outsidePoint, tri) << std::endl;
	//std::cout << "Parametric:    " << pointInTriangleParametric(outsidePoint, tri) << std::endl;
	//std::cout << "Edge Function: " << pointInTriangleEdgeFunction(outsidePoint, tri) << std::endl;
	//std::cout << "Projection:    " << pointInTriangleProjection(outsidePoint, tri) << std::endl;
}

int main() {
	testAllMethods();
	return 0;
}