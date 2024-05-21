#ifdef __APPLE__
// Defined before OpenGL and GLUT includes to avoid deprecation messages
#define GL_SILENCE_DEPRECATION
#include <iostream>
#include "mesh.h"
#include "model.h"
#endif

const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

int main() {

    glfwInit();

    // Window Hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Initializing a Window
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to make window" << std::endl;
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);

    // Loading GLAD
    gladLoadGL();

    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    Shader shaderProgram(
            "resources/shaders/default.vert",
            "resources/shaders/default.frag"
    );

    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);

    float ambient = 0.8F;
    float rotX = 1.0f;
    double prevTime = glfwGetTime();

    shaderProgram.Activate();
    glUniform4f(glGetUniformLocation(shaderProgram.id, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(shaderProgram.id, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
    glUniform1i(glGetUniformLocation(shaderProgram.id, "lightMode"), 0);
    glUniform1f(glGetUniformLocation(shaderProgram.id, "ambient"), ambient);
    glEnable(GL_DEPTH_TEST);

    Camera camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0f, 0.0f, 10.0f));

    Model model("resources/models/map/scene.gltf");

    // Keeping the Window Alive
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.Inputs(window);
        camera.updateMatrix(45.0f, 0.1f, 200.0f);

        if (glfwGetKey(window, GLFW_KEY_1)) {
            glUniform1i(glGetUniformLocation(shaderProgram.id, "lightMode"), 0);
        }

        if (glfwGetKey(window, GLFW_KEY_2)) {
            glUniform1i(glGetUniformLocation(shaderProgram.id, "lightMode"), 1);
        }

        if (glfwGetKey(window, GLFW_KEY_3)) {
            glUniform1i(glGetUniformLocation(shaderProgram.id, "lightMode"), 2);
        }

        if (glfwGetKey(window, GLFW_KEY_UP)) {
            ambient += 0.001f;
            glUniform1f(glGetUniformLocation(shaderProgram.id, "ambient"), ambient);
        }

        if (glfwGetKey(window, GLFW_KEY_DOWN)) {
            ambient -= 0.001f;
            glUniform1f(glGetUniformLocation(shaderProgram.id, "ambient"), ambient);
        }

        model.Draw(shaderProgram, camera);

        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    shaderProgram.Delete();

    // Destroy the Window
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}