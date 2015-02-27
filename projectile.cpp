#include "projectile.h"

#include <cstdlib>

Projectile::Projectile()
{
  float x = -1.0 + static_cast <float>(rand()) /( static_cast <float>(RAND_MAX/(1.0-(-1.0))));
  float y = -1.0 + static_cast <float>(rand()) /( static_cast <float> (RAND_MAX/(1.0-(-1.0))));
  pos[0] = x;
  pos[1] = y;
}

Projectile::Projectile(float x, float y)
{
  pos[0] = x;
  pos[1] = y;
}

float Projectile::get_x() const
{
  return pos[0];
}

float Projectile::get_y() const
{
  return pos[1];
}

std::ostream& operator<<(std::ostream& os, const Projectile& pos)
{
  os << pos.get_x() << ", " << pos.get_y();
  return os;
}