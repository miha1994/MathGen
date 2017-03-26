#include "line_edit.h"
#include "input.h"
#include "Core.h"

void line_edit::init(v2i pos, int len) {
	m_pos = pos;
	m_len = len;
	m_rs.setFillColor(str2clr ("8ef13c"));
	m_rs.setOutlineColor(str2clr("ff4f00"));
	m_rs.setOutlineThickness(4);
	m_rs.setPosition(!pos);
	m_rs.setSize(v2f(len, 30));

	m_cursor.setFillColor(str2clr("ff4f00"));
	m_cursor.setPosition(!pos + v2f(len - 7, 3));
	m_cursor.setSize(v2f(4,24));

	m_line.setFont(core.m_font_consolas);
	m_line.setCharacterSize(24);
	m_line.setFillColor(str2clr("3b14af"));
	m_line.setStyle(sf::Text::Bold);
	m_line.setString('0');
	m_one_letter_len = m_line.getLocalBounds().width + 2;
	m_line.setString("");
	m_cursor_pos = 0;
}

void line_edit::update(float dt) {
	m_time += dt;
	if (m_time > 1.0) {
		m_time -= 1.0;
	}
	if (!in.kb.shift.pressed_now) {
		FOR(i, 10) {
			if (in.kb['0' + i].signal) {
				insert('0' + i);
			}
		}
	}
	for (char c = 'a'; c <= 'z'; ++c) {
		if (in.kb[c].signal) {
			insert(c);
		}
	}
	if (in.kb.back_space.signal) {
		string s = m_line.getString();
		if (s.size() && -m_cursor_pos < s.size ()) {
			s.erase(int(s.size()) + m_cursor_pos - 1, 1);
			set_new_string(s);
		}
	}
	if (in.kb.delete_.signal) {
		string s = m_line.getString();
		if (s.size() && m_cursor_pos) {
			s.erase(int(s.size()) + m_cursor_pos, 1);
			m_cursor_pos++;
			set_new_string(s);
		}
	}
	if (in.kb.subtrack.signal && !in.kb.shift.pressed_now) {
		insert('-');
	}
	if (in.kb.equal.signal && in.kb.shift.pressed_now || in.kb.add.signal) {
		insert('+');
	}
	if (in.kb.divide.signal && !in.kb.shift.pressed_now) {
		insert('/');
	}
	if (in.kb['8'].signal && in.kb.shift.pressed_now || in.kb.multiply.signal) {
		insert('*');
	}
	if (in.kb['6'].signal && in.kb.shift.pressed_now) {
		insert('^');
	}
	if (in.kb['9'].signal && in.kb.shift.pressed_now) {
		insert('(');
	}
	if (in.kb['0'].signal && in.kb.shift.pressed_now) {
		insert(')');
	}
	if (in.kb.space.signal) {
		insert(' ');
	}
	if (in.kb.comma.signal) {
		if (in.kb.shift.pressed_now) {
			insert('<');
		}
		else {
			insert(',');
		}
	}
	if (in.kb.period.signal) {
		if (in.kb.shift.pressed_now) {
			insert('>');
		}
		else {
			insert('.');
		}
	}
	if (in.kb.left.signal || in.kb.right.signal) {
		upd_cursor_pos(m_cursor_pos + (in.kb.left.signal ? -1 : 1));
	}
	if (in.kb.end.just_pressed) {
		upd_cursor_pos(0);
	}
	if (in.kb.home.just_pressed) {
		upd_cursor_pos(-int(m_line.getString().getSize()));
	}
	if (in.mouse.left.just_pressed && m_rs.getGlobalBounds().contains(!in.mouse.pos)) {
		auto rect = m_rs.getGlobalBounds();
		upd_cursor_pos((in.mouse.pos.x - (rect.left + rect.width)) / m_one_letter_len);
	}
}

void line_edit::render(sf::RenderWindow *wind) {
	wind->draw(m_rs);
	wind->draw(m_line);
	if (m_time < 0.5) {
		wind->draw(m_cursor);
	}
}

void line_edit::insert(char c) {
	if ((int(m_line.getString ().getSize () + 1)) * m_one_letter_len > m_len) {
		return;
	}
	string s = m_line.getString();
	s.insert(s.begin () + int(s.length ()) + m_cursor_pos, c);
	set_new_string(s);
}

void line_edit::set_new_string(string line) {
	if (m_line.getString() != line) {
		m_time = 0;
	}
	m_line.setString(line);
	m_line.setPosition(v2f(m_pos.x + m_len - m_line.getGlobalBounds().width - 8, m_pos.y));
	upd_cursor_pos(m_cursor_pos);
}

void line_edit::upd_cursor_pos(int new_pos) {
	if (m_cursor_pos != new_pos) {
		m_time = 0;
	}
	m_cursor_pos = new_pos;
	if (m_cursor_pos > 0) {
		m_cursor_pos = 0;
	}
	if (m_cursor_pos < -int(m_line.getString().getSize())) {
		m_cursor_pos = -int(m_line.getString().getSize());
	}
	m_cursor.setPosition(!m_pos + v2f(m_len - 7 + m_one_letter_len * m_cursor_pos, 3));
}