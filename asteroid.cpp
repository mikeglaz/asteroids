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


