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

int char2num (char c) {
	if (isdigit (c)) {
		return c - '0';
	}
	c = tolower(c);
	if (c >= 'a' && c <= 'f') {
		return (c - 'a') + 10;
	}
	return -1;
}

CLR str2clr(string rgb0x) {
	return CLR(char2num(rgb0x[0]) * 16 + char2num(rgb0x[1]), char2num(rgb0x[2]) * 16 + char2num(rgb0x[3]), char2num(rgb0x[4]) * 16 + char2num(rgb0x[5]));
}

CLR operator * (CLR col, float fl) {
	col.r *= fl;
	col.g *= fl;
	col.b *= fl;
	return col;
}
CLR operator + (CLR c1, CLR c2) {
	c1.r += c2.r;
	c1.g += c2.g;
	c1.b += c2.b;
	return c1;
}

CLR clr_sum(CLR c1, CLR c2) {
	c1.r += c2.r;
	c1.g += c2.g;
	c1.b += c2.b;
	return c1;
}

inline int getch(FILE *f) {
	int n;
	fscanf_s(f, "%d", &n);
	return n;
}

inline void putch(FILE *f, int ch) {
	fprintf_s(f, "%d\n", ch);
}

string get_str(FILE *f) {
	string rv;
	int c;
	while ((c = getch(f)) != 289);
	while ((c = getch(f)) != 289) {
		rv += c;
	}
	return rv;
}

wstring get_wstr(FILE *f) {
	wstring rv;
	int c;
	while ((c = getch(f)) != 291);
	while ((c = getch(f)) != 291) {
		rv += c;
	}
	return rv;
}

void put_str(FILE *f, string &str) {
	putch(f, 289);
	for (auto c : str) {
		putch(f, c);
	}
	putch(f, 289);
}

void put_wstr(FILE *f, wstring &str) {
	putch(f, 291);
	for (auto c : str) {
		putch(f, c);
	}
	putch(f, 291);
}

bool isspace(string str) {
	for (auto c : str) {
		if (!isspace(c)) {
			return false;
		}
	}
	return true;
}