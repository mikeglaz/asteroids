#include <iostream>
#include <ctime>
#include <GL/glew.h>

#include "asteroid.h"
#include "ship.h"
#include "bullet.h"
#include "mgl.h"

using namespace std;

GLFWwindow* window;

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 800;

const int NUM_ASTEROIDS = 10;
const int NUM_ASTEROID_VERTICES = 8;

vector<GLfloat> Asteroid::asteroid_vertices;
vector<Asteroid> asteroids;
vector<Bullet> bullets;

Ship ship(0.0f, 0.0f);

const GLfloat RADIUS_LARGE = 0.1875f;
const GLfloat RADIUS_MEDIUM = 0.09375f;
const GLfloat RADIUS_SMALL = 0.046875f;

GLuint asteroids_vbo, asteroids_vao;
GLuint ship_vbo, ship_vao;
GLuint bullet_vbo, bullet_vao;

GLuint vertex_shader, frag_shader, program;

GLfloat now = 0, delta = 0;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
  if (key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT))
    ship.accelerate();

  if (key == GLFW_KEY_LEFT && (action == GLFW_REPEAT || action == GLFW_PRESS))
    ship.rotate(Direction::left);

  if (key == GLFW_KEY_RIGHT && (action == GLFW_REPEAT || action == GLFW_PRESS))
    ship.rotate(Direction::right);

  if(key == GLFW_KEY_SPACE && action == GLFW_PRESS)
  {
    Bullet bullet(0.0f, 0.0f);
    bullets.push_back(bullet);
  }
}

void init_glfw()
{
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  // Init GLFW
  glfwInit();

  // Set all the required options for GLFW
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  window = glfwCreateWindow(WIDTH, HEIGHT, "Asteroids", nullptr, nullptr);
  glfwMakeContextCurrent(window);

  glfwSetKeyCallback(window, key_callback);

  glewExperimental = GL_TRUE;

  glewInit();

  glViewport(0, 0, WIDTH, HEIGHT);
}

void create_asteroids()
{
  Asteroid::generate_asteroid_vertices(NUM_ASTEROID_VERTICES, RADIUS_LARGE);  

  for(int i=0; i != NUM_ASTEROIDS; i++)
  {
    Asteroid asteroid;
    asteroids.push_back(asteroid);
  }
}

void init_opengl()
{
  program = mgl::load_shaders("vertex.glsl", "fragment.glsl");

  create_asteroids();

  glGenVertexArrays(1, &asteroids_vao);
  glGenBuffers(1, &asteroids_vbo); 
  glBindVertexArray(asteroids_vao);

  glBindBuffer(GL_ARRAY_BUFFER, asteroids_vbo);
  glBufferData(GL_ARRAY_BUFFER, Asteroid::asteroid_vertices.size()*sizeof(GLfloat), Asteroid::asteroid_vertices.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);

  glGenVertexArrays(1, &ship_vao);
  glGenBuffers(1, &ship_vbo);
  glBindVertexArray(ship_vao);

  glBindBuffer(GL_ARRAY_BUFFER, ship_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*6, ship.get_vertices(), GL_STATIC_DRAW);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);

  glGenVertexArrays(1, &bullet_vao);
  glGenBuffers(1, &bullet_vbo);
  glBindVertexArray(bullet_vao);

  glBindBuffer(GL_ARRAY_BUFFER, bullet_vbo);
  // glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*bullets.size()*2, bullets.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);  
}

void draw()
{
  static GLfloat last = 0;
  now = glfwGetTime();
  delta = now - last;

  delta /= 10;

  last = now;
  GLint modelLoc = glGetUniformLocation(program, "model");

  glClear(GL_COLOR_BUFFER_BIT);

// draw asteroids
  glBindVertexArray(asteroids_vao);

  for(int i=0; i != asteroids.size(); i++)
  {
    glm::mat4 model;

    asteroids[i].move(delta);
    asteroids[i].check_position();

    model = glm::translate(model, asteroids[i].get_position());
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glDrawArrays(GL_LINE_LOOP, 0, NUM_ASTEROID_VERTICES);    
  }

  glBindVertexArray(0);

// draw ship
  glBindVertexArray(ship_vao);

  glm::mat4 model;

  ship.move(delta);
  ship.check_position();

  model = glm::translate(model, ship.get_position());
  model = glm::rotate(model, glm::radians(ship.get_angle()), glm::vec3(0.0f, 0.0f, 1.0f));

  glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
  glDrawArrays(GL_LINE_LOOP, 0, 3);
  glBindVertexArray(0);

// draw bullets 
  glPointSize(4.0);
  glBindVertexArray(bullet_vao);

  model = glm::mat4();

  glDrawArrays(GL_POINTS, 0, 1);
}

int main(int argc, char** argv)
{
  srand(static_cast<unsigned>(time(0)));

  // timer /= 100;

  init_glfw();

  init_opengl();


  // for(int i=0; i != NUM_ASTEROID_VERTICES*2; i += 2)
  //   cout << Asteroid::asteroid_vertices[i] << ", " << Asteroid::asteroid_vertices[i+1] << endl;

  while(!glfwWindowShouldClose(window))
  {
    glfwPollEvents();

    glUseProgram(program);

    draw();

    glfwSwapBuffers(window);
  }

  glDeleteVertexArrays(1, &asteroids_vao);
  glDeleteBuffers(1, &asteroids_vbo);
  glDeleteBuffers(1, &asteroids_vao);

  glfwTerminate();
}