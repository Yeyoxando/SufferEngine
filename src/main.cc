#include <stdio.h>
#include <GL/glew.h>
#include <window.h>
#include <glm.hpp>
#include <imgui.h>

// --------------------------------------------------------------//

void TestingGLM() {

	glm::vec4 vector_1 = { 1.0f, 1.0f, 1.0f, 1.0f };
	vector_1 *= glm::vec4(2, 2, 2, 2);
	
	float fModule = vector_1.length();
	vector_1 = glm::normalize(vector_1);

	glm::vec4 negative = { -1.0f, -1.0f, -1.0f, -1.0f };
	negative += glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

}

// --------------------------------------------------------------//

void TestingImGui() {

	ImGui::Begin("Testing");
	ImGui::End();

}

// --------------------------------------------------------------//

int main(int argc, char *argv[]) {

	TestingGLM();

	Suffer::Window wind;

	wind.init(800, 600);
	if (glewInit() != GLEW_OK) {
		return 1;
	}

	glClearColor(1.0f, 0.0f, 1.0f, 0.0f);

	while(1){
		wind.swapBuffers();
		glClear(GL_COLOR_BUFFER_BIT);
	}

	return 0;
}

// --------------------------------------------------------------//