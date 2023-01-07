#ifndef ENGINE_SHOWCASE_GLRENDERERWINDOW_H
#define ENGINE_SHOWCASE_GLRENDERERWINDOW_H

#include <memory>
#include <QKeyEvent>
#include <QOpenGLWindow>
#include <QCloseEvent>
#include <QElapsedTimer>
#include "../engine/World.h"

class GLRendererWindow: public QOpenGLWindow {
    Q_OBJECT
public:
    GLRendererWindow();
    virtual ~GLRendererWindow();
signals:
    void requestClose();
protected:
    std::unique_ptr<World> m_world;
    QElapsedTimer m_timer;
    double m_lastFrame { 0 };

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void keyPressEvent(QKeyEvent *event) override;
};


#endif //ENGINE_SHOWCASE_GLRENDERERWINDOW_H
