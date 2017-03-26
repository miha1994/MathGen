#include "input.h"

input in;

sf::Mouse::Button b_ar[3] = { sf::Mouse::Left, sf::Mouse::Right, sf::Mouse::Middle };
#define kb_	sf::Keyboard

void button_state::_upd(bool new_v, float dt) {
	if (new_v != pressed_now) {
		if (new_v) {
			just_pressed = true;
			just_released = false;
		}
		else {
			just_released = true;
			just_pressed = false;
		}
	}
	else {
		just_pressed = false;
		just_released = false;
	}
	pressed_now = new_v;
	signal = false;
	if (pressed_now) {
		if ((time -= dt) < 0) {
			if (just_pressed) {
				time += 0.6;
			}
			else {
				time += 0.035;
			}
			signal = true;
		}
	}
	else {
		time = 0.0;
	}
}

void input::upd(sf::RenderWindow *wind, float dt) {
	mouse.pos = sf::Mouse::getPosition(*wind);
	FOR(i, 3) {
		mouse.mbutton[i]._upd(sf::Mouse::isButtonPressed(b_ar[i]), dt);
	}
	FOR(i, 26) {
		kb._abc[i]._upd(kb_::isKeyPressed(kb_::Key(i)), dt);
	}
	FOR(i, 10) {
		kb._digits[i]._upd(kb_::isKeyPressed(kb_::Key(26 + i)) || kb_::isKeyPressed(kb_::Key(75 + i)), dt);
	}
	kb.ctrl._upd(kb_::isKeyPressed(kb_::LControl) || kb_::isKeyPressed(kb_::RControl), dt);
	kb.alt._upd(kb_::isKeyPressed(kb_::LAlt) || kb_::isKeyPressed(kb_::RAlt), dt);
	kb.shift._upd(kb_::isKeyPressed(kb_::LShift) || kb_::isKeyPressed(kb_::RShift), dt);
	kb.escape._upd(kb_::isKeyPressed(kb_::Escape), dt);
	kb.space._upd(kb_::isKeyPressed(kb_::Space), dt);
	kb.delete_._upd(kb_::isKeyPressed(kb_::Delete), dt);
	kb.enter._upd(kb_::isKeyPressed(kb_::Return), dt);
	kb.back_space._upd(kb_::isKeyPressed(kb_::BackSpace), dt);
	kb.comma._upd(kb_::isKeyPressed(kb_::Comma), dt);
	kb.period._upd(kb_::isKeyPressed(kb_::Period), dt);
	kb.divide._upd(kb_::isKeyPressed(kb_::Divide) || kb_::isKeyPressed(kb_::Slash), dt);
	kb.subtrack._upd(kb_::isKeyPressed(kb_::Subtract) || kb_::isKeyPressed(kb_::Dash), dt);
	kb.equal._upd(kb_::isKeyPressed(kb_::Equal), dt);
	kb.add._upd (kb_::isKeyPressed(kb_::Add), dt);
	kb.multiply._upd(kb_::isKeyPressed(kb_::Multiply), dt);
	kb.home._upd(kb_::isKeyPressed(kb_::Home), dt);
	kb.end._upd(kb_::isKeyPressed(kb_::End), dt);
	kb.dirs[D_RIGHT]._upd(kb_::isKeyPressed(kb_::Right), dt);
	kb.dirs[D_LEFT]._upd(kb_::isKeyPressed(kb_::Left), dt);
	kb.dirs[D_UP]._upd(kb_::isKeyPressed(kb_::Up), dt);
	kb.dirs[D_DOWN]._upd(kb_::isKeyPressed(kb_::Down), dt);
}