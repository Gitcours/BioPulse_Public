#pragma once

#include "Outils.h"

class EditorGrid {
public:
	vector<RectangleShape> grid;
	EditorGrid(int width = 60, int height = 60);
	void draw();
};