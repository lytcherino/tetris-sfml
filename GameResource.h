#ifndef GAME_RESOURCE_H
#define GAME_RESOURCE_H

#include <SFML/Graphics.hpp>
#include "ResourceHolder.h"

namespace Resource
{
  namespace Fonts
  {
    enum class ID
      {
        standard
      };
    typedef ResourceHolder<sf::Font, Resource::Fonts::ID> FontHolder;
    extern FontHolder fontHolder;
    void initialise();
  }
  namespace Texts
  {
    enum class ID
      {
        score,
        level,
        piecesCleared,
        linesCleared,
        time,
        highscore
      };
    typedef ResourceHolder<sf::Text, Resource::Texts::ID> TextHolder;
    extern TextHolder textHolder;

    void initialise();
  }
  void initialise();
}

#endif
