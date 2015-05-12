#include "projectile.h"

#include <cstdlib>

Projectile::Projectile()
{
  float x_side = rand() % 2;
  float y_side = rand() % 2;

  GLfloat x,y;

  if(x_side == 0)
    x = -1.0 + static_cast <GLfloat>(rand()) /( static_cast <GLfloat>(RAND_MAX/(-0.2 - (-1.0))));
  else
    x = 0.2 + static_cast <GLfloat>(rand()) /( static_cast <GLfloat>(RAND_MAX/(1.0-(0.2))));

  if(y_side == 0)
    y = -1.0 + static_cast <GLfloat>(rand()) /( static_cast <GLfloat>(RAND_MAX/(-0.2 - (-1.0))));
  else
    y = 0.2 + static_cast <GLfloat>(rand()) /( static_cast <GLfloat>(RAND_MAX/(1.0-(0.2))));  

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

void Projectile::set_position(glm::vec3 new_position)
{
  position = new_position;
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
  GLfloat radians = glm::radians(angle);

  position.x += delta*cos(radians);
  position.y += delta*sin(radians);  
}

GLboolean Projectile::get_active() const
{
  return active;
}

void Projectile::activate()
{
  active = GL_TRUE;
}

void Projectile::deactivate()
{
  active = GL_FALSE;
}

std::ostream& operator<<(std::ostream& os, const Projectile& position)
{
  os << position.get_x() << ", " << position.get_y();
  return os;
}