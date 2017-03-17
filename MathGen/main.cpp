#include "sfml.h"
#include "Core.h"

int main() {
	if (core.init(0)) {
		while (core.m_running) {
			core.update();
			core.render();
		}
	}
	return 0;
}