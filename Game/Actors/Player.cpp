#include "Player.h"
#include "Math/MathUtils.h"
#include "Projectile.h"
#include "Engine.h"
#include "Enemy.h"
#include "Asteroid.h"
#include "Kamikazi.h"
#include "PowerUp.h"
#include <memory>

Player::Player(const nc::Transform transform, std::shared_ptr<nc::Shape> shape, float speed) : nc::Actor{ transform, shape }, speed{ speed } {
	
}

void Player::Initialize(){
	lives = 20;
	std::unique_ptr locator = std::make_unique<Actor>();
	locator->transform.localposition = nc::Vector2{ -15, 0 };
	locator->transform.localrotation = nc::DegToRad(180);
	AddChild(std::move(locator));

	locator = std::make_unique<Actor>();
	locator->transform.localposition = nc::Vector2{ 0,5 };
	AddChild(std::move(locator));

	locator = std::make_unique<Actor>();
	locator->transform.localposition = nc::Vector2{ 0,-5 };
	AddChild(std::move(locator));

	std::unique_ptr visualLives = std::make_unique<Actor>(nc::Transform{}, scene->engine->Get<nc::ResourceSystem>()->Get<nc::Shape>("Lives.txt"));
	visualLives->transform.localposition = nc::Vector2{ -10,0 };
	AddChild(std::move(visualLives));
};


void Player::Update(float dt)
{
	Actor::Update(dt);

	children[3]->transform.localrotation += 5 * dt;

	//movement
	float thrust = 0;
	if (Core::Input::IsPressed('A')) transform.rotation -= 5 * dt;
	if (Core::Input::IsPressed('D')) transform.rotation += 5 * dt;
	if (Core::Input::IsPressed('W')) thrust = speed;
	//if (Core::Input::IsPressed('R')) ;

	//acceleration
	nc::Vector2 acceleration;
	acceleration = nc::Vector2::Rotate(nc::Vector2::right, transform.rotation) * thrust;
	////nc::Vector2 gravity = (nc::Vector2{ 400, 300 } - transform.position).Normalized() * 50;
	//nc::Vector2 gravity = (nc::Vector2::down - transform.position).Normalized() * 50;
	//acceleration += gravity;
	//
	velocity += acceleration * dt;
	transform.position += velocity * dt;

	velocity *= .985f;

	transform.position.x = nc::Clamp(transform.position.x, 0.0f, 800.0f);
	transform.position.y = nc::Clamp(transform.position.y, 00.f, 800.0f);

	//fire
	fireTimer -= dt ;
	immunityTimer -= dt;
	PUTimer -= dt;
	if (PUTimer <= 0) {
		doubleShot = false;
	}
	else {
		doubleShot = true;
	}

	if (fireTimer <= 0 && Core::Input::IsPressed(VK_SPACE)) {
		fireTimer = fireRate;
		std::vector<nc::Vector2> points = { {-5,-5}, {5,-5}, {0,8}, {-5,-5} };
		std::shared_ptr<nc::Shape> shape = std::make_shared<nc::Shape>(points, nc::Color{ 1,1,0 });
		
		if (doubleShot){
			{
				nc::Transform t = children[1]->transform;
				t.scale = 0.5f;

				std::unique_ptr<Projectile> projectile = std::make_unique <Projectile>(t, scene->engine->Get<nc::ResourceSystem>()->Get<nc::Shape>("Bullet.txt"), 600.0f);
				projectile->tag = "Player";
				scene->AddActor(std::move(projectile));
			}

			nc::Transform t = children[2]->transform;
			t.scale = 0.5f;

			std::unique_ptr<Projectile> projectile = std::make_unique <Projectile>(t, scene->engine->Get<nc::ResourceSystem>()->Get<nc::Shape>("Bullet.txt"), 600.0f);
			projectile->tag = "Player";
			scene->AddActor(std::move(projectile));
			scene->engine->Get<nc::AudioSystem>()->PlayAudio("PlayerShoot");
		}
		else{
			nc::Transform t = children[0]->transform;
			t.scale = 0.5f;

			std::unique_ptr<Projectile> projectile = std::make_unique <Projectile>(t, scene->engine->Get<nc::ResourceSystem>()->Get<nc::Shape>("Bullet.txt"), 600.0f);
			projectile->tag = "Player";
			scene->AddActor(std::move(projectile));
			scene->engine->Get<nc::AudioSystem>()->PlayAudio("PlayerShoot");
		}

		
	}

	//scene->engine->Get<nc::ParticleSystem>()->Create(transform.position, 5, 2, nc::Color::cyan, 100);
	std::vector<nc::Color> colors = { nc::Color::white, nc::Color::blue, nc::Color::green };
	scene->engine->Get<nc::ParticleSystem>()->Create(children[0]->transform.position, 3, 2 ,colors, 50, children[0]->transform.rotation, nc::DegToRad(30));

}

void Player::OnCollision(Actor* actor)
{
	if ((dynamic_cast<Projectile*>(actor) && actor->tag == "Enemy") || (dynamic_cast<Enemy*>(actor)) || (dynamic_cast<Asteroid*>(actor)) || (dynamic_cast<Kame*>(actor))) {
		if (immunityTimer <= 0) {
			if (lives == 1) {
				destroy = true;
				actor->destroy = true;
				scene->engine->Get<nc::ParticleSystem>()->Create(transform.position, 200, 1, nc::Color::red, 100);
				scene->engine->Get<nc::AudioSystem>()->PlayAudio("explosion");

				nc::Event event;
				event.name = "PlayerDead";
				//event.data = std::string("ahhhhhhhhh, i ded");
				scene->engine->Get<nc::EventSystem>()->Notify(event);
			}
			else
			{
				//actor->destroy = true;
				lives--;
				immunityTimer = immunityRate;

				nc::Event event;
				event.name = "PlayerLoseLife";
				event.data = lives;
				scene->engine->Get<nc::EventSystem>()->Notify(event);
			}
		}
	}
	else if (dynamic_cast<PowerUp*>(actor)) {
		//actor->destroy = true;
		/*doubleShot = true;*/
		PUTimer = PUTimeRate;
	}
}

int Player::GetLives()
{
	return lives;
}

