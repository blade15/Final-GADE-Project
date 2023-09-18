#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

const int boardSize = 8;
const float cellSize = 1.0f;
const float borderWidth = 0.5f;

// Function to draw the chessboard
void drawChessboard() {
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            float x = j * cellSize;
            float z = i * cellSize;

            // Randomize the height offset to create a 3D effect
            float yOffset = static_cast<float>(rand()) / RAND_MAX * 0.2f;

            glBegin(GL_QUADS);
            if ((i + j) % 2 == 0) {
                glColor3f(1.0f, 1.0f, 1.0f);  // White
            }
            else {
                glColor3f(0.0f, 0.0f, 0.0f);  // Black
            }
            glVertex3f(x, yOffset, z);
            glVertex3f(x + cellSize, yOffset, z);
            glVertex3f(x + cellSize, yOffset, z + cellSize);
            glVertex3f(x, yOffset, z + cellSize);
            glEnd();
        }
    }
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create a GLFW window and OpenGL context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow* window = glfwCreateWindow(800, 800, "3D Chessboard", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    srand(static_cast<unsigned>(time(nullptr)));

    // Main rendering loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glTranslatef(-boardSize / 2.0f, 0.0f, -boardSize / 2.0f);  // Center the board

        drawChessboard();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
