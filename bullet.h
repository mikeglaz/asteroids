#include "projectile.h"

class Bullet : public Projectile
{
public:
  Bullet(GLfloat x, GLfloat y) : Projectile{x,y} {
    active = GL_FALSE;
  }
  void set_angle(GLfloat);
  void set_position(glm::vec3);
  void move(GLfloat);
  void check_position();
};