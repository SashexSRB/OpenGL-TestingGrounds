#include "vector.h"

#include <math.h>

float vec3Length(vec3_t v) {
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

vec3_t vec3Normalize(vec3_t v) {
    float l = vec3Length(v);

    return (vec3_t){v.x / l, v.y / l, v.z / l};
}