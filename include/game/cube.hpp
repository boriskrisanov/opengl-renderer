#include "render/gameObject.hpp"
#include "render/model.hpp"

namespace game
{
class Cube : public render::GameObject
{
  public:
    void onStart() override
    {
      model = {render::Texture{}, render::ObjModel{"assets/cube.obj"}};
    }

    void onUpdate() override
    {
			
    }
};
} // namespace game