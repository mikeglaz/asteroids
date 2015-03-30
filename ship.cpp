#include "ship.h"

GLfloat* Ship::get_vertices()
{
  return vertices;
}

void Ship::accelerate()
{
  GLfloat radians = glm::radians(angle);

  if(speedX < 5.0f && speedX > -5.0f)
    speedX += cos(radians);

  if(speedX >= 5.0f && cos(radians) < 0.0f)
    speedX += cos(radians);
  else if(speedX <= -5.0f && cos(radians) > 0.0f)
    speedX += cos(radians);

  if(speedY < 5.0f && speedY > -5.0f)
    speedY += sin(radians);

  if(speedY >= 5.0f && sin(radians) < 0.0f)
    speedY += sin(radians);
  else if(speedY <= -5.0f && sin(radians) > 0.0f)
    speedY += sin(radians);
}

void Ship::move(GLfloat delta)
{
  position.x += speedX*delta;
  position.y += speedY*delta;
}

void Ship::rotate(Direction dir)
{
  if(dir == Direction::left)
    angle += 5.0f;
  else
    angle -= 5.0f;

  if(angle > 360)
    angle = 0.0f;
  else if(angle < 0)
    angle = 355.0f;  
}

GLfloat Ship::get_angle() const
{
  return angle;
}