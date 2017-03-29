#pragma once

#include "main_header.h"
#include "object.h"
#include "expression.h"
#include "Template.h"
#include "line_edit.h"
#include "button.h"

struct problem_result_info {
	wstring the_task;
	string correct_answer;
	string users_answer;
	bool users_answer_is_correct;
};

struct tester : Object {
	map <int, Template> m_templates;
	vec <Template> m_problems;
	list <list <problem_result_info>> m_info_archive;
	list <problem_result_info> m_info;
	sf::Texture m_pr_texture;
	sf::Sprite m_problem_text;
	sf::RectangleShape m_rbg;
	sf::Text m_result;
	line_edit m_user_answer;
	button m_submit_button;
	button m_continue;
	button m_skip;
	button m_go_to_results;
	bool m_submited;
	bool m_correct;
	float m_time;
	float m_time1;
	int m_current_problem;

	void render(sf::RenderWindow *);
	void update(float dt);
	void clean();
	void load();

	void init(list <int> &numbers);
	void init_sprite(wstring problem_text);
};

extern tester g_tester;