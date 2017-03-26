#pragma once

#include <cstdlib>
#include <string>

using namespace std;

#define ll	long long

ll gcd (ll a, ll b);

class Fraction {
public:
	ll a, b;
	void normalize () {
		ll gcd_ = gcd (a,b);
		if (b < 0) {
			gcd_ *= -1;
		}
		a /= gcd_;
		b /= gcd_;
	}
	Fraction (ll A = 0, ll B = 1) : a(A), b(B) {
		normalize ();
	}
	Fraction operator + (const Fraction &f) const {
		return Fraction (a * f.b + b * f.a, b * f.b);
	}
	Fraction operator - (const Fraction &f) const {
		return Fraction (a * f.b - b * f.a, b * f.b);
	}
	Fraction operator * (const Fraction &f) const {
		return Fraction (a * f.a, b * f.b);
	}
	Fraction operator / (const Fraction &f) const {
		return Fraction (a * f.b, b * f.a);
	}
	Fraction operator += (const Fraction &f) {
		*this = *this + f;
		return *this;
	}
	Fraction operator -= (const Fraction &f) {
		*this = *this - f;
		return *this;
	}
	Fraction operator *= (const Fraction &f) {
		*this = *this * f;
		return *this;
	}
	Fraction operator /= (const Fraction &f) {
		*this = *this / f;
		return *this;
	}
	bool operator == (const Fraction &f) const {
		return a == f.a && b == f.b;
	}
	string ToString () {
		return to_string (a) + (b == 1 ? "" : "/" + to_string(b));
	}
};

Fraction pow (Fraction p, Fraction q);