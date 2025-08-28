#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include <deque>
#include <cstdlib>
#include <ctime>

struct Snake_segment {
    glm::vec2 position;
    Snake_segment(float x, float y) : position(x, y) {}
};

class Snake {
    std::deque<Snake_segment> segments;
    glm::vec2 direction, food_position;
    int grid_size;
    float cell_size;

public:
    Snake(int grid_size = 20) : grid_size(grid_size), cell_size(2.0f / grid_size) {
        // Инициализация случайных чисел
        std::srand(std::time(0));
        
        // Начальная позиция змейки
        segments.push_back(Snake_segment(0, 0));
        direction = glm::vec2(1, 0); // движение вправо
        spawn_food();
    }
    
    void spawn_food() {
        food_position = glm::vec2(
            std::rand() % grid_size - grid_size/2,
            std::rand() % grid_size - grid_size/2
        );
    }
    
    void move() {
        // Добавляем новую голову
        glm::vec2 new_head = segments.front().position + direction;
        segments.push_front(Snake_segment(new_head.x, new_head.y));

        // Если еда не съедена - удаляем хвост
        if (new_head != food_position) {
            segments.pop_back();
        } else {
            spawn_food();
        }
    }
    
    void change_direction(glm::vec2 new_direction) {
        // Запрещаем движение в противоположном направлении
        if (new_direction != -direction) {
            direction = new_direction;
        }
    }
    
    bool check_collision() {
        glm::vec2 head = segments.front().position;

        // Стены
        if (std::abs(head.x) > grid_size/2 || std::abs(head.y) > grid_size/2) {
            return true;
        }
        
        // Сама себя
        for (size_t i = 1; i < segments.size(); ++i) {
            if (head == segments[i].position) {
                return true;
            }
        }
        
        return false;
    }
    
    const std::deque<Snake_segment>& get_segments() const { return segments; }
    glm::vec2 get_food_position() const { return food_position; }
    float get_cell_size() const { return cell_size; }
};

class Window {
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
    
    // Функции рисования вынесены как методы класса
    void draw_square(float x, float y, float size, glm::vec3 color) {
        glBegin(GL_QUADS);
        glColor3f(color.r, color.g, color.b);
        glVertex2f(x - size/2, y - size/2);
        glVertex2f(x + size/2, y - size/2);
        glVertex2f(x + size/2, y + size/2);
        glVertex2f(x - size/2, y + size/2);
        glEnd();
    }
    
    void draw_snake(const Snake& snake) {
        float cell_size = snake.get_cell_size();

        // Рисуем змейку
        for(const auto& segment : snake.get_segments()) {
            draw_square(segment.position.x * cell_size,
                        segment.position.y * cell_size,
                        cell_size * 0.9f,
                        glm::vec3(0, 1, 0)); // зеленый цвет
        }
        
        // Рисуем еду
        glm::vec2 food_position = snake.get_food_position();
        draw_square(food_position.x * cell_size,
                    food_position.y * cell_size,
                    cell_size * 0.9f,
                    glm::vec3(1, 0, 0)); // красный цвет
    }
    
    static void key_callback(GLFWwindow* window, int key, int scan_code, int action, int mods) {
        if (action == GLFW_PRESS || action == GLFW_REPEAT) {
            Snake* snake = static_cast<Snake*>(glfwGetWindowUserPointer(window));
            if (snake) {
                switch (key) {
                    case GLFW_KEY_UP: 
                        snake->change_direction(glm::vec2(0, 1)); 
                        break;
                    case GLFW_KEY_DOWN: 
                        snake->change_direction(glm::vec2(0, -1)); 
                        break; 
                    case GLFW_KEY_LEFT: 
                        snake->change_direction(glm::vec2(-1, 0)); 
                        break;
                    case GLFW_KEY_RIGHT: 
                        snake->change_direction(glm::vec2(1, 0)); 
                        break;
                }
            }
        }
    }

public:
    Window() {
        initGLFW();
    }
    
    ~Window() {
        glfwTerminate();
    }
    
    void start_game_snake() {
        std::cout << "Snake game started with OpenGL\n";
        
        // Инициализация
        Snake snake;
        glfwSetWindowUserPointer(glfwWindow, &snake);
        glfwSetKeyCallback(glfwWindow, key_callback);
        
        double lastTime = glfwGetTime();
        
        while (!glfwWindowShouldClose(glfwWindow)) {
            // Обновление игры с фиксированным интервалом
            double currentTime = glfwGetTime();
            if (currentTime - lastTime >= 0.2) { // Двигаем змейку каждые 0.2 секунды
                snake.move();
                
                // Проверка столкновений
                if (snake.check_collision()) {
                    std::cout << "Game Over! Collision detected.\n";
                    break;
                }
                
                lastTime = currentTime;
            }
            
            // Рендеринг
            glClear(GL_COLOR_BUFFER_BIT);
            draw_snake(snake);
            
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

int main() {
    try {
        Window window;
        window.start_game_snake();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
