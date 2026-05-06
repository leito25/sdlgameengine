#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

int main(int argc, char* argv[]) {
    glm::vec3 position(1.0f, 2.0f, 3.0f);
    glm::mat4 matrix = glm::translate(glm::mat4(1.0f), position);

    std::cout << "✓ GLM is working!" << std::endl;
    std::cout << "GLM Version: " << GLM_VERSION_MAJOR << "."
              << GLM_VERSION_MINOR << "." << GLM_VERSION_PATCH << std::endl;
    std::cout << "Vector position: (" << position.x << ", " << position.y << ", " << position.z << ")" << std::endl;

    return 0;
}
