#ifndef ENGINE_SHOWCASE_TRIANGLE_H
#define ENGINE_SHOWCASE_TRIANGLE_H

#include <QMatrix4x4>
#include "DemoObject.h"

class Triangle : public DemoObject {
public:
    Triangle();
    ~Triangle() override = default;
    Triangle(const Triangle &other) = delete;
    Triangle &operator=(const Triangle &other) = delete;

    [[nodiscard]] QMatrix4x4 getModelMatrix() const override;
    void render() override;
    void cleanup() override;
protected:
    unsigned int vao, vbo;
    static constexpr float vertices[] = {
            -0.5, -0.5, 0,
            0.5, -0.5, 0,
            0, 0.5, 0
    };
};


#endif //ENGINE_SHOWCASE_TRIANGLE_H
