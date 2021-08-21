/// <summary>
/// @author Peter Lowe
/// @date May 2019
///
/// you need to change the above lines or lose marks
/// </summary>

#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 
	setupSprite(); // load texture
	setupSound();
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
		if (sf::Event::KeyReleased == newEvent.type)
		{
			processKeyReleases(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
	if (sf::Keyboard::Space == t_event.key.code)
	{
		if (canChange)
		{
			changeCharacter();
			canChange = false;
		}
	}
}

void Game::processKeyReleases(sf::Event t_event)
{
	if (sf::Keyboard::Space == t_event.key.code)
	{
		canChange = true;
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	getDirection();
	move();
	checkBounds();
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_characterName);
	m_window.draw(m_logoSprite);
	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	
	if (!m_mariofont.loadFromFile("ASSETS\\FONTS\\SuperMario256.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_characterName.setFont(m_mariofont);
	m_characterName.setString("Luigi");
	m_characterName.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_characterName.setPosition(40.0f, 40.0f);
	m_characterName.setCharacterSize(80U);
	m_characterName.setOutlineColor(sf::Color::Black);
	m_characterName.setFillColor(sf::Color::Green);
	m_characterName.setOutlineThickness(3.0f);

	centerText();


}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite()
{
	if (!m_brosTexture.loadFromFile("ASSETS\\IMAGES\\mario-luigi-64.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}
	m_logoSprite.setTexture(m_brosTexture);
	m_logoSprite.setTextureRect(sf::IntRect{ 64, 0, 64, 148 });
	m_logoSprite.setPosition(m_location - m_spriteOffset);
}

void Game::setupSound()
{
	if (!m_beepBuffer.loadFromFile("ASSETS\\AUDIO\\mario.wav"))
	{
		std::cout << "problem with sound" << std::endl;
	}
	
	m_beepSound.setBuffer(m_beepBuffer);
	
}

void Game::changeCharacter()
{
	m_ImMario = !m_ImMario;
	if(m_ImMario)
	{
		m_characterName.setString("Mario");
		m_characterName.setFillColor(sf::Color::Red);
		m_logoSprite.setTextureRect(sf::IntRect{ 0,0,64,148 });
		centerText();
	}
	else
	{
		m_characterName.setString("Luigi");
		m_characterName.setFillColor(sf::Color::Green);
		m_logoSprite.setTextureRect(sf::IntRect{ 64,0,64,148 });
		centerText();
	}
}

void Game::getDirection()
{
	m_heading = Direction::None;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_heading = Direction::Up;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_heading = Direction::Down;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_heading = Direction::Left;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_heading = Direction::Right;
	}
}

void Game::centerText()
{
	sf::Vector2f location{ 0.0f,0.0f };
	location.y = 50.0f;
	location.x = 400 - (m_characterName.getGlobalBounds().width / 2);
	m_characterName.setPosition(location);
}

void Game::move()
{
	sf::Vector2f move{ 0.0f,0.0f };
	switch (m_heading)
	{
	case Direction::None:
		break;
	case Direction::Up:
		move.y = -m_speed;
		break;
	case Direction::Down:
		move.y = m_speed;
		break;
	case Direction::Left:
		move.x = -m_speed;
		break;
	case Direction::Right:
		move.x = m_speed;
		break;
	default:
		break;
	}
	m_location += move;
	m_logoSprite.setPosition(m_location - m_spriteOffset);

}

void Game::checkBounds()
{
	bool bump{ false };
	if (m_location.x < 0.0f)
	{
		m_location.x = 0.0f;
		bump = true;
	}
	if (m_location.x > 800.0f)
	{
		m_location.x = 800.0f;
		bump = true;
	}
	if (m_location.y < 0.0f)
	{
		m_location.y = 0.0f;
		bump = true;
	}
	if (m_location.y > 600.0f)
	{
		m_location.y = 600.0f;
		bump = true;
	}
	if (bump)
	{
		if (sf::Sound::Playing != m_beepSound.getStatus())
		{
			m_beepSound.play();
		}
	}
}
