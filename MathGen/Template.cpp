#include "Template.h"
#include "expression.h"

#include <iostream>

int Template::load(FILE *f) {
	m_problem_text.clear();
	m_ints.clear();
	m_floats.clear();
	m_answer.clear();
	m_test_mode.clear();

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
			ERR_BREAK;
		}
	}
	if ((c = getwc(f)) != '1') {
		ERR_BREAK;
	}
	while ((c = getwc(f)) != '\n');
	while (1) {
		while ((c = getwc(f)) != '%') {
			m_problem_text += c;
		}
		bool break_ = true;
		if ((c = getc(f)) != '2') {
			if (c == '%') {
				m_problem_text += c;
				break_ = false;
			}
			else {
				ERR_BREAK;
			}
		}
		if (break_) {
			break;
		}
	}
	while (isspace(m_problem_text.back())) {
		m_problem_text.pop_back();
	}
	while ((c = getc(f)) != '\n');
	
	string s;
	Int int_;
	Float float_;
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
				else {
					ERR_BREAK;
				}
			}
			m_ints.push_back(int_);
		}
		else if (s == "float") {
			float_.letter.clear();
			float_.expr.clear();
			float_.segments.clear();
			float_.no_zero = false;
			float_.numerator.clear();
			float_.denominator.clear();

			while (isspace(c = getc(f)));
			float_.letter = c;
			while (!isspace(c = getc(f))) {
				if (c == '\'') {
					float_.no_zero = true;
					break;
				}
				else {
					float_.letter += c;
				}
			}
			Float::segment segm;
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
					segm.a = 0;
					segm.b = 0;
					segm.n_of_digits_after_point = -1;
					while (isdigit(c = getc(f)) || c == '.') {
						if (isdigit(c)) {
							segm.a = segm.a * 10 + (c - '0');
							if (segm.n_of_digits_after_point >= 0) {
								++segm.n_of_digits_after_point;
							}
						}
						else {
							segm.n_of_digits_after_point = 0;
						}
					}
					while (isspace(c = getc(f)));
					ungetc(c, f);
					int nodap = -1;
					while (isdigit(c = getc(f)) || c == '.') {
						if (isdigit(c)) {
							segm.b = segm.b * 10 + (c - '0');
							if (nodap >= 0) {
								++nodap;
							}
						}
						else {
							nodap = 0;
						}
					}
					if (nodap != segm.n_of_digits_after_point) {
						ERR_BREAK;
					}
					ungetc(c, f);
					float_.segments.push_back(segm);
				}
				else if (c == '=') {
					while ((c = getc(f)) != '\n') {
						float_.expr += c;
					}
					break;
				}
				else if (isalpha(c)) {
					float_.numerator += c;
					while (isalnum(c = getc(f)) || c == '_') {
						float_.numerator += c;
					}
					while (isspace(c = getc(f)));
					float_.denominator += c;
					while (isalnum(c = getc(f)) || c == '_') {
						float_.numerator += c;
					}
				}
				else {
					ERR_BREAK;
				}
			}
			m_floats.push_back(float_);
		}
	}
	if ((c = getc(f)) != '3') {
		ERR_BREAK;
	}
	{
		char c;
		while (isspace(c = getc(f))) {
			if (feof(f)) {
				ERR_BREAK;
			}
		}
		m_test_mode += c;
		while (!isspace(c = getc(f))) {
			m_test_mode += c;
		}
		if (m_test_mode != "calc_frac" && m_test_mode != "calc_python") {
			ERR_BREAK;
		}
	}
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
	rv.m_test_mode = m_test_mode;
	rv.m_ints = m_ints;
	rv.m_floats = m_floats;
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
			letters.insert(pair<string, string>(p->letter, e.calc_frac().ToString ()));
		}
	}
	forstl(p, end, rv.m_floats) {
		if (p->segments.size()) {
			auto segm = p->segments[rand_n(p->segments.size())];
			p->value = Tstr (segm.a + rand_n(segm.b - segm.a + 1));
			while (p->value.size() < segm.n_of_digits_after_point + 1) {
				p->value = "0" + p->value;
			}
			if (p->no_zero && p->value.back() == '0') {
				p->value.back() = '1' + rand_n(9);
			}
			p->value.insert(p->value.begin () + int(p->value.size()) - segm.n_of_digits_after_point, '.');
			bool break_ = false;
			while (!p->value.empty () && (p->value.back() == '0' || p->value.back() == '.')) {
				if (p->value.back() == '.') {
					break_ = true;
				}
				p->value.pop_back();
				if (break_) {
					break;
				}
			}
			if (p->value.empty()) {
				p->value = "0";
			}
			letters.insert(pair<string,string> (p->letter, p->value));
		}
		else {
			expression e = str2expr (p->expr);
			e.insert_values(letters);
			e.calculate();
			letters.insert(pair<string, string> (p->letter, p->value = e.ToString ()));
		}
		if (p->numerator.size()) {
			string num, den;
			for (auto c : p->value) {
				if (isdigit(c)) {
					num += c;
					if (den.size()) {
						den += '0';
					}
				}
				else {
					den = "1";
				}
			}
			Fraction fr(atoll(num.c_str()), atoll(den.c_str()));
			letters.insert(pair<string, string>(p->numerator, Tstr(fr.a)));
			letters.insert(pair<string, string>(p->denominator, Tstr(fr.b)));
		}
	}
	string last_word;
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
				if (last_word == "calc_frac") {
					expr = str2expr(expr.calc_frac().ToString());
					For(9) {
						rv.m_problem_text.pop_back();
						rv.m_problem_text_for_log.pop_back();
					}
				}
				else {
					expr.calculate();
				}
			}
			if (last_word == "latex_im") {
				For(8) {
					rv.m_problem_text.pop_back();
					rv.m_problem_text_for_log.pop_back();
				}
				e = expr.ToLatexString();
				rv.m_problem_text += L"$" + wstring(e.begin(), e.end()) + L"$";
				e = expr.ToString();
				rv.m_problem_text_for_log += wstring(e.begin(), e.end());
			}
			else {
				e = expr.ToString();
				rv.m_problem_text += wstring(e.begin(), e.end());
				rv.m_problem_text_for_log += wstring(e.begin(), e.end());
			}
		}
		else {
			rv.m_problem_text += *c;
			rv.m_problem_text_for_log += *c;
			if (wstring(L"calc_fraclatexim").find(*c) != string::npos) {
				last_word += *c;
			}
			else {
				last_word = "";
			}
		}
	}
	last_word = "";
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
				if (last_word == "calc_frac") {
					expr = str2expr(expr.calc_frac().ToString ());
					For(9) {
						rv.m_answer.pop_back();
					}
				}
				else {
					expr.calculate();
				}
			}

			e = expr.ToString();
			rv.m_answer += e;
		}
		else {
			rv.m_answer += *c;
			if (string ("calc_frac").find (*c) != string::npos) {
				last_word += *c;
			}
			else {
				last_word = "";
			}
		}
	}
	rv.m_ans_expr = str2expr(rv.m_answer);
	return rv;
}