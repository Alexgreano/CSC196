#pragma once
#include"Base/Actor.h"

class Kame : public nc::Actor {
public:
	Kame(const nc::Transform transform, std::shared_ptr<nc::Shape> shape, float speed) : nc::Actor{ transform, shape }, speed{ speed } {tag = "Enemy"; };

	virtual void Update(float dt) override;
	void OnCollision(Actor* actor) override;



private:
	float speed{ 200 };
	float fireTimer{ 0 };
	float fireRate{ 0 };

};