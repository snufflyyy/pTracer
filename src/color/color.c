#include "color.h"

inline Color color_scale(Color color, f32 scalar) {
	return (Color) { color.red * scalar, color.green * scalar, color.blue * scalar };
}

inline Color color_add(Color a, Color b) {
	return (Color) { a.red + b.red, a.green + b.green, a.blue + b.blue };
}
