#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_opengl3_loader.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>

using json = nlohmann::json;

struct TodoItem {
    std::string text;
    bool done = false;
};

std::vector<TodoItem> todos;
char inputText[256] = "";
bool saveRequested = false;

void saveTodos(const std::vector<TodoItem>& list, const std::string& filename) {
    json j;
    for (const auto& item : list) {
        j.push_back({ {"text", item.text}, {"done", item.done} });
    }
    std::ofstream file(filename);
    if (file) file << j.dump(2);
}

void loadTodos(std::vector<TodoItem>& list, const std::string& filename) {
    std::ifstream file(filename);
    if (!file) return;
    json j;
    file >> j;
    for (auto& entry : j) {
        list.push_back({ entry["text"], entry["done"] });
    }
}

void glfw_error_callback(int error, const char* description) {
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

int main() {
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) return 1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow* window = glfwCreateWindow(800, 600, "To-Do App", nullptr, nullptr);
    if (!window) return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (!gladLoadGL()) {
        fprintf(stderr, "Failed to initialize GLAD\n");
        return 1;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    loadTodos(todos, "tasks.json");

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("📋 To-Do List");

        if (ImGui::InputText("##NewTask", inputText, IM_ARRAYSIZE(inputText), ImGuiInputTextFlags_EnterReturnsTrue)) {
            if (strlen(inputText) > 0) {
                todos.push_back({ inputText });
                memset(inputText, 0, sizeof(inputText));
            }
        }

        for (int i = 0; i < todos.size(); ++i) {
            ImGui::PushID(i);
            ImGui::Checkbox("##done", &todos[i].done);
            ImGui::SameLine();
            ImGui::Text("%s", todos[i].text.c_str());
            ImGui::SameLine(ImGui::GetWindowWidth() - 100);
            if (ImGui::Button("Delete")) {
                todos.erase(todos.begin() + i);
                ImGui::PopID();
                break;
            }
            ImGui::PopID();
        }

        if (ImGui::Button("💾 Save")) {
            saveRequested = true;
        }

        ImGui::End();

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.1f, 0.12f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);

        if (saveRequested) {
            saveTodos(todos, "tasks.json");
            saveRequested = false;
        }
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}