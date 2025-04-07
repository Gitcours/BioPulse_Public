#include "EditorGrid.hpp"

EditorGrid::EditorGrid(int width, int height)
{
	int pixWidth = width * tileRes; int pixHeight = height * tileRes;

	for (int i = 1; i < width; i++) {
		RectangleShape newColumn;
		newColumn.setSize(Vector2f(2, pixHeight));
		newColumn.setPosition(tileRes * i - 1, 0);
		newColumn.setFillColor(Color(150, 150, 150, 180));
		grid.push_back(newColumn);
	}
	for (int i = 1; i < height; i++) {
		RectangleShape newRow;
		newRow.setSize(Vector2f(pixWidth, 2));
		newRow.setPosition(0, tileRes * i - 1);
		newRow.setFillColor(Color(150, 150, 150, 180));
		grid.push_back(newRow);
	}

	RectangleShape leftLimit;
	leftLimit.setSize(Vector2f(2, pixHeight));
	leftLimit.setPosition(0, 0);
	RectangleShape rightLimit;
	rightLimit.setSize(Vector2f(2, pixHeight));
	rightLimit.setPosition(pixWidth, 0);
	RectangleShape topLimit;
	topLimit.setSize(Vector2f(pixWidth, 2));
	topLimit.setPosition(0, 0);
	RectangleShape bottomLimit;
	bottomLimit.setSize(Vector2f(pixWidth, 2));
	bottomLimit.setPosition(0, pixHeight);

	leftLimit.setScale(-1, 1);
	topLimit.setScale(1, -1);

	leftLimit.setFillColor(Color::Red);
	rightLimit.setFillColor(Color::Red);
	topLimit.setFillColor(Color::Red);
	bottomLimit.setFillColor(Color::Red);

	grid.push_back(leftLimit);
	grid.push_back(rightLimit);
	grid.push_back(topLimit);
	grid.push_back(bottomLimit);
}

void EditorGrid::draw()
{
	for (RectangleShape rect : grid) {
		window.draw(rect);
	}
}
