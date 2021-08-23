#pragma once
#include <math.h>

struct vec2 {
    double x = 0., y = 0.;

    vec2(double x_, double y_) :x(x_), y(y_) {};

    vec2(double val) :x(val), y(val) {};

    vec2 operator/(vec2 other)  { return vec2(x / other.x, y / other.y); }

    vec2 operator+(vec2 other) { return vec2(x + other.x, y + other.y); }

    vec2 operator-(vec2 other) { return vec2(x - other.x, y - other.y); }

    double len() { return sqrt(x * x + y * y); }
};

struct vec3 {
    double x = 0., y = 0., z = 0.;
public:
    vec3(double x_, double y_, double z_) :x(x_), y(y_), z(z_) {};

    vec3(double val) :x(val), y(val), z(val) {};

    vec3(vec2 v, double d) : x(v.x), y(v.y), z(d) {};

    vec3(double d, vec2 v) : x(d), y(v.x), z(v.y) {};

    vec3 operator/(vec3 other) {  return vec3(x / other.x, y / other.y, z / other.z); }

    vec3 operator+(vec3 other) {  return vec3(x + other.x, y + other.y, z + other.z);  }

    vec3 operator-(vec3 other) { return vec3(x - other.x, y - other.y, z - other.z); }

    vec3 operator*(double val) { return vec3(x * val, y * val, z * val); }

    vec3 operator*(vec3 other) { return vec3(x * other.x, y * other.y, z * other.z); }
    
    vec3 operator-() { return vec3(-x, -y, -z); }

    double len() { return sqrt(x * x + y * y + z * z);}
};


double dot(vec3 v1, vec3 v2) { return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; }

double dot(vec2 v1, vec2 v2) { return v1.x * v2.x + v1.y * v2.y;  }

double sign(double v) {  return (0 < v) - (v < 0); }

double step(double x, double edge) { return x > edge; }

vec3 step(vec3 edge, vec3 x) { return vec3(step(x.x, edge.x), step(x.y, edge.y), step(x.z, edge.z)); }

vec3 sign(vec3 v) { return vec3(sign(v.x), sign(v.y), sign(v.z)); }

vec3 norm(vec3 v) { return v / v.len(); }
