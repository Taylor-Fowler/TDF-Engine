#include "..\Scene.h"
#include <vector>

class RenderResourceFactory;
class RenderLoop;
class GameObject;

class HeroScene : public Scene
{
private:
	std::vector<GameObject*> m_objects;
public:
	HeroScene(RenderResourceFactory& renderResourceFactory, RenderLoop& renderLoop);
	bool Initialise() override { return true; }

};