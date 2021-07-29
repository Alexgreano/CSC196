#include "Game.h"
#include <variant>

//nc::Engine engine;
//nc::Scene scene;

Game game;

bool Update(float dt){
	/*deltaTime = dt;
	gameTime += deltaTime;*/


	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	//timer += dt * 2;

	//if (Core::Input::IsPressed(Core::Input::BUTTON_LEFT)) {
	//	//int x, y;
	//	//Core::Input::GetMousePos(x, y);
	//	//psPosition.x = static_cast<float>(x);
	//	//psPosition.y = static_cast<float>(y);

	//	//std::vector<nc::Color> colors = { nc::Color::white, nc::Color::red, nc::Color::green, nc::Color::blue, nc::Color::orange, nc::Color::purple, nc::Color::cyan, nc::Color::yelllow };
	//	////engine.Get<nc::ParticleSystem>()->Create(psPosition, 200, 2, colors[nc::RandomRangeInt(0, colors.size())], 150);
	//	//engine.Get<nc::AudioSystem>()->PlayAudio("explosion");
	//}
	game.Update(dt);

	nc::Vector2 input;

	//scene.GetActor<Player>()->shape->color = nc::Color{nc::Random(), nc::Random(), nc::Random() };
	//scene.GetActor<Enemy>()->shape->color = nc::Color{nc::Random(), nc::Random(), nc::Random() };
	
	/*scene.Update(dt);
	engine.Update(dt);*/


	return quit;
}

void Draw(Core::Graphics& graphics)
{
	game.Draw(graphics);
}

union Data {
	int i;
	char str[5];
	bool b;
};

int main(){
	Data data = { 0 };
	data.b = true;
	data.i = 534;
	data.str[0] = '#';

	std::cout << data.i << std::endl;
	std::cout << data.b << std::endl;
	std::cout << data.str << std::endl;

	std::variant<int, std::string, float, bool>var;
	var = 20;
	var = true;
	
	//std::cout << std::get<int>(var) << std::endl;
	/*for (int i = 0; i < var._Storage; i++) {

	}*/
	std::cout << std::get<bool>(var) << std::endl;
	std::cout << std::get<3>(var) << std::endl;

	/*int (*operation)(int);
	operation = &dec;

	std::cout << operation(7) << std::endl;*/

	//system("pause");

	srand(123);
	std::cout << RAND_MAX << std::endl;
	for (size_t i = 0; i < 5; i++) {
		int r = rand();
		std::cout << r << "" << r / static_cast<float>(RAND_MAX) << std::endl;
	}

	nc::Random();

	char name[] = "CSC196";
	Core::Init(name, 800, 600, 200);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	game.Initialize();

	Core::GameLoop();
	Core::Shutdown();

	game.Shutdown();
}

