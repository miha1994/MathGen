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
	if (!m_submited) {
		m_user_answer.update(dt);
		m_submit_button.update(dt);
		if (m_submit_button.m_state.just_pressed || in.kb.enter.just_pressed) {
			m_submited = true;
			m_correct = correct_expr (m_user_answer.m_line.getString ()) && str2expr (m_user_answer.m_line.getString()) == m_problems[m_current_problem].m_ans_expr;
			if (m_correct) {
				m_result.setString(L"ВЕРНО");
				m_rbg.setFillColor(str2clr ("92ec00"));
			}
			else {
				m_result.setString(L"НЕВЕРНО");
				m_rbg.setFillColor(str2clr("ff3100"));
			}
			m_time = 0;
		}
	}
	if (m_submited) {
		m_time += dt;
		m_continue.update(dt);
		float y = 0;
		if (m_time * 1.3 <= D_PI/2) {
			y = (1 - sin(m_time*1.3)) * 600;
		}
		m_rbg.setPosition(0, y);
		m_result.setPosition((800 - m_result.getLocalBounds ().width)/2, 200 + y);
		if (m_time > 1 && m_continue.m_state.just_pressed) {
			m_user_answer.set_new_string("");
			if (++m_current_problem == m_problems.size()) {
				core.m_current_state = core.STATE_MENU;
			}
			else {
				m_problem_text.setString(m_problems[m_current_problem].m_problem_text);
				m_submited = 0;
			}
		}
	}
}

void tester::render(sf::RenderWindow *wind) {
	wind->draw(m_bg);
	wind->draw(m_problem_text);
	m_user_answer.render(wind);
	m_submit_button.render(wind);
	if (m_submited) {
		wind->draw(m_rbg);
		wind->draw(m_result);
		if (m_time > 1) {
			m_continue.render(wind);
		}
	}
}

void tester::clean() {
	//PUT YOUR CODE HERE
}

void tester::load() {
	FILE *f;
	fopen_s(&f, "assets/txt/templates.txt", "r");
	Template tmp;
	int num;
	while (num = tmp.load(f)) {
		m_templates[num] = tmp;
	}
	fclose(f);

	m_bg.setFillColor(str2clr("210672"));
	m_bg.setPosition(v2f(0, 0));
	m_bg.setSize(v2f(800, 600));
	m_rbg.setSize(v2f(800, 600));

	m_problem_text.setFont(core.m_font_cg);
	m_problem_text.setStyle(sf::Text::Bold);
	m_problem_text.setFillColor(str2clr("ff4f00"));

	m_result.setFont(core.m_font_cg);
	m_result.setCharacterSize(120);
	m_result.setFillColor(str2clr("210672"));

	m_user_answer.init(v2i(10, 560), 630);

	m_submit_button.init(sf::FloatRect(650, 556, 144, 38), L"Ответить", str2clr("ff4а00"), str2clr("8ef13c"), str2clr("47a300"), str2clr("ecfc00"));
	m_submit_button.m_text.setPosition(m_submit_button.m_text.getPosition() + v2f(0, -7));
	m_continue.init(sf::FloatRect(300, 450, 200, 38), L"Продолжить", str2clr("ff4а00"), str2clr("8ef13c"), str2clr("47a300"), str2clr("ecfc00"));
	m_continue.m_text.setPosition(m_continue.m_text.getPosition() + v2f(0, -7));
}

void tester::init(list <int> &numbers) {
	m_problems.clear();
	for (auto n : numbers) {
		m_problems.push_back(m_templates[n].get_instance());
	}
	m_submited = false;
	m_user_answer.set_new_string("");
	
	m_current_problem = 0;
	m_problem_text.setString(m_problems[m_current_problem].m_problem_text);
}