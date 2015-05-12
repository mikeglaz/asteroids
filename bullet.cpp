#include "bullet.h"

void Bullet::set_angle(GLfloat ship_angle)
{
  angle = ship_angle;
}

void Bullet::set_position(glm::vec3 ship_position)
{
  position = ship_position;
}

void Bullet::move(GLfloat delta)
{
  GLfloat radians = glm::radians(angle);

  position.x += 20*delta*cos(radians);
  position.y += 20*delta*sin(radians);  
}

void Bullet::check_position()
{
  if(position.x > 1.0 || position.x < -1.0)
  {
    active = GL_FALSE;
    position.x = 0.0f;
    position.y = 0.0f;
  }

  if(position.y > 1.0 || position.y < -1.0)
  {
    active = GL_FALSE;
    position.x = 0.0f;
    position.y = 0.0f;    
  }
}