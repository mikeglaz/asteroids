#include "asteroid.h"

#include <iostream>

Asteroid::Asteroid(Radius r)
{
  active = GL_FALSE;
  radius = r;
}

void Asteroid::generate_asteroid_vertices(int num_vertices, Radius radius)
{
  GLfloat angle, x, y;

  for(int i=0; i != num_vertices; i++)
  {
    angle = 2*M_PI/num_vertices * i;

    x = static_cast<GLfloat>(radius)/1000 * cos(angle);
    y = static_cast<GLfloat>(radius)/1000 * sin(angle);

    if(radius == Radius::large)
    {
      large_asteroid_vertices.push_back(x);
      large_asteroid_vertices.push_back(y);
    }
    else if(radius == Radius::medium)
    {
      medium_asteroid_vertices.push_back(x);
      medium_asteroid_vertices.push_back(y);
    }
    else if(radius == Radius::small)
    {
      small_asteroid_vertices.push_back(x);
      small_asteroid_vertices.push_back(y);
    }
  }
}

void Asteroid::move(GLfloat delta)
{
  position.x += delta*cos(angle);
  position.y += delta*sin(angle);  
}

bool Asteroid::check_collision(glm::vec3 ship_position)
{  
  if(std::abs(position.x - ship_position.x) < static_cast<GLfloat>(radius)/1000 && std::abs(position.y - ship_position.y) < static_cast<GLfloat>(radius)/1000)
      return true;
}


