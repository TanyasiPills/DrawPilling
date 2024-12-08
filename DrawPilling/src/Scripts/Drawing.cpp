#include "Drawing.h"
#include <vector>
#include <math.h>

#define PI 3.1415927f

std::vector<float> Drawing::drawCircle(float x, float y, float r, int sides) {
    std::vector<float> vertices;
	const float step = 2 * PI / sides;

    for (int i = 0; i < sides; ++i) {
        float theta = step * i;
        float dX = x + r * cosf(theta);
        float dY = y + r * sinf(theta);
        vertices.push_back(dX);
        vertices.push_back(dY);
    }
    return vertices;
}