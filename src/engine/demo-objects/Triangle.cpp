#include <QOpenGLVersionFunctionsFactory>
#include <QOpenGLFunctions_4_3_Core>
#include <QMatrix4x4>
#include "Triangle.h"

Triangle::Triangle() {
    auto gl = QOpenGLVersionFunctionsFactory::get<QOpenGLFunctions_4_3_Core>();;

    gl->glGenVertexArrays(1, &vao);
    gl->glBindVertexArray(vao);
    gl->glGenBuffers(1, &vbo);
    gl->glBindBuffer(GL_ARRAY_BUFFER, vbo);
    gl->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    gl->glEnableVertexAttribArray(0);
    gl->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) nullptr);
    gl->glBindVertexArray(0);
}

void Triangle::render() {
    auto gl = QOpenGLVersionFunctionsFactory::get<QOpenGLFunctions_4_3_Core>();
    gl->glBindVertexArray(vao);
    gl->glDrawArrays(GL_TRIANGLES, 0, 3);
    gl->glBindVertexArray(0);
}

QMatrix4x4 Triangle::getModelMatrix() const {
    QMatrix4x4 model;
    model.setToIdentity();
    return model;
}

void Triangle::cleanup() {
    auto gl = QOpenGLVersionFunctionsFactory::get<QOpenGLFunctions_4_3_Core>();
    gl->glDeleteBuffers(1, &vbo);
    gl->glDeleteVertexArrays(1, &vao);
}
