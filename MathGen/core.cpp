#include "Core.h"
#include "input.h"
#include <iostream>
#include <fstream>
#include "menu.h"
#include "tester.h"

Core core;

bool Core::init(bool fullscreen) {
	if (!m_font_cg.loadFromFile("assets/fonts/cg.ttf") || !m_font_consolas.loadFromFile("assets/fonts/consolas.ttf")) {
		return false;
	}
	m_window.create(sf::VideoMode(800, 600), "MathGen", fullscreen ? sf::Style::Fullscreen : sf::Style::Default & ~sf::Style::Resize);
	m_window.setVerticalSyncEnabled(true);
	m_window.setFramerateLimit(120);

	m_running = true;
	m_paused = false;

	m_current_state = STATE_MENU;
	m_spaces[STATE_MENU] = &g_menu;
	m_spaces[STATE_TESTER] = &g_tester;

	for (auto p : m_spaces) {
		p.second->load();
	}

	return true;
}

void Core::update() {
	rand();
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		switch (event.type) {
		case sf::Event::Closed:
			m_window.close();
			m_running = false;
			break;
		case sf::Event::GainedFocus:
			m_paused = false;
			break;
		case sf::Event::LostFocus:
			m_paused = true;
			break;
		default:
			break;
		}
	}
	if (!m_paused) {
		float dt = (m_clock.restart()).asSeconds();
		dt = min(dt, 0.02f);

		in.upd(&m_window, dt);
		m_spaces[m_current_state]->update(dt);
	}
}

void Core::render() {
	m_window.clear(CLR::White);

	m_spaces[m_current_state]->render(&m_window);

	m_window.display();
}

void Core::del() {
	for (auto p : m_spaces) {
		p.second->clean();
	}
}