#pragma once
#include "main_header.h"

struct line_edit {
	v2i m_pos;
	int m_len;
	string m_line;
	sf::RectangleShape m_rs;
	float m_time;

	void init(v2i pos, int len);
};