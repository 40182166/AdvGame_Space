#include "GameState.hpp"
#include "MainMenu.hpp"
#include "Play.hpp"
#include "Player.hpp"
#include "PauseMenu.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <SFML/Audio.hpp>
#include <sstream>
#include <Windows.h>
#include "Ammo.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "PowerupLife.h"
#include "PowerupFireRate.h"

using namespace sf;

RenderWindow GameState::window;
GameState::States GameState::currentState = s_uninitialized;
bool GameState::isFullScreen = false;
bool GameState::isJoysticConnected = false;
bool GameState::isplayerDead = false;
bool isPause = false;
bool isMusicActive = true;

int counter = 0;
int counter2 = 0;
int counter3 = 0;
float spawningRateEnemy = 2.0f;
int waveMaxSpawnEnemy = 2;
int waveNumber = 1;
int waveWait = 30;

float spawningRatePowerups = 1.3f;
int waveMaxSpawnPowerups = 3;

sf::Clock shootingClock;
sf::Clock takeDamage;
sf::Clock deadClock;
sf::Clock spawningTimeEnemy;
sf::Clock waveTime;
sf::Clock spawningTimePowerups;
sf::Clock powerupLifeTime;

std::ofstream initialScore;


MainMenu main;
PauseMenu pauseMenu;
Play game; 
Player _player;
Ammo ammo1;
Enemy1 enemy1;
Enemy2 enemy2;
PowerupLife powerLife;
PowerupFireRate powerFire;

vector<Ammo>::const_iterator iterAmmo;
vector<Ammo> ammoVector;

vector<Enemy1>::const_iterator iterEnemy1;
vector<Enemy1> enemy1Vector;

vector<Enemy2>::const_iterator iterEnemy2;
vector<Enemy2> enemy2Vector;

vector<PowerupLife>::const_iterator iterPowerupLife;
vector<PowerupLife> powerupLifeVector;

vector<PowerupFireRate>::const_iterator iterPowerupFire;
vector<PowerupFireRate> powerupFireVector;

Texture playBackgroundImage;
Sprite playBackgroundSquare;
Texture pauseBckImage;
Sprite pauseBckSquare;

Texture loseBackgroundTexture;
Sprite loseBackground;

sf::Text lifeText;
sf::Text scoreText;
sf::Text attackText;
sf::Text fireRateText;
sf::Text waveText;
sf::Font fontStats;

sf::Music mainMusic;
sf::Sound shootSound;
sf::Sound enemyDestroy;
sf::Sound playerHit;
sf::Sound playerDead;
sf::Sound powerupSound;


GameState::GameState()
{
}


GameState::~GameState()
{
}

void GameState::Start()
{
	srand(time(NULL));
	if (currentState != s_uninitialized)
		return;
	window.create(VideoMode::getDesktopMode(), "Cat Invaders", sf::Style::Close);
	window.setFramerateLimit(60);
	currentState = GameState::s_menu;
	
	DrawGameBoard();

	fontStats.loadFromFile("res/img/agencyb.ttf");

	mainMusic.openFromFile("res/audio/background_music.wav");
	mainMusic.play();
	mainMusic.setLoop(true);

	initialScore.open("res/scores.txt", std::ios_base::app | std::ios_base::out);
	initialScore << "0" << "\n";
	initialScore.close();

	sf::SoundBuffer bufferShoot;
	bufferShoot.loadFromFile("res/audio/shoot.wav");
	shootSound.setBuffer(bufferShoot);
	
	sf::SoundBuffer bufferEnemyDestroy;
	bufferEnemyDestroy.loadFromFile("res/audio/enemyDestroy.wav");
	enemyDestroy.setBuffer(bufferEnemyDestroy);

	sf::SoundBuffer bufferPlayerDead;
	bufferPlayerDead.loadFromFile("res/audio/playerDestroy.wav");
	playerDead.setBuffer(bufferPlayerDead);

	sf::SoundBuffer bufferplayerHit;
	bufferplayerHit.loadFromFile("res/audio/playerHit.wav");
	playerHit.setBuffer(bufferplayerHit);

	sf::SoundBuffer bufferpowerup;
	bufferpowerup.loadFromFile("res/audio/powerup.wav");
	powerupSound.setBuffer(bufferpowerup);

	initialize();
}

void GameState::initialize()
{
	_player.CreateShip(window);


	if (sf::Joystick::isConnected(0))
	{
		isJoysticConnected = true;
	}

	while (window.isOpen()) {

		if (isJoysticConnected)
		{
			if (Joystick::isButtonPressed(0, 6)) // Xbox rt
			{
				if (isFullScreen)
				{
					window.create(VideoMode::getDesktopMode(), "Cat Invaders", sf::Style::Close);
					sf::sleep(sf::seconds(0.3));
					isFullScreen = false;
				}
				else
				{
					window.create(VideoMode::getDesktopMode(), "Cat Invaders", sf::Style::Fullscreen);
					sf::sleep(sf::seconds(0.3));
					isFullScreen = true;
				}
			}
		}

		Event event;
		while (window.pollEvent(event)) {

			switch (event.type)
			{
			case Event::KeyReleased:
				switch (event.key.code)
				{
				case Keyboard::B:
					if (isFullScreen)
					{
						window.create(VideoMode::getDesktopMode(), "Cat Invaders", sf::Style::Close);
						sf::sleep(sf::seconds(0.3));
						isFullScreen = false;
					}
					else
					{
						window.create(VideoMode::getDesktopMode(), "Cat Invaders", sf::Style::Fullscreen);
						sf::sleep(sf::seconds(0.3));
						isFullScreen = true;
					}
					break;
				}
				break;

				case Event::Closed:
					isExiting();
					
					break;
			}
		}
		
		window.clear();
		//Update and Render should be here
		running();
		window.display();
	}
}




void GameState::running()
{

	switch (currentState)
	{
		case s_menu:
			menu();
			break;

		case s_play:
			mainMusic.stop();
			play();
			break;

		case s_pause:
			pause();
			break;

		case s_exit:
			window.close();
			break;

		case s_save:
			toBeSaved();
			break;
		case s_score:
			highScore();
			break;

		case s_lose:
			lose();
			break;

		default:
			break;
	}
}


void GameState::menu()
{
	
	main.showMenu(window);
}

void GameState::play()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) || isJoysticConnected == true && Joystick::isButtonPressed(0, 7)) //xbox start
	{
		isPause = true;
		sf::sleep(sf::seconds(0.5));
		currentState = GameState::s_pause;
	}

	window.draw(playBackgroundSquare);

	_player.DrawShip(window);
	DrawGameStats();



	////////////////////////////////////////////			 WAVES CODE	 

	if (spawningTimeEnemy.getElapsedTime().asSeconds() > spawningRateEnemy)
	{
		spawningTimeEnemy.restart();


		int whichEnemy = ((rand() % 2) + 1);

		switch (whichEnemy)
		{
		case 1:
			if (enemy1Vector.size() < waveMaxSpawnEnemy)
			{
				enemy1.rect.setPosition(randomSpawn(50, window.getSize().x - 200), -10);
				enemy1Vector.push_back(enemy1);
			}
			break;
		case 2:
			if (enemy2Vector.size() < waveMaxSpawnEnemy)
			{
				enemy2.rect.setPosition(randomSpawn(50, window.getSize().x - 200), -10);
				enemy2Vector.push_back(enemy2);
			}
			break;
		default:
			break;
		}
	}

	else if (spawningTimePowerups.getElapsedTime().asSeconds() > spawningRatePowerups)
	{
		spawningTimePowerups.restart();

		int whichPowerup = ((rand() % 2) + 1);

		switch (whichPowerup)
		{
		case 1:
			if (powerupLifeVector.size() < waveMaxSpawnPowerups)
			{
				powerLife.rect.setPosition(randomSpawn(50, window.getSize().x - 200), -10);
				powerupLifeVector.push_back(powerLife);
			}
			break;
		case 2:
			if (powerupFireVector.size() < waveMaxSpawnPowerups)
			{
				powerFire.rect.setPosition(randomSpawn(50, window.getSize().x - 200), -10);
				powerupFireVector.push_back(powerFire);
			}
			break;
		default:
			break;
		}
	}

	if (waveTime.getElapsedTime().asSeconds() > waveWait)
	{
		waveTime.restart();
		waveMaxSpawnEnemy = waveMaxSpawnEnemy * 2;
		if (spawningRateEnemy >= 0.1)
		{
			spawningRateEnemy -= 0.2f;
		}
		else
		{
			spawningRateEnemy = 0.1f;
		}
		spawningRateEnemy -= 0.2f;
		waveNumber++;
		enemy1.life += 2;
		enemy2.life += 2;
		enemy1.movementSpeed += 0.2f;
		enemy2.movementSpeed += 0.2f;
		_player.movementSpeed += 50.0f;
		enemy1.attackDamage += 1;
		enemy2.attackDamage += 1;
		powerFire.movementSpeed += 0.1f;
		powerLife.movementSpeed += 0.1f;

	}

	

	/////////////////////////////////////// SHOOTING /////////////////////////
	if (Keyboard::isKeyPressed(Keyboard::Space) || Joystick::isButtonPressed(0, 1) && isJoysticConnected == true) //XBOX B
	{
		if (shootingClock.getElapsedTime().asSeconds() >= _player.fireRate)
		{
			shootSound.play();
			shootingClock.restart();
			ammo1.rect.setPosition(_player.rect.getPosition().x + 50.0f, _player.rect.getPosition().y);
			ammo1.sprite.setPosition(ammo1.rect.getPosition());

			ammoVector.push_back(ammo1);
		}
	}
	///////////////////////////////////////////////Draw ammo
	counter = 0;
	for (iterAmmo = ammoVector.begin(); iterAmmo != ammoVector.end(); iterAmmo++)
	{
		ammoVector[counter].shooted();
		window.draw(ammoVector[counter].sprite);
		counter++;
	}

	///////////////////////////////////Draw Enemy1

	counter = 0;
	for (iterEnemy1 = enemy1Vector.begin(); iterEnemy1 != enemy1Vector.end(); iterEnemy1++)
	{
		enemy1Vector[counter].movement(window);
		window.draw(enemy1Vector[counter].sprite);
		//window.draw(enemy1Array[counter].rect);
		counter++;
	}

	///////////////////////////////////Draw Enemy2

	counter = 0;
	for (iterEnemy2 = enemy2Vector.begin(); iterEnemy2 != enemy2Vector.end(); iterEnemy2++)
	{
		enemy2Vector[counter].update();
		enemy2Vector[counter].movement();
		window.draw(enemy2Vector[counter].sprite);
		//window.draw(enemy2Vector[counter].rect);
		counter++;
	}

	///////////////////////////////////Draw POWER UP LIFE

	counter = 0;
	for (iterPowerupLife = powerupLifeVector.begin(); iterPowerupLife != powerupLifeVector.end(); iterPowerupLife++)
	{
		powerupLifeVector[counter].update();
		powerupLifeVector[counter].movement();
		window.draw(powerupLifeVector[counter].sprite);
		//window.draw(powerupLifeVector[counter].rect);
		counter++;
	}


	///////////////////////////////////Draw POWER UP FIRE RATE

	counter = 0;
	for (iterPowerupFire = powerupFireVector.begin(); iterPowerupFire != powerupFireVector.end(); iterPowerupFire++)
	{
		powerupFireVector[counter].update();
		powerupFireVector[counter].movement();
		window.draw(powerupFireVector[counter].sprite);
		//window.draw(powerupFireVector[counter].rect);
		counter++;
	}


	/////////////////////////////////////////////Ammo - Enemy1 collision

	counter = 0;
	for (iterAmmo = ammoVector.begin(); iterAmmo != ammoVector.end(); iterAmmo++)
	{
		counter2 = 0;
		for (iterEnemy1 = enemy1Vector.begin(); iterEnemy1 != enemy1Vector.end(); iterEnemy1++)
		{
			if (ammoVector[counter].rect.getGlobalBounds().intersects(enemy1Vector[counter2].rect.getGlobalBounds()))
			{
				ammoVector[counter].collided = true;
				enemy1Vector[counter2].life--;
				if (enemy1Vector[counter2].life <= 0)
				{
					enemy1Vector[counter2].dead = true;
					_player.score += 10;
				}
			}
			counter2++;
		}
		counter++;
	}

	counter = 0;
	for (iterEnemy1 = enemy1Vector.begin(); iterEnemy1 != enemy1Vector.end(); iterEnemy1++)
	{
		if (enemy1Vector[counter].dead == true)
		{
			enemyDestroy.play();
			enemy1Vector.erase(iterEnemy1);
			break;
		}
		else if (enemy1Vector[counter].rect.getPosition().y > 2500)
		{
			enemy1Vector.erase(iterEnemy1);
			break;
		}
		counter++;
	}


	/////////////////////////////////////////////Ammo - Enemy2 collision

	counter = 0;
	for (iterAmmo = ammoVector.begin(); iterAmmo != ammoVector.end(); iterAmmo++)
	{
		counter2 = 0;
		for (iterEnemy2 = enemy2Vector.begin(); iterEnemy2 != enemy2Vector.end(); iterEnemy2++)
		{
			if (ammoVector[counter].rect.getGlobalBounds().intersects(enemy2Vector[counter2].rect.getGlobalBounds()))
			{
				ammoVector[counter].collided = true;
				enemy2Vector[counter2].life--;
				if (enemy2Vector[counter2].life <= 0)
				{
					enemy2Vector[counter2].dead = true;
					_player.score += 20;
				}
			}
			counter2++;
		}
		counter++;
	}

	counter = 0;
	for (iterEnemy2 = enemy2Vector.begin(); iterEnemy2 != enemy2Vector.end(); iterEnemy2++)
	{
		if (enemy2Vector[counter].dead == true)
		{
			enemyDestroy.play();
			enemy2Vector.erase(iterEnemy2);
			break;
		}
		else if (enemy2Vector[counter].rect.getPosition().y > 2500)
		{
			enemy2Vector.erase(iterEnemy2);
			break;
		}
		counter++;
	}

	//////////////Destroy Ammo on collision
	counter = 0;
	for (iterAmmo = ammoVector.begin(); iterAmmo != ammoVector.end(); iterAmmo++)
	{
		if (ammoVector[counter].collided == true)
		{
			ammoVector.erase(iterAmmo);
			break;
		}
		counter++;
	}


	if (takeDamage.getElapsedTime().asSeconds() >= 1.0)
	{
		////////////////////////////////////Enemy1 - Player collision
		takeDamage.restart();
		counter = 0;
		for (iterEnemy1 = enemy1Vector.begin(); iterEnemy1 != enemy1Vector.end(); iterEnemy1++)
		{
			if (_player.rect.getGlobalBounds().intersects(enemy1Vector[counter].rect.getGlobalBounds()))
			{
				playerHit.play();
				_player.life -= enemy1Vector[counter].attackDamage;
			}
			counter++;
		}
		////////////////////////////////////Enemy2 - Player collision
		counter = 0;
		for (iterEnemy2 = enemy2Vector.begin(); iterEnemy2 != enemy2Vector.end(); iterEnemy2++)
		{
			if (_player.rect.getGlobalBounds().intersects(enemy2Vector[counter].rect.getGlobalBounds()))
			{
				playerHit.play();
				_player.life -= enemy2Vector[counter].attackDamage;
			}
			counter++;
		}

		//////////////////////////////////// Powerup LIFE - Player collision

		counter = 0;
		for (iterPowerupLife = powerupLifeVector.begin(); iterPowerupLife != powerupLifeVector.end(); iterPowerupLife++)
		{
			if (_player.rect.getGlobalBounds().intersects(powerupLifeVector[counter].rect.getGlobalBounds()))
			{
				powerupLifeVector[counter].picked = true;
				powerupSound.play();
				_player.life += 1;
			}
			counter++;
		}

		//////////////////////////////////// Powerup FIRE RATE - Player collision

		counter = 0;
		for (iterPowerupFire = powerupFireVector.begin(); iterPowerupFire != powerupFireVector.end(); iterPowerupFire++)
		{
			if (_player.rect.getGlobalBounds().intersects(powerupFireVector[counter].rect.getGlobalBounds()))
			{
				powerupFireVector[counter].picked = true;
				powerupSound.play();
				if (_player.fireRate > 0.1f)
				{
					_player.fireRate -= 0.1f;
					
				}
				else
				{
					_player.fireRate = 0.1f;
				}
				
			}
			counter++;
		}

	}


	counter = 0;
	for (iterPowerupFire = powerupFireVector.begin(); iterPowerupFire != powerupFireVector.end(); iterPowerupFire++)
	{
		if (powerupFireVector[counter].picked == true)
		{
			powerupFireVector.erase(iterPowerupFire);
			break;
		}
		else if (powerupFireVector[counter].rect.getPosition().y > 2500)
		{
			powerupFireVector.erase(iterPowerupFire);
			break;
		}
		counter++;
	}

	counter = 0;
	for (iterPowerupLife = powerupLifeVector.begin(); iterPowerupLife != powerupLifeVector.end(); iterPowerupLife++)
	{
		if (powerupLifeVector[counter].picked == true)
		{
			powerupLifeVector.erase(iterPowerupLife);
			break;
		}
		else if (powerupLifeVector[counter].rect.getPosition().y > 2500)
		{
			powerupLifeVector.erase(iterPowerupLife);
			break;
		}
		counter++;
	}



	///////////////////////////////   LOSE GAME   /////////////////////////////////////////////////////////////
	if (_player.life <= 0)
	{
		playerDead.play();

		if (deadClock.getElapsedTime().asSeconds() >= 2.0)
		{
			currentState = GameState::s_lose;

		}

	}




}

void GameState::pause()
{	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) || isJoysticConnected == true && Joystick::isButtonPressed(0, 7)) {
		sf::sleep(sf::seconds(0.5));
		currentState = GameState::s_play;
	}

	pauseMenu.showMenu(window);
		
	if (PauseMenu::isSaved)
	{
		pauseMenu.saveScore(window, _player.score);
	}
}

void GameState::toBeSaved()
{
	pauseMenu.saveScore(window, _player.score);
}

void GameState::highScore()
{
	main.showHighScore(window);
}


bool GameState::isExiting()
{
	if (currentState == GameState::s_exit)
		return true;
	else
		return false;
}

void GameState::DrawGameBoard()
{
	playBackgroundImage.loadFromFile("res/img/play_background.jpg");
	sf::Vector2f targetSize(window.getSize().x, window.getSize().y);
	playBackgroundSquare.setTexture(playBackgroundImage);
	playBackgroundSquare.setScale(
		targetSize.x / playBackgroundSquare.getLocalBounds().width,
		targetSize.y / playBackgroundSquare.getLocalBounds().height);
}

void GameState::DrawGameStats()
{
	std::ostringstream thisLife;
	thisLife << "Life: " << _player.life;

	lifeText.setFont(fontStats);
	lifeText.setCharacterSize(40);
	lifeText.setColor(sf::Color::White);
	lifeText.setStyle(sf::Text::Bold);
	lifeText.setString(thisLife.str());
	lifeText.setPosition(20.0f, 20.0f);

	window.draw(lifeText);

	std::ostringstream thisScore;
	thisScore << "Score: " << _player.score;

	scoreText.setFont(fontStats);
	scoreText.setCharacterSize(40);
	scoreText.setColor(sf::Color::White);
	scoreText.setStyle(sf::Text::Bold);
	scoreText.setString(thisScore.str());
	scoreText.setPosition(lifeText.getPosition().x, lifeText.getPosition().y + 50.0f);

	window.draw(scoreText);


	std::ostringstream this_damage;
	this_damage << "Attack Damage: " << _player.attackDamage;

	attackText.setFont(fontStats);
	attackText.setCharacterSize(40);
	attackText.setColor(sf::Color::White);
	attackText.setStyle(sf::Text::Bold);
	attackText.setString(this_damage.str());
	attackText.setPosition(scoreText.getPosition().x, scoreText.getPosition().y + 50.0f);

	window.draw(attackText);

	std::ostringstream this_fire_rate;
	this_fire_rate << "Fire Rate: " << _player.fireRate * 10.0f;

	fireRateText.setFont(fontStats);
	fireRateText.setCharacterSize(40);
	fireRateText.setColor(sf::Color::White);
	fireRateText.setStyle(sf::Text::Bold);
	fireRateText.setString(this_fire_rate.str());
	fireRateText.setPosition(attackText.getPosition().x, attackText.getPosition().y + 50.0f);

	window.draw(fireRateText);

	std::ostringstream this_wave;
	this_wave << "Wave: " << waveNumber;

	waveText.setFont(fontStats);
	waveText.setCharacterSize(40);
	waveText.setColor(sf::Color::White);
	waveText.setStyle(sf::Text::Bold);
	waveText.setString(this_wave.str());
	waveText.setPosition(attackText.getPosition().x, window.getSize().y - 100.0f);

	window.draw(waveText);
}

int GameState::randomSpawn(int min, int max)
{
	int random = rand() % (max - min + 1) + min;
	return random;
}

void GameState::lose()
{

	loseBackgroundTexture.loadFromFile("res/img/pause_background.jpg");
	sf::Vector2f targetSize(window.getSize().x, window.getSize().y);
	loseBackground.setTexture(loseBackgroundTexture);
	loseBackground.setScale(
		targetSize.x / loseBackground.getLocalBounds().width,
		targetSize.y / loseBackground.getLocalBounds().height);

	window.draw(loseBackground);

	sf::Text loseTxt;
	loseTxt.setFont(fontStats);
	loseTxt.setCharacterSize(100);
	loseTxt.setColor(sf::Color::White);
	loseTxt.setStyle(sf::Text::Bold);
	loseTxt.setString("YOU DIED!");

	sf::FloatRect textRect = loseTxt.getLocalBounds();
	loseTxt.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	loseTxt.setPosition(sf::Vector2f(window.getSize().x / 2.0f, 200.0f));

	window.draw(loseTxt);

	sf::Texture p_menuVisual;
	sf::Sprite p_menuText;


	sf::Texture backToMainTexture;
	sf::Sprite backToMain;

	backToMainTexture.loadFromFile("res/img/exit_on.png");
	backToMain.setTexture(backToMainTexture);


	sf::FloatRect backRect = backToMain.getLocalBounds();
	backToMain.setOrigin(backRect.left + backRect.width / 2.0f,
		backRect.top + backRect.height / 2.0f);
	backToMain.setPosition(sf::Vector2f(window.getSize().x / 2.0f, 500.0f));

	window.draw(backToMain);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || Joystick::isButtonPressed(0, 2) && GameState::isJoysticConnected == true) {
		
		mainMusic.play();
		mainMusic.setLoop(true);
		initialScore.open("res/scores.txt", std::ios_base::app | std::ios_base::out);
		initialScore << _player.score << "\n";
		currentState = GameState::s_exit;
	}


}
