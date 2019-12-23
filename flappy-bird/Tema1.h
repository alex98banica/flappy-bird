#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>

class Tema1 : public SimpleScene
{
	public:
		Tema1();
		~Tema1();

		void Init() override;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;
		Mesh* CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned short>& indices);
		Mesh* CreateCircle(std::string name, glm::vec3 leftBottomCorner, float radius, glm::vec3 color, bool fill);

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

	protected:
		glm::mat3 modelMatrix;
		float translateX, translateY;
		float scaleX, scaleY;
		float angularStep;
		float distance[30] = { 0,0,0,0,0,0,0,0 };
		float distance2[30] = { 1000,1500,2000,2500,3000,3500,4000,4500,5000,5500};
		float distance3[30] = { 1000,1500,2000,2500,3000,3500,4000,4500,5000,5500 };
		float Rand[6];
		float RandC[6];
		float acceleration, gravity = 0 , zboara=0;
		float Time;
		int start = 0;
		float rotation_angle = 0;
		float x = 0;
		int score = 0;


};
