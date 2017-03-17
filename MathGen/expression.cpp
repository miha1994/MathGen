#include "expression.h"
#include "main_header.h"
#include <iostream>
#include <fstream>

struct func_info {
	string name;
	int num_of_args;
	func_info(string _name, int _num_of_args) {
		name = _name;
		num_of_args = _num_of_args;
	}
};

func_info functions[] = {
	func_info("()", 1),
	func_info ("sin", 1),
	func_info("cos", 1),
	func_info("sqrt", 1),
	func_info("min", 2),
	func_info("max", 2)
};

int priority(string Operator) {
	if (Operator == "+" || Operator == "-") {
		return 0;
	}
	else if (Operator == "*" || Operator == "/" || Operator == ":") {
		return 1;
	}
	else if (Operator == "^") {
		return 2;
	}
	else if (Operator == "#") {
		return 3;
	}
	return -1;
}

expression str2expr(string expr) {
	expression nxt;
	expression last;
	last.m_type = "empty";
	vector <expression> lexems;
	vector <expression> stck;

	string val;
	expression rv;
	forstl(c, end, expr) {
		if (isspace(*c)) {
			continue;
		}
		auto pos = string("+-*/:^").find(*c);
		if (isdigit(*c)) {
			val = *c;
			while (1) {
				++c;
				if (c == end) {
					--c;
					break;
				}
				if (isdigit(*c) || *c == '.') {
					val += *c;
				}
				else {
					--c;
					break;
				}
			}
			nxt.m_type = "number";
			nxt.m_value = val;
			lexems.push_back(last = nxt);
		}
		else if (*c == '(') {
			if (stck.empty() || stck.back().m_type != "func" || stck.back().m_value == "()") {
				nxt.m_type = "func";
				nxt.m_value = "()";
				stck.push_back(nxt);
			}
			nxt.m_type = "(";
			nxt.m_value = "";
			stck.push_back(last = nxt);
		}
		else if (*c == ')') {
			if (stck.empty()) {
				return rv;
			}
			while (!(stck.empty ()) && stck.back().m_type != "(") {
				lexems.push_back(stck.back());
				stck.pop_back();
			}
			if (stck.empty()) {
				return rv;
			}
			stck.pop_back();
			last.m_type = ")";
			last.m_value = "";
		}
		else if (pos != string::npos || isalpha (*c)) {
			val = *c;
			if (isalpha(*c)) {
				while (1) {
					++c;
					if (c == end) {
						--c;
						break;
					}
					if (isalnum(*c)) {
						val += *c;
					}
					else {
						--c;
						break;
					}
				}
			}
			bool func = false;
			FOR(i, sizeof(functions) / sizeof(func_info)) {
				if (val == functions[i].name) {
					func = true;
					break;
				}
			}
			if (func) {
				nxt.m_type = "func";
				nxt.m_value = val;
				stck.push_back(last = nxt);
			}
			else if (pos != string::npos) {
				if ((val == "-") && (last.m_type == "empty" || last.m_type == "(" || last.m_type == ",")) {
					nxt.m_type = "operator";
					nxt.m_value = "#";
					stck.push_back(last = nxt);
				}
				else {
					while (1) {
						if (stck.size() && ((stck.back().m_type == "operator" && priority(val) <= priority(stck.back().m_value)) || stck.back().m_type == "func")) {
							lexems.push_back(stck.back());
							stck.pop_back();
						}
						else {
							break;
						}
					}
					nxt.m_type = "operator";
					nxt.m_value = val;
					stck.push_back(last = nxt);
				}
			}
			else {
				nxt.m_type = "var";
				nxt.m_value = val;
				lexems.push_back(last = nxt);
			}
		}
		else if (*c == ',') {
			while (!(stck.empty()) && stck.back().m_type != "(") {
				lexems.push_back(stck.back());
				stck.pop_back();
			}
			last.m_type = ",";
			last.m_value = "";
		}
	}
	while (stck.size()) {
		lexems.push_back(stck.back());
		stck.pop_back();
	}

	stck.clear();
	forstl(p, end, lexems) {
		if (p->m_type == "number" || p->m_type == "var") {
			stck.push_back(*p);
		}
		else if (p->m_type == "operator") {
			nxt = *p;
			nxt.m_arguments.push_front(stck.back ());
			stck.pop_back ();
			if (p->m_value != "#") {
				nxt.m_arguments.push_front(stck.back());
				stck.pop_back();
			}
			stck.push_back(nxt);
			nxt.m_arguments.clear();
		}
		else if (p->m_type == "func") {
			nxt = *p;
			int n;
			FOR(i, sizeof(functions) / sizeof(func_info)) {
				if (nxt.m_value == functions[i].name) {
					n = i;
					break;
				}
			}
			For(functions[n].num_of_args) {
				nxt.m_arguments.push_front(stck.back());
				stck.pop_back();
			}
			stck.push_back(nxt);
			nxt.m_arguments.clear();
		}
	}
	rv = stck.back();
	return rv;
}

string expression::ToString() {
	if (m_type == "number" || m_type == "var") {
		return m_value;
	}
	if (m_type == "operator") {
		if (m_value == "#") {
			return "-" + m_arguments.back().ToString();
		}
		else {
			return m_arguments.front().ToString() + " " + m_value + " " + m_arguments.back().ToString();
		}
	}
	if (m_type == "func") {
		if (m_value == "()") {
			return "(" + m_arguments.back().ToString() + ")";
		}
		else {
			string rv = m_value + " (";
			forstl(p, end, m_arguments) {
				rv += p->ToString();
				auto q = p;
				if ((++q) != end) {
					rv += ", ";
				}
			}
			rv += ")";
			return rv;
		}
	}
	return "";
}

void expression::insert_values(map <string, string> values) {
	if (m_type == "var") {
		if (D_CONTAINES(values, m_value)) {
			m_value = values[m_value];
		}
	}
	forstl(p, end, m_arguments) {
		p->insert_values(values);
	}
}

void expression::calculate() {
	ofstream out;
	out.open("input.txt");
	out << ToString();
	out.close();
	system("assets\\calc\\main.exe");
	ifstream in;
	in.open("output.txt");
	string str;
	getline(in, str);
	in.close();
	*this = str2expr(str);
}