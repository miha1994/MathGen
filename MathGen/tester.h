#pragma once

#include "main_header.h"
#include "object.h"
#include "expression.h"
#include "Template.h"

struct tester : Object {
	vec <int> m_problem_numbers;
	vec <Template> m_problem_templates;
	sf::Font m_font;
	sf::Text m_problem_text;

	void render(sf::RenderWindow *);
	void update(float dt);
	void clean();
	void load();
};

extern tester g_tester;