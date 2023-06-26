#pragma once

sf::Texture playerTexture;
sf::Texture floor1Texture;
sf::Texture floor2Texture;
sf::Texture wallTexture;
sf::Texture appleTexture;
sf::Texture snakeHeadTexture;
sf::Texture snakeBodyTexture;
sf::Texture snakeTailTexture;
sf::Texture snakeRotateTexture;
sf::Texture snakeDeadTexture;

sf::Sprite floor1Sprite;
sf::Sprite floor2Sprite;
sf::Sprite wallsprite;
sf::Sprite appleSprite;
sf::Sprite snakeHeadSprite;
sf::Sprite snakeBodySprite;
sf::Sprite snakeTailSprite;
sf::Sprite snakeRotateSprite;
sf::Sprite snakeDeadSprite;

void LoadTextures()
{
	playerTexture.loadFromFile("Graphics/snakeHead.png");
	floor1Texture.loadFromFile("Graphics/floor1.png");
	floor2Texture.loadFromFile("Graphics/floor2.png");
	wallTexture.loadFromFile("Graphics/wall.png");
	appleTexture.loadFromFile("Graphics/apple.png");
	snakeHeadTexture.loadFromFile("Graphics/snakeHead.png");
	snakeBodyTexture.loadFromFile("Graphics/snakeBody.png");
	snakeTailTexture.loadFromFile("Graphics/snakeTail.png");
	snakeRotateTexture.loadFromFile("Graphics/snakeRotate.png");
	snakeDeadTexture.loadFromFile("Graphics/snakeDead.png");

	floor1Sprite.setTexture(floor1Texture);
	floor2Sprite.setTexture(floor2Texture);
	wallsprite.setTexture(wallTexture);
	appleSprite.setTexture(appleTexture);
	snakeHeadSprite.setTexture(snakeHeadTexture);
	snakeBodySprite.setTexture(snakeBodyTexture);
	snakeTailSprite.setTexture(snakeTailTexture);
	snakeRotateSprite.setTexture(snakeRotateTexture);
	snakeDeadSprite.setTexture(snakeDeadTexture);
}

bool CheckIfRotatedSprite(int& i, std::vector<Snake>& snake, sf::Sprite& snakeSpriteToDraw)
{
	if (i != 0 && i != snake.size() - 1)
	{
		if (snake[i].currentDirection != snake[i + 1].currentDirection)
		{
			snakeSpriteToDraw = snakeRotateSprite;
			return true;
		}
	}

	return false;
}

void SetSnakeRotation(int& i, std::vector<Snake>& snake, sf::Sprite& snakeRotationSprite)
{
	if (i == 0 && i == snake.size() - 1)
		return;

	if(snake[i+1].x < snake[i].x && snake[i-1].y < snake[i].y)
		snakeRotationSprite.setRotation(0.0f);
	else if(snake[i+1].y < snake[i].y && snake[i-1].x < snake[i].x)
		snakeRotationSprite.setRotation(0.0f);
	else if (snake[i + 1].x < snake[i].x && snake[i - 1].y > snake[i].y)
		snakeRotationSprite.setRotation(-90.0f);
	else if(snake[i+1].y > snake[i].y && snake[i-1].x < snake[i].x)
		snakeRotationSprite.setRotation(-90.0f);
	else if(snake[i+1].x > snake[i].x && snake[i-1].y > snake[i].y)
		snakeRotationSprite.setRotation(180.0f);
	else if(snake[i+1].y > snake[i].y && snake[i-1].x > snake[i].x)
		snakeRotationSprite.setRotation(180.0f);
	else if(snake[i+1].x > snake[i].x && snake[i-1].y < snake[i].y)
		snakeRotationSprite.setRotation(90.0f);
	else if(snake[i+1].y < snake[i].y && snake[i-1].x > snake[i].x)
		snakeRotationSprite.setRotation(90.0f);

}

void DrawSnake(std::vector<Snake>& snake, sf::RenderWindow& window, sf::Sprite& snakeHeadSprite, sf::Sprite& snakeTailSprite,
	sf::Sprite& snakeBodySprite)
{
	for (int i = 0; i < snake.size(); i++)
	{
		sf::Sprite snakeSpriteToDraw;
		if (i == 0)
			snakeSpriteToDraw = snakeHeadSprite;
		else if (i + 1 >= snake.size())
			snakeSpriteToDraw = snakeTailSprite;
		else
			snakeSpriteToDraw = snakeBodySprite;

		switch (snake[i].currentDirection)
		{
		case UpDirection:
			snakeSpriteToDraw.setRotation(0.0f);
			break;
		case DownDirection:
			snakeSpriteToDraw.setRotation(180.0f);
			break;
		case RightDirection:
			snakeSpriteToDraw.setRotation(90.0f);
			break;
		case LeftDirection:
			snakeSpriteToDraw.setRotation(-90.0f);
			break;
		}

		if (CheckIfRotatedSprite(i, snake, snakeSpriteToDraw))
			SetSnakeRotation(i, snake, snakeSpriteToDraw);

		snakeSpriteToDraw.setOrigin(sf::Vector2f(
			snakeSpriteToDraw.getLocalBounds().width, snakeSpriteToDraw.getLocalBounds().height) / 2.f);

		Place(snakeSpriteToDraw, window, snake[i].x - 0.5f, snake[i].y + 0.5f);
	}
}



void Place(sf::Sprite& sprite, sf::RenderWindow& window, float x, float y)
{
	sprite.setScale(sizeMultiplier, sizeMultiplier);
	sprite.setPosition(x * size, y * size);
	window.draw(sprite);
}