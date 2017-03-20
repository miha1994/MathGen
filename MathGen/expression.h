#pragma once
#include <string>
#include <list>
#include <map>

using namespace std;

struct expression {
	string m_type;
	string m_value;
	
	list <expression> m_arguments;

	string ToString();
	void insert_values(map <string, string> &values);
	void calculate();
	bool operator == (expression &expr);
	void _make_elements_map(map <string, int> &map_);
};

expression str2expr(string expr);
bool correct_expr(string str);