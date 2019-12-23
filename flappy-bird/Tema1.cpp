#include "Tema1.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Transform2D.h"


using namespace std;

Tema1::Tema1()
{
}

Tema1::~Tema1()
{
}


Mesh* Tema1::CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned short>& indices)
{
	unsigned int VAO = 0;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO = 0;
	GLuint VBO_ID;
	glGenBuffers(1, &VBO_ID);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_ID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	unsigned int IBO = 0;

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));

	glBindVertexArray(0);

	CheckOpenGLError();

	meshes[name] = new Mesh(name);
	meshes[name]->InitFromBuffer(VAO, static_cast<unsigned short>(indices.size()));
	return meshes[name];
}

//se creaza cerc
Mesh* Tema1::CreateCircle(std::string name, glm::vec3 leftBottomCorner, float radius, glm::vec3 color, bool fill)
{
	float angle = M_PI / 100;

	glm::vec3 corner = leftBottomCorner;
	vector<VertexFormat> vertices = {
		VertexFormat(corner + glm::vec3(0, 0, 0), color),
		VertexFormat(corner + glm::vec3(radius, 0, 0), color),
	};
	vector<unsigned short> indices = {};

	for (int i = 1; i <= 202; i++) {
		float newX = radius * sin(angle * i);
		float newY = radius * cos(angle * i);
		vertices.push_back(VertexFormat(corner + glm::vec3(newX, newY, 0), color));
		indices.push_back(0);
		indices.push_back(i);
		indices.push_back(i + 1);
	}
	Mesh* circle = new Mesh(name);
	circle->InitFromData(vertices, indices);
	return circle;
}

void Tema1::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);
	glm::vec3 vect = glm::vec3((float)resolution.x, (float)resolution.y,0);
	glm::vec3 corner = glm::vec3(0, 0, 0);
	float squareSide = 100;
	

	//stalactite stalacmite 
	vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(  0,   0,  0), glm::vec3(0, 0.75f, 0)),   
		VertexFormat(glm::vec3(100,   0,  0), glm::vec3(0, 0.75f, 0)),
		VertexFormat(glm::vec3(100, 100,  0), glm::vec3(0, 0.75f, 0)),
		VertexFormat(glm::vec3(  0, 100,  0), glm::vec3(0, 0.75f, 0)),

		VertexFormat(glm::vec3(  0,   0,  0), glm::vec3(0, 0.85f, 0)),
		VertexFormat(glm::vec3(  0, 100,  0), glm::vec3(0, 0.85f, 0)),
		VertexFormat(glm::vec3( 10,   0,  0), glm::vec3(0, 0.85f, 0)),
		VertexFormat(glm::vec3( 10, 100,  0), glm::vec3(0, 0.85f, 0)),

		VertexFormat(glm::vec3(100, 100,  0), glm::vec3(0, 0.65f, 0)),
		VertexFormat(glm::vec3( 90, 100,  0), glm::vec3(0, 0.65f, 0)),
		VertexFormat(glm::vec3( 90,   0,  0), glm::vec3(0, 0.65f, 0)),
		VertexFormat(glm::vec3(100,   0,  0), glm::vec3(0, 0.65f, 0)),

		VertexFormat(glm::vec3(-10, 100,  0), glm::vec3(0, 0.75f, 0)),
		VertexFormat(glm::vec3(-10, 110,  0), glm::vec3(0, 0.75f, 0)),
		VertexFormat(glm::vec3(110, 110,  0), glm::vec3(0, 0.75f, 0)),
		VertexFormat(glm::vec3(110, 100,  0), glm::vec3(0, 0.75f, 0)),

		VertexFormat(glm::vec3( -10,  0,  0), glm::vec3(0, 0.75f, 0)),
		VertexFormat(glm::vec3( -10,-10,  0), glm::vec3(0, 0.75f, 0)),
		VertexFormat(glm::vec3(110,   0,  0), glm::vec3(0, 0.75f, 0)),
		VertexFormat(glm::vec3(110, -10,  0), glm::vec3(0, 0.75f, 0)),

		VertexFormat(glm::vec3(-20,   0,  0), glm::vec3(0, 0.85f, 0)),
		VertexFormat(glm::vec3(-20, -10,  0), glm::vec3(0, 0.85f, 0)),
		VertexFormat(glm::vec3(-10,   0,  0), glm::vec3(0, 0.85f, 0)),
		VertexFormat(glm::vec3(-10, -10,  0), glm::vec3(0, 0.85f, 0)),

		VertexFormat(glm::vec3(110,   0,  0), glm::vec3(0, 0.65f, 0)),
		VertexFormat(glm::vec3(120,   0,  0), glm::vec3(0, 0.65f, 0)),
		VertexFormat(glm::vec3(110, -10,  0), glm::vec3(0, 0.65f, 0)),
		VertexFormat(glm::vec3(120, -10,  0), glm::vec3(0, 0.65f, 0)),

		VertexFormat(glm::vec3(-20, 110,  0), glm::vec3(0, 0.85f, 0)),
		VertexFormat(glm::vec3(-10, 110,  0), glm::vec3(0, 0.85f, 0)),
		VertexFormat(glm::vec3(-20, 100,  0), glm::vec3(0, 0.85f, 0)),
		VertexFormat(glm::vec3(-10, 100,  0), glm::vec3(0, 0.85f, 0)),


		VertexFormat(glm::vec3(120, 110,  0), glm::vec3(0, 0.65f, 0)),
		VertexFormat(glm::vec3(120, 100,  0), glm::vec3(0, 0.65f, 0)),
		VertexFormat(glm::vec3(110, 110,  0), glm::vec3(0, 0.65f, 0)),
		VertexFormat(glm::vec3(110, 100,  0), glm::vec3(0, 0.65f, 0)),

		VertexFormat(glm::vec3(-20, 100,  0), glm::vec3(0,0,0)),
		VertexFormat(glm::vec3(120, 100,  0), glm::vec3(0,0,0)),
		VertexFormat(glm::vec3(50, 100.5f,  0), glm::vec3(0,0,0)),

		VertexFormat(glm::vec3(-20,   0,  0), glm::vec3(0,0,0)),
		VertexFormat(glm::vec3(120,   0,  0), glm::vec3(0,0,0)),
		VertexFormat(glm::vec3(50, -0.5f,  0), glm::vec3(0,0,0)),

	};
	vector<unsigned short> indices 
	{
		39,40,41,
		36,37,38,

		32,33,34,
		33,34,35,

		28,29,30,
		29,30,31,

		24,25,26,
		25,26,27,

		20,21,22,
		23,22,21,

		12,13,14,
		14,15,12,

		16,17,18,
		18,17,19,


		4, 5, 6,
		6, 5, 7,

		8,9,10,
		10,11,8,

		0, 1, 2,
		2, 3, 0,

	};


	//pasare
	vector<VertexFormat> vertices_b
	{
		VertexFormat(glm::vec3( 4, -1,  0), glm::vec3(0, 1, 1)),  
		VertexFormat(glm::vec3( 0,  4,  0), glm::vec3(0, 0, 1)),  
		VertexFormat(glm::vec3( 8,  3,  0), glm::vec3(0, 1, 1)),  
		VertexFormat(glm::vec3( 5,  1,  0), glm::vec3(0, 1, 0)), 
		VertexFormat(glm::vec3(12, 14,  0), glm::vec3(1, 1, 1)), 
		VertexFormat(glm::vec3(19, 15,  0), glm::vec3(1, 0, 0)), 
		VertexFormat(glm::vec3(18, 19,  0), glm::vec3(1, 0, 0)), 
		VertexFormat(glm::vec3(26, 14,  0), glm::vec3(1, 0, 0)), 
		VertexFormat(glm::vec3(19,  9,  0), glm::vec3(0, 1, 1)), 
		VertexFormat(glm::vec3( 5,  1,  0), glm::vec3(1, 1, 1)), 
		VertexFormat(glm::vec3(20, 17,  0), glm::vec3(0, 0, 0)),
		VertexFormat(glm::vec3(20, 16,  0), glm::vec3(0, 0, 0)), 
		VertexFormat(glm::vec3(21, 16,  0), glm::vec3(0, 0, 0)), 
		VertexFormat(glm::vec3( 9,  7,  0), glm::vec3(0, 1, 0)), 
		VertexFormat(glm::vec3(16, 15,  0), glm::vec3(1, 0, 0)),
		VertexFormat(glm::vec3( 2, 21,  0), glm::vec3(1, 0, 1)),
		

	};
	vector<unsigned short> indices_b =
	{

		10,11,12,
		13,14,15,
		6, 5, 7,
		4, 6, 7,
		5, 8, 9,
		0, 1, 2,
		3, 4, 5,




	};

	//pasarea cu aripile in jos
	vector<VertexFormat> vertices_b2
	{
		VertexFormat(glm::vec3( 4, -1,  0), glm::vec3(0, 1, 1)),  
		VertexFormat(glm::vec3( 0,  4,  0), glm::vec3(0, 0, 1)), 
		VertexFormat(glm::vec3( 8,  3,  0), glm::vec3(0, 1, 1)),  
		VertexFormat(glm::vec3( 5,  1,  0), glm::vec3(0, 1, 0)), 
		VertexFormat(glm::vec3(12, 14,  0), glm::vec3(1, 1, 1)), 
		VertexFormat(glm::vec3(19, 15,  0), glm::vec3(1, 0, 0)), 
		VertexFormat(glm::vec3(18, 19,  0), glm::vec3(1, 0, 0)),
		VertexFormat(glm::vec3(26, 14,  0), glm::vec3(1, 0, 0)), 
		VertexFormat(glm::vec3(19,  9,  0), glm::vec3(0, 1, 1)),
		VertexFormat(glm::vec3( 5,  1,  0), glm::vec3(1, 1, 1)), 
		VertexFormat(glm::vec3(20, 17,  0), glm::vec3(0, 0, 0)),
		VertexFormat(glm::vec3(20, 16,  0), glm::vec3(0, 0, 0)), 
		VertexFormat(glm::vec3(21, 16,  0), glm::vec3(0, 0, 0)), 
		VertexFormat(glm::vec3( 9,  7,  0), glm::vec3(0, 1, 0)), 
		VertexFormat(glm::vec3(16, 15,  0), glm::vec3(1, 0, 0)),
		VertexFormat(glm::vec3(25, -2,  0), glm::vec3(1, 0, 1)),


	};
	vector<unsigned short> indices_b2 =
	{
		10,11,12,
		13,14,15,
		6, 5, 7,
		4, 6, 7,
		5, 8, 9,
		0, 1, 2,
		3, 4, 5,
	};

	//pamant
	vector<VertexFormat> vertices_p1
	{
		VertexFormat(glm::vec3(   0,  0,  0), glm::vec3(0.6f, 0.4f, 0)),    
		VertexFormat(glm::vec3(2000, 50,  0), glm::vec3(0.6f, 0.4f, 0)),   
		VertexFormat(glm::vec3(   0, 50,  0), glm::vec3(0.6f, 0.4f, 0)),  
		VertexFormat(glm::vec3(2000,  0,  0), glm::vec3(0.6f, 0.4f, 0)),
	};
	vector<unsigned short> indices_p1 =
	{
		0, 1, 2,
		1, 0, 3,
	};

	//iarba
	vector<VertexFormat> vertices_p2
	{
		VertexFormat(glm::vec3(   0,  50,  0), glm::vec3(0, 0.9f, 0)), 
		VertexFormat(glm::vec3(2000, 100,  0), glm::vec3(0, 0.9f, 0)),   
		VertexFormat(glm::vec3(   0, 100,  0), glm::vec3(0, 0.9f, 0)),   
		VertexFormat(glm::vec3(2000, 50,   0), glm::vec3(0, 0.9f, 0)),  
	};
	vector<unsigned short> indices_p2 =
	{
		0, 1, 2,
		1, 0, 3,
	};

	//munti josi
	vector<VertexFormat> vertices_p3
	{
		VertexFormat(glm::vec3(  0, 100,  0), glm::vec3(0.67f, 0.7f, 0.1f)),  
		VertexFormat(glm::vec3(300, 100,  0), glm::vec3(0.67f, 0.7f, 0.1f)),
		VertexFormat(glm::vec3(150, 300,  0), glm::vec3(0.67f, 0.7f, 0.1f)),
	};
	vector<unsigned short> indices_p3 =
	{
		0, 1, 2,
	};

	//munti inalti
	vector<VertexFormat> vertices_p4
	{
		VertexFormat(glm::vec3(-50, 100,  0), glm::vec3(0.97f, 1, 0.3f)),
		VertexFormat(glm::vec3(450, 100,  0), glm::vec3(0.97f, 1, 0.3f)),
		VertexFormat(glm::vec3(200, 600,  0), glm::vec3(0.97f, 1, 0.3f)),
	};
	vector<unsigned short> indices_p4 =
	{
		0, 1, 2,
	};


	float cx = corner.x + squareSide / 2;
	float cy = corner.y + squareSide / 2;

	translateX = 0;
	translateY = 0;

	scaleX = 1;
	scaleY = 1;

	angularStep = 0;

	Rand[0] = (rand() % 4) +1;
	Rand[1] = (rand() % 4) + 1;
	Rand[2] = (rand() % 4) + 1;
	Rand[3] = (rand() % 4) + 1;
	Rand[4] = (rand() % 4) + 1;
	Rand[5] = (rand() % 4) + 1;

	RandC[0] = 6 - Rand[0];
	RandC[1] = 6 - Rand[1];
	RandC[2] = 6 - Rand[2];
	RandC[3] = 6 - Rand[3];
	RandC[4] = 6 - Rand[4];
	RandC[5] = 6 - Rand[5];

	Mesh* p1 = CreateMesh("p1", vertices_p1, indices_p1);
	Mesh* p2 = CreateMesh("p2", vertices_p2, indices_p2);
	Mesh* p3 = CreateMesh("p3", vertices_p3, indices_p3);
	Mesh* p4 = CreateMesh("p4", vertices_p4, indices_p4);

	Mesh* square1 = CreateMesh("square1", vertices, indices);

	Mesh* bird = CreateMesh("bird", vertices_b, indices_b);
	Mesh* bird2 = CreateMesh("bird2", vertices_b2, indices_b2);
	Mesh* circle = CreateCircle("circle", glm::vec3(100, 600, 0), 100.3f, glm::vec3(1, 1, 1),true);
	AddMeshToList(circle);
	Mesh* circle2 = CreateCircle("circle2", glm::vec3(200, 600, 0), 5.3f, glm::vec3(0.96f, 0.97f,0.72f), true);
	AddMeshToList(circle2);

}

void Tema1::FrameStart()
{
	glClearColor(0,0, 0.55f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	glViewport(0, 0, resolution.x, resolution.y);
}
void Tema1::Update(float deltaTimeSeconds)
{
	//in miscare
	if (start == 1) {

		//Viteza stalactitelor si stalagmitelor
		if(x<12)
			x += 0.0002f;

		distance[0] -= (deltaTimeSeconds * 200 + x);
		distance[1] -= (deltaTimeSeconds * 200 + x);
		distance[2] -= (deltaTimeSeconds * 200 + x);
		distance[3] -= (deltaTimeSeconds * 200 + x);
		distance[4] -= (deltaTimeSeconds * 200 + x);
		distance[5] -= (deltaTimeSeconds * 200 + x);
		Time = deltaTimeSeconds;
		acceleration += 0.2f;
		if (zboara < 0)
			gravity -= (4 + acceleration);
		else
			gravity += 8;
		zboara -= 0.7;


		//Collision
	
		if ((400 + gravity <= 0) || (400+gravity>700))
			start = 2;

		if (110 < distance2[0] + distance[0] + 100 &&
			100 + 75 > distance2[0] + distance[0] &&
			400+gravity < 50 - (RandC[0] * 75) + 450 &&
			51 + 400+gravity> 50 - (RandC[0] * 75)) {
			start = 2;
		}
		if (110 < distance2[1] + distance[1] + 100 &&
			100 + 75 > distance2[1] + distance[1] &&
			400 + gravity < 50 - (RandC[1] * 75) + 450 &&
			51 + 400+gravity> 50 - (RandC[1] * 75)) {
			start = 2;
		}
		if (110 < distance2[2] + distance[2] + 100 &&
			100 + 75 > distance2[2] + distance[2] &&
			400 + gravity < 50 - (RandC[2] * 75) + 450 &&
			51 + 400+gravity> 50 - (RandC[2] * 75)) {
			start = 2;
		}
		if (110 < distance2[3] + distance[3] + 100 &&
			100 + 75 > distance2[3] + distance[3] &&
			400 + gravity < 50 - (RandC[3] * 75) + 450 &&
			51 + 400> 50 - (RandC[0] * 75)) {
			start = 2;
		}

		if (110 < distance2[0] + distance[0] + 100 &&
			100 + 75 > distance2[0] + distance[0] &&
			400 + gravity <780 - (RandC[0] * 75) + 400 &&
			51 + 400+gravity> 800 - (RandC[0] * 75)) {
			start = 2;
		}
		if (110 < distance2[1] + distance[1] + 100 &&
			100 + 75 > distance2[1] + distance[1] &&
			400 + gravity < 780 - (RandC[1] * 75) + 400 &&
			51 + 400+gravity> 800 - (RandC[1] * 75)) {
			start = 2;
		}
		if (110 < distance2[2] + distance[2] + 100 &&
			100 + 75 > distance2[2] + distance[2] &&
			400 + gravity < 780 - (RandC[2] * 75) + 400 &&
			51 + 400+gravity> 800 - (RandC[2] * 75)) {
			start = 2;
		}
		if (110 < distance2[3] + distance[3] + 100 &&
			100 + 75 > distance2[3] + distance[3] &&
			400 + gravity < 780 - (RandC[3] * 75) + 400 &&
			51 + 400+gravity>800 - (RandC[3] * 75)) {
			start = 2;
		}

		//stalactitele si stalagmitele
		modelMatrix = glm::mat3(1);
		if (distance2[0] + distance[0] < -150) {
			distance2[0] = 1850;
			distance[0] = 0;
			Rand[0] = (rand() % 4) + 1;
			RandC[0] = 6 - Rand[0];
			score++;
			printf("Scorul este: %d\n", score);

		}
		modelMatrix *= Transform2D::Translate(distance2[0] + distance[0], 50 - (RandC[0] * 75));
		modelMatrix *= Transform2D::Scale(1, 4);
		RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		if (distance2[1] + distance[1] < -150) {
			distance2[1] = 1850;
			distance[1] = 0;
			Rand[1] = (rand() % 4) + 1;
			RandC[1] = 6 - Rand[1];
			score++;
			printf("Scorul este: %d\n", score);

		}
		modelMatrix *= Transform2D::Translate(distance2[1] + distance[1], 50 - (RandC[1] * 75));
		modelMatrix *= Transform2D::Scale(1, 4);
		RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		if (distance2[2] + distance[2] < -150) {
			distance2[2] = 1850;
			distance[2] = 0;
			Rand[2] = (rand() % 4) + 1;
			RandC[2] = 6 - Rand[2];
			score++;
			printf("Scorul este: %d\n", score);
		}
		modelMatrix *= Transform2D::Translate(distance2[2] + distance[2], 50 - (RandC[2] * 75));
		modelMatrix *= Transform2D::Scale(1, 4);
		RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		if (distance2[3] + distance[3] < -150) {
			distance2[3] = 1850;
			distance[3] = 0;
			Rand[3] = (rand() % 4) + 1;
			RandC[3] = 6 - Rand[3];
			score++;
			printf("Scorul este: %d\n", score);
		}
		modelMatrix *= Transform2D::Translate(distance2[3] + distance[3], 50 - (RandC[3] * 75));
		modelMatrix *= Transform2D::Scale(1, 4);
		RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);



		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(distance2[0] + distance[0], 800 - (RandC[0] * 75));
		modelMatrix *= Transform2D::Scale(1, 4);
		RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);


		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(distance2[1] + distance[1], 800 - (RandC[1] * 75));
		modelMatrix *= Transform2D::Scale(1, 4);
		RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);


		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(distance2[2] + distance[2], 800 - (RandC[2] * 75));
		modelMatrix *= Transform2D::Scale(1, 4);
		RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(distance2[3] + distance[3], 800 - (RandC[3] * 75));
		modelMatrix *= Transform2D::Scale(1, 4);
		RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

		zboara += acceleration * deltaTimeSeconds;


		//pasare
		modelMatrix = glm::mat3(1);


		modelMatrix *= Transform2D::Translate(100, 400 + gravity);
		if (zboara > 0) {
			modelMatrix *= Transform2D::Rotate(0.3f);
			rotation_angle = 0;
		}
		else
			if (rotation_angle > -2) {
				rotation_angle -= 0.05f;
				modelMatrix *= Transform2D::Rotate(rotation_angle);
			}
			else
				modelMatrix *= Transform2D::Rotate(rotation_angle);
		modelMatrix *= Transform2D::Scale(3, 3);
		modelMatrix *= Transform2D::Translate(-13, -10);
		if(zboara <0)
			RenderMesh2D(meshes["bird"], shaders["VertexColor"], modelMatrix);
		else
			RenderMesh2D(meshes["bird2"], shaders["VertexColor"], modelMatrix);


		//peisaj
		modelMatrix = glm::mat3(1);
		RenderMesh2D(meshes["p1"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		RenderMesh2D(meshes["p2"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		RenderMesh2D(meshes["p3"], shaders["VertexColor"], modelMatrix);
		RenderMesh2D(meshes["p3"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(250, 0);
		RenderMesh2D(meshes["p3"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(530, 0);
		RenderMesh2D(meshes["p3"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(670, 0);
		RenderMesh2D(meshes["p3"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(800, 0);
		RenderMesh2D(meshes["p3"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(1000, 0);
		RenderMesh2D(meshes["p3"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		RenderMesh2D(meshes["p4"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(250, 0);
		RenderMesh2D(meshes["p4"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(370, -50);
		RenderMesh2D(meshes["p4"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(500, 0);
		RenderMesh2D(meshes["p4"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(700, 0);
		RenderMesh2D(meshes["p4"], shaders["VertexColor"], modelMatrix);

		//luna
		modelMatrix = glm::mat3(1);
		RenderMesh2D(meshes["circle"], shaders["VertexColor"], modelMatrix);

		//stele
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(625, 100);
		RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(615, 65);
		RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(400, 50);
		RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(550, 110);
		RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(950, 94);
		RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(150, 45);
		RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(300, 73);
		RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(100, 45);
		RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(1110, 63);
		RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(900, 100);
		RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(880, 88);
		RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(746, 95);
		RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(-150, -162);
		RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(834, -10);
		RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(586, -30);
		RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(930, 7);
		RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(1005, -41);
		RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(83, -119);
		RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(883, -200);
		RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(953, -82);
		RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(983, -20);
		RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix);
	}

	//inceputul jocului 
	if(start == 0)
	{
		//stalactitele si stalagmitele
		modelMatrix = glm::mat3(1);
		if (distance2[0] + distance[0] < -150) {
			distance2[0] = 1850;
			distance[0] = 0;
			Rand[0] = (rand() % 4) + 1;
			RandC[0] = 6 - Rand[0];
		}
		modelMatrix *= Transform2D::Translate(distance3[0], 50 - (RandC[0] * 75));
		modelMatrix *= Transform2D::Scale(1, 4);
		RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		if (distance2[1] + distance[1] < -150) {
			distance2[1] = 1850;
			distance[1] = 0;
			Rand[1] = (rand() % 4) + 1;
			RandC[1] = 6 - Rand[1];

		}
		modelMatrix *= Transform2D::Translate(distance3[1], 50 - (RandC[1] * 75));
		modelMatrix *= Transform2D::Scale(1, 4);
		RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);


		modelMatrix = glm::mat3(1);
		if (distance2[2] + distance[2] < -150) {
			distance2[2] = 1850;
			distance[2] = 0;
			Rand[2] = (rand() % 4) + 1;
			RandC[2] = 6 - Rand[2];
		}
		modelMatrix *= Transform2D::Translate(distance3[2], 50 - (RandC[2] * 75));
		modelMatrix *= Transform2D::Scale(1, 4);
		RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);
		

		modelMatrix = glm::mat3(1);
		if (distance2[3] + distance[3] < -150) {
			distance2[3] = 1850;
			distance[3] = 0;
			Rand[3] = (rand() % 4) + 1;
			RandC[3] = 6 - Rand[3];
		}
		modelMatrix *= Transform2D::Translate(distance3[3], 50 - (RandC[3] * 75));
		modelMatrix *= Transform2D::Scale(1, 4);
		RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);


		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(distance3[0], 800 - (RandC[0] * 75));
		modelMatrix *= Transform2D::Scale(1, 4);
		RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);


		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(distance3[1], 800 - (RandC[1] * 75));
		modelMatrix *= Transform2D::Scale(1, 4);
		RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);


		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(distance3[2], 800 - (RandC[2] * 75));
		modelMatrix *= Transform2D::Scale(1, 4);
		RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);


		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(distance3[3], 800 - (RandC[3] * 75));
		modelMatrix *= Transform2D::Scale(1, 4);
		RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);


		zboara += acceleration * deltaTimeSeconds;


		//pasare
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(100, 400);
		modelMatrix *= Transform2D::Scale(3, 3);
		modelMatrix *= Transform2D::Translate(-13, -10);
		RenderMesh2D(meshes["bird"], shaders["VertexColor"], modelMatrix);

		//peisaj
		modelMatrix = glm::mat3(1);
		RenderMesh2D(meshes["p1"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		RenderMesh2D(meshes["p2"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		RenderMesh2D(meshes["p3"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(250, 0);
		RenderMesh2D(meshes["p3"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(530, 0);
		RenderMesh2D(meshes["p3"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(670, 0);
		RenderMesh2D(meshes["p3"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(800, 0);
		RenderMesh2D(meshes["p3"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(1000, 0);
		RenderMesh2D(meshes["p3"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		RenderMesh2D(meshes["p4"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(250, 0);
		RenderMesh2D(meshes["p4"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(370, -50);
		RenderMesh2D(meshes["p4"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(500, 0);
		RenderMesh2D(meshes["p4"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(700, 0);
		RenderMesh2D(meshes["p4"], shaders["VertexColor"], modelMatrix);

		//luna
		modelMatrix = glm::mat3(1);
		RenderMesh2D(meshes["circle"], shaders["VertexColor"], modelMatrix);

		//stele
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(625, 100);
		RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(615, 65);
		RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(400, 50);
		RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(550, 110);
		RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(950, 94);
		RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(150, 45);
		RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(300, 73);
		RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(100,45 );
		RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(1110, 63);
		RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(900, 100);
		RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(880, 88);
		RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(746, 95);
		RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(-150, -162);
		RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(834, -10);
		RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(586, -30);
		RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(930, 7);
		RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(1005, -41);
		RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(83, -119);
		RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(883, -200);
		RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(953, -82);
		RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(983, -20);
		RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix);

		for (int i = 0; i < 5; i++)
		{
			distance[i] = 0;
			distance2[i] = distance3[i];
		}
		x = 0;
		zboara = 0;
		gravity = 0;
		acceleration = 0;

	}

	//Game over
	if (start == 2)
	{
		modelMatrix *= Transform2D::Translate(100, 600);
		modelMatrix *= Transform2D::Scale(4, 4);
		modelMatrix *= Transform2D::Translate(-13, -10);
		RenderMesh2D(meshes["bird"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(400, -850);
		modelMatrix *= Transform2D::Scale(2, 2);
		RenderMesh2D(meshes["circle"], shaders["VertexColor"], modelMatrix);
	}

}

void Tema1::FrameEnd()
{
}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}

void Tema1::OnKeyPress(int key, int mods)
{
	if (key == GLFW_KEY_SPACE)
	{
		if(start ==0)
			start = 1;
		acceleration = 0.0f;
		zboara = 10;
	}
	if (key == GLFW_KEY_R)
	{
		score = 0;
		start = 0;
	}
}

void Tema1::OnKeyRelease(int key, int mods)
{
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}
