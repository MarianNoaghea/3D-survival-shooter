#include "lab_m1/tema2/tema2.h"

#include <vector>
#include <string>
#include <iostream>
#include <random>

using namespace std;
using namespace m1;

void Tema2::GenerateRandomMap() {
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> distr(0, 4); // define the range
	int k = distr(gen);

	if (k == 0) {
		for (int i = 0; i < mapSize; i++) {
			for (int j = 0; j < mapSize; j++) {
				map[i][j] = map0[i][j];
			}
		}
	}

	if (k == 1) {
		for (int i = 0; i < mapSize; i++) {
			for (int j = 0; j < mapSize; j++) {
				map[i][j] = map1[i][j];
			}
		}
	}

	if (k == 2) {
		for (int i = 0; i < mapSize; i++) {
			for (int j = 0; j < mapSize; j++) {
				map[i][j] = map2[i][j];
			}
		}
	}

	if (k == 3) {
		for (int i = 0; i < mapSize; i++) {
			for (int j = 0; j < mapSize; j++) {
				map[i][j] = map3[i][j];
			}
		}
	}

	if (k == 4) {
		for (int i = 0; i < mapSize; i++) {
			for (int j = 0; j < mapSize; j++) {
				map[i][j] = map4[i][j];
			}
		}
	}
}

glm::vec3 Tema2::GetInitialCameraPoz(glm::vec3* position, glm::vec3* center) {

	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> distr(0, 9); // define the range
	int i = 0, j = 0;
	int i2, j2;
	while (map[i][j] != 0 && map[i][j] != 2)
	{
		i = distr(gen);
		j = distr(gen);
	}

	glm::vec3 randPoz = glm::vec3(0);
	randPoz.x = i;
	randPoz.z = j;
	randPoz.y = 3;

	*center = randPoz;

	if (i - 1 >= 0 && map[i - 1][j] == 0 && map[i - 1][j] != 2 && map[i - 1][j] != 3) {
		glm::vec3 result = randPoz + (randPoz - glm::vec3(i - 1, 2.5, j));
		*position = result;
		return result;
	}

	if (i + 1 < 10 && map[i + 1][j] == 0 && map[i + 1][j] != 2 && map[i + 1][j] != 3) {
		glm::vec3 result = randPoz + (randPoz - glm::vec3(i + 1, 2.5, j));
		*position = result;
		return result;
	}

	if (j - 1 >= 0 && map[i][j - 1] == 0 && map[i][j - 1] != 2 && map[i][j - 1] != 3) {
		glm::vec3 result = randPoz + (randPoz - glm::vec3(i, 2.5, j - 1));
		*position = result;
		return result;
	}

	if (j + 1 < 10 && map[i][j + 1] == 0 && map[i][j + 1] != 2 && map[i][j + 1] != 3) {
		glm::vec3 result = randPoz + (randPoz - glm::vec3(i, 2.5, j + 1));
		*position = result;
		return result;
	}

	if (i - 1 >= 0 && map[i - 1][j] == 0) {
		glm::vec3 result = randPoz + (randPoz - glm::vec3(i - 1, 2.5, j));
		*position = result;
		return result;
	}

	if (i + 1 < 10 && map[i + 1][j] == 0) {
		glm::vec3 result = randPoz + (randPoz - glm::vec3(i + 1, 2.5, j));
		*position = result;
		return result;
	}

	if (j - 1 >= 0 && map[i][j - 1] == 0) {
		glm::vec3 result = randPoz + (randPoz - glm::vec3(i, 2.5, j - 1));
		*position = result;
		return result;
	}

	if (j + 1 < 10 && map[i][j + 1] == 0) {
		glm::vec3 result = randPoz + (randPoz - glm::vec3(i, 2.5, j + 1));
		*position = result;
		return result;
	}

}


Tema2::Enemy3 Tema2::createEnemy(int x, int z) {
	Enemy3 newEnemy;
	float ratio = newEnemy.ratio;
	newEnemy.floorCoords.x = (float)x;
	newEnemy.floorCoords.y = 0;
	newEnemy.floorCoords.z = (float)z;

	newEnemy.startCoords = newEnemy.floorCoords + glm::vec3(0, 1, 0);
	newEnemy.enemyCoords = newEnemy.startCoords;

	newEnemy.lim_b_x = newEnemy.enemyCoords.x + ratio;
	newEnemy.lim_b_z = newEnemy.enemyCoords.z + ratio;

	newEnemy.lim_c_x = newEnemy.enemyCoords.x + ratio;
	newEnemy.lim_c_z = newEnemy.enemyCoords.z - ratio;

	newEnemy.lim_d_x = newEnemy.enemyCoords.x - ratio;
	newEnemy.lim_d_z = newEnemy.enemyCoords.z - ratio;

	newEnemy.lim_e_x = newEnemy.enemyCoords.x - ratio;
	newEnemy.lim_e_z = newEnemy.enemyCoords.z + ratio;

	newEnemy.alive = true;
	return newEnemy;
}


void Tema2::getEnemies(std::vector<Enemy3>* enemies) {
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> distr(0, 9); // define the range


	for (int k = 0; k < 5; k++) {
		int i = 0, j = 0;
		while (map[i][j] != 0 && map[i][j] != 3)
		{
			i = distr(gen);
			j = distr(gen);
		}

		Enemy3 newEnemy = createEnemy(i, j);
		map[i][j] = 3;

		enemies->push_back(newEnemy);
	}
}

void Tema2::CreateEnemyMesh() {
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(0, 1, 1), glm::vec3(0.2, 0.8, 0.2)),
			VertexFormat(glm::vec3(1, -1,  1), glm::vec3(1, 0, 1), glm::vec3(0.9, 0.4, 0.2)),
			VertexFormat(glm::vec3(-1,  1,  1), glm::vec3(1, 0, 0), glm::vec3(0.7, 0.7, 0.1)),
			VertexFormat(glm::vec3(1,  1,  1), glm::vec3(0, 1, 0), glm::vec3(0.7, 0.3, 0.7)),
			VertexFormat(glm::vec3(-1, -1, -1), glm::vec3(1, 1, 1), glm::vec3(0.3, 0.5, 0.4)),
			VertexFormat(glm::vec3(1, -1, -1), glm::vec3(0, 1, 1), glm::vec3(0.5, 0.2, 0.9)),
			VertexFormat(glm::vec3(-1,  1, -1), glm::vec3(1, 1, 0), glm::vec3(0.7, 0.0, 0.7)),
			VertexFormat(glm::vec3(1,  1, -1), glm::vec3(0, 0, 1), glm::vec3(0.1, 0.5, 0.8)),
		};

		vector<unsigned int> indices =
		{
			0, 1, 2,        1, 3, 2,
			2, 3, 7,        2, 7, 6,
			1, 7, 3,        1, 5, 7,
			6, 7, 4,        7, 5, 4,
			0, 4, 1,        1, 4, 5,
			2, 6, 4,        0, 2, 4,
		};

		CreateMesh("enemy", vertices, indices);
	}
}

void Tema2::CreatePlayerMesh() {

	vector<unsigned int> cubeIndices =
	{
		0, 1, 2,
		1, 3, 2,
		2, 3, 7,
		2, 7, 6,
		1, 7, 3,
		1, 5, 7,
		6, 7, 4,
		7, 5, 4,
		0, 4, 1,
		1, 4, 5,
		2, 6, 4,
		0, 2, 4
	};


	vector<unsigned int> indicesPlayer;

	int k = 0;
	for (int i = 0; i < 63; i += 8) {
		for (int j = 0; j < 36; j++) {
			indicesPlayer.push_back(cubeIndices[j] + i);
		}
	}

	glm::vec3 vec1 = glm::vec3(0, 1, 1);
	glm::vec3 colorSkin = glm::vec3(0.804, 0.522, 0.247);
	glm::vec3 colorShirt = glm::vec3(0.482, 0.408, 0.933);
	glm::vec3 colorPants = glm::vec3(0.502, 0.000, 0.000);
	glm::vec3 colorRed = glm::vec3(1, 0.000, 0.000);

	vector<VertexFormat> verticesPlayer =
	{
		// head
		VertexFormat(glm::vec3(-0.5f, 6,  1), vec1,  colorRed),
		VertexFormat(glm::vec3(0.5f, 6,  1), vec1,  colorRed),
		VertexFormat(glm::vec3(-0.5f, 7,  1), vec1,  colorRed),
		VertexFormat(glm::vec3(0.5f, 7,  1), vec1,  colorRed),
		VertexFormat(glm::vec3(-0.5f, 6,  0), vec1, colorSkin),
		VertexFormat(glm::vec3(0.5f, 6,  0), vec1, colorSkin),
		VertexFormat(glm::vec3(-0.5f, 7,  0), vec1, colorSkin),
		VertexFormat(glm::vec3(0.5f, 7,  0), vec1, colorSkin),


		// body
		VertexFormat(glm::vec3(-1, 6,  1), vec1, colorShirt),
		VertexFormat(glm::vec3(1, 6,  1), vec1, colorShirt),
		VertexFormat(glm::vec3(-1, 3,  1), vec1, colorShirt),
		VertexFormat(glm::vec3(1, 3,  1), vec1, colorShirt),
		VertexFormat(glm::vec3(-1, 6,  0), vec1, colorShirt),
		VertexFormat(glm::vec3(1, 6,  0), vec1, colorShirt),
		VertexFormat(glm::vec3(-1, 3,  0), vec1, colorShirt),
		VertexFormat(glm::vec3(1, 3,  0), vec1, colorShirt),

		// left_arm
		VertexFormat(glm::vec3(-2, 4, 1), vec1, colorShirt),
		VertexFormat(glm::vec3(-1, 4,  1), vec1, colorShirt),
		VertexFormat(glm::vec3(-2, 6,  1), vec1, colorShirt),
		VertexFormat(glm::vec3(-1, 6,  1), vec1, colorShirt),
		VertexFormat(glm::vec3(-2, 6,  0), vec1, colorShirt),
		VertexFormat(glm::vec3(-1, 6,  0), vec1, colorShirt),
		VertexFormat(glm::vec3(-2, 4,  0), vec1, colorShirt),
		VertexFormat(glm::vec3(-1, 4,  0), vec1, colorShirt),

		// right_arm
		VertexFormat(glm::vec3(1, 4,  1), vec1, colorShirt),
		VertexFormat(glm::vec3(2, 4,  1), vec1, colorShirt),
		VertexFormat(glm::vec3(1, 6,  1), vec1, colorShirt),
		VertexFormat(glm::vec3(2, 6,  1), vec1, colorShirt),
		VertexFormat(glm::vec3(1, 4,  0), vec1, colorShirt),
		VertexFormat(glm::vec3(2, 4,  0), vec1, colorShirt),
		VertexFormat(glm::vec3(1, 6,  0), vec1, colorShirt),
		VertexFormat(glm::vec3(2, 6,  0), vec1, colorShirt),

		// left_leg
		VertexFormat(glm::vec3(-1, 1,  1), vec1, colorPants),
		VertexFormat(glm::vec3(0, 1,  1), vec1, colorPants),
		VertexFormat(glm::vec3(-1, 3,  1), vec1, colorPants),
		VertexFormat(glm::vec3(0, 3,  1), vec1, colorPants),
		VertexFormat(glm::vec3(-1, 1,  0), vec1, colorPants),
		VertexFormat(glm::vec3(0, 1,  0), vec1, colorPants),
		VertexFormat(glm::vec3(-1, 3,  0), vec1, colorPants),
		VertexFormat(glm::vec3(0, 3,  0), vec1, colorPants),

		// right_leg
		VertexFormat(glm::vec3(0, 3,  1), vec1, colorPants),
		VertexFormat(glm::vec3(1, 3,  1), vec1, colorPants),
		VertexFormat(glm::vec3(0, 1,  1), vec1, colorPants),
		VertexFormat(glm::vec3(1, 1,  1), vec1, colorPants),
		VertexFormat(glm::vec3(0, 3,  0), vec1, colorPants),
		VertexFormat(glm::vec3(1, 3,  0), vec1, colorPants),
		VertexFormat(glm::vec3(0, 1,  0), vec1, colorPants),
		VertexFormat(glm::vec3(1, 1,  0), vec1, colorPants),

		// left_hand
		VertexFormat(glm::vec3(-2, 4,  1), vec1, colorSkin),
		VertexFormat(glm::vec3(-1, 4,  1), vec1, colorSkin),
		VertexFormat(glm::vec3(-2, 3,  1), vec1, colorSkin),
		VertexFormat(glm::vec3(-1, 3,  1), vec1, colorSkin),
		VertexFormat(glm::vec3(-2, 4,  0), vec1, colorSkin),
		VertexFormat(glm::vec3(-1, 4,  0), vec1, colorSkin),
		VertexFormat(glm::vec3(-2, 3,  0), vec1, colorSkin),
		VertexFormat(glm::vec3(-1, 3,  0), vec1, colorSkin),


		// right_hand
		VertexFormat(glm::vec3(1, 4,  1), vec1, colorSkin),
		VertexFormat(glm::vec3(2, 4,  1), vec1, colorSkin),
		VertexFormat(glm::vec3(1, 3,  1), vec1, colorSkin),
		VertexFormat(glm::vec3(2, 3,  1), vec1, colorSkin),
		VertexFormat(glm::vec3(1, 4,  0), vec1, colorSkin),
		VertexFormat(glm::vec3(2, 4,  0), vec1, colorSkin),
		VertexFormat(glm::vec3(1, 3,  0), vec1, colorSkin),
		VertexFormat(glm::vec3(2, 3,  0), vec1, colorSkin),
	};

	Tema2::CreateMesh("player", verticesPlayer, indicesPlayer);
}

Tema2::Tema2()
{
}


Tema2::~Tema2()
{
}


void Tema2::Init()
{
	// initial false
	renderCameraTarget = true;

	GenerateRandomMap();

	glm::vec3 randomPoz = glm::vec3(0);
	glm::vec3 center = glm::vec3(0);

	getEnemies(&enemies);

	randomPoz = GetInitialCameraPoz(&randomPoz, &center);
	center.y = 0;

	camera->Set(randomPoz, center, glm::vec3(0, 1, 0));



	for (int i = 0; i < mapSize; i++) {
		for (int j = 0; j < mapSize; j++) {
			if (map[i][j] == 1) {
				Obstacle newObstacle;
				newObstacle.x = i;
				newObstacle.y = 1;
				newObstacle.z = j;
				obstacles.push_back(newObstacle);
			}
			if (map[i][j] == 2) {
				finishBlock.x = i;
				finishBlock.y = 0;
				finishBlock.z = j;
			}
		}
	}

	CreatePlayerMesh();
	CreateEnemyMesh();

	fov = RADIANS(60);
	near = 0.001f;
	far = 200.f;
	left = -5.f;
	right = 5.f;
	bottom = -5.f;
	top = 5.f;
	znear = 0.001f;
	zfar = 200.f;
	deltaOrtho = 0;

	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Shader* shader = new Shader("DeadEnemyShader");
		shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
		shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	// TODO(student): After you implement the changing of the projection
	// parameters, remove hardcodings of these parameters
	projectionMatrix = glm::perspective(fov, window->props.aspectRatio, near, far);

}


void Tema2::FrameStart()
{
	// Clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// Sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}


void Tema2::Update(float deltaTimeSeconds)
{
	if (thirdPerson && CheckPlayerFinishCollision(camera->GetTargetPosition(), finishBlock)) {
		printf("YOU WON! GAME OVER! FINAL SCORE %f\n", player.score + player.time);
		GAMEOVER = true;
	}
	else {

		if (player.time > 0 && player.health > 0) {
			player.time -= deltaTimeSeconds;

			printf("player time = %f   |   player health = %d   |   player score = %d\n", player.time, player.health, player.score);


			if (perspective) {
				projectionMatrix = glm::perspective(fov, window->props.aspectRatio, near, far);
			}
			else {
				projectionMatrix = glm::ortho(left - deltaOrtho, right + deltaOrtho, bottom - deltaOrtho, top + deltaOrtho, near, far);
			}

			float moveSpeed = 7;
			for (int i = 0; i < bullets.size(); i++) {
				glm::mat4 modelMatrix = glm::mat4(1);
				float travelDistance = (!(moveSpeed * deltaTimeSeconds < glm::length(bullets[i].dirVecOfBullet)) ? glm::length(bullets[i].dirVecOfBullet) : moveSpeed * deltaTimeSeconds);
				bullets[i].vecPosition += glm::normalize(bullets[i].dirVecOfBullet) * travelDistance;

				modelMatrix = glm::translate(modelMatrix, player.playerPoz);
				modelMatrix = glm::translate(modelMatrix, bullets[i].vecPosition);
				modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));

				bullets[i].x = bullets[i].vecPosition.x + player.playerPoz.x;
				bullets[i].y = bullets[i].vecPosition.y + player.playerPoz.y;
				bullets[i].z = bullets[i].vecPosition.z + player.playerPoz.z;

				bullets[i].TTL -= deltaTimeSeconds;



				for (int j = 0; j < obstacles.size(); j++) {
					if (CheckBulletObstacleCollision(glm::vec3(bullets[i].x, bullets[i].y, bullets[i].z), obstacles[j]) || bullets[i].TTL <= 0) {
						bullets.erase(bullets.begin() + i);
						break;
					}
				}

				RenderMesh(meshes["sphere"], shaders["VertexNormal"], modelMatrix);

			}

			for (int i = 0; i < mapSize; i++) {
				for (int j = 0; j < mapSize; j++) {
					{
						glm::mat4 modelMatrix = glm::mat4(1);
						modelMatrix = glm::translate(modelMatrix, glm::vec3(i, 0, j));
						RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);
					}

					if (map[i][j] == 1) {
						{
							glm::mat4 modelMatrix = glm::mat4(1);
							modelMatrix = glm::translate(modelMatrix, glm::vec3(i, 1, j));
							RenderMesh(meshes["box"], shaders["Simple"], modelMatrix);
						}
					}
				}
			}

			for (int i = 0; i < enemies.size(); i++)
			{
				float ratio = 0.33333;

				if (enemies[i].dir == 'a') {
					enemies[i].enemyCoords.x += ratio;
					enemies[i].enemyCoords.z += ratio;
					enemies[i].dir = 'b';

				}

				if (enemies[i].dir == 'b') {
					if (enemies[i].enemyCoords.z >= enemies[i].lim_c_z) {
						enemies[i].enemyCoords.z -= deltaTimeSeconds;

						if (!enemies[i].alive) {
							enemies[i].TTL += deltaTimeSeconds;
						}

					}
					else {
						enemies[i].dir = 'c';
					}
				}

				if (enemies[i].dir == 'c') {
					if (enemies[i].enemyCoords.x >= enemies[i].lim_d_x) {
						enemies[i].enemyCoords.x -= deltaTimeSeconds;

						if (!enemies[i].alive) {
							enemies[i].TTL += deltaTimeSeconds;
						}
					}
					else {
						enemies[i].dir = 'd';
					}
				}

				if (enemies[i].dir == 'd') {
					if (enemies[i].enemyCoords.z <= enemies[i].lim_e_z) {
						enemies[i].enemyCoords.z += deltaTimeSeconds;

						if (!enemies[i].alive) {
							enemies[i].TTL += deltaTimeSeconds;
						}

						if (!enemies[i].alive && enemies[i].TTL >= 5) {

						}
					}
					else {
						enemies[i].dir = 'e';
					}
				}

				if (enemies[i].dir == 'e') {
					if (enemies[i].enemyCoords.x <= enemies[i].lim_b_x) {
						enemies[i].enemyCoords.x += deltaTimeSeconds;

						if (!enemies[i].alive) {
							enemies[i].TTL += deltaTimeSeconds;
						}
					}
					else {
						enemies[i].dir = 'b';
					}
				}

				// ENEMYmesh
				{
					glm::mat4 modelMatrix = glm::mat4(1);
					modelMatrix = glm::translate(modelMatrix, enemies[i].enemyCoords);
					modelMatrix = glm::scale(modelMatrix, glm::vec3(ratio));

					if (enemies[i].alive)
						RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);
					else {
						if (enemies[i].TTL <= 0.5)
							RenderMesh(meshes["enemy"], shaders["DeadEnemyShader"], modelMatrix);
					}
				}
			}



			for (int i = 0; i < enemies.size(); i++) {
				if (enemies[i].alive && thirdPerson && CheckPlayerEnemyCollision(camera->GetTargetPosition(), enemies[i])) {
					enemies[i].alive = false;
					player.health -= 20;
				}
			}


			for (int i = 0; i < bullets.size(); i++) {
				for (int j = 0; j < enemies.size(); j++) {
					if (CheckBulletEnemyCollision(bullets[i], enemies[j])) {
						bullets.erase(bullets.begin() + i);
						enemies[j].alive = false;
						player.score += 100;
						break;
					}
				}
			}




			glm::vec3 a = camera->forward;
			glm::vec3 b1 = (glm::vec3(1, 0, -1));
			glm::vec3 b2 = (glm::vec3(0, 0, 1));
			float rotateAngle1 = (acos((a[0] * b1[0] + a[1] * b1[1] + a[2] * b1[2]) / (sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]) * sqrt(b1[0] * b1[0] + b1[1] * b1[1] + b1[2] * b1[2]))));
			float rotateAngle2 = (acos((a[0] * b2[0] + a[1] * b2[1] + a[2] * b2[2]) / (sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]) * sqrt(b2[0] * b2[0] + b2[1] * b2[1] + b2[2] * b2[2]))));
			float angle;
			if (abs(a.x) > abs(a.z)) {
				if (a.x < 0) {
					// Q1
					angle = rotateAngle1 - RADIANS(90 - 45);
				}
				else {
					// Q3
					angle = rotateAngle2 - RADIANS(180);
				}
			}
			else {
				if (a.z < 0) {
					// Q4
					angle = rotateAngle2 - RADIANS(180 - 45);
				}
				else {
					// Q2
					angle = -rotateAngle1 - RADIANS(90 - 45);
				}
			}

			{
				if (thirdPerson)
				{
					//glm::vec3 player.playerPoz = camera->GetTargetPosition();
					glm::mat4 modelMatrix = glm::mat4(1);
					modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -1 + 0.2, 0) + camera->GetTargetPosition());
					modelMatrix = glm::rotate(modelMatrix, angle, glm::vec3(0, 1, 0));
					modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15f));

					RenderMesh(meshes["player"], shaders["VertexNormal"], modelMatrix);
				}
				else {
					glm::mat4 modelMatrix = glm::mat4(1);
					modelMatrix = glm::translate(modelMatrix, camera->GetTargetPosition());
					modelMatrix = glm::rotate(modelMatrix, angle, glm::vec3(0, 1, 0));
					modelMatrix = glm::scale(modelMatrix, glm::vec3(0.01f));

					RenderMesh(meshes["sphere"], shaders["VertexNormal"], modelMatrix);
				}

			}
		}
		else {
			printf("YOU LOST! GAME OVER! - FINAL SCORE: %d\n", player.score);
			GAMEOVER = true;
		}
	}
}


void Tema2::FrameEnd()
{
	DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);
}


void Tema2::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
	if (!mesh || !shader || !shader->program)
		return;

	// Render an object using the specified shader and the specified position
	shader->Use();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	glUniform1f(glGetUniformLocation(shader->GetProgramID(), "time"), Engine::GetElapsedTime());

	mesh->Render();
}

void Tema2::CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices)
{
	unsigned int VAO = 0;
	// TODO(student): Create the VAO and bind it
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO = 0;
	// TODO(student): Create the VBO and bind it
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// TODO(student): Send vertices data into the VBO buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	unsigned int IBO = 0;
	// TODO(student): Create the IBO and bind it

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	// TODO(student): Send indices data into the IBO buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	// ========================================================================
	// This section demonstrates how the GPU vertex shader program
	// receives data. It will be learned later, when GLSL shaders will be
	// introduced. For the moment, just think that each property value from
	// our vertex format needs to be sent to a certain channel, in order to
	// know how to receive it in the GLSL vertex shader.

	// Set vertex position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

	// Set vertex normal attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

	// Set texture coordinate attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

	// Set vertex color attribute
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
	// ========================================================================

	// TODO(student): Unbind the VAO
	// glBindVertexArray(0);

	// Check for OpenGL errors
	if (GetOpenGLError() == GL_INVALID_OPERATION)
	{
		cout << "\t[NOTE] : For students : DON'T PANIC! This error should go away when completing the tasks." << std::endl;
		cout << "\t[NOTE] : For developers : This happens because OpenGL core spec >=3.1 forbids null VAOs." << std::endl;
	}

	// Mesh information is saved into a Mesh object
	meshes[name] = new Mesh(name);
	meshes[name]->InitFromBuffer(VAO, static_cast<unsigned int>(indices.size()));
}

bool Tema2::CheckPlayerEnemyCollision(glm::vec3 one, Enemy3 two) // AABB - Circle collision
{
	// get center point circle first 
	glm::vec2 center(one.x, one.z);
	// calculate AABB info (center, half-extents)
	glm::vec2 aabb_half_extents(two.ratio / 2.0f, two.ratio / 2.0f);
	glm::vec2 aabb_center(
		two.enemyCoords.x,
		two.enemyCoords.z
	);
	// get difference vector between both centers
	glm::vec2 difference = center - aabb_center;
	glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
	// add clamped value to AABB_center and we get the value of box closest to circle
	glm::vec2 closest = aabb_center + clamped;
	// retrieve vector between center circle and closest point AABB and check if length <= radius
	difference = closest - center;
	return glm::length(difference) < 0.3 / 2.0f;
}

bool Tema2::CheckPlayerObstacleCollision(glm::vec3 one, Obstacle two) // AABB - Circle collision
{
	// get center point circle first 
	glm::vec2 center(one.x, one.z);
	// calculate AABB info (center, half-extents)
	glm::vec2 aabb_half_extents(1 / 2.0f, 1 / 2.0f);
	glm::vec2 aabb_center(
		two.x,
		two.z
	);
	// get difference vector between both centers
	glm::vec2 difference = center - aabb_center;
	glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
	// add clamped value to AABB_center and we get the value of box closest to circle
	glm::vec2 closest = aabb_center + clamped;
	// retrieve vector between center circle and closest point AABB and check if length <= radius
	difference = closest - center;
	return glm::length(difference) < 0.4 / 2.0f;
}

bool Tema2::CheckPlayerFinishCollision(glm::vec3 one, Finish two) // AABB - Circle collision
{
	// get center point circle first 
	glm::vec2 center(one.x, one.z);
	// calculate AABB info (center, half-extents)
	glm::vec2 aabb_half_extents(1 / 2.0f, 1 / 2.0f);
	glm::vec2 aabb_center(
		two.x,
		two.z
	);
	// get difference vector between both centers
	glm::vec2 difference = center - aabb_center;
	glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
	// add clamped value to AABB_center and we get the value of box closest to circle
	glm::vec2 closest = aabb_center + clamped;
	// retrieve vector between center circle and closest point AABB and check if length <= radius
	difference = closest - center;
	return glm::length(difference) < 0.4 / 2.0f;
}

bool Tema2::CheckBulletObstacleCollision(glm::vec3 one, Obstacle two)
{
	float x = max(two.x - 0.5f, min(one.x, two.x + 0.5f));
	float y = max(two.y - 0.5f, min(one.y, two.y + 0.5f));
	float z = max(two.z - 0.5f, min(one.z, two.z + 0.5f));

	// this is the same as isPointInsideone
	float distance = sqrt((x - one.x) * (x - one.x) +
		(y - one.y) * (y - one.y) +
		(z - one.z) * (z - one.z));

	return distance < 0.1 * 0.5;

}

bool Tema2::CheckBulletEnemyCollision(Bullet3D sphere, Enemy3 box) {

	if (!box.alive) {
		return false;
	}

	float x = max(box.enemyCoords.x - box.ratio + 0.15f, min(sphere.x, box.enemyCoords.x + box.ratio - 0.15f));
	float y = max(box.enemyCoords.y - box.ratio + 0.15f, min(sphere.y, box.enemyCoords.y + box.ratio - 0.15f));
	float z = max(box.enemyCoords.z - box.ratio + 0.15f, min(sphere.z, box.enemyCoords.z + box.ratio - 0.15f));

	// this is the same as isPointInsideSphere
	float distance = sqrt((x - sphere.x) * (x - sphere.x) +
		(y - sphere.y) * (y - sphere.y) +
		(z - sphere.z) * (z - sphere.z));

	return distance < 0.1 * 0.4;

}

bool Tema2::CheckAllPlayerObstacleCollisions(glm::vec3 one, std::vector<Obstacle> obstacles) {
	for (int i = 0; i < obstacles.size(); i++) {
		if (CheckPlayerObstacleCollision(one, obstacles[i]))
			return true;
	}
	return false;
}

void Tema2::OnInputUpdate(float deltaTime, int mods)
{
	// move the camera only if MOUSE_RIGHT button is 
	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT) && thirdPerson && !GAMEOVER)
	{
		float cameraSpeed = 2.0f;

		if (window->KeyHold(GLFW_KEY_W)) {
			camera->MoveForward(cameraSpeed * deltaTime);

			glm::vec3 ipoteticPoz = camera->GetTargetPosition();

			if (CheckAllPlayerObstacleCollisions(ipoteticPoz, obstacles)) {
				camera->MoveForward(-cameraSpeed * deltaTime);
			}
		}

		if (window->KeyHold(GLFW_KEY_A)) {
			camera->TranslateRight(-cameraSpeed * deltaTime);

			glm::vec3 ipoteticPoz = camera->GetTargetPosition();

			if (CheckAllPlayerObstacleCollisions(ipoteticPoz, obstacles)) {
				camera->TranslateRight(cameraSpeed * deltaTime);
			}
		}

		if (window->KeyHold(GLFW_KEY_S)) {
			camera->MoveForward(-cameraSpeed * deltaTime);

			glm::vec3 ipoteticPoz = camera->GetTargetPosition();

			if (CheckAllPlayerObstacleCollisions(ipoteticPoz, obstacles)) {
				camera->MoveForward(cameraSpeed * deltaTime);
			}

		}

		if (window->KeyHold(GLFW_KEY_D)) {
			camera->TranslateRight(cameraSpeed * deltaTime);

			glm::vec3 ipoteticPoz = camera->GetTargetPosition();

			if (CheckAllPlayerObstacleCollisions(ipoteticPoz, obstacles)) {
				camera->TranslateRight(-cameraSpeed * deltaTime);
			}
		}

		if (window->KeyHold(GLFW_KEY_Q)) {
			camera->TranslateUpward(-cameraSpeed * deltaTime);

		}

		if (window->KeyHold(GLFW_KEY_E)) {
			camera->TranslateUpward(cameraSpeed * deltaTime);
		}


	}
	player.playerPoz = camera->GetTargetPosition();




	// TODO(student): Change projection parameters. Declare any extra
	// variables you might need in the class header. Inspect this file
	// for any hardcoded projection arguments (can you find any?) and
	// replace them with those extra variables.
	if (window->KeyHold(GLFW_KEY_X)) {
		fov += RADIANS(deltaTime * 20.f);
	}

	if (window->KeyHold(GLFW_KEY_Z)) {
		fov -= RADIANS(deltaTime * 20.f);
	}

	if (window->KeyHold(GLFW_KEY_C)) {
		deltaOrtho -= deltaTime * 10.f;
	}

	if (window->KeyHold(GLFW_KEY_V)) {
		deltaOrtho += deltaTime * 10.f;
	}
}


void Tema2::OnKeyPress(int key, int mods)
{

	// direction = forward
	// y = 0 la forward pt linie dreapta

	if (window->KeyHold(GLFW_KEY_SPACE)) {

		// intru in first person
		if (thirdPerson) {
			thirdPerson = 0;

			// salvez camera
			cameraPoz = camera->position;
			saved_forward = camera->forward;
			saved_up = camera->up;
			saved_right = camera->right;

			camera->position = player.playerPoz;
			camera->distanceToTarget = 0.5;
		}
		//ies din first person
		else {
			thirdPerson = 1;
			camera->position = cameraPoz;
			camera->forward = saved_forward;
			camera->up = saved_up;
			camera->right = saved_right;
			camera->distanceToTarget = 2.5;
		}
	}

	// Add key press event
	if (key == GLFW_KEY_T)
	{
		renderCameraTarget = !renderCameraTarget;
	}
	// TODO(student): Switch projections

	if (key == GLFW_KEY_P) {
		perspective = true;
	}

	if (key == GLFW_KEY_O) {
		perspective = false;
	}

}


void Tema2::OnKeyRelease(int key, int mods)
{
	// Add key release event
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// Add mouse move event

	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float sensivityOX = 0.001f;
		float sensivityOY = 0.001f;

		{
			renderCameraTarget = true;

			if (thirdPerson == 1) {
				camera->RotateThirdPerson_OX(-deltaY * sensivityOY);
				camera->RotateThirdPerson_OY(-deltaX * sensivityOX);
			}
			else {
				camera->RotateFirstPerson_OX(-deltaY * sensivityOY);
				camera->RotateFirstPerson_OY(-deltaX * sensivityOX);
			}
		}



	}
}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	if (!thirdPerson) {
		Bullet3D newBullet;

		newBullet.dirVecOfBullet = camera->forward;
		newBullet.transX = camera->GetTargetPosition().x;
		newBullet.transY = camera->GetTargetPosition().y;
		newBullet.transZ = camera->GetTargetPosition().z;
		newBullet.TTL = 1.0f;

		bullets.push_back(newBullet);
	}
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// Add mouse button release event
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema2::OnWindowResize(int width, int height)
{
}
