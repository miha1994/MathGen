#include "button.h"
#include "Core.h"

const float button_max_time = 0.3;

void button::init(sf::Rect<float> rect, wstring text, CLR not_active_rect_color, CLR not_active_text_color, CLR active_rect_color, CLR active_text_color) {
	m_rect.setPosition(v2f (rect.left, rect.top));
	m_rect.setSize(v2f (rect.width, rect.height));
	m_text.setFont(core.m_font_cg);
	m_text.setString(text);
	m_text.setPosition(v2f (rect.left + rect.width/2 - m_text.getGlobalBounds ().width/2, rect.top + rect.height / 2 - m_text.getGlobalBounds().height / 2));
	m_not_active_rect_color = not_active_rect_color;
	m_not_active_text_color = not_active_text_color;
	m_active_rect_color = active_rect_color;
	m_active_text_color = active_text_color;
}

void button::render(sf::RenderWindow *wind) {
	m_rect.setFillColor(clr_sum(m_not_active_rect_color * ((button_max_time - m_time)/button_max_time), m_active_rect_color * (m_time / button_max_time)));
	wind->draw(m_rect);
	m_text.setFillColor(clr_sum(m_not_active_text_color * ((button_max_time - m_time) / button_max_time), m_active_text_color * (m_time / button_max_time)));
	wind->draw(m_text);
}

void button::update(float dt) {
	if (m_rect.getGlobalBounds().contains(!in.mouse.pos)) {
		m_time += dt;
		m_state._upd(in.mouse.left.pressed_now, dt);
	}
	else {
		m_time -= dt;
		m_state._upd(false, dt);
	}

	if (m_time < 0) {
		m_time = 0;
	}
	else if (m_time > button_max_time) {
		m_time = button_max_time;
	}
}