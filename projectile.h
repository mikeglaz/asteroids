#include <iostream>

class Projectile{
  float pos[2];

public:
  Projectile();
  Projectile(float, float);

  float get_x() const;
  float get_y() const;
};

std::ostream& operator<<(std::ostream&, const Projectile&);