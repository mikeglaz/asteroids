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

const int NUM_LARGE_ASTEROIDS = 10;
const int NUM_MEDIUM_ASTEROIDS = 20;
const int NUM_SMALL_ASTEROIDS = 20;
const int NUM_ASTEROID_VERTICES = 8;
const GLint NUM_BULLETS = 10;

vector<GLfloat> Asteroid::large_asteroid_vertices;
vector<GLfloat> Asteroid::medium_asteroid_vertices;
vector<GLfloat> Asteroid::small_asteroid_vertices;
vector<Asteroid> large_asteroids;
vector<Asteroid> medium_asteroids;
vector<Asteroid> small_asteroids;
vector<Bullet> bullets;

Ship ship(0.0f, 0.0f);

GLuint large_asteroids_vbo, large_asteroids_vao;
GLuint medium_asteroids_vbo, medium_asteroids_vao;
GLuint small_asteroids_vbo, small_asteroids_vao;
GLuint ship_vbo, ship_vao;
GLuint bullet_vbo, bullet_vao;

GLuint vertex_shader, frag_shader, program;

GLfloat now = 0, delta = 0;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
  if(key == GLFW_KEY_SPACE && action == GLFW_PRESS)
  {
    int i=0;
    for(int i=0; i<NUM_BULLETS; i++)
    {
      if(!bullets[i].get_active())
      {
        bullets[i].set_angle(ship.get_angle());
        bullets[i].set_position(ship.get_position());
        bullets[i].activate();
        break;
      }
    }
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

  glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);

  glfwSetKeyCallback(window, key_callback);

  glewExperimental = GL_TRUE;

  glewInit();

  glViewport(0, 0, WIDTH, HEIGHT);
}

void create_asteroids()
{
  Asteroid::generate_asteroid_vertices(NUM_ASTEROID_VERTICES, Radius::large);  

  for(int i=0; i != NUM_LARGE_ASTEROIDS; i++)
  {
    Asteroid asteroid;
    asteroid.activate();
    asteroid.set_radius(Radius::large);
    large_asteroids.push_back(asteroid);
  }

  Asteroid::generate_asteroid_vertices(NUM_ASTEROID_VERTICES, Radius::medium);  

  for(int i=0; i != NUM_MEDIUM_ASTEROIDS; i++)
  {
    Asteroid asteroid;
    asteroid.set_radius(Radius::medium);
    medium_asteroids.push_back(asteroid);
  }

  Asteroid::generate_asteroid_vertices(NUM_ASTEROID_VERTICES, Radius::small);  

  for(int i=0; i != NUM_SMALL_ASTEROIDS; i++)
  {
    Asteroid asteroid;
    asteroid.set_radius(Radius::small);
    small_asteroids.push_back(asteroid);
  }    
}

void create_bullets()
{
  for(int i=0; i<NUM_BULLETS; i++)
  {
    Bullet bullet(0,0);
    bullets.push_back(bullet);
  }
}

void init_opengl()
{
  program = mgl::load_shaders("vertex.glsl", "fragment.glsl");

  create_asteroids();
  create_bullets();

  // init large asteroids
  glGenVertexArrays(1, &large_asteroids_vao);
  glGenBuffers(1, &large_asteroids_vbo); 
  glBindVertexArray(large_asteroids_vao);

  glBindBuffer(GL_ARRAY_BUFFER, large_asteroids_vbo);
  glBufferData(GL_ARRAY_BUFFER, Asteroid::large_asteroid_vertices.size()*sizeof(GLfloat), Asteroid::large_asteroid_vertices.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);

  // init medium asteroids
  glGenVertexArrays(1, &medium_asteroids_vao);
  glGenBuffers(1, &medium_asteroids_vbo); 
  glBindVertexArray(medium_asteroids_vao);

  glBindBuffer(GL_ARRAY_BUFFER, medium_asteroids_vbo);
  glBufferData(GL_ARRAY_BUFFER, Asteroid::medium_asteroid_vertices.size()*sizeof(GLfloat), Asteroid::medium_asteroid_vertices.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);

  // init small asteroids
  glGenVertexArrays(1, &small_asteroids_vao);
  glGenBuffers(1, &small_asteroids_vbo); 
  glBindVertexArray(small_asteroids_vao);

  glBindBuffer(GL_ARRAY_BUFFER, small_asteroids_vbo);
  glBufferData(GL_ARRAY_BUFFER, Asteroid::small_asteroid_vertices.size()*sizeof(GLfloat), Asteroid::small_asteroid_vertices.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);

// init ship
  glGenVertexArrays(1, &ship_vao);
  glGenBuffers(1, &ship_vbo);
  glBindVertexArray(ship_vao);

  glBindBuffer(GL_ARRAY_BUFFER, ship_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*6, ship.get_vertices(), GL_STATIC_DRAW);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);

// init bullets
  glGenVertexArrays(1, &bullet_vao);
  glGenBuffers(1, &bullet_vbo);
  glBindVertexArray(bullet_vao);

  glBindBuffer(GL_ARRAY_BUFFER, bullet_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*bullets.size()*2, bullets.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);  
}

void check_keyboard()
{
  int state = glfwGetKey(window, GLFW_KEY_LEFT);

  if(state == GLFW_PRESS)
    ship.rotate(Direction::left);

  state = glfwGetKey(window, GLFW_KEY_RIGHT);

  if(state == GLFW_PRESS)
    ship.rotate(Direction::right);

  state = glfwGetKey(window, GLFW_KEY_UP);  

  if(state == GLFW_PRESS)
    ship.accelerate();
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

// draw large asteroids
  glBindVertexArray(large_asteroids_vao);

  for(int i=0; i != large_asteroids.size(); i++)
  {
    if(large_asteroids[i].get_active())
    {
      glm::mat4 model;

      large_asteroids[i].move(delta);
      large_asteroids[i].check_collision(ship.get_position());
      large_asteroids[i].check_position();

      model = glm::translate(model, large_asteroids[i].get_position());
      glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
      glDrawArrays(GL_LINE_LOOP, 0, NUM_ASTEROID_VERTICES);    
    }
  }

  glBindVertexArray(0);

// draw medium asteroids
  glBindVertexArray(medium_asteroids_vao);

  for(int i=0; i != medium_asteroids.size(); i++)
  {
    if(medium_asteroids[i].get_active())
    {
      glm::mat4 model;

      medium_asteroids[i].move(delta);
      medium_asteroids[i].check_position();

      model = glm::translate(model, medium_asteroids[i].get_position());
      glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
      glDrawArrays(GL_LINE_LOOP, 0, NUM_ASTEROID_VERTICES);    
    }
  }

  glBindVertexArray(0);  

// draw large asteroids
  glBindVertexArray(small_asteroids_vao);

  for(int i=0; i != small_asteroids.size(); i++)
  {
    if(small_asteroids[i].get_active())
    {
      glm::mat4 model;

      small_asteroids[i].move(delta);
      small_asteroids[i].check_position();

      model = glm::translate(model, small_asteroids[i].get_position());
      glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
      glDrawArrays(GL_LINE_LOOP, 0, NUM_ASTEROID_VERTICES);    
    }
  }

  glBindVertexArray(0);  

// draw ship
  glBindVertexArray(ship_vao);

  glm::mat4 model;

  check_keyboard();

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

  for(int i=0; i<NUM_BULLETS; i++)
  {
    model = glm::mat4();

    if(bullets[i].get_active())
    {
      bullets[i].move(delta);
      bullets[i].check_position();
      model = glm::translate(model, bullets[i].get_position());   
      glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));    
      glDrawArrays(GL_POINTS, 0, 1);      
    }
  }
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

  glDeleteVertexArrays(1, &large_asteroids_vao);
  glDeleteBuffers(1, &large_asteroids_vbo);
  glDeleteBuffers(1, &large_asteroids_vao);

  glDeleteVertexArrays(1, &medium_asteroids_vao);
  glDeleteBuffers(1, &medium_asteroids_vbo);
  glDeleteBuffers(1, &medium_asteroids_vao);

  glDeleteVertexArrays(1, &small_asteroids_vao);
  glDeleteBuffers(1, &small_asteroids_vbo);
  glDeleteBuffers(1, &small_asteroids_vao);

  glfwTerminate();
}