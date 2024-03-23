#include "objects/Camera.h"
std::shared_ptr<Camera> Camera::camera;
Camera::Camera()
{
    viewpoint = {1.0f,0.0f,0.0f};
    total = 1.0f;
    center = {0.0f,0.0f,0.0f};
    height = 0;
    width = 0;
    yaw = 0.0f;
    roll = 0.0f;
    xpos = 0;
    ypos = 0;
    uboMatrices = 0;
    proj = glm::mat4(1.0f);
    view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, -0.5f, -1.0f));
}
void Camera::linkShader(Shader* sh)
{
    sh->activate();
    GLuint ufBlockIndex = glGetUniformBlockIndex(sh->ID, "Matrices");
    glUniformBlockBinding(sh->ID, ufBlockIndex, 0);

    glGenBuffers(1, &uboMatrices);

    glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
    glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);

    glBindBufferRange(GL_UNIFORM_BUFFER, 0, uboMatrices, 0, 2 * sizeof(glm::mat4));
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(proj));
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));

    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
void Camera::updateProjection(int w, int h)
{
    proj = glm::perspective(glm::radians(FOV), (float)(h * 1.0 / w * 1.0), 0.1f, 100.0f);
    glViewport(0, 0, w, h);
    width = w;
    height = h;
}
void Camera::setFocus(glm::mat4 focus)
{
    Camera::focus = focus;
}
const glm::mat4& Camera::getProj()
{
    return proj;
}
const glm::mat4& Camera::getView()
{
    return view;
}
glm::vec2 Camera::toXY(glm::mat4 model, glm::vec4 point) {
    glm::vec4 vec = proj * view * focus * point;
    return glm::vec2((1 + vec[0] / vec[3]) * width / 2, (1 + vec[1] / vec[3]) * height / 2);
}
float Camera::distance(std::pair<float, float>& p1, std::pair<float, float> p2)
{
    return sqrtf(
        powf(p1.first - p2.first, 2.0f) +
        powf(p1.second - p2.second, 2.0f));
}
void Camera::handleResize(GLFWwindow* window,int w, int h)
{
    camera->updateProjection(w,h);
}
void Camera::handleMouseButton(GLFWwindow* window, int button, int action, int mods) {
    glfwGetCursorPos(window, &xpos, &ypos);
    if (button == GLFW_MOUSE_BUTTON_1)
        if (action == GLFW_PRESS) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
            glfwGetCursorPos(window, &xpos, &ypos);
        }
        else
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    else if (button == GLFW_MOUSE_BUTTON_2 && action == GLFW_PRESS && GLFW_PRESS == glfwGetKey(window,GLFW_KEY_LEFT_CONTROL))
    {
        double x;
        double y;
        int size[2];
        glfwGetCursorPos(window, &x, &y);
        glfwGetWindowSize(window,size,size+1);
        glm::vec3 directionx = panDirection(*size-x,0);
        glm::vec3 directiony = panDirection(0,*(size+1)-y);
        //TODO determine the point at which is clicked
        //notify(glm::translate());
        
    }
}
//temp
void Camera::handleMouseWheel(GLFWwindow* window, double xoffset, double yoffset)
{
    total += yoffset * PAN_SCALAR * -1;
    refresh();
}
glm::vec3 Camera::panDirection(float xdiff, float ydiff)
{
    ydiff *= -1;
    glm::vec3 localRight = glm::cross(center - viewpoint, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::vec3 localUp = glm::cross(localRight, center - viewpoint);
    glm::mat4 yawRotation = glm::rotate(glm::mat4(1.0f), yaw, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 rollRotation = glm::rotate(glm::mat4(1.0f), roll, localRight);
    glm::vec3 rotatedLocalRight = glm::vec3(yawRotation * glm::vec4(localRight, 0.0f));
    glm::vec3 rotatedLocalUp = glm::vec3(rollRotation * glm::vec4(localUp, 0.0f));
    glm::vec3 finalRight = glm::normalize(glm::cross(center - viewpoint, rotatedLocalUp));
    glm::vec3 finalUp = glm::normalize(glm::cross(rotatedLocalRight, center - viewpoint));

    return (finalRight*xdiff)+(finalUp*ydiff);
}
float Camera::subtractFromOne(float num) {
    if (num > 0.0f)
        return 1.0f - num;
    else
        return -1.0f - num;
}
void Camera::handleKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_EQUAL)
    {
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        {
            total -= .05f;
            if (total < .05f)
                total = .05f;
            refresh();
        }
        else
        {
            total += .05f;
            refresh();
        }
    }
}
void Camera::handleDrag(GLFWwindow* window,double xnewpos, double ynewpos) {
    if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_HIDDEN)
        if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        {
            glm::vec3 var = panDirection(xpos-xnewpos,ypos-ynewpos);
            center += var * PAN_SCALAR;
            refresh();
            xpos = xnewpos;
            ypos = ynewpos;
        }
        else
        {
            yaw -= (float)glm::radians(xpos - xnewpos);
            roll += (float)glm::radians(ypos - ynewpos);
            if (roll > 1.0f)
                roll = .999f;
            if (roll < -1.0f)
                roll = -.999f;
            refresh();
            xpos = xnewpos;
            ypos = ynewpos;
        }
}
void Camera::refresh()
{
    float zperc = sinf(yaw * PI);
    float xperc = cosf(yaw * PI);

    viewpoint = glm::vec3(center);
    float temp = total - fabs(total * roll);
    viewpoint[1] += total * roll;
    viewpoint[2] += zperc * temp;
    viewpoint[0] += xperc * temp;

    view = glm::lookAt(viewpoint, center, glm::vec3(0.0f, 1.0f, 0.0f));

    glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}