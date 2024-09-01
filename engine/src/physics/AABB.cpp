#include "AABB.hpp"

AABB::AABB(const std::vector<Vector3<>> &vertexes)
{
    for (const auto [x, y, z] : vertexes)
    {
        min.x = std::min(min.x, x);
        min.y = std::min(min.y, y);
        min.z = std::min(min.z, z);

        max.x = std::max(max.x, x);
        max.y = std::max(max.y, y);
        max.z = std::max(max.z, z);
    }

    points = {
        Vector3{min.x, min.y, min.z},
        Vector3{max.x, min.y, min.z},
        Vector3{min.x, max.y, min.z},
        Vector3{max.x, max.y, min.z},
        Vector3{min.x, min.y, max.z},
        Vector3{max.x, min.y, max.z},
        Vector3{min.x, max.y, max.z},
        Vector3{max.x, max.y, max.z},
    };

    // Vertexes are counterclockwise
    faces = {
        std::array{points[0], points[1], points[5], points[4]},
        std::array{points[0], points[2], points[6], points[4]},
        std::array{points[2], points[5], points[7], points[6]},
        std::array{points[1], points[3], points[7], points[5]},
        std::array{points[0], points[1], points[7], points[2]},
        std::array{points[4], points[5], points[7], points[6]},
    };
}

bool AABB::intersects(Vector3<> rayStart, Vector3<> directionVector) const
{
    for (auto [p1, p2, p3, p4] : faces)
    {
        const Vector3 normal = cross(p2 - p1, p4 - p1);
        if (dot(directionVector, normal) == 0)
        {
            // The line is perpendicular to the normal, so it is parallel to the plane and will never intersect
            continue;
        }
        // Plane: r.n = d
        // Line: r = a + xb
        // (a1 + xb1)n1 + (a2 + xb2)n2 + (a3 + xb3)n3 = d
        // a1n1 + xb1n1 + a2n2 + xb2n2 + a3n3 + xb3n3 = d
        // a1n1 + a2n2 + a3n3 + x(b1n1 + b2n2 + b3n3) = d
        // x = (d - a1n1 - a2n2 - a3n3) / (b1n1 + b2n2 + b3n3)
        // x = (d - (a1n1 + a2n2 + a3n3)) / (b1n1 + b2n2 + b3n3)
        const double d = dot(p1, normal);
        const double parameter = (d - dot(rayStart, normal)) / dot(directionVector, normal);
        const Vector3<> intersectionPoint = rayStart + parameter * directionVector;
        if (intersectionPoint >= min && intersectionPoint <= max)
        {
            return true;
        }
    }
    return false;
}
