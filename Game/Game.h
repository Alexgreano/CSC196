#pragma once
#include "Engine.h"
#include "Actors/Player.h"


class Game {
public:
	enum class eState {
		Title,
		Startgame,
		StartLevel,
		Game,
		GameOver,
		Restart
	};



public: 
	void Initialize();
	void Shutdown();

	void Update(float dt);
	void Draw(Core::Graphics& graphics);

private:
	void UpdateTitle(float dt);
	void UpdateStartLevel(float dt, size_t level);
	void OnAddPoints(const nc::Event& event);
	void OnPlayerDead(const nc::Event& event);
	void PlayerLoseLife(const nc::Event& event);

public:
	std::unique_ptr<nc::Engine> engine;
	std::unique_ptr<nc::Scene> scene;

private:
	eState state = eState::Title;
	float stateTimer = 0.0f;
	float SpawnTimer = 0.0f;

	void (Game::* stateFunction) (float) = nullptr;

	size_t score = 0;
	size_t lives = 0;
	size_t level = 0;
};