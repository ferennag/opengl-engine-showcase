#ifndef ENGINE_SHOWCASE_DEMOOBJECT_H
#define ENGINE_SHOWCASE_DEMOOBJECT_H

#include <QMatrix3x3>
#include <QMatrix4x4>

class DemoObject {
public:
    virtual ~DemoObject() = default;

    virtual QMatrix4x4 getModelMatrix() const = 0;
    QMatrix3x3 getNormalMatrix() {
        return getModelMatrix().normalMatrix();
    }
    virtual void render() = 0;
    virtual void cleanup() = 0;

    void rotate(double angle) {
        m_rotation += angle;
    }
protected:
    double m_rotation {0.0};
};

#endif //ENGINE_SHOWCASE_DEMOOBJECT_H
