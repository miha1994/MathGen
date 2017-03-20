#pragma once

#include "main_header.h"
#include "object.h"
#include "expression.h"
#include "Template.h"
#include "line_edit.h"
#include "button.h"

struct tester : Object {
	map <int, Template> m_templates;
	vec <Template> m_problems;
	sf::RectangleShape m_bg;
	sf::RectangleShape m_rbg;
	sf::Text m_problem_text;
	sf::Text m_result;
	line_edit m_user_answer;
	button m_submit_button;
	button m_continue;
	bool m_submited;
	bool m_correct;
	float m_time;
	int m_current_problem;

	void render(sf::RenderWindow *);
	void update(float dt);
	void clean();
	void load();

	void init(list <int> &numbers);
};

extern tester g_tester;