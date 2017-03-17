#pragma once

#include "type.h"
#include "main_header.h"

struct Object {
	Type m_type;

	virtual void render(sf::RenderWindow *) = 0;
	virtual void update(float dt) = 0;
	virtual void clean() = 0;
	virtual void load() = 0;

	Object() {}
	virtual ~Object() {}
};