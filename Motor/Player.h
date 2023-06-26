#pragma once
#include "Human.h"
#include "InputManager.h"

class Player : public Human
{
protected:
	int vidas = 3;
	InputManager* inputManager;
public:
	Player();
	~Player();
	int getVidas() {
		return this->vidas;
	}
	void setVidas(int vidas) {
		this->vidas = vidas;
	}
	void init(int vidas, float speed, glm::vec2 position,InputManager* inputManager);
	void update(const vector<string>& levelData, vector<Human*>& humans,
		vector<Zombie*>& zombies);
};

