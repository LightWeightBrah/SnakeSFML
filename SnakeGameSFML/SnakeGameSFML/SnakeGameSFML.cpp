#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "Declarations.h"
#include "GraphicsLogic.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(mapWidth * size, mapHeight * size), "Snake Game with SFML");
	srand(time(0));
	LoadTextures();

	Apple apple;
	std::vector<Snake> snake;
	InitSnake(snake);
	GenerateApple(apple, snake);

	sf::Clock snakeMoveClock;
	while (window.isOpen())
	{
		sf::Event mainEvent;
		while (window.pollEvent(mainEvent))
		{
			if (mainEvent.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		window.clear();

		HandleInput(snake, apple);
		DrawMap(window, floor1Sprite, floor2Sprite, wallsprite);
		Place(appleSprite, window, apple.position.x, apple.position.y);
		MoveSnake(snakeMoveClock, snake, apple);
		DrawSnake(snake, window, snakeHeadSprite, snakeTailSprite, snakeBodySprite);

		window.display();
	}
}

void InitSnake(std::vector<Snake>& snake)
{
	for (int i = 0; i < snakeInitSize; i++)
	{
		Snake singleSnake(RightDirection);
		singleSnake.x = snakeSpawnX - i;
		singleSnake.y = snakeSpawnY;
		snake.push_back(singleSnake);
	}
}

void HandleInput(std::vector<Snake>& snake, Apple& apple)
{
	if (hasLost)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
			PlayAgain(snake, apple);

		return;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && snake[1].currentDirection != DownDirection)
		snake[0].currentDirection = UpDirection;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && snake[1].currentDirection != UpDirection)
		snake[0].currentDirection = DownDirection;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && snake[1].currentDirection != RightDirection)
		snake[0].currentDirection = LeftDirection;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && snake[1].currentDirection != LeftDirection)
		snake[0].currentDirection = RightDirection;
}

void PlayAgain(std::vector<Snake>& snake, Apple& apple)
{
	hasLost = false;
	score = 0;
	scoreText.setString("Score: " + std::to_string(score));
	snake.clear();
	InitSnake(snake);
	GenerateApple(apple, snake);
}

void MoveSnake(sf::Clock& snakeMoveClock, std::vector<Snake>& snake, Apple& apple)
{
	if (hasLost)
		return;

	sf::Time elapsedSnakeMove = snakeMoveClock.getElapsedTime();
	if (elapsedSnakeMove.asSeconds() > snakeMoveTimer)
	{
		snakeMoveClock.restart();

		switch (snake[0].currentDirection)
		{
		case UpDirection:
			if (LooseCheck(snake, snake[0].x, snake[0].y - 1))
				return ;
			break;
		case DownDirection:
			if (LooseCheck(snake, snake[0].x, snake[0].y + 1))
				return ;
			break;
		case RightDirection:
			if (LooseCheck(snake, snake[0].x + 1, snake[0].y))
				return ;
			break;
		case LeftDirection:
			if (LooseCheck(snake, snake[0].x - 1, snake[0].y))
				return ;
			break;
		}

		for (int i = snake.size() - 1; i > 0; i--)
		{
			snake[i].x = snake[i - 1].x;
			snake[i].y = snake[i - 1].y;
			snake[i].currentDirection = snake[i - 1].currentDirection;
		}
		lastHeadDirection = snake[0].currentDirection;

		switch (snake[0].currentDirection)
		{
		case UpDirection:
			snake[0].y--;
			break;
		case DownDirection:
			snake[0].y++;
			break;
		case RightDirection:
			snake[0].x++;
			break;
		case LeftDirection:
			snake[0].x--;
			break;
		}

		if (snake[0].x == (apple.position.x + 1) && snake[0].y == apple.position.y)
			Scored(snake, apple);
	}
}

bool LooseCheck(std::vector<Snake>& snake, int headX, int headY)
{
	int x = headX - 1;
	if (IsWall(x, headY))
	{
		GameOver();
		return true;
	}

	for (int i = 1; i < snake.size(); i++)
	{
		if (headX == snake[i].x && headY == snake[i].y)
		{
			GameOver();
			return true;
		}
	}

	return false;
}

void GameOver()
{
	hasLost = true;
}

void Scored(std::vector<Snake>& snake, Apple& apple)
{
	score++;
	GenerateApple(apple, snake);
	scoreText.setString("Score: " + std::to_string(score));

	Direction lastDirection = snake[snake.size() - 1].currentDirection;
	Snake newSnake(lastDirection);
	snake.push_back(newSnake);
}

void GenerateApple(Apple& apple, std::vector<Snake>& snake)
{
	int previousX = apple.position.x;
	int previousY = apple.position.y;

	while (IsWall(apple.position.x, apple.position.y) || IsOnSnake(apple.position.x, apple.position.y, snake)
		|| (apple.position.x == previousX && apple.position.y == previousY))
	{
		apple.GenerateRandomPosition();
	}
}

bool IsOnSnake(int& x, int& y, std::vector<Snake>& snake)
{
	for (int i = 0; i < snake.size(); i++)
	{
		if (x + 1 == snake[i].x && y == snake[i].y)
			return true;
	}

	return false;
}

bool IsWall(int& x, int& y)
{
	return (y == 0 || x == 0 || (y == mapHeight - 1) || (x == mapWidth - 1));
}

int GetRandom(int lowerBound, int higherBound)
{
	return lowerBound == 0 ? rand() % higherBound + 1 : rand() % higherBound + lowerBound;
}