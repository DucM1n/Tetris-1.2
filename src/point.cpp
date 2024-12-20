#include "point.h"
Point::Point() {
	if (gameOver == true) {
		int highscore =  hey.high_score;
		highscores.push_back(highscore);
	}
	
}
void Point::Drawscore() {
	DrawText("Hello", 410, 100, 30, WHITE);
	DrawText(TextFormat("Score: %d", high_score), 410, 200, 30, WHITE);
	int y = 300;
	for (int i = 0; i < highscores.size(); i++) {
		DrawText(TextFormat("High Score: %d", high_score), 410, y, 30, GREEN);
		y += 40;
	}
}