#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stdio.h"
#include "math.h"

#include "shader.h"

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

	Shader ourShader("src\\shader.vs", "src\\shader.fs");

	/* triangle */
	float vertices[] = {
		/* postitions */ /* colors */   
		 0.5, -0.5, 0.0, 0.0, 1.0, 0.0, /* bottom right */
		-0.5, -0.5, 0.0, 1.0, 0.0, 0.0, /* bottom left */
		 0.0,  0.5, 0.0, 0.0, 0.0, 1.0  /* top */
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
    	glClearColor(0.1, 0.5, 0.2, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		
		/* render */
		ourShader.use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		/* swap buffers and poll IO events */
		glfwSwapBuffers(window);
        glfwPollEvents();
    }

	glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

	/* exit */
    glfwTerminate();
    return 0;
}