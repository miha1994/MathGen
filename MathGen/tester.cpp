#include "tester.h"
#include "input.h"
#include "Core.h"
#include "conclusion.h"
#include <iostream>
#include <fstream>

tester g_tester;

string str_to_spacestr(string str, int len) {
	while (str.length() < len) {
		str = " " + str;
	}
	return str;
}

int mark(float pr) {
	if (pr > 0.949) {
		return 5;
	}
	if (pr > 0.749) {
		return 4;
	}
	if (pr > 0.499) {
		return 3;
	}
	return 2;
}

void tester::update(float dt) {
	if (!m_submited) {
		m_user_answer.update(dt);
		m_submit_button.update(dt);
		m_skip.update(dt);
		m_go_to_results.update(dt);
		if (m_go_to_results.m_state.just_pressed) {
			problem_result_info pri;
			pri.the_task = to_wstring(m_problems[m_current_problem].m_id) + L") " + m_problems[m_current_problem].m_problem_text;
			pri.correct_answer = m_problems[m_current_problem].m_answer;
			pri.users_answer = "<no answer>";
			pri.users_answer_is_correct = false;
			m_info.push_back(pri);

			m_user_answer.set_new_string("");
			while (1) {
				if (++m_current_problem == m_problems.size()) {
					core.m_current_state = core.STATE_CONCLUSION;

					int num_of_correct_a = 0;
					int num_of_wrong_a = 0;
					int num_of_skips = 0;
					forstl(p, end, m_info) {
						if (p->users_answer_is_correct) {
							++num_of_correct_a;
						}
						else if (isspace(p->users_answer) || p->users_answer == "<no answer>") {
							++num_of_skips;
						}
						else {
							++num_of_wrong_a;
						}
					}
					string s;
					s += str_to_spacestr(Tstr(num_of_correct_a), 4) + str_to_spacestr(" (" + Tstr(num_of_correct_a * 100 / m_info.size()) + "%)", 7) + "\n";
					s += str_to_spacestr(Tstr(num_of_wrong_a), 4) + str_to_spacestr(" (" + Tstr(num_of_wrong_a * 100 / m_info.size()) + "%)", 7) + "\n";
					s += str_to_spacestr(Tstr(num_of_skips), 4) + str_to_spacestr(" (" + Tstr(num_of_skips * 100 / m_info.size()) + "%)", 7);
					g_conclusion.m_stat_numbers.setString(s);
					g_conclusion.m_resolve.m_active = num_of_wrong_a || num_of_skips;
					g_conclusion.m_resolve.m_time = 0;
					g_conclusion.m_go_to_menu.m_time = 0;
					if (m_info.size() > 3) {
						g_conclusion.m_mark.setCharacterSize(40);
						g_conclusion.m_mark.setString(L"Ваша оценка - \" " + to_wstring (mark (float(num_of_correct_a) / float (m_info.size()))) + L" \"");
						g_conclusion.m_mark.setPosition(v2f(400 - g_conclusion.m_mark.getGlobalBounds().width / 2, 130));
					}
					else {
						g_conclusion.m_mark.setCharacterSize(25);
						g_conclusion.m_mark.setString(L"Слишком мало заданий для выставления оценки");
						g_conclusion.m_mark.setPosition(v2f(400 - g_conclusion.m_mark.getGlobalBounds().width / 2, 130));
					}

					m_info_archive.push_back(m_info);
					m_info.clear();
					if (m_info_archive.size() > 100) {
						m_info_archive.pop_front();
					}
					break;
				}
				else {
					pri.the_task = to_wstring(m_problems[m_current_problem].m_id) + L") " + m_problems[m_current_problem].m_problem_text;
					pri.correct_answer = m_problems[m_current_problem].m_answer;
					m_info.push_back(pri);
				}
			}
			FILE *f;
			fopen_s(&f, "log.txt", "w");
			fprintf_s(f, "%d\n", m_info_archive.size());
			string tmp;

			forstl(inf, en, m_info_archive) {
				fprintf_s(f, "%d\n", inf->size());
				forstl(p, end, *inf) {
					put_wstr(f, p->the_task);
					put_str(f, p->correct_answer);
					put_str(f, p->users_answer);
					tmp = p->users_answer_is_correct ? "correct" : "incorrect";
					put_str(f, tmp);
				}
			}
			fclose(f);
		}
		if ((m_submit_button.m_state.just_pressed || in.kb.enter.just_pressed) && !isspace(m_user_answer.m_line.getString()) || m_skip.m_state.just_pressed) {
			if (!m_skip.m_state.just_pressed) {
				m_submited = true;

				SWITCH (m_problems[m_current_problem].m_test_mode)
				CASE ("calc_python") {
					m_correct = correct_expr(m_user_answer.m_line.getString()) && str2expr(m_user_answer.m_line.getString()) == m_problems[m_current_problem].m_ans_expr;
				}
				CASE ("calc_frac") {
					m_correct = frac_expr_are_equal(str2expr(m_user_answer.m_line.getString()), m_problems[m_current_problem].m_ans_expr);
				}
				if (m_correct) {
					m_result.setString(L"ВЕРНО");
					m_rbg.setFillColor(str2clr("92ec00"));
				}
				else {
					m_result.setString(L"НЕВЕРНО");
					m_rbg.setFillColor(str2clr("ff3100"));
				}
				m_time = 0;

				problem_result_info pri;
				pri.the_task = to_wstring(m_problems[m_current_problem].m_id) + L") " + m_problems[m_current_problem].m_problem_text;
				pri.correct_answer = m_problems[m_current_problem].m_answer;
				pri.users_answer = m_user_answer.m_line.getString();
				pri.users_answer_is_correct = m_correct;
				m_info.push_back(pri);
			}
			else {
				problem_result_info pri;
				pri.the_task = to_wstring(m_problems[m_current_problem].m_id) + L") " + m_problems[m_current_problem].m_problem_text;
				pri.correct_answer = m_problems[m_current_problem].m_answer;
				pri.users_answer = "<no answer>";
				pri.users_answer_is_correct = false;
				m_info.push_back(pri);

				m_user_answer.set_new_string("");
				if (++m_current_problem == m_problems.size()) {
					core.m_current_state = core.STATE_CONCLUSION;

					int num_of_correct_a = 0;
					int num_of_wrong_a = 0;
					int num_of_skips = 0;
					forstl(p, end, m_info) {
						if (p->users_answer_is_correct) {
							++num_of_correct_a;
						}
						else if (isspace(p->users_answer) || p->users_answer == "<no answer>") {
							++num_of_skips;
						}
						else {
							++num_of_wrong_a;
						}
					}
					string s;
					s += str_to_spacestr(Tstr(num_of_correct_a), 4) + str_to_spacestr(" (" + Tstr(num_of_correct_a * 100 / m_info.size()) + "%)", 7) + "\n";
					s += str_to_spacestr(Tstr(num_of_wrong_a), 4) + str_to_spacestr(" (" + Tstr(num_of_wrong_a * 100 / m_info.size()) + "%)", 7) + "\n";
					s += str_to_spacestr(Tstr(num_of_skips), 4) + str_to_spacestr(" (" + Tstr(num_of_skips * 100 / m_info.size()) + "%)", 7);
					g_conclusion.m_stat_numbers.setString(s);
					g_conclusion.m_resolve.m_active = num_of_wrong_a || num_of_skips;
					g_conclusion.m_resolve.m_time = 0;
					g_conclusion.m_go_to_menu.m_time = 0;
					if (m_info.size() > 3) {
						g_conclusion.m_mark.setCharacterSize(40);
						g_conclusion.m_mark.setString(L"Ваша оценка - \" " + to_wstring(mark(float(num_of_correct_a) / float(m_info.size()))) + L" \"");
						g_conclusion.m_mark.setPosition(v2f(400 - g_conclusion.m_mark.getGlobalBounds().width / 2, 130));
					}
					else {
						g_conclusion.m_mark.setCharacterSize(25);
						g_conclusion.m_mark.setString(L"Слишком мало заданий для выставления оценки");
						g_conclusion.m_mark.setPosition(v2f(400 - g_conclusion.m_mark.getGlobalBounds().width / 2, 130));
					}

					m_info_archive.push_back(m_info);
					m_info.clear();
					if (m_info_archive.size() > 100) {
						m_info_archive.pop_front();
					}
				}
				else {
					m_problem_text.setString(m_problems[m_current_problem].m_problem_text);
					m_submited = 0;
					m_time1 = -1;
					m_time = -1;
				}
			}

			FILE *f;
			fopen_s(&f, "log.txt", "w");
			fprintf_s(f, "%d\n", m_info.size() ? m_info_archive.size() + 1 : m_info_archive.size());
			string tmp;

			forstl(inf, en, m_info_archive) {
				fprintf_s(f, "%d\n", inf->size());
				forstl(p, end, *inf) {
					put_wstr(f, p->the_task);
					put_str(f, p->correct_answer);
					put_str(f, p->users_answer);
					tmp = p->users_answer_is_correct ? "correct" : "incorrect";
					put_str(f, tmp);
				}
			}

			if (m_info.size()) {
				fprintf_s(f, "%d\n", m_info.size());
				forstl(p, end, m_info) {
					put_wstr(f, p->the_task);
					put_str(f, p->correct_answer);
					put_str(f, p->users_answer);
					tmp = p->users_answer_is_correct ? "correct" : "incorrect";
					put_str(f, tmp);
				}
			}

			fclose(f);
		}
		m_time1 -= dt;
		float y = (1 - sin(m_time1*1.3)) * 600;
		m_rbg.setPosition(0, y);
		m_result.setPosition((800 - m_result.getLocalBounds().width) / 2, 200 + y);
	}
	if (m_submited) {
		m_time += dt;
		m_continue.update(dt);
		float y = 0;
		if (m_time * 1.3 <= D_PI / 2) {
			y = (1 - sin(m_time*1.3)) * 600;
		}
		m_rbg.setPosition(0, y);
		m_result.setPosition((800 - m_result.getLocalBounds().width) / 2, 200 + y);
		if (m_time > 1 && (m_continue.m_state.just_pressed || in.kb.enter.just_pressed)) {
			m_user_answer.set_new_string("");
			if (++m_current_problem == m_problems.size()) {
				core.m_current_state = core.STATE_CONCLUSION;

				int num_of_correct_a = 0;
				int num_of_wrong_a = 0;
				int num_of_skips = 0;
				forstl(p, end, m_info) {
					if (p->users_answer_is_correct) {
						++num_of_correct_a;
					}
					else if (isspace(p->users_answer) || p->users_answer == "<no answer>") {
						++num_of_skips;
					}
					else {
						++num_of_wrong_a;
					}
				}
				string s;
				s += str_to_spacestr(Tstr(num_of_correct_a), 4) + str_to_spacestr(" (" + Tstr(num_of_correct_a * 100 / m_info.size()) + "%)", 7) + "\n";
				s += str_to_spacestr(Tstr(num_of_wrong_a), 4) + str_to_spacestr(" (" + Tstr(num_of_wrong_a * 100 / m_info.size()) + "%)", 7) + "\n";
				s += str_to_spacestr(Tstr(num_of_skips), 4) + str_to_spacestr(" (" + Tstr(num_of_skips * 100 / m_info.size()) + "%)", 7);
				g_conclusion.m_stat_numbers.setString(s);
				g_conclusion.m_resolve.m_active = num_of_wrong_a || num_of_skips;
				g_conclusion.m_resolve.m_time = 0;
				g_conclusion.m_go_to_menu.m_time = 0;
				if (m_info.size() > 3) {
					g_conclusion.m_mark.setCharacterSize(40);
					g_conclusion.m_mark.setString(L"Ваша оценка - \" " + to_wstring(mark(float(num_of_correct_a) / float(m_info.size()))) + L" \"");
					g_conclusion.m_mark.setPosition(v2f(400 - g_conclusion.m_mark.getGlobalBounds().width / 2, 130));
				}
				else {
					g_conclusion.m_mark.setCharacterSize(25);
					g_conclusion.m_mark.setString(L"Слишком мало заданий для выставления оценки");
					g_conclusion.m_mark.setPosition(v2f(400 - g_conclusion.m_mark.getGlobalBounds().width / 2, 130));
				}

				m_info_archive.push_back(m_info);
				m_info.clear();
				if (m_info_archive.size() > 100) {
					m_info_archive.pop_front();
				}
			}
			else {
				m_problem_text.setString(m_problems[m_current_problem].m_problem_text);
				m_submited = 0;
				m_time1 = D_PI / 2.6;
				m_time = -1;
			}
		}
	}
}

void tester::render(sf::RenderWindow *wind) {
	wind->draw(m_bg);
	wind->draw(m_problem_text);
	m_user_answer.render(wind);
	m_submit_button.render(wind);
	m_skip.render(wind);
	m_go_to_results.render(wind);
	if (m_submited || m_time1 > 0) {
		wind->draw(m_rbg);
		wind->draw(m_result);
		if (m_time > 1) {
			m_continue.render(wind);
		}
	}
}

void tester::clean() {
	//PUT YOUR CODE HERE
}

void tester::load() {
	FILE *f;
	fopen_s(&f, "assets/txt/templates.txt", "r");
	Template tmp;
	int num;
	while (num = tmp.load(f)) {
		m_templates[num] = tmp;
	}
	fclose(f);

	m_bg.setFillColor(str2clr("210672"));
	m_bg.setPosition(v2f(0, 0));
	m_bg.setSize(v2f(800, 600));
	m_rbg.setSize(v2f(800, 600));

	m_problem_text.setPosition(10, 10);
	m_problem_text.setCharacterSize(24);
	m_problem_text.setFont(core.m_font_cg);
	m_problem_text.setStyle(sf::Text::Bold);
	m_problem_text.setFillColor(str2clr("ff4f00"));

	m_result.setFont(core.m_font_cg);
	m_result.setCharacterSize(120);
	m_result.setFillColor(str2clr("210672"));

	m_user_answer.init(v2i(10, 520), 630);

	m_submit_button.init(sf::FloatRect(650, 516, 144, 38), L"Ответить", str2clr("ff4а00"), str2clr("8ef13c"), str2clr("47a300"), str2clr("ecfc00"));
	m_submit_button.m_text.setPosition(m_submit_button.m_text.getPosition() + v2f(0, -7));
	m_continue.init(sf::FloatRect(300, 450, 200, 38), L"Продолжить", str2clr("ff4а00"), str2clr("8ef13c"), str2clr("47a300"), str2clr("ecfc00"));
	m_continue.m_text.setPosition(m_continue.m_text.getPosition() + v2f(0, -7));
	m_skip.init(sf::FloatRect(6, 560, 370, 35), L"Пропустить задание", str2clr("ff4а00"), str2clr("8ef13c"), str2clr("47a300"), str2clr("ecfc00"));
	m_skip.m_text.setPosition(m_skip.m_text.getPosition() + v2f(0, -7));
	m_go_to_results.init(sf::FloatRect(382, 560, 412, 35), L"Пропустить все задания", str2clr("ff4а00"), str2clr("8ef13c"), str2clr("47a300"), str2clr("ecfc00"));
	m_go_to_results.m_text.setPosition(m_go_to_results.m_text.getPosition() + v2f(0, -7));

	FILE *in;
	fopen_s(&in, "log.txt", "r");
	int n, m;
	fscanf_s(in, "%d", &n);
	string s;
	wstring ws;
	list <problem_result_info> lst;
	problem_result_info pri;
	while (n--) {
		fscanf_s(in, "%d", &m);
		lst.clear();
		for (int i = 0; i < m; ++i) {
			pri.the_task = get_wstr(in);
			pri.correct_answer = get_str(in);
			pri.users_answer = get_str(in);
			pri.users_answer_is_correct = get_str(in) == "correct";
			lst.push_back(pri);
		}
		m_info_archive.push_back(lst);
	}
	if (m_info_archive.size() > 100) {
		m_info_archive.pop_front();
	}
	fclose(in);
}

void tester::init(list <int> &numbers) {
	m_problems.clear();
	for (auto n : numbers) {
		m_problems.push_back(m_templates[n].get_instance());
	}
	m_submited = false;
	m_user_answer.set_new_string("");
	m_info.clear();
	m_time1 = -1;
	m_time = -1;

	m_current_problem = 0;
	m_problem_text.setString(m_problems[m_current_problem].m_problem_text);
}