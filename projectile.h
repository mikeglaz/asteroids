#include <iostream>
#include <cmath>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Projectile{
  glm::vec3 position;
  GLfloat angle;

public:
  Projectile();
  Projectile(GLfloat, GLfloat);

  GLfloat get_x() const;
  GLfloat get_y() const;
  glm::vec3 get_position() const;
  GLfloat get_angle() const;
  void reverse_x();
  void reverse_y();
  void move(GLfloat);
  void check_position();
};

std::ostream& operator<<(std::ostream&, const Projectile&);