#include <vector>
#include <memory> // For pointers

class SceneManager
{
public:
	std::vector<std::shared_ptr<Scene>> scenes;
	std::shared_ptr<Scene> active_scene;

};

class Scene
{

};