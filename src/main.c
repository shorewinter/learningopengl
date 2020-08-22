#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stdio.h"
#include "math.h"

/* vertex shader */
const char *vertexShaderSource = 
	"#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"layout (location = 1) in vec3 aColor;\n"
	"out vec3 ourColor;\n"
	"void main()\n"
	"{\n"
	"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"	ourColor = aColor;\n"
	"}\0";

/* fragment shader */
const char *fragmentShaderSource = 
	"#version 330 core\n"
	"out vec4 FragColor;\n"
	"in vec3 ourColor;\n"
	"void main()\n"
	"{\n"
	"	FragColor = vec4(ourColor, 1.0);\n"
	"}\0";

/* user input */
void process_input(GLFWwindow* window){
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

/* resize window */
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

int main(void) {
	/* initialize glfw & glad */
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(1024, 576, "gl", NULL, NULL);
    glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
	
	/* compile vertex shader */
	unsigned int vertex_shader;
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertex_shader);
	
	/* check vertex shader errors */
	int success;
	char info_log[512];
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if(!success) {
		glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
		printf("%s\n", info_log);
	}
	
	/* compile fragment shader */
	unsigned int fragment_shader;
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragment_shader);
	
	/* check fragment shader errors */
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if(!success) {
		glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
		printf("%s\n", info_log);
	}
	
	/* link shaders */
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertex_shader);
	glAttachShader(shaderProgram, fragment_shader);
	glLinkProgram(shaderProgram);
	
	/* check link errors */
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if(!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, info_log);
		printf("%s\n", info_log);
	}
	
	/* delete shaders */
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	
	// /* rectangle (vertex data) */
	// float vertices[] = {
	// 	 0.5f,  0.5f, 0.0f,  /* top right */
	// 	 0.5f, -0.5f, 0.0f,  /* bottom right */
	// 	-0.5f, -0.5f, 0.0f, /* bottom left */
	// 	-0.5f,  0.5f, 0.0f,  /* top left */
	// };

	/* triangle */
	float vertices[] = {
		/* postitions */ /* colors */   
		 0.5, -0.5, 0.0, 0.0, 1.0, 0.0, /* bottom right */
		-0.5, -0.5, 0.0, 1.0, 0.0, 0.0, /* bottom left */
		 0.0,  0.5, 0.0, 0.0, 0.0, 1.0  /* top */
	};

	unsigned int indicies[] = {
		0, 1, 3, /* first triangle */
		1, 2, 3  /* second triangle */
	};
	
	/* vertex array object */
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	/* vertex buffer object */
	unsigned int VBO;
	glGenBuffers(1, &VBO); /* creates a vbo */
	glBindBuffer(GL_ARRAY_BUFFER, VBO); /* binds the vbo to the GL_ARRAY_BUFFER type */
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); /* copys vertices to currently bound buffer */
	
	/* element buffer object */
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

	/* position attributes */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);	

	/* color attributes */
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
	/* render loop */
    while (!glfwWindowShouldClose(window)) {
		/* input */
		process_input(window);

		/* clear color buffer */
    	glClearColor(0.9, 0.9, 0.9, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		
		/* update unifrom color */
		float time = glfwGetTime();
		float green = sin(time) / 2.0 + 0.5;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		glUniform4f(vertexColorLocation, 0.0, green, 0.0, 1.0);
		
		/* render */
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); /* wireframe */
		// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// glBindVertexArray(0);	

		/* swap buffers and poll IO events */
		glfwSwapBuffers(window);
        glfwPollEvents();
    }

	glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
	
	/* exit */
    glfwTerminate();
    return 0;
}