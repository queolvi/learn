#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class window {
protected:
    GLFWwindow* glfwWindow;
    int width = 800;
    int height = 600;
    
    void initGLFW() {
        if (!glfwInit()) {
            throw std::runtime_error("Failed to initialize GLFW");
        }
        
        glfwWindowHint(GLFW_SAMPLES, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        
        glfwWindow = glfwCreateWindow(width, height, "Game Window", NULL, NULL);
        if (!glfwWindow) {
            glfwTerminate();
            throw std::runtime_error("Failed to create GLFW window");
        }
        
        glfwMakeContextCurrent(glfwWindow);
        glewExperimental = true;
        if (glewInit() != GLEW_OK) {
            throw std::runtime_error("Failed to initialize GLEW");
        }
    }

public:
    window() {
        initGLFW();
    }
    
    ~window() {
        glfwTerminate();
    }
    
    void start_game_snake() {
        std::cout << "Snake game started with OpenGL\n";
        // Инициализация игры Змейка
        while (!glfwWindowShouldClose(glfwWindow)) {
            // Рендеринг и логика змейки
            glClear(GL_COLOR_BUFFER_BIT);
            
            // Здесь код отрисовки змейки
            
            glfwSwapBuffers(glfwWindow);
            glfwPollEvents();
        }
    }
    
    void start_game_minesweeper() {
        std::cout << "Minesweeper game started with OpenGL\n";
        // Инициализация игры Сапер
        while (!glfwWindowShouldClose(glfwWindow)) {
            glClear(GL_COLOR_BUFFER_BIT);
            
            // Здесь код отрисовки сапера
            
            glfwSwapBuffers(glfwWindow);
            glfwPollEvents();
        }
    }
    
    void start_game_tic_tac_toe() {
        std::cout << "Tic tac toe game started with OpenGL\n";
        // Инициализация игры Крестики-нолики
        while (!glfwWindowShouldClose(glfwWindow)) {
            glClear(GL_COLOR_BUFFER_BIT);
            
            // Здесь код отрисовки крестиков-ноликов
            
            glfwSwapBuffers(glfwWindow);
            glfwPollEvents();
        }
    }
    
    void start_game_rider_motocycle() {
        std::cout << "Rider motocycle game started with OpenGL\n";
        // Инициализация игры Мотоциклист
        while (!glfwWindowShouldClose(glfwWindow)) {
            glClear(GL_COLOR_BUFFER_BIT);
            
            // Здесь код отрисовки мотоциклиста
            
            glfwSwapBuffers(glfwWindow);
            glfwPollEvents();
        }
    }
};
class games : public window{
private:
  size_t choice;
public:
  size_t get_choice() { return choice; };
  games(size_t ch) : choice(ch) {
    if (get_choice() >= 1 && get_choice() <= 4) {
      if (get_choice() == 1) { window win; win.start_game_snake(); }
      else if (get_choice() == 2) { window win; win.start_game_minesweeper(); }
      else if (get_choice() == 3) { window win; win.start_game_tic_tac_toe(); }
      else if (get_choice() == 4) { window win; win.start_game_rider_motocycle(); }
      else {  std::cout << "(1)Game choice has been stoped. Restart and choose wright value. \n"; }
    }
    else if (get_choice() < 0 && get_choice() >= 5) { throw std::invalid_argument("Invalid entered input. You may restart programm. \n"); }
    else {}
  }

};



