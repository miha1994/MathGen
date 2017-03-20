#pragma once

#include "main_header.h"
#include "object.h"
#include "button.h"

struct menu : Object {
	sf::RectangleShape m_bg;
	sf::Text m_mg;
	button m_test_from_file;

	void render(sf::RenderWindow *);
	void update(float dt);
	void clean();
	void load();
};

extern menu g_menu;