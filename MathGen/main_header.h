#pragma once

#include "sfml.h"
#include <string>
#include <list>
#include <map>
#include <vector>

using namespace std;

#define FOR(I_,N_)				for (int I_=0; I_<N_; ++I_)
#define For(N_)					FOR (tmp_variable_for_loop__,N_)
#define FOR_2D(v_, M_X, M_Y)	for (v2i v_ = v2i(0,0); v_.x < M_X; ++v_.x) \
	for (v_.y = 0; v_.y < M_Y; ++v_.y)
#define FOR_2D_EXTRA(v_, ARRAY_)  auto last_array_of_arrays_in_for_2d = &(ARRAY_); for (v2i v_ = v2i(ARRAY_.min_x,ARRAY_.min_y); v_.x < ARRAY_.min_x + ARRAY_.w; ++v_.x) \
	for (v_.y = ARRAY_.min_y; v_.y < ARRAY_.min_y + ARRAY_.h; ++v_.y)
#define AR_(coords)				(last_array_of_arrays_in_for_2d->operator[] (coords))
#define POINT_IN_RECT(p, x0, y0, x1, y1)	(p.x >= x0 && p.y >= y0 && p.x < x1 && p.y < y1)

#define TRN_ON(mask, flag)	(mask) |= (flag)
#define TRN_OFF(mask,flag)	(mask) &= (~(flag))

#define SWITCH(Var)				auto cpy_for_switch = Var; if (false) {}
#define CASE(Value)				else if (cpy_for_switch == Value)
#define CASE2(Value, Value2)	else if (cpy_for_switch == Value || cpy_for_switch == Value2)
#define DEFAULT					else if (1)

extern int zero_for_err_break;
#define ERR_BREAK	zero_for_err_break = (1 / zero_for_err_break)

#define forvector(p_,end_,type_,vector_)		for (std::vector<type_>::iterator (p_) = (vector_).begin(), (end_) = (vector_).end(); (p_) != (end_); ++(p_))
#define formap(p_,end_,type1_,type2_,map_)		for (std::map<type1_,type2_>::iterator (p_) = (map_).begin(), (end_) = (map_).end(); (p_) != (end_); ++(p_))
#define forset(p_,end_,type_,set_)				for (std::set<type_>::iterator (p_) = (set_).begin(), (end_) = (set_).end(); (p_) != (end_); ++(p_))
#define forlist(p_,end_,type_,list_)			for (std::list<type_>::iterator (p_) = (list_).begin(), (end_) = (list_).end(); (p_) != (end_); ++(p_))
#define forlist_no_inc(p_,end_,type_,list_)		for (std::list<type_>::iterator (p_) = (list_).begin(), (end_) = (list_).end(); (p_) != (end_); )
#define forstl(p_,end_,container_)              for (auto (p_) = (container_).begin (), (end_) = (container_).end (); (p_) != (end_); ++(p_))
#define forstl_no_inc(p_,end_,container_)       for (auto (p_) = (container_).begin (), (end_) = (container_).end (); (p_) != (end_); )
#define forstl_p(p_,container_)					for (auto p_ : container_)

#define D_CONTAINES(stl, obj)		((stl).find (obj) != (stl).end ())

typedef unsigned int uint;
#define vec		std::vector
#define vec_erase(vector_,I_)	vector_.erase (vector_.begin () + I_)
#define v2i		sf::Vector2i
#define v2f		sf::Vector2f
#define v2u		sf::Vector2u
#define CLR		sf::Color
#define kb_		sf::Keyboard

#define sleep10			{sf::sleep (sf::milliseconds(10));}

extern v2i std_directions[];
int vec_to_dir(v2i v);
float length(v2f v);
#define D_UP	0
#define D_RIGHT 1
#define D_DOWN	2
#define D_LEFT	3

#define D_PI	(3.1415926535)

inline v2i operator ! (v2f vf) { return v2i(vf); }
inline v2f operator ! (v2i vi) { return v2f(vi); }

#define rand1	(rand() / float(RAND_MAX))

///////////////////////
/// Random number in segment [0 .. n-1]
///////////////////////
int rand_n(int n);

#define _n_		<< ' ' <<
#define Tstr(something)		std::to_string (something)