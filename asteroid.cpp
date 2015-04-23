#include "asteroid.h"

#include <iostream>



void Asteroid::generate_asteroid_vertices(int num_vertices, Radius radius)
{
  GLfloat angle, x, y;

  for(int i=0; i != num_vertices; i++)
  {
    angle = 2*M_PI/num_vertices * i;

    if(radius == Radius::large)
    {
      x = RADIUS_LARGE * cos(angle);
      y = RADIUS_LARGE * sin(angle);

      large_asteroid_vertices.push_back(x);
      large_asteroid_vertices.push_back(y);
    }
    else if(radius == Radius::medium)
    {
      x = RADIUS_MEDIUM * cos(angle);
      y = RADIUS_MEDIUM * sin(angle);

      medium_asteroid_vertices.push_back(x);
      medium_asteroid_vertices.push_back(y);
    }
    else if(radius == Radius::small)
    {
      x = RADIUS_SMALL * cos(angle);
      y = RADIUS_SMALL * sin(angle);

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

void Asteroid::set_radius(Radius r)
{
  radius = r;
}

bool Asteroid::check_collision(glm::vec3 ship_position)
{
  static int i=0;
  
  if(std::abs(position.x - ship_position.x) < RADIUS_LARGE && std::abs(position.y - ship_position.y) < RADIUS_LARGE)
    return true;
  else
    return false;
  // std::cout << position.x << ", " << ship_position.x << std::endl;
}


