#include "projectile.h"

enum class Direction { left, right };

class Ship : public Projectile
{
  GLfloat vertices[6] {
      -0.05f, 0.03f,
      -0.05f, -0.03f,
      0.05f, 0.0f
    };
    GLfloat speedX;
    GLfloat speedY;

public:
  Ship(GLfloat x, GLfloat y) : Projectile{x,y} {
    speedX = speedY = 0.0f;
    angle = 90.0f;
  }
  GLfloat* get_vertices();
  void accelerate();
  void move(GLfloat);
  void rotate(Direction);
  GLfloat get_angle() const;
};