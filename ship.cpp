#include "ship.h"

GLfloat* Ship::get_vertices()
{
  return vertices;
}

void Ship::accelerate()
{
  GLfloat radians = glm::radians(angle);

  if(speedX < 3.0f && speedX > -3.0f)
    speedX += .01*cos(radians);

  if(speedX >= 3.0f && cos(radians) < 0.0f)
    speedX += .01*cos(radians);
  else if(speedX <= -3.0f && cos(radians) > 0.0f)
    speedX += .01*cos(radians);

  if(speedY < 3.0f && speedY > -3.0f)
    speedY += .01*sin(radians);

  if(speedY >= 3.0f && sin(radians) < 0.0f)
    speedY += .01*sin(radians);
  else if(speedY <= -3.0f && sin(radians) > 0.0f)
    speedY += .01*sin(radians);
}

void Ship::move(GLfloat delta)
{
  position.x += speedX*delta;
  position.y += speedY*delta;
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

GLfloat Ship::get_angle() const
{
  return angle;
}