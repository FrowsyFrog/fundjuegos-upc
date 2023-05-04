#include "MainGame.h"
#include <iostream>
#include "Error.h"
using namespace std;

MainGame::MainGame() {
	width = 800;
	height = 600;
	gameState = GameState::PLAY;
	time = 0;
}

MainGame::~MainGame() {
	for (auto sprite : sprites) {
		delete sprite;
	}
}
void MainGame::processInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type)
		{
		case SDL_QUIT:
			gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			//cout << event.motion.x << " , " << event.motion.y << endl;
			break;
		}
	}
}

void MainGame::initShaders()
{
	program.compileShaders("Shaders/colorShaderVert.glsl", "Shaders/colorShaderFrag.glsl");
	program.addAtribute("vertexPosition");
	program.addAtribute("vertexColor");
	program.addAtribute("vertexUV");
	program.linkShader();
}

void MainGame::init() {
	SDL_Init(SDL_INIT_EVERYTHING);
	window.create("Hola", width, height, 0);
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		fatalError("Glew not initialized");
	}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	initShaders();
}

void MainGame::draw() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	program.use();
	glActiveTexture(GL_TEXTURE0);

	GLuint timeLocation = program.getUniformLocation("time");
	glUniform1f(timeLocation, time);

	GLuint imageLocation = program.getUniformLocation("myImage");
	glUniform1i(imageLocation, 0);

	time += 0.02;

	for (Sprite* spritePtr : sprites) {
		spritePtr->draw();
	}

	program.unuse();
	window.swapWindow();
}

void MainGame::run() {
	init();

	// Primer sprite
	Sprite* sprite = new Sprite();
	sprite->init(-1, -1, 1, 1, "Textures/imagen.png");
	sprites.push_back(sprite);
	
	// Segundo sprite
	Sprite* secondSprite = new Sprite();
	secondSprite->init(0, 0, 1, 1, "Textures/imagen2.png");
	sprites.push_back(secondSprite);

	update();
}

void MainGame::update() {
	while (gameState != GameState::EXIT) {
		draw();
		processInput();
	}
}