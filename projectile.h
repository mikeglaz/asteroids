#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <iostream>
#include <cmath>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Projectile{

protected:
  glm::vec3 position;
  GLfloat angle;
  GLboolean active;

public:
  Projectile();
  Projectile(GLfloat, GLfloat);

  GLfloat get_x() const;
  GLfloat get_y() const;
  glm::vec3 get_position() const;
  GLfloat get_angle() const;
  void reverse_x();
  void reverse_y();
  virtual void move(GLfloat);
  void check_position();
  GLboolean get_active() const;
  void activate();
  void deactivate();
};

std::ostream& operator<<(std::ostream&, const Projectile&);

#endif