#pragma once

#include <math.h>
#include "renderer.h"

#define WIDTH 1200
#define HEIGHT 675

typedef struct { float x, y, z, w; } vec4d_t;
typedef struct { float x, y; } vec2d_t;

// 16 vertices of a tesseract (all ±1 combos)
static vec4d_t verts[16] = {
    {-1,-1,-1,-1},{1,-1,-1,-1},{-1,1,-1,-1},{1,1,-1,-1},
    {-1,-1,1,-1}, {1,-1,1,-1}, {-1,1,1,-1}, {1,1,1,-1},
    {-1,-1,-1,1}, {1,-1,-1,1}, {-1,1,-1,1}, {1,1,-1,1},
    {-1,-1,1,1},  {1,-1,1,1},  {-1,1,1,1},  {1,1,1,1},
};

// Edges: two vertices differ in exactly one bit
static int edges[32][2];
int edge_count = 0;

static inline void buildEdges() {
    for (int i = 0; i < 16; i++)
        for (int j = i+1; j < 16; j++) {
            // vertices connected if they differ in exactly 1 coordinate
            int diff = 0;
            if (verts[i].x != verts[j].x) diff++;
            if (verts[i].y != verts[j].y) diff++;
            if (verts[i].z != verts[j].z) diff++;
            if (verts[i].w != verts[j].w) diff++;
            if (diff == 1) edges[edge_count][0] = i, edges[edge_count++][1] = j;
        }
}

static inline vec4d_t rotateXW(vec4d_t v, float a) {
    return (vec4d_t){
        v.x * cosf(a) - v.w * sinf(a),
        v.y,
        v.z,
        v.x * sinf(a) + v.w * cosf(a)
    };
}

static inline vec4d_t rotateZW(vec4d_t v, float a) {
    return (vec4d_t){
        v.x,
        v.y,
        v.z * cosf(a) - v.w * sinf(a),
        v.z * sinf(a) + v.w * cosf(a)
    };
}

static inline vec2d_t project(vec4d_t v) {
    float w_dist = 2.5f;   // 4D perspective distance
    float z_dist = 3.5f;   // 3D perspective distance
    float w4 = 1.f / (w_dist - v.w);
    // 4D -> 3D
    float x3 = v.x * w4;
    float y3 = v.y * w4;
    float z3 = v.z * w4;
    // 3D -> 2D
    float z3p = 1.f / (z_dist - z3);
    return (vec2d_t){
        WIDTH/2  + x3 * z3p * 200.f,
        HEIGHT/2 + y3 * z3p * 200.f
    };
}

// another fun function for testing kek
static inline void drawTesseract(float angle) {
    static int built = 0;
    if (!built) {
        buildEdges();
        built = 1;
    }

    float angle2 = angle * 0.7f; // slightly different speed

    for (int i = 0; i < edge_count; i++) {
        vec4d_t a = verts[edges[i][0]];
        vec4d_t b = verts[edges[i][1]];

        a = rotateXW(a, angle);
        a = rotateZW(a, angle2);
        b = rotateXW(b, angle);
        b = rotateZW(b, angle2);

        vec2d_t pa = project(a);
        vec2d_t pb = project(b);

        rendererDrawLine(
            (vec2_t){pa.x, pa.y},
            (vec2_t){pb.x, pb.y},
            1.5f,
            (vec4_t){0.2f, 0.8f, 1.f, 1.f}
        );
    }
}

