#include "core.h"
#include <iostream>
#include <vector>

struct Vector2
{
	float x, y;

	Vector2() : x{ 0 }, y{ 0 } {}
	Vector2(float x, float y) : x{ x }, y{ y } {}
};

Vector2 position;
std::vector<Vector2> points = { {0,0}, {10,0}, {5,10}, {0,0} };

bool Update(float dt)
{
	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	int x, y;
	Core::Input::GetMousePos(x, y);
	position.x = static_cast<float>(x);
	position.y = static_cast<float>(y);

	return quit;
}

void Draw(Core::Graphics& graphics)
{
	/*graphics.SetColor(RGB(255, 255, 255));*/
	for (int i = 0; i < 20; i++) {
		graphics.SetColor(RGB(rand() % 256 , rand() % 256 , rand() % 256 ));
		//graphics.DrawLine(static_cast<float>(rand() % 800), static_cast<float>(rand() % 600), static_cast<float>(rand() % 800), static_cast<float>(rand() % 600));
	}
	
	graphics.SetColor(RGB(255, 255, 255));
	//graphics.DrawLine(0, 0, position.x, position.y);

	for (size_t i = 0; i < points.size() - 1; i++) {
		graphics.DrawLine(points[i].x, points[i].y, points[i+1].x, points[i + 1].y);

	}
}

int main()
{
	char name[] = "CSC196";
	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();
}
