#ifndef ENGINE_SHOWCASE_WORLD_H
#define ENGINE_SHOWCASE_WORLD_H

#include <memory>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QSize>
#include "camera/Camera.h"
#include "demo-objects/Cube.h"
#include "lighting/DirectionalLight.h"
#include "lighting/PointLight.h"

enum class ProjectionType {
    PERSPECTIVE,
    ORTHOGRAPHIC
};

class World {
public:
    World(ProjectionType projectionType, const QSize &viewportSize);
    World(const World& other) = delete;
    World& operator=(const World& other) = delete;
    virtual ~World() = default;

    void setViewportSize(const QSize &viewportSize);
    void update(double deltaTime);
    void render(double deltaTime);
protected:
    Camera m_camera;
    ProjectionType m_projectionType;
    QMatrix4x4 m_projection;
    QSize m_viewportSize;
    std::unique_ptr<Cube> m_cube;
    DirectionalLight dirLight;
    PointLight pointLight;

    void setupProjection();
};


#endif //ENGINE_SHOWCASE_WORLD_H
