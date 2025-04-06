#include <SFML/Graphics.hpp>
#include <iostream>
#include "game.hpp"

int main(int arg, char** agrv[])
{
	Game game;
	while(!game.GetWindow()->IsDone())
	{
		game.Update();
		game.Render();
		game.LastUpdate();
	}
}