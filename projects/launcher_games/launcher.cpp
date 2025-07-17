///////
// CREATED BY korp #17.07.25#
// launcher definition
//////

#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
int main() {
    // Инициализация GLFW
    if (!glfwInit()) {
        return -1;
    }

    // Настройка окна и контекста OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Создание окна
    GLFWwindow* window = glfwCreateWindow(800, 600, "Game Launcher", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // gpt_ask_1
    glfwMakeContextCurrent(window);
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    
    // Главный цикл
    while (!glfwWindowShouldClose(window)) {
        // Очистка экрана (чёрный)
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Здесь будет рендеринг (кнопки, текст и т. д.)
        
        //gpt_ask_2
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        ImGui::Begin("Game Launcher");
        if (ImGui::Button("Launch Game")) {
        system("./game_executable"); // Запуск игры
        }
        ImGui::End();

        // Рендеринг ImGui
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


        // Обмен буферов и обработка событий
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Завершение работы
    glfwTerminate();
    return 0;
}
