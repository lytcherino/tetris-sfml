#include "GameResource.h"


namespace Resource
{

  namespace Fonts
  {
    void initialise()
    {
      FontHolder fontHolder;
      fontHolder.load(Resource::Fonts::ID::standard, "ss");
    }
  }

  namespace Texts
  {
    void initialise()
    {
      TextHolder textHolder;
    }
  }
  void initialise()
  {
    Resource::Fonts::initialise();
  }
}
