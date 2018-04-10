#include "..\Scene.h"
#include <vector>

class RenderResourceFactory;
class RenderLoop;
class GameObject;

class HeroScene : public Scene
{
private:
	std::vector<std::shared_ptr<GameObject>> m_objects;
	std::vector<std::shared_ptr<GameObject>> m_rocks;
public:
	HeroScene(RenderResourceFactory& renderResourceFactory, RenderLoop& renderLoop);
	void Update();

	~HeroScene();
	bool Initialise() override { return true; }

};