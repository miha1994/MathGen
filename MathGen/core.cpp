#include "Core.h"
#include "input.h"
#include <iostream>
#include <fstream>
#include "tester.h"

Core core;

bool Core::init(bool fullscreen) {
	m_window.create(sf::VideoMode(600, 400), "execute me", fullscreen ? sf::Style::Fullscreen : sf::Style::Default);
	m_window.setVerticalSyncEnabled(true);
	m_window.setFramerateLimit(120);

	m_running = true;
	m_paused = false;

	m_current_state = STATE_TESTER;
	m_spaces[STATE_TESTER] = &g_tester;

	for (auto p : m_spaces) {
		p.second->load();
	}

	return true;
}

void Core::update() {
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
		in.upd(&m_window);
		float dt = (m_clock.restart()).asSeconds();
		dt = min(dt, 0.3f);
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