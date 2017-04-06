asteroids: main.cpp mgl.cpp asteroid.cpp bullet.cpp projectile.cpp ship.cpp
	g++ -std=c++11 -o asteroids main.cpp mgl.cpp asteroid.cpp bullet.cpp projectile.cpp ship.cpp -lglfw -lGLEW -lGL
