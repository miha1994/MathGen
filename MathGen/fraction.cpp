#include "fraction.h"
#include "main_header.h"

ll gcd (ll a, ll b) {
	a = abs (a), b = abs (b);
	ll c;
	while (a != 0) {
		c = a;
		a = b % a;
		b = c;
	}
	return b;
}

Fraction pow (Fraction p, Fraction q) {
	Fraction rv (1);
	if (q.b == 1) {
		if (q.a < 0) {
			q.a = -q.a;
			p = Fraction(1i64) / p;
		}
		For (q.a) {
			rv *= p;
		}
	}
	return rv;
}