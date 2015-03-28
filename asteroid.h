#include <vector>

#include "projectile.h"

enum class Radius { small, medium, large };

class Asteroid : public Projectile
{
  Radius radius;

public:
  static std::vector<GLfloat> asteroid_vertices;
  Asteroid() : Projectile(){};
  Asteroid(GLfloat x, GLfloat y) : Projectile{x,y} {}
  static void generate_asteroid_vertices(int, GLfloat);
};
