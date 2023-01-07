#include "Camera.h"

Camera::Camera(const QVector3D &pos, const QVector3D &target) {
    setPosition(pos);
    setTarget(target);
}

QMatrix4x4 Camera::getViewMatrix() const {
    auto view = QMatrix4x4();
    view.setToIdentity();
    view.lookAt(m_position, m_target, {0, 1, 0});
    return view;
}

void Camera::setPosition(const QVector3D &pos) {
    m_position = pos;
}

QVector3D Camera::getPosition() const {
    return m_position;
}

void Camera::setTarget(const QVector3D &target) {
    m_target = target;
}

QVector3D Camera::getTarget() const {
    return m_target;
}
