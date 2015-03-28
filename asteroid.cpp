#include "asteroid.h"

#include <iostream>

using namespace std;

void Asteroid::generate_asteroid_vertices(int num_vertices, GLfloat radius)
{
  GLfloat angle, x, y;

  asteroid_vertices.clear();

  for(int i=0; i != num_vertices; i++)
  {
    angle = 2*M_PI/num_vertices * i;
    x = radius * cos(angle);
    y = radius * sin(angle);

    asteroid_vertices.push_back(x);
    asteroid_vertices.push_back(y);
  }
}

