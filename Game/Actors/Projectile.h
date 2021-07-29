#pragma once
#include "Base/Actor.h"

class Projectile : public nc::Actor {
public:
	Projectile(const nc::Transform transform, std::shared_ptr<nc::Shape> shape, float speed) : nc::Actor{ transform, shape }, speed{ speed } {};
	virtual void Update(float dt) override;

	void OnCollision(Actor* actor) override;


private:
	float lifetime{ 1 };
	float speed{ 300 };
};