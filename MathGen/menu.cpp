#include "menu.h"
#include "Core.h"
#include "tester.h"

menu g_menu;

int char2int(char c) {
	if (isdigit(c)) {
		return c - '0';
	}
	switch (c) {
	case 'q': return 1; break;
	case 'w': return 2; break;
	case 'e': return 3; break;
	case 'r': return 4; break;
	case 't': return 5; break;
	case 'y': return 6; break;
	case 'u': return 7; break;
	case 'i': return 8; break;
	case 'o': return 9; break;
	case 'p': return 0; break;
	}
}

void menu::update(float dt) {
	m_test_from_file.update(dt);
	if (m_test_from_file.m_state.just_pressed) {
		core.m_current_state = core.STATE_TESTER;
		FILE *f;
		fopen_s(&f, "p_list.txt", "r");
		int n;
		list <int> numbers;
		char c;
		while (1) {
			n = 0;
			while ((c = getc(f)) != 's' && c != ' ' && c != EOF) {
				n = 10 * n + char2int (c);
			}
			numbers.push_back(n);
			if (c == EOF) {
				break;
			}
		}
		g_tester.init(numbers);
	}
}

void menu::render(sf::RenderWindow *wind) {
	wind->draw(m_bg);
	wind->draw(m_mg);
	m_test_from_file.render(wind);
}

void menu::clean() {
	//PUT YOUR CODE HERE
}

void menu::load() {
	m_bg.setFillColor(str2clr("210672"));
	m_bg.setPosition(v2f(0, 0));
	m_bg.setSize(v2f(800, 600));

	m_mg.setCharacterSize(100);
	m_mg.setFont(core.m_font_cg);
	m_mg.setString("MathGen");
	m_mg.setPosition(v2f(400 - m_mg.getGlobalBounds().width / 2, 30));
	m_mg.setFillColor(str2clr("ECFC00"));

	m_test_from_file.init(sf::FloatRect(200, 200, 400, 70), L"Пройти тест из файла", str2clr("ffa500"), str2clr("210672"), str2clr("6c48d7"), str2clr("ecfc00"));
	m_test_from_file.m_text.setPosition(m_test_from_file.m_text.getPosition() + v2f(0, -7));
}