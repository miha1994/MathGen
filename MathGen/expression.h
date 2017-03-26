#pragma once
#include <string>
#include <list>
#include <map>
#include "fraction.h"

using namespace std;

struct expression {
	string m_type;
	string m_value;
	
	list <expression> m_arguments;

	string ToString();
	string ToPythonString();
	void insert_values(map <string, string> &values);
	void calculate();
	bool operator == (expression &expr);
	void _make_elements_map(map <string, int> &map_, bool exact = false);
	Fraction calc_frac();
};

expression str2expr(string expr);
bool correct_expr(string str, bool frac = false);
bool frac_expr_are_equal(expression e1, expression e2);