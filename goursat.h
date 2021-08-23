#pragma once
#include "vectors.h"

vec3 goursat_normal(vec3 pos, double kb) 
{
    return norm(vec3(4.0) * pos * pos * pos - vec3(2.0) * pos * kb);
}


double goursat_intersect(vec3 ro, vec3 rd, double ka, double kb) 
{
    double po = 1.0;
    vec3 rd2 = rd * rd; vec3 rd3 = rd2 * rd;
    vec3 ro2 = ro * ro; vec3 ro3 = ro2 * ro;
    double k4 = dot(rd2, rd2);
    double k3 = dot(ro, rd3);
    double k2 = dot(ro2, rd2) - kb / 6.0;
    double k1 = dot(ro3, rd) - kb * dot(rd, ro) / 2.0;
    double k0 = dot(ro2, ro2) + ka - kb * dot(ro, ro);
    k3 /= k4;
    k2 /= k4;
    k1 /= k4;
    k0 /= k4;
    double c2 = k2 - k3 * (k3);
    double c1 = k1 + k3 * (2.0 * k3 * k3 - 3.0 * k2);
    double c0 = k0 + k3 * (k3 * (c2 + k2) * 3.0 - 4.0 * k1);

    if (abs(c1) < 0.1 * abs(c2))
    {
        po = -1.0;
        double tmp = k1; k1 = k3; k3 = tmp;
        k0 = 1.0 / k0;
        k1 = k1 * k0;
        k2 = k2 * k0;
        k3 = k3 * k0;
        c2 = k2 - k3 * (k3);
        c1 = k1 + k3 * (2.0 * k3 * k3 - 3.0 * k2);
        c0 = k0 + k3 * (k3 * (c2 + k2) * 3.0 - 4.0 * k1);
    }

    c0 /= 3.0;
    double Q = c2 * c2 + c0;
    double R = c2 * c2 * c2 - 3.0 * c0 * c2 + c1 * c1;
    double h = R * R - Q * Q * Q;

    if (h > 0.0) // 2 intersections
    {
        h = sqrt(h);
        double s = sign(R + h) * pow(abs(R + h), 1.0 / 3.0); // cube root
        double u = sign(R - h) * pow(abs(R - h), 1.0 / 3.0); // cube root
        double x = s + u + 4.0 * c2;
        double y = s - u;
        double ks = x * x + y * y * 3.0;
        double k = sqrt(ks);
        double t = -0.5 * po * abs(y) * sqrt(6.0 / (k + x)) - 2.0 * c1 * (k + x) / (ks + x * k) - k3;
        return (po < 0.0) ? 1.0 / t : t;
    }

    // 4 intersections
    double sQ = sqrt(Q);
    double w = sQ * cos(acos(-R / (sQ * Q)) / 3.0);
    double d2 = -w - c2;
    if (d2 < 0.0) return -1.0; //no intersection
    double d1 = sqrt(d2);
    double h1 = sqrt(w - 2.0 * c2 + c1 / d1);
    double h2 = sqrt(w - 2.0 * c2 - c1 / d1);
    double t1 = -d1 - h1 - k3; t1 = (po < 0.0) ? 1.0 / t1 : t1;
    double t2 = -d1 + h1 - k3; t2 = (po < 0.0) ? 1.0 / t2 : t2;
    double t3 = d1 - h2 - k3; t3 = (po < 0.0) ? 1.0 / t3 : t3;
    double t4 = d1 + h2 - k3; t4 = (po < 0.0) ? 1.0 / t4 : t4;
    double t = 1e20;
    if (t1 > 0.0) t = t1;
    if (t2 > 0.0) t = fmin(t, t2);
    if (t3 > 0.0) t = fmin(t, t3);
    if (t4 > 0.0) t = fmin(t, t4);
    return t;
}