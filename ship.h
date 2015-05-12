#include "projectile.h"

enum class Direction { left, right };

class Ship : public Projectile
{
  GLfloat vertices[6] {
    -0.05f, 0.03f,
    -0.05f, -0.03f,
    0.05f, 0.0f
  };

  GLubyte sideA[2] {
    0, 1
  };

  GLubyte sideB[2] {
    1, 2
  };

  GLubyte sideC[2] {
    0, 2
  };

  glm::vec3 speed;

public:
  Ship(GLfloat x, GLfloat y) : Projectile{x,y} {
    speed.x = speed.y = 0.0f;
    angle = 90.0f;
  }
  GLfloat* get_vertices();
  void accelerate();
  void move(GLfloat);
  void rotate(Direction);
  void reset();
  void teleport(GLfloat, GLfloat);
  GLubyte* get_sideA();
  GLubyte* get_sideB();
  GLubyte* get_sideC();
  GLfloat get_angle() const;
};