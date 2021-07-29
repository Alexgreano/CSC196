#include "Game.h"

#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include "Actors/Asteroid.h"
#include "Actors/Projectile.h"
#include "Actors/Kamikazi.h"
#include "Actors/PowerUp.h"


void Game::Initialize()
{
	engine = std::make_unique<nc::Engine>();
	engine->Startup();
	scene = std::make_unique<nc::Scene>();
	scene->engine = engine.get();


	engine->Get<nc::AudioSystem>()->AddAudio("explosion", "Explosion.wav");
	engine->Get<nc::AudioSystem>()->AddAudio("PlayerShoot", "Laser_Shoot1.wav");
	engine->Get<nc::AudioSystem>()->AddAudio("EnemyShoot", "Laser_ShootEnemy.wav");
	engine->Get<nc::AudioSystem>()->AddAudio("PowerUp", "Powerup.wav");
	engine->Get<nc::AudioSystem>()->AddAudio("Menu", "Menu.wav");
	engine->Get<nc::AudioSystem>()->AddAudio("Level1", "Level1.wav");
	engine->Get<nc::AudioSystem>()->AddAudio("Level2", "Level2.wav");
	engine->Get<nc::AudioSystem>()->AddAudio("Level3", "Level3.wav");

	engine->Get<nc::EventSystem>()->Subscribe("AddPoints", std::bind(&Game::OnAddPoints, this, std::placeholders::_1));
	engine->Get<nc::EventSystem>()->Subscribe("PlayerDead", std::bind(&Game::OnPlayerDead, this, std::placeholders::_1));
	engine->Get<nc::EventSystem>()->Subscribe("PlayerLoseLife", std::bind(&Game::PlayerLoseLife, this, std::placeholders::_1));

	//stateFunction = &Game::UpdateTitle;
}

void Game::Shutdown()
{
}

void Game::Update(float dt){

	stateTimer += dt;
	SpawnTimer += dt;


	switch (state)
	{
	case Game::eState::Title:
		if (Core::Input::IsPressed(VK_SPACE)) {
			state = eState::Startgame;
		}
		break;
	case Game::eState::Startgame:
		score = 0;
		lives = 3;
		state = eState::StartLevel;
		
		break;
	case Game::eState::StartLevel: {
		scene->engine->Get<nc::AudioSystem>()->PlayAudio("Level1");
		
		UpdateStartLevel(dt, level);
		state = eState::Game;
	}

		break;
	case Game::eState::Game:
		if ((scene->GetActors<Enemy>().size() == 0) && (scene->GetActors<Kame>().size() == 0)) {
			for (size_t i = 0; i < (nc::RandomRangeInt(1, 5)); i++) {
				scene->AddActor(std::make_unique <Enemy>(nc::Transform{ {nc::RandomRange(0, 800), nc::RandomRange(0, 600)}, nc::RandomRange(0.0f, nc::TwoPi), 2.0f
					}, engine->Get<nc::ResourceSystem>()->Get<nc::Shape>("Enemy.txt"), 75.0f));
			}
			for (size_t i = 0; i < (nc::RandomRangeInt(1, 3)); i++) {
				scene->AddActor(std::make_unique <Asteroid>(nc::Transform{ {nc::RandomRange(0, 800), nc::RandomRange(0, 600)}, nc::RandomRange(0.0f, nc::TwoPi), 2.0f
					}, engine->Get<nc::ResourceSystem>()->Get<nc::Shape>("Asteroid.txt"), 175.0f));
			}
			for (size_t i = 0; i < (nc::RandomRangeInt(1, 5)); i++) {
				scene->AddActor(std::make_unique <Kame>(nc::Transform{ {nc::RandomRange(0, 800), nc::RandomRange(0, 600)}, nc::RandomRange(0.0f, nc::TwoPi), 2.0f
					}, engine->Get<nc::ResourceSystem>()->Get<nc::Shape>("Kame.txt"), 125.0f));
			}
			if (nc::RandomRange(1,0) <= .5f) {
			scene->AddActor(std::make_unique <PowerUp>(nc::Transform{ {nc::RandomRange(0, 800), nc::RandomRange(0, 600)}, nc::RandomRange(0.0f, nc::TwoPi), 2.0f
				}, engine->Get<nc::ResourceSystem>()->Get<nc::Shape>("PowerUp.txt"), 250.0f));

			}
			SpawnTimer = 0.0f;

			//(nc::RandomRangeInt(1, 5))
			//
		}

		break;
	case Game::eState::GameOver:
		break;
	
	case Game::eState::Restart:
			state = eState::StartLevel;
		break;
	default:
		break;
	}

	engine->Update(dt);
	scene->Update(dt);
}

void Game::Draw(Core::Graphics& graphics){
	switch (state)
	{
	case Game::eState::Title:
		graphics.SetColor(nc::Color::purple);
		graphics.DrawString(360, static_cast<int>(300 + std::sin(stateTimer * 6.0f)), "Machia");

		graphics.DrawString(300, 400, "Press Enter To Start");

		break;
	case Game::eState::Startgame:
		break;
	case Game::eState::StartLevel:
		break;
	case Game::eState::Game:
		break;
	case Game::eState::GameOver:
		graphics.SetColor(nc::Color::red);
		graphics.DrawString(360, static_cast<int>(300 + std::sin(stateTimer * 6.0f)), "GAME OVER");
		break;
	default:
		break;
	}

	graphics.SetColor(nc::Color::cyan);
	graphics.DrawString(30,20,std::to_string(score).c_str());
	graphics.DrawString(320,20,std::to_string(lives).c_str());


	scene->Draw(graphics);
	engine->Draw(graphics);
}

void Game::OnAddPoints(const nc::Event& event)
{
	score += std::get<int>(event.data);
}

void Game::PlayerLoseLife(const nc::Event& event)
{
	lives = std::get<int>(event.data);
}


void Game::OnPlayerDead(const nc::Event& event)
{
	//std::cout << std::get<std::string>(event.data) << std::endl;
	state = eState::GameOver;
	lives = 0;
}

void Game::UpdateStartLevel(float dt, size_t level)
{
		scene->AddActor(std::make_unique<Player>(nc::Transform{ nc::Vector2{400.0f, 300.0f}, 0.0f, 3.0f 
			}, engine->Get<nc::ResourceSystem>()->Get<nc::Shape>("Player.txt"), 600.0f));

}
