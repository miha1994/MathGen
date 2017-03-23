#pragma once

#include "main_header.h"
#include "object.h"
#include "button.h"

struct conclusion : Object {
	sf::RectangleShape m_bg;
	sf::Text m_results;
	sf::Text m_stat_text;
	sf::Text m_stat_numbers;
	button m_go_to_menu;
	button m_resolve;

	void render(sf::RenderWindow *);
	void update(float dt);
	void clean();
	void load();
};

extern conclusion g_conclusion;