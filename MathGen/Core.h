#pragma once

#include "sfml.h"
#include <map>
#include "object.h"

using namespace std;

class Core {
public:
	enum state {
		STATE_TESTER
	};
	sf::RenderWindow m_window;
	sf::Clock m_clock;
	bool m_running;
	bool m_paused;
	
	state m_current_state;
	map <state, Object *> m_spaces;

	Core() : m_running(false) {}

	bool init(bool fullscreen);

	void update();
	void render();

	void del();
};

extern Core core;