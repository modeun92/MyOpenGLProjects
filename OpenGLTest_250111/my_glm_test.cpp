#include "config.cpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
glm::mat4 test1();
glm::mat4 test2();
int main() {
    //glm::mat4 trans(test1());
    glm::mat4 trans(test2());
    glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
    vec = trans * vec;
    cout << "vec : {" << vec.x << ", " << vec.y << ", " << vec.z << "}" << endl;
    return 0;
}
glm::mat4 test1() {
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
    return trans;
}
glm::mat4 test2() {
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::rotate(trans, glm::radians(70.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));
    return trans;
}
