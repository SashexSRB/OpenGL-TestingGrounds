#pragma once

#include "vector.h"

void rendererInit(int width, int height);
void rendererClear();

void rendererDrawPoint(vec2_t point, float size, vec4_t color);
void rendererDrawQuad(vec2_t center, vec2_t size, float angle, vec4_t color);
void rendererDrawLine(vec2_t p0, vec2_t p1, float width, vec4_t color);