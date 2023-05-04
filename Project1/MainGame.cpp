#include "MainGame.h"
#include <iostream>
#include "Error.h"
#include <stdlib.h>
#include <time.h>
using namespace std;

MainGame::MainGame() {
	width = 800;
	height = 600;
	gameState = GameState::PLAY;
	counter = 0;
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
	srand(time(NULL));
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

void MainGame::addRandomSprites() {
	float xPos = ((static_cast <float> (rand()) / RAND_MAX) * -1.0f); // Genera un valor aleatorio entre -1 y 0
	float yPos = ((static_cast <float> (rand()) / RAND_MAX) * -1.0f);

	counter = (rand() % 3) + 4; // El siguiente aparecerá en un tiempo aleatorio

	Sprite* sprite = new Sprite();
	sprite->init(xPos, yPos, 1, 1, "Textures/imagen.png");

	// Agregar el sprite al vector de sprites
	sprites.push_back(sprite);
}

void MainGame::draw() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	program.use();
	glActiveTexture(GL_TEXTURE0);

	GLuint imageLocation = program.getUniformLocation("myImage");
	glUniform1i(imageLocation, 0);

	counter -= 0.02;

	// Al llegar el counter a 0, se reinicia y se añade uno nuevo
	if (counter <= 0) addRandomSprites();

	for (Sprite* spritePtr : sprites) {
		spritePtr->draw();
	}

	program.unuse();
	window.swapWindow();
}

void MainGame::run() {
	init();

	addRandomSprites(); // Colocar un cuadro inicial

	update();
}

void MainGame::update() {
	while (gameState != GameState::EXIT) {
		draw();
		processInput();
	}
}