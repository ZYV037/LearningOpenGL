﻿#include <stdio.h>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void process_input(GLFWwindow* window)
{
    if( GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE) )
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

void frabe_buffersize_callback_fun(GLFWwindow* /*window*/, int width, int height)
{
    glViewport(0, 0, width, height);
}

char* vertexShaderSource = \
"#version 460 core\n    \
layout (location = 0) in vec3 aPos;\n   \
void main()\n \
{\n   \
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n    \
}\n\0";

char* fragmentShaderSource = \
"#version 460 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


int main()
{
	// glfw initialize and configure---------------------------------------------------------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation-----------------------------------------------------------------------------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello Triangle", nullptr, nullptr);
    if(window == nullptr)
    {
        std::cout << "Failed to glfwCreateWindow()!" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, frabe_buffersize_callback_fun);

	// glad: load all opengl function pointers---------------------------------------------------------------------
    if( !gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize glad!" << std::endl;
        return -1;
    }

	//build and compile our shader program-------------------------------------------------------------------------
    //vertex shader
    unsigned int vertex_shader;
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertex_shader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertex_shader);

    int sucess;
    char infoLog[512];
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &sucess);
    if(!sucess)
    {
        glGetShaderInfoLog(vertex_shader, 512, nullptr, infoLog);
        std::cout << "Error::SHADER::VERTEX::COMPILATION\n" << infoLog << std::endl;
    }

	//fragment shader
    unsigned int fragment_shader;
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragment_shader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragment_shader);

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &sucess);
    if(!sucess)
    {
        glGetShaderInfoLog(fragment_shader, 512, nullptr, infoLog);
        std::cout << "Error::SHADER::FRAGMENT::COMPILATION\n" << infoLog << std::endl;
    }

    // link shaders
    unsigned int shader_programe;
    shader_programe = glCreateProgram();

    glAttachShader(shader_programe, vertex_shader);
    glAttachShader(shader_programe, fragment_shader);
    glLinkProgram(shader_programe);

    glGetProgramiv(shader_programe, GL_LINK_STATUS, &sucess);
    if(!sucess)
    {
        glGetProgramInfoLog(shader_programe, 512, nullptr, infoLog);
        std::cout << "Error::PROGRAME::LINK\n" << infoLog << std::endl;
    }
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

	// set up vertex data( and buffers(s)) and configure vertex attributes-------------------------------------
    float vertices[] =
    {
        -0.5f, -0.5f, 0.0f,	//left
         0.5f, -0.5f, 0.0f,	//right
         0.0f,  0.5f, 0.0f  //top
    };

    unsigned int VBO;
    glGenBuffers(1, &VBO);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s)
    glBindVertexArray(VAO);

    glBindBuffer( GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0 );
    glEnableVertexAttribArray(0);

    //unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glUseProgram(shader_programe);
    glBindVertexArray(VAO);

    while(!glfwWindowShouldClose(window))
    {
		process_input(window);

		//render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glDeleteProgram(shader_programe);

    glfwTerminate();
    return 0;
}
