#include "vec2.h"

vec2 vec2_add(vec2 a, vec2 b) {
	return (vec2) { a.x + b.x, a.y + b.y };
}
