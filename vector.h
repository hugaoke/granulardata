//
// vector.h
//
// Vector structure and its operations for 3-d space vectors.
//
// Written by: Yanting Wang           12/25/2002
//
#include <iostream>
#include <math.h>
using namespace std;

#ifndef __VECTOR__H
#define __VECTOR__H

struct Vector{
    double x, y, z;
    Vector() : x(0.0), y(0.0), z(0.0) {}
    Vector(double x, double y, double z ) : x(x), y(y), z(z) {}
    void set(double xx, double yy, double zz ) { x = xx; y = yy; z = zz; }
    void clear() { x = 0.0;   y = 0.0;   z = 0.0; }
// square length of a vector
    double r2() const { return x*x + y*y + z*z; }
// length of a vector
    double r() const { return sqrt( r2() ); }
// the unit vector
    Vector normal() const{
        double r = sqrt( x*x + y*y + z*z );
        return Vector( x/r, y/r, z/r );
    }
    const Vector &operator = (const Vector &v ) { 
        x = v.x;   y = v.y;   z = v.z; 
        return v;
    }
    const Vector &operator += (const Vector &v ){
        x += v.x;   y += v.y;   z += v.z;
        return *this;
    }

    const Vector &operator -= (const Vector &v ){
        x -= v.x;   y -= v.y;   z -= v.z;
        return *this;
    }

    const Vector &operator *= (double d ){
        x *= d;   y *= d;   z *= d;
        return *this;
    }

    const Vector &operator /= (double d ){
        x /= d;   y /= d;   z /= d;
        return *this;
    }
    };

    Vector operator+(const Vector &v1, const Vector &v2 ){
        return Vector( v1.x + v2.x, v1.y + v2.y, v1.z + v2.z );
    }

    Vector operator-(const Vector &v1, const Vector &v2 ){
        return Vector( v1.x - v2.x, v1.y - v2.y, v1.z - v2.z );
    }   

    Vector operator-(const Vector &v1 ){
        return Vector( -v1.x, -v1.y, -v1.z );
    }

    Vector operator*(const Vector &v, const double d ){
        return Vector( v.x*d, v.y*d, v.z*d );
    }

    Vector operator*(const double d, const Vector &v ){
        return Vector( v.x*d, v.y*d, v.z*d );
    }

//scalar product
    double operator*(const Vector &v1, const Vector &v2 ){
        return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
    }

//vector product
    Vector operator^(const Vector &v1, const Vector &v2 ){
        return Vector(v1.y*v2.z - v1.z*v2.y,
		v1.z*v2.x - v1.x*v2.z,v1.x*v2.y - v1.y*v2.x );
    }

    Vector operator/(const Vector &v, const double d ){
        return Vector( v.x/d, v.y/d, v.z/d );
    }

    ostream &operator<<(ostream &output, const Vector &p ){
        output << p.x << " " << p.y << " " << p.z;
        return output;
    }

    istream &operator>>(istream &input, Vector &p ){
        input >> p.x >> p.y >> p.z;
        return input;
    }

#endif //__VECTOR__H
