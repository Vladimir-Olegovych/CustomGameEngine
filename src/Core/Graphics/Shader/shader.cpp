#include "shader.h"

std::string get_file_content(const char *filename)
{
    std::ifstream in(filename, std::ios::binary);
    if (in)
    {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return (contents);
    }
    throw(errno);
}
Shader::Shader(const char *vertexFile, const char *fragmentFile)
{
    std::string vertexCode = get_file_content(vertexFile);
    std::string fragmentCode = get_file_content(fragmentFile);
    const char *vertextSource = vertexCode.c_str();
    const char *fragmentSource = fragmentCode.c_str();
    // Создаем объект вершинного шейдера
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Объединяем объект вершинного шейдера с его кодом
    glShaderSource(vertexShader, 1, &vertextSource, NULL);
    // Компилируем шейдер
    glCompileShader(vertexShader);
    // Создаем объект фрагментного шейдера
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // Объединяем объект фрагментного шейдера с его кодом
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    // Компилируем шейдер
    glCompileShader(fragmentShader);
    // Создаем объект программы шейдера
    ID = glCreateProgram();
    // Объединяем программу шейдера с объектами вершинного и фрагментного шейдера
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    // Связываем все в программе шейдера
    glLinkProgram(ID);
    // Удаляем отработавшие объекты
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}
void Shader::activate()
{
    glUseProgram(ID);
}
void Shader::remove()
{
    glDeleteProgram(ID);
}
void Shader::setInt(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setFloat(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setVec2(const std::string& name, const glm::vec2& value) const {
    glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(value));
}
void Shader::setVec3(const std::string& name, const glm::vec3& value) const {
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(value));
}
void Shader::setMat4(const std::string& name, const glm::mat4& value) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}