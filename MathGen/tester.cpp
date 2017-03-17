#include "tester.h"
#include "input.h"
#include "Core.h"
#include <iostream>
#include <fstream>

tester g_tester;

void tester::update(float dt) {
	if (in.kb['C'].just_pressed) {
		ifstream in;
		in.open("assets/txt/templates.txt");
		string str;
		getline(in, str);
		str2expr(str);
	}
}

void tester::render(sf::RenderWindow *wind) {
	wind->draw(m_problem_text);
}

void tester::clean() {
	//PUT YOUR CODE HERE
}

void tester::load() {
	if (!m_font.loadFromFile("assets/fonts/cg.ttf")) {
		ERR_BREAK;
	}

	FILE *f;
	fopen_s(&f, "assets/txt/templates.txt", "r");
	Template tmp;
	if (!tmp.load(f)) {
		ERR_BREAK;
	}
	m_problem_templates.push_back(tmp);

	tmp = tmp.get_instance();

	m_problem_text.setFont(m_font);
	m_problem_text.setFillColor(CLR::Black);
	m_problem_text.setString(tmp.m_problem_text + wstring(L" ") + wstring (tmp.m_answer.begin (), tmp.m_answer.end()));
}
