#include <iostream>
#include <ctime>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "projectile.h"

using namespace std;

int main(int argc, char** argv)
{
  srand(static_cast<unsigned>(time(0)));
  Projectile p = Projectile();

  cout << p << endl;
}