#include "Shader.h"

#ifdef _MSC_VER
#define DEBUG_BREAK __debugbreak
#else
#define DEBUG_BREAK __builtin_trap
#endif

void glClearError()
{
    while (glGetError() != GL_NO_ERROR)
        ;
}

bool glCheckError()
{
    GLenum error;
    while ((error = glGetError()) != GL_NO_ERROR)
    {
        std::cout << "Error: " << error << std::endl;
        DEBUG_BREAK();
    }
    return true;
}

std::string read_from_file(const std::string &filename)
{
    std::ifstream ifs(filename, std::ios::in);
    if (!ifs)
        std::cout << "failed to open file: " << filename << std::endl;
    std::stringstream ss;
    ss << ifs.rdbuf();
    return ss.str();
}

Shader::Shader(const std::string &name)
{
    std::vector<unsigned int> shaders;
    shaders.push_back(CreateShader(GL_VERTEX_SHADER, read_from_file(name + "Vertex.vs")));
    shaders.push_back(CreateShader(GL_FRAGMENT_SHADER, read_from_file(name + "Fragment.fs")));

    m_RendererID = CompileProgram(shaders);
    std::for_each(shaders.begin(), shaders.end(), glDeleteShader);
}

void Shader::createFromFile(const std::string &name)
{
    std::vector<unsigned int> shaders;
    shaders.push_back(CreateShader(GL_VERTEX_SHADER, read_from_file(name + "Vertex.vs")));
    shaders.push_back(CreateShader(GL_FRAGMENT_SHADER, read_from_file(name + "Fragment.fs")));

    m_RendererID = CompileProgram(shaders);
    std::for_each(shaders.begin(), shaders.end(), glDeleteShader);
}

void Shader::bind() const
{
    Call(glUseProgram(m_RendererID));
}

void Shader::unbind() const
{
    Call(glUseProgram(0));
}

void Shader::setUniform1i(const std::string &name, int v0)
{
    bind();
    Call(glUniform1i(GetUniformLocation(name), v0));
}

void Shader::setUniform4f(const std::string &name, glm::vec4 v)
{
    bind();
    Call(glUniform4f(GetUniformLocation(name), v.x, v.y, v.z, v.w));
}

void Shader::setUniform3f(const std::string &name, glm::vec3 v)
{
    bind();
    Call(glUniform3f(GetUniformLocation(name), v.x, v.y, v.z));
}

void Shader::setUniform1f(const std::string &name, float v0)
{
    bind();
    Call(glUniform1f(GetUniformLocation(name), v0));
}

void Shader::setUniformMat4fv(const std::string &name, glm::mat4 matrix)
{
    bind();
    Call(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

void Shader::setUniformMaterial(const std::string &name, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular,
                                float shininess)
{
    bind();
    Call(glUniform3f(GetUniformLocation(name + ".ambient"), ambient.x, ambient.y, ambient.z));
    Call(glUniform3f(GetUniformLocation(name + ".diffuse"), diffuse.x, diffuse.y, diffuse.z));
    Call(glUniform3f(GetUniformLocation(name + ".specular"), specular.x, specular.y, specular.z));
    Call(glUniform1f(GetUniformLocation(name + ".shininess"), shininess));
}

int Shader::GetUniformLocation(const std::string &name)
{
    if (locationCache.find(name) != locationCache.end())
        return locationCache[name];
    int location = glGetUniformLocation(m_RendererID, name.c_str());
    locationCache[name] = location;
    if (location == -1)
        std::cout << "Uniform doesn't exist: " << name << std::endl;
    return location;
}

unsigned int Shader::CreateShader(GLenum type, const std::string &strShaderFile)
{
    unsigned int shader = glCreateShader(type);
    const char *shader_code = strShaderFile.c_str();
    glShaderSource(shader, 1, &shader_code, NULL);
    glCompileShader(shader);
    int status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
        glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

        const char *strShaderType = NULL;
        switch (type)
        {
        case GL_VERTEX_SHADER:
            strShaderType = "vertex";
            break;
        case GL_GEOMETRY_SHADER:
            strShaderType = "geometry";
            break;
        case GL_FRAGMENT_SHADER:
            strShaderType = "fragment";
            break;
        }

        fprintf(stderr, "Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
        delete[] strInfoLog;
    }

    return shader;
}

unsigned int Shader::CompileProgram(std::vector<unsigned int> shaderList)
{
    unsigned int program = glCreateProgram();
    for (auto x : shaderList)
        glAttachShader(program, x);

    glLinkProgram(program);

    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
        glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
        fprintf(stderr, "Linker failure: %s\n", strInfoLog);
        delete[] strInfoLog;
    }

    for (auto x : shaderList)
        glDetachShader(program, x);

    return program;
}
