#include "projectile.h"

class Bullet : public Projectile
{
  GLfloat vertices[2] {
    0.0f, 0.05f
  };
  
public:
  Bullet(GLfloat x, GLfloat y) : Projectile{x,y} {}
};