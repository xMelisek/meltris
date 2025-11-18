#include "math.h"
namespace math {
	float lerp(float a, float b, float t) {
		return (b-a) * t + a;
	}
}
