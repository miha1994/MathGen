#pragma once
#include "main_header.h"
#include "expression.h"

struct Template {
	wstring m_problem_text;
	struct Int {
		char letter;
		struct segment {
			int a;
			int b;
			segment(int _a = 0, int _b = 0) {
				a = _a;
				b = _b;
			}
		};
		vector <segment> segments;
		int value;
	};
	list <Int> m_ints;
	string m_answer;
	expression m_ans_expr;
	
	bool load(FILE *in);
	Template get_instance();
};