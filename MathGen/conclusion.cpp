#include "conclusion.h"
#include "core.h"
#include "tester.h"

conclusion g_conclusion;

void conclusion::update(float dt) {
	m_go_to_menu.update(dt);
	if (m_go_to_menu.m_state.just_pressed) {
		core.m_current_state = core.STATE_MENU;
	}
	m_resolve.update(dt);
	if (m_resolve.m_state.just_pressed) {
		list <int> numbers;
		auto p1 = g_tester.m_info_archive.back().begin();
		forstl(p, end, g_tester.m_problems) {
			if (!p1->users_answer_is_correct) {
				numbers.push_back(p->m_id);
			}
			++p1;
		}
		if (numbers.empty()) {
			core.m_current_state = core.STATE_MENU;
		}
		else {
			g_tester.init(numbers);

			core.m_current_state = core.STATE_TESTER;
		}
	}
}

void conclusion::render(sf::RenderWindow *wind) {
	wind->draw(m_bg);
	wind->draw(m_results);
	wind->draw(m_mark);
	wind->draw(m_stat_text);
	wind->draw(m_stat_numbers);
	m_go_to_menu.render(wind);
	m_resolve.render(wind);
}

void conclusion::clean() {
	//PUT YOUR CODE HERE
}

void conclusion::load() {
	m_bg.setFillColor(str2clr("210672"));
	m_bg.setPosition(v2f(0, 0));
	m_bg.setSize(v2f(800, 600));

	m_results.setCharacterSize(100);
	m_results.setFont(core.m_font_cg);
	m_results.setString(L"Результаты");
	m_results.setPosition(v2f(400 - m_results.getGlobalBounds().width / 2, 10));
	m_results.setFillColor(str2clr("ECFC00"));

	m_mark.setFont(core.m_font_cg);
	m_mark.setFillColor(str2clr ("ff6c00"));

	m_stat_text.setCharacterSize(32);
	m_stat_text.setFont(core.m_font_cg);
	m_stat_text.setString(L"Выполненных верно заданий:\nВыполненных неверно заданий:\nПропущено заданий:");
	m_stat_text.setPosition(v2f(40, 195));
	m_stat_text.setFillColor(str2clr("ff6c00"));

	m_stat_numbers.setCharacterSize(32);
	m_stat_numbers.setFont(core.m_font_consolas);
	m_stat_numbers.setPosition(v2f(590, 195));
	m_stat_numbers.setFillColor(str2clr("ff6c00"));

	m_go_to_menu.init(sf::FloatRect(100, 350, 600, 70), L"Вернуться в меню", str2clr("acf53d"), str2clr("210672"), str2clr("ff3900"), str2clr("ecfc00"));
	m_go_to_menu.m_text.setPosition(m_go_to_menu.m_text.getPosition() + v2f(0, -7));
	m_resolve.init(sf::FloatRect(100, 450, 600, 70), L"Прорешать незасчитанные номера", str2clr("acf53d"), str2clr("210672"), str2clr("ff3900"), str2clr("ecfc00"));
	m_resolve.m_text.setPosition(m_resolve.m_text.getPosition() + v2f(0, -7));
}