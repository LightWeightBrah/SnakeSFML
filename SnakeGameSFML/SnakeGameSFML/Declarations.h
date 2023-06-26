	#pragma once

const int mapWidth = 30;
const int mapHeight = 20;
const int pixelSize = 16;
const float sizeMultiplier = 2.0f;
const int size = pixelSize * sizeMultiplier;

const float snakeMoveTimer = 2.15f;
const int snakeInitSize = 4;
int snakeSpawnY = mapHeight / 2;
int snakeSpawnX = 5;

int score = 0;

enum Direction
{
	UpDirection = 0,
	DownDirection,
	LeftDirection,
	RightDirection
};

Direction lastHeadDirection = RightDirection;
int GetRandom(int lowerBound, int higherBound);

struct Apple
{
	sf::Vector2i position;

	Apple()
	{
		GenerateRandomPosition();
	}

	void GenerateRandomPosition()
	{
		position.x = GetRandom(0, mapWidth - 1);
		position.y = GetRandom(0, mapHeight - 1);
	}
};

struct Snake
{
	int x;
	int y;
	Direction currentDirection;

	Snake(Direction direction)
	{
		currentDirection = direction;
	}

	sf::Sprite sprite;
};

void GameOver();
bool LooseCheck(std::vector<Snake>& snake, int headX, int headY);
void Scored(std::vector<Snake>& snake, Apple& apple);
bool IsWall(int& x, int& y);
void Place(sf::Sprite& sprite, sf::RenderWindow& window, float x, float y);
void DrawSnake(std::vector<Snake>& snake, sf::RenderWindow& window, sf::Sprite& snakeHeadSprite, sf::Sprite& snakeTailSprite,
    sf::Sprite& snakeBodySprite);
void MoveSnake(sf::Clock& snakeMoveClock, std::vector<Snake>& snake, Apple& apple);
void DrawMap(sf::RenderWindow& window, sf::Sprite& floor1Sprite, sf::Sprite& floor2Sprite, sf::Sprite& wallsprite);
void HandleSnakeInput(std::vector<Snake>& snake);
void GenerateApple(Apple& apple, std::vector<Snake>& snake);
void InitSnake(std::vector<Snake>& snake);
bool IsOnSnake(int& x, int& y, std::vector<Snake>& snake);
