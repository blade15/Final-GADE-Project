//#include <stdio.h>
//#include <string.h>
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//#define STB_IMAGE_IMPLEMENTATION
//#include <stb_image.h>
//
//// Dimensions for our height map
//#define WIDTH 500
//#define HEIGHT 500
//
//float heightMap[WIDTH][HEIGHT];
//
//GLuint vertexArray;
//GLuint vertexBuffer;
//GLuint indexBuffer;
//GLuint shaderProgram;
//
//// Load a raw grayscale image as a height map
//void loadHeightmap(const char* filename) {
//    FILE* file = fopen(filename, "rb");
//    if (!file) {
//        printf("Failed to open %s\n", filename);
//        return;
//    }
//
//    for (int y = 0; y < HEIGHT; y++) {
//        for (int x = 0; x < WIDTH; x++) {
//            unsigned char value;
//            fread(&value, 1, 1, file);
//            heightMap[x][y] = (float)value / 255.0f;
//        }
//    }
//
//    fclose(file);
//}
//
//void initOpenGL() {
//    // Initialize GLEW
//    glewInit();
//
//    // Vertex data
//    GLfloat vertices[WIDTH * HEIGHT * 3]; // x, y, z
//    for (int y = 0; y < HEIGHT; y++) {
//        for (int x = 0; x < WIDTH; x++) {
//            vertices[(y * WIDTH + x) * 3 + 0] = x;
//            vertices[(y * WIDTH + x) * 3 + 1] = heightMap[x][y];
//            vertices[(y * WIDTH + x) * 3 + 2] = y;
//        }
//    }
//
//    // Index data
//    GLuint indices[(WIDTH - 1) * (HEIGHT - 1) * 6]; // 2 triangles per cell = 6 indices
//    int counter = 0;
//    for (int y = 0; y < HEIGHT - 1; y++) {
//        for (int x = 0; x < WIDTH - 1; x++) {
//            // First triangle
//            indices[counter++] = y * WIDTH + x;
//            indices[counter++] = (y + 1) * WIDTH + x;
//            indices[counter++] = y * WIDTH + x + 1;
//
//            // Second triangle
//            indices[counter++] = y * WIDTH + x + 1;
//            indices[counter++] = (y + 1) * WIDTH + x;
//            indices[counter++] = (y + 1) * WIDTH + x + 1;
//        }
//    }
//
//    glGenVertexArrays(1, &vertexArray);
//    glBindVertexArray(vertexArray);
//
//    glGenBuffers(1, &vertexBuffer);
//    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//    glGenBuffers(1, &indexBuffer);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//   
//
//// Vertex Shader
//    const char* vertexShaderSource = R"glsl(
//    #version 330 core
//    layout(location = 0) in vec3 inPosition;
//
//    uniform mat4 model;
//    uniform mat4 view;
//    uniform mat4 projection;
//
//    void main()
//    {
//        gl_Position = projection * view * model * vec4(inPosition, 1.0);
//    }
//    )glsl";
//
//    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
//    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//    glCompileShader(vertexShader);
//
//    // Fragment Shader
//    const char* fragmentShaderSource = R"glsl(
//    #version 330 core
//    out vec4 FragColor;
//
//    void main()
//    {
//        FragColor = vec4(0.5, 0.5, 0.5, 1.0);  // Simple gray color
//    }
//    )glsl";
//
//    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//    glCompileShader(fragmentShader);
//
//    shaderProgram = glCreateProgram();
//    glAttachShader(shaderProgram, vertexShader);
//    glAttachShader(shaderProgram, fragmentShader);
//    glLinkProgram(shaderProgram);
//
//    glDeleteShader(vertexShader);
//    glDeleteShader(fragmentShader);
//
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glBindVertexArray(0);
//}
//
//int main() {
//    if (!glfwInit()) {
//        printf("Failed to initialize GLFW.\n");
//        return -1;
//    }
//
//    GLFWwindow* window = glfwCreateWindow(800, 600, "Heightmap OpenGL", NULL, NULL);
//    if (!window) {
//        printf("Failed to create GLFW window.\n");
//        glfwTerminate();
//        return -1;
//    }
//
//    glfwMakeContextCurrent(window);
//
//    initOpenGL();
//    loadHeightmap("path_to_your_heightmap.raw");  // Provide the correct path
//
//    while (!glfwWindowShouldClose(window)) {
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//        glUseProgram(shaderProgram);
//
//        // Set uniform values for model, view, projection etc. 
//
//        glBindVertexArray(vertexArray);
//        glDrawElements(GL_TRIANGLES, (WIDTH - 1) * (HEIGHT - 1) * 6, GL_UNSIGNED_INT, 0);
//
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    glDeleteVertexArrays(1, &vertexArray);
//    glDeleteBuffers(1, &vertexBuffer);
//    glDeleteBuffers(1, &indexBuffer);
//
//    glfwDestroyWindow(window);
//    glfwTerminate();
//    return 0;
//}

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

