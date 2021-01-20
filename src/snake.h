#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"

class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 2),
        head_y(grid_height / 2) {}

  void Update();

  void GrowBody();
  //This function handles the shrinking of the snake body when it eats a bonus food
  void ShrinkBody();
  bool SnakeCell(int x, int y);

  Direction direction = Direction::kUp;

  //Add Getter/setter for the snake class
  float getSpeed() const { return speed;}
  void setSpeed(float _speed) { speed=_speed;}
  float getSize()const {return size;}
  void setSize(int _sz) { size=_sz;}
  bool isAlive() const {return alive;}
  float getHeadX() const { return head_x;}
  float getHeadY() const {return head_y;}
  const std::vector<SDL_Point>&getBody() const{return body;}

  //This stores all the snake body parts


 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  bool growing{false};
  bool eat_bonus{false};
  int grid_width;
  int grid_height;
  float speed{0.1f};
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;
};

#endif
