#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width-1)),
      random_h(0, static_cast<int>(grid_height-1)) {
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    //we need a indicator which redner to call
    //if there is no bous food on screen call the noraml render
    //otherwise call the bonus food render
    if(bonus==false)
      renderer.Render(snake, food);
    else
      renderer.Render(snake, food, bonus_food);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}
//This Function Handles the bonus food Generation
//Currently The bonus food is called whenever score%10 is 0
//TODO: Change if required in future
void Game::PlaceBonusFood() {
  //The bonus food should be generated when the user scores is greater than 10
  int x, y;
  bonus=true;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      bonus_food.x = x;
      bonus_food.y = y;
      return;
    }
  }
}

//Update the game Update function to include the bonus food item as well
void Game::Update() {
  if (!snake.isAlive()) return;

  snake.Update();

  int new_x = static_cast<int>(snake.getHeadX());
  int new_y = static_cast<int>(snake.getHeadY());

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    if(score%10==0)
      PlaceBonusFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    //reduce the growth speed
    float curr_speed=snake.getSpeed();
    float new_speed=curr_speed+0.01;
    snake.setSpeed(new_speed);
    //normalise the speed at every interval
    if(score%20==0)
    {
      float curr_speed=snake.getSpeed();
      //make the speed 80% of the original _speed
      float new_speed=curr_speed*0.80;
      snake.setSpeed(new_speed);
    }
  }
  if (bonus_food.x == new_x && bonus_food.y == new_y) {
    //the snake eats the bonus food
    bonus=false;
    //Done: Once the snake eats the bonus food, its length reduces by 10% and the score remaines the same
    snake.ShrinkBody();
    //after eating the bonus set the bonus food co-ordinates to some big value untill a new value is not generated;
    bonus_food.x = 32;
    bonus_food.y = 32;
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.getSize(); }
