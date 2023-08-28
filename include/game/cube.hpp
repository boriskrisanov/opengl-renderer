#include "render/gameObject.hpp"
#include "render/model.hpp"

namespace game
{
class Cube : public render::GameObject
{
  public:
    Cube(): render::GameObject{render::Model{render::Texture{}, render::ObjModel{"assets/cube.obj"}}} {}

    void onStart() override
    {
      
    }

    void onUpdate() override
    {
			
    }
};
} // namespace game