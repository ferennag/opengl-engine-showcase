#ifndef ENGINE_SHOWCASE_CAMERA_H
#define ENGINE_SHOWCASE_CAMERA_H

#include <QVector3D>
#include <QMatrix4x4>

class Camera {
public:
    Camera() = default;
    Camera(const QVector3D &pos, const QVector3D &target);
    virtual ~Camera() = default;
    void setPosition(const QVector3D &pos);
    QVector3D getPosition() const;
    void setTarget(const QVector3D &target);
    QVector3D getTarget() const;

    QMatrix4x4 getViewMatrix() const;
protected:
    QVector3D m_position {0, 0, -1};
    QVector3D m_target {0, 0, 0};
};


#endif //ENGINE_SHOWCASE_CAMERA_H
