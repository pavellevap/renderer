//
// Created by pavel on 08.04.16.
//

#include <cmath>
#include "Sphere.h"

RayIntersection Sphere::intersect(Ray ray) const {
    const double EPS = 1e-5;

    RayIntersection inter;

    // double a = 1;
    double b = 2 * dot(Vector3D(center, ray.origin), ray.dir);
    double c = Vector3D(center, ray.origin).squaredLen() - radius * radius;
    double d2 = b * b - 4 * c;
    if (d2 < 0) {
        inter.isValid = false;
        return inter;
    }
    double d = sqrt(d2);
    if (-b - d < EPS) {
        if (-b + d < EPS) {
            inter.isValid = false;
            return inter;
        }
        inter.isValid = true;
        inter.rayCoord = (-b + d) / 2;
    }
    else {
        inter.isValid = true;
        inter.rayCoord = (-b - d) / 2;
    }

    inter.point = ray.getPoint(inter.rayCoord);
    inter.norm = Vector3D(center, inter.point);
    inter.norm.normalize();

    inter.material = material;
    inter.texture = texture;

    double dx = inter.point.x - center.x;
    double dy = inter.point.y - center.y;
    double dz = inter.point.z - center.z;
    double phi = atan2(dz, dx);
    double theta = atan2(-dy, sqrt(dx * dx + dz * dz));
    inter.texCoords = Point2D(phi / M_PI / 2 + 0.5, theta / M_PI + 0.5);

    return inter;
}

Box Sphere::getBoundingBox() const {
    Box box;
    box.min = Point3D(center.x - radius, center.y - radius, center.z - radius);
    box.max = Point3D(center.x + radius, center.y + radius, center.z + radius);
    return box;
}