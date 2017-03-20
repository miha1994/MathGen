#pragma once
#include "main_header.h"

struct line_edit {
	v2i m_pos;
	int m_len;
	int m_one_letter_len;
	sf::Text m_line;
	sf::RectangleShape m_rs;
	sf::RectangleShape m_cursor;
	int m_cursor_pos;
	float m_time;
	bool m_active;

	void init(v2i pos, int len);
	void update(float dt);
	void render(sf::RenderWindow *wind);

	void set_new_string(string line);
	void upd_cursor_pos(int new_pos);
	void insert(char c);
};