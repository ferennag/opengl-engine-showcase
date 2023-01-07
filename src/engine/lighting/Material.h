#ifndef ENGINE_SHOWCASE_MATERIAL_H
#define ENGINE_SHOWCASE_MATERIAL_H

#include <string>
#include <QVector3D>
#include <QOpenGLShaderProgram>

struct Material {
    int diffuse {0};
    int specular {1};
    float shininess {0};

    void setUniformValue(const std::string &name, QOpenGLShaderProgram &shader) const {
        shader.setUniformValue((name + ".diffuse").c_str(), diffuse);
        shader.setUniformValue((name + ".specular").c_str(), specular);
        shader.setUniformValue((name + ".shininess").c_str(), shininess);
    }
};

#endif //ENGINE_SHOWCASE_MATERIAL_H
