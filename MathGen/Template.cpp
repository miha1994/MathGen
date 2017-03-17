#include "Template.h"
#include "expression.h"

#include <iostream>

bool Template::load(FILE *f) {
	m_problem_text.clear();
	m_ints.clear();
	m_answer.clear();

	wchar_t c;
	while ((c = getwc(f)) != '%');
	if ((c = getwc(f)) != '1') {
		return false;
	}
	while ((c = getwc(f)) != '\n');
	while ((c = getwc(f)) != '%') {
		if (c >= 192 && c <= 223) {
			c = L'�' + (c - 192);
		}
		if (c >= 224 && c <= 255) {
			c = L'�' + (c - 224);
		}
		m_problem_text += c;
	}
	if ((c = getc(f)) != '2') {
		return false;
	}
	while ((c = getc(f)) != '\n');
	
	string s;
	Int int_;
	while (1) {
		while (isspace(c = getc(f)));
		if (c == '%') {
			break;
		}
		s = c;
		while (!isspace(c = getc(f))) {
			s += c;
		}
		if (s == "int") {
			while (isspace(c = getc(f)));
			int_.letter = c;
			Int::segment segm;
			while (1) {
				while (isspace(c = getc(f))) {
					if (c == '\n') {
						break;
					}
				}
				if (c == '\n') {
					break;
				}
				ungetc(c, f);
				fscanf_s(f, "%d%d", &segm.a, &segm.b);
				int_.segments.push_back(segm);
			}
			m_ints.push_back(int_);
		}
	}
	if ((c = getc(f)) != '3') {
		return false;
	}
	while ((c = getc(f)) != '\n');
	char cc;
	while ((cc = getc(f)) != '%' && cc != EOF) {
		if (cc >= 192 && cc <= 223) {
			cc = L'�' + (cc - 192);
		}
		if (cc >= 224 && cc <= 255) {
			cc = L'�' + (cc - 224);
		}
		m_answer += cc;
	}
	if (cc == '%') {
		ungetc(cc, f);
	}
	
	return true;
}

Template Template::get_instance() {
	Template rv;
	rv.m_ints = m_ints;
	map <string, string> letters;
	forstl(p, end, rv.m_ints) {
		auto segm = p->segments[rand_n(p->segments.size())];
		p->value = segm.a + rand_n (segm.b - segm.a + 1);
		string l;
		l += p->letter;
		letters.insert(pair<string, string>(l, Tstr(p->value)));
	}
	forstl(c, end, m_problem_text) {
		if (*c == '[' || *c == '{') {
			char br = *c;
			++c;
			string e;
			while (*c != ']' && *c != '}') {
				e += *c;
				++c;
			}
			expression expr;
			expr = str2expr(e);
			expr.insert_values(letters);
			if (br == '{') {
				expr.calculate();
			}

			e = expr.ToString();
			rv.m_problem_text += wstring (e.begin (), e.end());
		}
		else {
			rv.m_problem_text += *c;
		}
	}
	forstl(c, end, m_answer) {
		if (*c == '[' || *c == '{') {
			char br = *c;
			++c;
			string e;
			while (*c != ']' && *c != '}') {
				e += *c;
				++c;
			}
			expression expr;
			expr = str2expr(e);
			expr.insert_values(letters);
			if (br == '{') {
				expr.calculate();
			}

			e = expr.ToString();
			rv.m_answer += e;
		}
		else {
			rv.m_answer += *c;
		}
	}
	rv.m_ans_expr = str2expr(rv.m_answer);
	return rv;
}