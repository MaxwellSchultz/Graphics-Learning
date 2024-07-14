#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "\tgl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSourceOrange = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "\tFragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

const char *fragmentShaderSourceYellow = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "\tFragColor = vec4(0.98f, 0.73f, 0.01f, 1.0f);\n"
    "}\0";

int main(void)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Alex is real pretty", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return EXIT_FAILURE;
    }

    glViewport(0,0,800,600);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" 
                << infoLog << std::endl;
    }

    unsigned int fragmentShaderOrange;
    fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderOrange, 1, &fragmentShaderSourceOrange, NULL);
    glCompileShader(fragmentShaderOrange);

    glGetShaderiv(fragmentShaderOrange, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShaderOrange, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" 
                << infoLog << std::endl;
    }

    unsigned int fragmentShaderYellow;
    fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderYellow, 1, &fragmentShaderSourceYellow, NULL);
    glCompileShader(fragmentShaderYellow);

    glGetShaderiv(fragmentShaderYellow, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShaderYellow, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" 
                << infoLog << std::endl;
    }

    unsigned int shaderProgramOrange, shaderProgramYellow;
    shaderProgramOrange = glCreateProgram();
    shaderProgramYellow = glCreateProgram();

    glAttachShader(shaderProgramOrange, vertexShader);
    glAttachShader(shaderProgramOrange, fragmentShaderOrange);
    glLinkProgram(shaderProgramOrange);

    glGetShaderiv(shaderProgramOrange, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shaderProgramOrange, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" 
                << infoLog << std::endl;
    }

    glAttachShader(shaderProgramYellow, vertexShader);
    glAttachShader(shaderProgramYellow, fragmentShaderYellow);
    glLinkProgram(shaderProgramYellow);

    glGetShaderiv(shaderProgramYellow, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shaderProgramYellow, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" 
                << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShaderOrange);
    glDeleteShader(fragmentShaderYellow);


    // vertex data
    float triangle_vertices_left[] = {
        -0.6f, -0.25f, 0.0f,
        -0.1f, -0.25f, 0.0f,
        -0.35f, 0.25f, 0.0f
    };

    float triangle_vertices_right[] = {
        0.6f, -0.25f, 0.0f,
        0.1f, -0.25f, 0.0f,
        0.35f, 0.25f, 0.0f
    };

    // float rectangle_vertices[] = {
    //     // first triangle
    //     0.5f, 0.5f, 0.0f, // top right
    //     0.5f, -0.5f, 0.0f, // bottom right
    //     -0.5f, 0.5f, 0.0f, // top left
    //     // second triangle
    //     0.5f, -0.5f, 0.0f, // bottom right
    //     -0.5f, -0.5f, 0.0f, // bottom left
    //     -0.5f, 0.5f, 0.0f // top left
    // };  

    // Element Buffer Object Ex
    // float rectangle_vertices[] = {
    //     0.5f, 0.5f, 0.0f, // top right
    //     0.5f, -0.5f, 0.0f, // bottom right
    //     -0.5f, -0.5f, 0.0f, // bottom left
    //     -0.5f, 0.5f, 0.0f // top left
    // };

    // unsigned int rectangle_indices[] = { 
    //     0, 1, 3, // first triangle
    //     1, 2, 3 // second triangle
    // };

    unsigned int VBO_left, VAO_left, VBO_right, VAO_right;
    glGenVertexArrays(1, &VAO_left);
    glGenBuffers(1, &VBO_left);
    glBindVertexArray(VAO_left);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_left);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices_left), 
                        triangle_vertices_left, GL_STATIC_DRAW);

    // VBO
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    // UNBIND
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glGenVertexArrays(1, &VAO_right);
    glGenBuffers(1, &VBO_right);
    glBindVertexArray(VAO_right);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_right);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices_right), 
                    triangle_vertices_right, GL_STATIC_DRAW);

    // VBO
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //EBO
    // unsigned int EBO;
    // glGenBuffers(1, &EBO);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rectangle_indices), 
    //                 rectangle_indices, GL_STATIC_DRAW);

    

    // unbind buffer as glVertexAttribPointer registered VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // unbinds VBO but not necessary
    //glBindVertexArray(0)

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        // rendering commands
        glClearColor(0.2f,0.3f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgramOrange);
        glBindVertexArray(VAO_left); // unnecessary to bind every time when there is only one
        // glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
        glDrawArrays(GL_TRIANGLES,0,3);
        glBindVertexArray(0);
        glUseProgram(shaderProgramYellow);
        glBindVertexArray(VAO_right);
        glDrawArrays(GL_TRIANGLES,0,3);
        glBindVertexArray(0);

        // check and poll events / swap buffer
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return EXIT_SUCCESS;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0,0,width,height);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}