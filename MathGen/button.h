#pragma once
#include "main_header.h"
#include "input.h"

struct button {
	button_state m_state;
	sf::RectangleShape m_rect;
	sf::Text m_text;
	CLR m_not_active_rect_color;
	CLR m_not_active_text_color;
	CLR m_active_rect_color;
	CLR m_active_text_color;
	float m_time;
	bool m_active;

	void init(sf::Rect<float> rect, wstring text, CLR not_active_rect_color, CLR not_active_text_color, CLR active_rect_color, CLR active_text_color);
	void render(sf::RenderWindow *);
	void update(float dt);
};