#pragma once
#include"Base/Actor.h"

class PowerUp : public nc::Actor {
public:
	PowerUp(const nc::Transform transform, std::shared_ptr<nc::Shape> shape, float speed) : nc::Actor{ transform, shape }, speed{ speed } {tag = "PowerUp"; };

	virtual void Update(float dt) override;
	void OnCollision(Actor* actor) override;



private:
	float speed{ 100 };

};