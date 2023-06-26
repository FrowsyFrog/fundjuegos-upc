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
	bool alive = true;
	float speed;
	Color color;
	void checkTilePosition(const vector<string>& levelData,
		vector<glm::vec2>& collideTilePosition,float x,float y);
	void collideWithTile(glm::vec2 tilePos);
public:
	Agent();
	bool getAlive() {
		return alive;
	}
	void setColor(Color color) {
		this->color = color;
	}
	Color getColor() {
		return this->color;
	}
	void setAlive(bool alive) {
		this->alive = alive;
	}

	glm::vec2 getPosition() {
		return position;
	}
	void setPosition(glm::vec2 position) {
		this->position = position;
	}
	virtual void update(const vector<string>& levelData,vector<Human*>& humans,
			vector<Zombie*>& zombies) = 0;
	void draw(SpriteBatch& spriteBatch);
	bool collideWithLevel(const vector<string>& levelData);
	virtual ~Agent();
	bool collideWithAgent(Agent* agent);
};

