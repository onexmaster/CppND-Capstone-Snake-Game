#include "snake.h"
#include <cmath>
#include <iostream>

//functions for the snakebody
// template<class T>
// SnakeBody<T>::SnakeBody()
// {
//   std::cout<<"constructor called"<<std::endl;
// }
// template<class T>
// SnakeBody<T>::~SnakeBody()
// {
//   std::cout<<"Destructor called"<<std::endl;
// }

template<typename T>
void SnakeBody<T>::remove(){
  std::lock_guard<std::mutex>lock_guard(_mutex);
  body.erase(body.begin());
}
template<typename T>
  void SnakeBody<T>::add(const T &msg) {
      std::lock_guard<std::mutex> lock_guard(_mutex);
      body.push_back(msg);
  }

  template<typename T>
  std::vector<T> SnakeBody<T>::getSnakeBody() {
      return body;
  }


void Snake::Update() {
  SDL_Point prev_cell{
      static_cast<int>(head_x),
      static_cast<int>(
          head_y)};  // We first capture the head's cell before updating.
  UpdateHead();
  SDL_Point current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};  // Capture the head's cell after updating.

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    UpdateBody(current_cell, prev_cell);
  }
}

void Snake::UpdateHead() {
  switch (direction) {
    case Direction::kUp:
      head_y -= speed;
      break;

    case Direction::kDown:
      head_y += speed;
      break;

    case Direction::kLeft:
      head_x -= speed;
      break;

    case Direction::kRight:
      head_x += speed;
      break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  head_x = fmod(head_x + grid_width, grid_width);
  head_y = fmod(head_y + grid_height, grid_height);
}

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell) {
  // Add previous head location to vector
  _body->add(prev_head_cell);

  if (!growing) {
    // Remove the tail from the vector.
    _body->remove();
  } else {
    growing = false;
    size++;
  }
  //if bonus eaten
  if(eat_bonus)
  {
    int dec=size*0.1;
    std::cout<<"Bonus Eaten: reduce size by "<<dec<<std::endl;
    for(int i=0;i<dec;i++)
    {
    _body->remove();
      size--;
    }
    eat_bonus=false;
  }
  // Check if the snake has died.
  for (auto const &item : _body->getSnakeBody()) {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
      alive = false;
    }
  }
}

void Snake::GrowBody() { growing = true; }

void Snake::ShrinkBody()
{
  eat_bonus=true;
}

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y) {
  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) {
    return true;
  }
  for (auto const &item : _body->getSnakeBody()) {
    if (x == item.x && y == item.y) {
      return true;
    }
  }
  return false;
}
