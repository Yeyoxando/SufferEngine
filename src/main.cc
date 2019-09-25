#include <stdio.h>
#include <window.h>
#include <glm.hpp>

// --------------------------------------------------------------//

void TestingGLM() {

	glm::vec4 vector_1 = { 1.0f, 1.0f, 1.0f, 1.0f };
	vector_1 *= glm::vec4(2, 2, 2, 2);
	
	float fModule = vector_1.length();
	glm::normalize(vector_1);

	glm::vec4 negative = { -1.0f, -1.0f, -1.0f, -1.0f };
	negative += glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

}

// --------------------------------------------------------------//

int main(int argc, char *argv[]) {

	TestingGLM();

	Suffer::Window wind;

	wind.init(800, 600);

	while(1){
	}

	return 0;
}

// --------------------------------------------------------------//