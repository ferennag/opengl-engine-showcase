#ifndef ENGINE_SHOWCASE_DIRECTIONALLIGHT_H
#define ENGINE_SHOWCASE_DIRECTIONALLIGHT_H

#include <string>
#include <QVector3D>
#include <QOpenGLShaderProgram>

struct DirectionalLight {
    QVector3D direction {0, 0, 0};
    QVector3D ambient {0, 0, 0};
    QVector3D diffuse {0, 0, 0};
    QVector3D specular {0, 0, 0};

    void setUniformValue(const std::string &name, QOpenGLShaderProgram &shader) const {
        shader.setUniformValue((name + ".ambient").c_str(), ambient);
        shader.setUniformValue((name + ".diffuse").c_str(), diffuse);
        shader.setUniformValue((name + ".specular").c_str(), specular);
        shader.setUniformValue((name + ".direction").c_str(), direction);
    }
};

#endif //ENGINE_SHOWCASE_DIRECTIONALLIGHT_H
