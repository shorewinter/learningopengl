#include <glad/glad.h>
#include <GLFW/glfw3.h>

void process_input(GLFWwindow* window){
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

int main(void) {
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(640, 360, "gl", NULL, NULL);
	
    glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
	
    while (!glfwWindowShouldClose(window)) {
        /* render */
		process_input(window);
        
		/* render */
		glClearColor(0.1f, 0.1f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		glfwSwapBuffers(window);
        glfwPollEvents();
    }
	
    glfwTerminate();
    return 0;
}