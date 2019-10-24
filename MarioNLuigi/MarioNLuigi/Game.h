/// <summary>
/// author Pete Lowe May 2019
/// you need to change the above line or lose marks
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>

enum class Direction
{
	None,
	Up,
	Down,
	Left,
	Right
};


class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void processKeyReleases(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupFontAndText();
	void setupSprite();
	void changeCharacter();
	void getDirection();
	void centerText();
	void move();

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_mariofont; // font used by message
	sf::Text m_characterName; // text used for message on screen
	sf::Texture m_brosTexture; // texture used for sfml logo
	sf::Sprite m_logoSprite; // sprite used for sfml logo
	bool m_exitGame; // control exiting game
	sf::Vector2f m_location{ 400.0f,300.0f };
	sf::Vector2f m_spriteOffset{ 32.0f,74.0f };
	bool m_ImMario{ true };
	bool canChange{ true };
	Direction m_heading{ Direction::None };
	float m_speed{ 1.6f };

};

#endif // !GAME_HPP

