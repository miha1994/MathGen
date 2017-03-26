#pragma once
#include "main_header.h"
#include "expression.h"

struct Template {
	int m_id;
	wstring m_problem_text;
	struct Int {
		string letter;
		struct segment {
			int a;
			int b;
			segment(int _a = 0, int _b = 0) {
				a = _a;
				b = _b;
			}
		};
		vector <segment> segments;
		string expr;
		int value;
	};
	struct Float {
		string letter;
		struct segment {
			int n_of_digits_after_point;
			int a;
			int b;
			segment(int a_ = 0, int b_ = 0, int n_of_digits_after_point_ = 0) {
				a = a_;
				b = b_;
				n_of_digits_after_point = n_of_digits_after_point_;
			}
		};
		vec <segment> segments;
		string expr;
		string value;
		string numerator;
		string denominator;
		bool no_zero;
	};
	list <Int> m_ints;
	list <Float> m_floats;
	string m_answer;
	expression m_ans_expr;
	string m_test_mode;
	
	int load(FILE *in);
	Template get_instance();
};