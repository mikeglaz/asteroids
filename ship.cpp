#include "ship.h"

GLfloat* Ship::get_vertices()
{
  return vertices;
}

void Ship::accelerate()
{
  GLfloat radians = glm::radians(angle);

  if(speed.x < 3.0f && speed.x > -3.0f)
    speed.x += .01*cos(radians);

  if(speed.x >= 3.0f && cos(radians) < 0.0f)
    speed.x += .01*cos(radians);
  else if(speed.x <= -3.0f && cos(radians) > 0.0f)
    speed.x += .01*cos(radians);

  if(speed.y < 3.0f && speed.y > -3.0f)
    speed.y += .01*sin(radians);

  if(speed.y >= 3.0f && sin(radians) < 0.0f)
    speed.y += .01*sin(radians);
  else if(speed.y <= -3.0f && sin(radians) > 0.0f)
    speed.y += .01*sin(radians);
}

void Ship::move(GLfloat delta)
{
  position.x += speed.x*delta;
  position.y += speed.y*delta;
}

void Ship::rotate(Direction dir)
{
  if(dir == Direction::left)
    angle += 0.25f;
  else
    angle -= 0.25f;

  if(angle > 360)
    angle = 0.0f;
  else if(angle < 0)
    angle = 360.0f;  
}

void Ship::reset()
{
  angle = 90.0f;
  position.x = 0.0f;
  position.y = 0.0f;
  speed.x = 0.0f;
  speed.y = 0.0f;
}

void Ship::teleport(GLfloat x, GLfloat y)
{
  position.x = x;
  position.y = y;
}

GLfloat Ship::get_angle() const
{
  return angle;
}

GLubyte* Ship::get_sideA()
{
  return sideA;
}

GLubyte* Ship::get_sideB() 
{
  return sideB;
}

GLubyte* Ship::get_sideC() 
{
  return sideC;
}