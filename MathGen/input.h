#pragma once

#include "main_header.h"
#include <cctype>

// множество кнопок мыши
enum mouse {
	MOUSE_LEFT,
	MOUSE_RIGHT,
	MOUSE_MIDDLE
};

// состояние кнопки
class button_state {
public:
	bool pressed_now = false;  // нажата ли сейчас кнопка?
	bool just_released = false;// была ли кнопка только что отпущена?
	bool just_pressed = false; // была ли кнопка только что нажата?
	bool signal = false;
	float time = 0.0f;
	void _upd(bool _pressed_now, float dt);		// обновляет состояние по заданному новому значению pressed_now поля
};

// структура, обеспечивающая обработку пользовательского ввода
struct input {
	struct _mouse_info {
		friend struct input;
		v2i pos;
		button_state mbutton[3];
		button_state &left;
		button_state &right;
		button_state &middle;
		_mouse_info() : left(mbutton[MOUSE_LEFT]), right(mbutton[MOUSE_RIGHT]), middle(mbutton[MOUSE_MIDDLE]) {
			FOR(i, 3) {
				mbutton[i].pressed_now = false;
				mbutton[i].just_pressed = false;
				mbutton[i].just_released = false;
			}
		}
	} mouse; // хранит текущее состояние датчиков мыши
	struct _kb_info {
		friend struct input;
		button_state ctrl;
		button_state alt;
		button_state shift;
		button_state escape;
		button_state space;
		button_state delete_;
		button_state enter;
		button_state back_space;
		button_state divide;
		button_state subtrack;
		button_state equal;
		button_state add;
		button_state multiply;
		button_state home;
		button_state end;
		button_state dirs[4];
		button_state &left;
		button_state &right;
		button_state &up;
		button_state &down;
	private:
		button_state _abc[26];
		button_state _digits[10];
	public:
		button_state &operator [] (char letter) { return isdigit(letter) ? _digits[letter - '0'] : (_abc[letter - (isupper(letter) ? 'A' : 'a')]); }
		_kb_info() : left(dirs[D_LEFT]), right(dirs[D_RIGHT]), up(dirs[D_UP]), down(dirs[D_DOWN]) {
			FOR(i, 26) {
				_abc[i].just_pressed = false;
				_abc[i].just_released = false;
				_abc[i].pressed_now = false;
			}
		}
	} kb; // --//-- клавиатура
	void upd(sf::RenderWindow *wind, float dt); // обновить состояния датчиков
};

extern input in;