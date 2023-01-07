#ifndef ENGINE_SHOWCASE_POINTLIGHT_H
#define ENGINE_SHOWCASE_POINTLIGHT_H

#include <QVector3D>
#include <QOpenGLShaderProgram>

struct PointLight {
    QVector3D position{0, 0, 0};
    QVector3D ambient{0, 0, 0};
    QVector3D diffuse{0, 0, 0};
    QVector3D specular{0, 0, 0};
    float constant{0};
    float linear{0};
    float quadratic{0};

    void setUniformValue(const std::string &name, QOpenGLShaderProgram &shader) const {
        shader.setUniformValue((name + ".ambient").c_str(), ambient);
        shader.setUniformValue((name + ".diffuse").c_str(), diffuse);
        shader.setUniformValue((name + ".specular").c_str(), specular);
        shader.setUniformValue((name + ".position").c_str(), position);
        shader.setUniformValue((name + ".constant").c_str(), constant);
        shader.setUniformValue((name + ".linear").c_str(), linear);
        shader.setUniformValue((name + ".quadratic").c_str(), quadratic);
    }
};

#endif //ENGINE_SHOWCASE_POINTLIGHT_H
