#pragma once

#include "components/simple_scene.h"
#include "lab_m1/tema2/lab_camera.h"
#include <vector>




namespace m1
{

	class Tema2 : public gfxc::SimpleScene
	{
	public:
		Tema2();
		~Tema2();
		int xPlayer = 0;
		int yPlayer = -1;
		int zPlayer = 0;

		void Init() override;

	private:
		typedef struct Bullet3D {
			float x;
			float y;
			float z;

			float transX;
			float transY;
			float transZ;

			glm::vec3 dirVecOfBullet = glm::vec3(0, 0, 1);

			glm::vec3 vecPosition = glm::vec3(0, 0, 0);

			float angle;

			float TTL = 0;

			float size = 0.99f;

		}Bullet3D;

		typedef struct Enemy3 {
			char dir = 'a';
			float ratio = 0.33333f;
			glm::vec3 floorCoords;
			glm::vec3 startCoords;

			glm::vec3 enemyCoords;

			float lim_b_x;
			float lim_b_z;

			float lim_c_x;
			float lim_c_z;

			float lim_d_x;
			float lim_d_z;

			float lim_e_x;
			float lim_e_z;

			bool alive;

			float TTL = 0.0f;
		}Enemy3;

		typedef struct Obstacle {
			int x;
			int y;
			int z;
		}Obstacle;

		typedef struct Player3D {
			int health = 100;
			int score = 0;
			float time = 100;
			glm::vec3 playerPoz = glm::vec3(1, 0, 1);
		}Player3D;

		typedef struct Finish {
			int x;
			int y;
			int z;
		}Finish;

		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix) override;

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

		void getEnemies(std::vector<Enemy3>* enemies);
		Enemy3 createEnemy(int x, int z);
		void CreatePlayerMesh();
		void Tema2::CreateEnemyMesh();
		glm::vec3 Tema2::GetInitialCameraPoz(glm::vec3* randPoz, glm::vec3* adjacentPoz);
		void CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices);
		bool Tema2::CheckAllPlayerObstacleCollisions(glm::vec3 one, std::vector<Obstacle> obstacles);
		bool CheckPlayerObstacleCollision(glm::vec3 one, Obstacle two);
		bool Tema2::CheckPlayerEnemyCollision(glm::vec3 one, Enemy3 two);
		bool Tema2::CheckBulletEnemyCollision(Bullet3D sphere, Enemy3 box);
		bool Tema2::CheckBulletObstacleCollision(glm::vec3 one, Obstacle two);
		bool Tema2::CheckPlayerFinishCollision(glm::vec3 one, Finish two);
		void Tema2::GenerateRandomMap();


	protected:

		// third
		implemented::Camera2* camera = new implemented::Camera2();
		glm::mat4 projectionMatrix;

		bool renderCameraTarget;

		// TODO(student): If you need any other class variables, define them here.
		float fov;
		float near, far;
		float left, right, znear, zfar;
		float bottom, top;

		float deltaOrtho;
		bool perspective = true;

		int mapSize = 10;

		int map0[10][10] = {
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
			{1, 1, 0, 0, 0, 0, 1, 1, 0, 1},
			{1, 0, 0, 1, 1, 0, 1, 0, 0, 1},
			{1, 1, 0, 1, 0, 0, 1, 0, 1, 1},
			{1, 1, 0, 1, 0, 0, 0, 0, 1, 1},
			{1, 1, 0, 1, 1, 1, 1, 0, 0, 1},
			{1, 0, 0, 1, 1, 1, 1, 1, 0, 1},
			{1, 1, 0, 1, 0, 0, 0, 0, 0, 1},
			{2, 0, 0, 0, 1, 1, 1, 1, 1, 1},
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
		};

		int map1[10][10] = {
			{1, 1, 1, 1, 1, 1, 1, 1, 2, 1},
			{1, 0, 0, 1, 0, 0, 0, 0, 0, 1},
			{1, 0, 0, 1, 0, 1, 0, 1, 1, 1},
			{1, 0, 1, 0, 0, 1, 0, 0, 0, 1},
			{1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
			{1, 0, 1, 1, 1, 1, 0, 0, 0, 1},
			{1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
			{1, 1, 0, 1, 1, 0, 1, 0, 0, 1},
			{1, 0, 0, 0, 1, 0, 1, 0, 0, 1},
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
		};

		int map2[10][10] = {
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
			{1, 1, 1, 0, 0, 0, 1, 1, 1, 1},
			{1, 0, 1, 0, 1, 0, 0, 0, 0, 1},
			{2, 0, 0, 0, 1, 0, 0, 1, 1, 1},
			{1, 0, 1, 1, 0, 0, 0, 0, 1, 1},
			{1, 0, 1, 0, 1, 0, 1, 0, 1, 1},
			{1, 0, 1, 0, 1, 0, 0, 1, 0, 1},
			{1, 0, 0, 0, 0, 0, 1, 1, 0, 1},
			{1, 1, 0, 1, 1, 0, 0, 0, 0, 1},
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
		};

		int map3[10][10] = {
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
			{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
			{1, 0, 1, 1, 1, 0, 1, 1, 0, 1},
			{1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
			{1, 0, 0, 1, 1, 1, 0, 1, 1, 1},
			{1, 1, 0, 1, 0, 0, 0, 1, 0, 1},
			{1, 0, 0, 1, 0, 1, 0, 1, 0, 1},
			{1, 1, 0, 1, 0, 1, 0, 0, 0, 1},
			{1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
			{1, 1, 1, 1, 1, 1, 1, 1, 2, 1}
		};

		int map4[10][10] = {
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
			{1, 1, 0, 0, 0, 0, 1, 1, 0, 1},
			{1, 0, 0, 1, 1, 0, 1, 0, 0, 1},
			{1, 1, 0, 1, 0, 0, 1, 0, 1, 1},
			{1, 1, 0, 1, 0, 0, 0, 0, 1, 1},
			{1, 1, 0, 0, 1, 1, 1, 0, 0, 1},
			{1, 0, 0, 1, 1, 0, 1, 1, 0, 1},
			{1, 1, 0, 1, 0, 0, 0, 0, 0, 1},
			{2, 0, 0, 0, 1, 1, 1, 0, 0, 1},
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
		};



		int map[10][10] = {
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			{2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
		};

		float deltahX = 0.f;
		float deltahY = 0.f;



		float rotateAngle = 90.0f;
		float direction = 0;

		int thirdPerson = 1;


		glm::vec3 cameraPoz = glm::vec3(0);

		glm::vec3 saved_forward;
		glm::vec3 saved_up;
		glm::vec3 saved_right;

		std::vector<Bullet3D> bullets;
		std::vector<Enemy3> enemies;
		std::vector<Obstacle> obstacles;

		Player3D player;

		Finish finishBlock;

		bool GAMEOVER = false;
	};
}
