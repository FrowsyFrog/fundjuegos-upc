#pragma once
#include <glm/glm.hpp>
#include "SpriteBatch.h"
#include "GLTexture.h"
#include <string>
#include "Level.h"

class Zombie;
class Human;

const float AGENT_WIDTH = 60.f;
const float AGENT_RADIUS = AGENT_WIDTH / 2.0f;

class Agent
{
protected:
	string path;
	glm::vec2 position;
	int vidas;
	bool alive;
	float speed;
	Color color;
	void checkTilePosition(const vector<string>& levelData,
		vector<glm::vec2>& collideTilePosition,float x,float y);
	void collideWithTile(glm::vec2 tilePos);
public:
	Agent();
	bool getAlive() const {
		return alive;
	}
	int getVidas() {
		return this->vidas;
	}
	void setColor(Color color) {
		this->color = color;
	}
	void setVidas(int vidas) {
		this->vidas = vidas;
	}
	Color getColor() const {
		return this->color;
	}
	void setAlive(bool alive) {
		this->alive = alive;
	}

	glm::vec2 getPosition() const {
		return position;
	}
	void setPosition(glm::vec2 position) {
		this->position = position;
	}
	bool isDead();
	virtual void update(const vector<string>& levelData,vector<Human*>& humans,
			vector<Zombie*>& zombies) = 0;
	void draw(SpriteBatch& spriteBatch);
	bool collideWithLevel(const vector<string>& levelData);
	virtual ~Agent();
	bool collideWithAgent(Agent* agent);
};

