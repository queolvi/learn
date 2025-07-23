#include "utils.hpp"
#pragma once
class launcher_game {
class LG_window : public launcher_game 
  {
  
  };
private:
dino_game Object_DG;
minesweeper_game Object_MG;
snake_game Object_SG;
// here need object WONDOW for launch (menu, statistics, and exit foo)
public:

launcher_game(); // here need object games
virtual ~launcher_game(); // in this place all processes will get close
private:

};

class menu_launcher : public launcher_game {
class ML_window : public launcher_game, public LG_window
  {

  };
private:

public:
menu_launcher();
~menu_launcher()

private:

};

class dino_game : public launcher_game, public menu_launcher{
class DG_window : public launcher_game, public LG_window, public ML_window
  {

  };
private:

public:
dino_game();
~dino_game();
private:

};

class minesweeper_game : public launcher_game, public menu_launcher{
class MG_window : public launcher_game, public LG_window, public ML_window
  {

  };
private:

public:
minesweeper_game();
~minesweeper_game();
private:

};

class snake_game : public launcher_game, public menu_launcher{
class SG_window : public launcher_game, public LG_window, public ML_window
  {

  }; 
private:

public:
snake_game();
~snake_game();
private:

};
