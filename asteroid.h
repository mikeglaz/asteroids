#include <vector>

#include "projectile.h"

enum class Radius { small = 46 , medium = 93, large = 187 };

const GLfloat RADIUS_LARGE = 0.1875f;
const GLfloat RADIUS_MEDIUM = 0.09375f;
const GLfloat RADIUS_SMALL = 0.046875f;

class Asteroid : public Projectile
{
  Radius radius;

public:
  static std::vector<GLfloat> large_asteroid_vertices;
  static std::vector<GLfloat> medium_asteroid_vertices;
  static std::vector<GLfloat> small_asteroid_vertices;
  Asteroid(Radius);
  // Asteroid(GLfloat x, GLfloat y) : Projectile{x,y} {}
  static void generate_asteroid_vertices(int, Radius);
  void move(GLfloat);
  bool check_collision(glm::vec3);
};
