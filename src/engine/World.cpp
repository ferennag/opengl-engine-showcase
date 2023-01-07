#include "World.h"
#include "texture/TextureManager.h"
#include "shader/ShaderManager.h"

World::World(const ProjectionType projectionType, const QSize &viewportSize) {
    m_projectionType = projectionType;
    m_viewportSize = viewportSize;
    setupProjection();

    m_camera.setPosition({0, 2, 5});

    dirLight.ambient = {0.2, 0.2, 0.2};
    dirLight.diffuse = {0.9, 0.9, 0.9};
    dirLight.specular = {1, 1, 1};
    dirLight.direction = {0, 2, -5};

    pointLight.ambient = {0.2, 0.2, 0.2};
    pointLight.diffuse = {0.9, 0.2, 0.2};
    pointLight.specular = {1, 1, 1};
    pointLight.position = {3, 1, 0};
    pointLight.constant = 1.0;
    pointLight.linear = 0.022;
    pointLight.quadratic = 0.0019;

    ShaderManager::getInstance().load("simple", "../resources/shaders/simple-vertex.glsl", "../resources/shaders/simple-fragment.glsl");
    ShaderManager::getInstance().load("other", "../resources/shaders/simple-vertex.glsl", "../resources/shaders/simple-fragment.glsl");
    TextureManager::getInstance().loadTexture("container", "../resources/textures/container.png");
    TextureManager::getInstance().loadTexture("container-specular", "../resources/textures/container_specular.png");
    m_cube = std::make_unique<Cube>("container", "container-specular");
}

void World::setupProjection() {
    const auto w = static_cast<float>(m_viewportSize.width());
    const auto h = static_cast<float>(m_viewportSize.height());

    if (m_projectionType == ProjectionType::ORTHOGRAPHIC) {
        m_projection.setToIdentity();
        m_projection.ortho(0, 0, w, h, 0.1f, 100.0f);
    } else {
        m_projection.setToIdentity();
        m_projection.perspective(45.0f, w / h, 0.1f, 100.0f);
    }
}

void World::setViewportSize(const QSize &viewportSize) {
    m_viewportSize = viewportSize;
    setupProjection();
}

void World::update(double deltaTime) {
}

void World::render(double deltaTime) {
    auto& shaderProgram = ShaderManager::getInstance().getShaderProgram("simple");
    auto view = m_camera.getViewMatrix();
    m_cube->rotate(deltaTime * 20.0);

    shaderProgram.bind();
    shaderProgram.setUniformValue("projection", m_projection);
    shaderProgram.setUniformValue("view", view);
    shaderProgram.setUniformValue("model", m_cube->getModelMatrix());
    shaderProgram.setUniformValue("normalMatrix", m_cube->getNormalMatrix());
    shaderProgram.setUniformValue("viewPos", m_camera.getPosition());
    dirLight.setUniformValue("dirLight", shaderProgram);
    pointLight.setUniformValue("pointLight", shaderProgram);
    m_cube->getMaterial().setUniformValue("material", shaderProgram);

    m_cube->render();
    shaderProgram.release();
}
