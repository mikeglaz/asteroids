#include "projectile.h"

#include <cstdlib>

Projectile::Projectile()
{
  GLfloat x = -1.0 + static_cast <GLfloat>(rand()) /( static_cast <GLfloat>(RAND_MAX/(1.0-(-1.0))));
  GLfloat y = -1.0 + static_cast <GLfloat>(rand()) /( static_cast <GLfloat> (RAND_MAX/(1.0-(-1.0))));
  position.x = x;
  position.y = y;

  angle = rand()/(RAND_MAX/360);
}

Projectile::Projectile(GLfloat x, GLfloat y)
{
  position.x = x;
  position.y = y;
}

GLfloat Projectile::get_x() const
{
  return position.x;
}

GLfloat Projectile::get_y() const
{
  return position.y;
}

glm::vec3 Projectile::get_position() const
{
  return position;
}

GLfloat Projectile::get_angle() const
{
  return angle;
}

void Projectile::check_position()
{
  if(position.x < -1.0)
    position.x += 2.0;
  else if(position.x > 1.0)
    position.x -= 2.0;

  if(position.y < -1.0)
    position.y += 2.0;
  else if(position.y > 1.0)
    position.y -= 2.0;
}

void Projectile::move(GLfloat delta)
{
  position.x += delta*cos(angle);
  position.y += delta*sin(angle);  
}

std::ostream& operator<<(std::ostream& os, const Projectile& position)
{
  os << position.get_x() << ", " << position.get_y();
  return os;
}