#include "Projectile.h"
#include "Math/MathUtils.h"
#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Asteroid.h"
#include "Kamikazi.h"
#include "PowerUp.h"


void Projectile::Update(float dt)
{
	Actor::Update(dt);

	lifetime -= dt;
	if (lifetime <= 0) destroy = true;

	transform.position += nc::Vector2::Rotate(nc::Vector2::right, transform.rotation) * speed * dt;
	transform.position.x = nc::Clamp(transform.position.x, 0.0f, 800.0f);
	transform.position.y = nc::Clamp(transform.position.y, 0.0f, 600.0f);

	std::vector<nc::Color> colors = { nc::Color::white, nc::Color::red, nc::Color::green, nc::Color::blue, nc::Color::orange, nc::Color::purple, nc::Color::cyan, nc::Color::yelllow };
	scene->engine->Get<nc::ParticleSystem>()->Create(transform.position, 5, .5f, colors[nc::RandomRangeInt(0, colors.size())], 50);
}

void Projectile::OnCollision(Actor* actor)
{
	/*if (!dynamic_cast<Asteroid*>(actor)) {
		if (actor ->tag != actor->tag)
		destroy = true;
		
		scene->engine->Get<nc::ParticleSystem>()->Create(transform.position, 200, 1, nc::Color::red, 100);
		scene->engine->Get<nc::AudioSystem>()->PlayAudio("explosion");
	}*/
}
