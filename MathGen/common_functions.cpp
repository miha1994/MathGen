#include "main_header.h"

int zero_for_err_break = 0;

v2i std_directions[] = {
	v2i(0,-1),
	v2i(1,0),
	v2i(0,1),
	v2i(-1,0)
};

int vec_to_dir(v2i v) {
	if (v.x) {
		return v.x > 0 ? 1 : 3;
	}
	else {
		return v.y > 0 ? 2 : 0;
	}
}

int rand_n(int n) {
	return rand() % n;
}

float length(v2f v) {
	return sqrt(v.x * v.x + v.y * v.y);
}