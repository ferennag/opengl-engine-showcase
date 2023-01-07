#include <string>
#include <string_view>
#include <QOpenGLTexture>
#include <QOpenGLVersionFunctionsFactory>
#include <QOpenGLFunctions_4_3_Core>
#include "Cube.h"
#include "../texture/TextureManager.h"

Cube::Cube(std::string_view textureName, std::string_view specularTextureName) {
    m_textureName = textureName;
    m_specularTextureName = specularTextureName;
    m_material = {
            .shininess = 32.2f,
    };

    auto gl = QOpenGLVersionFunctionsFactory::get<QOpenGLFunctions_4_3_Core>();

    gl->glGenVertexArrays(1, &vao);
    gl->glBindVertexArray(vao);
    gl->glGenBuffers(1, &vbo);
    gl->glBindBuffer(GL_ARRAY_BUFFER, vbo);
    gl->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    gl->glEnableVertexAttribArray(0);
    gl->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) nullptr);
    gl->glEnableVertexAttribArray(1);
    gl->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
    gl->glEnableVertexAttribArray(2);
    gl->glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (5 * sizeof(float)));
    gl->glBindVertexArray(0);
}

QMatrix4x4 Cube::getModelMatrix() const {
    QMatrix4x4 model;
    model.setToIdentity();
    model.rotate(m_rotation, {0, 1, 0});
    return model;
}

void Cube::render() {
    auto& texture = TextureManager::getInstance().getTexture(m_textureName);
    auto& specularTexture = TextureManager::getInstance().getTexture(m_specularTextureName);
    auto gl = QOpenGLVersionFunctionsFactory::get<QOpenGLFunctions_4_3_Core>();
    gl->glBindVertexArray(vao);
    // TODO not working, only one texture is ivsible at anyt tgiven time
    gl->glActiveTexture(GL_TEXTURE0);
    gl->glBindTexture(GL_TEXTURE_2D, texture.textureId());
    gl->glActiveTexture(GL_TEXTURE1);
    gl->glBindTexture(GL_TEXTURE_2D, specularTexture.textureId());
    gl->glDrawArrays(GL_TRIANGLES, 0, 36);
    texture.release();
    specularTexture.release();
    gl->glBindVertexArray(0);
}

void Cube::cleanup() {
    auto gl = QOpenGLVersionFunctionsFactory::get<QOpenGLFunctions_4_3_Core>();
    gl->glDeleteBuffers(1, &vbo);
    gl->glDeleteVertexArrays(1, &vao);
}

Material Cube::getMaterial() const {
    return m_material;
}
