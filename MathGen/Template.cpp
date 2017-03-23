#include "Template.h"
#include "expression.h"

#include <iostream>

int Template::load(FILE *f) {
	m_problem_text.clear();
	m_ints.clear();
	m_answer.clear();

	int rv;

	wchar_t c;
	while ((c = getwc(f)) != '%') {
		if (feof(f)) {
			return 0;
		}
	}
	fscanf_s(f, "%d", &rv);
	m_id = rv;
	while ((c = getwc(f)) != '%') {
		if (feof(f)) {
			return 0;
		}
	}
	if ((c = getwc(f)) != '1') {
		return false;
	}
	while ((c = getwc(f)) != '\n');
	while ((c = getwc(f)) != '%') {
		if (c >= 192 && c <= 255) {
			c = L'À' + (c - 192);
		}
		m_problem_text += c;
	}
	while (isspace(m_problem_text.back())) {
		m_problem_text.pop_back();
	}
	if ((c = getc(f)) != '2') {
		return 0;
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
			int_.letter.clear();
			int_.value = 0;
			int_.expr.clear();
			int_.segments.clear();

			while (isspace(c = getc(f)));
			int_.letter = c;
			while (!isspace(c = getc(f))) {
				int_.letter += c;
			}
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
				if (isdigit(c)) {
					ungetc(c, f);
					fscanf_s(f, "%d%d", &segm.a, &segm.b);
					int_.segments.push_back(segm);
				}
				else if (c == '=') {
					while ((c = getc(f)) != '\n') {
						int_.expr += c;
					}
					break;
				}
			}
			m_ints.push_back(int_);
		}
	}
	if ((c = getc(f)) != '3') {
		return 0;
	}
	while ((c = getc(f)) != '\n');
	char cc;
	while ((cc = getc(f)) != '%' && cc != EOF) {
		if (cc >= 192 && cc <= 223) {
			cc = L'À' + (cc - 192);
		}
		if (cc >= 224 && cc <= 255) {
			cc = L'à' + (cc - 224);
		}
		if (!isspace(cc)) {
			m_answer += cc;
		}
	}
	if (cc == '%') {
		ungetc(cc, f);
	}
	
	return rv;
}

Template Template::get_instance() {
	Template rv;
	rv.m_id = m_id;
	rv.m_ints = m_ints;
	map <string, string> letters;
	forstl(p, end, rv.m_ints) {
		if (p->segments.size()) {
			auto segm = p->segments[rand_n(p->segments.size())];
			p->value = segm.a + rand_n(segm.b - segm.a + 1);
			letters.insert(pair<string, string>(p->letter, Tstr(p->value)));
		}
		else {
			expression e = str2expr (p->expr);
			e.insert_values(letters);
			e.calculate();
			letters.insert(pair<string, string>(p->letter, e.ToString ()));
		}
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