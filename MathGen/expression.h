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
	void insert_values(map <string, string> values);
	void calculate();
};

expression str2expr(string expr);