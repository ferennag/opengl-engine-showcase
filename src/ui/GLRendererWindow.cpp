#include <memory>
#include <QKeyEvent>
#include <QSurfaceFormat>
#include "GLRendererWindow.h"
#include "../engine/texture/TextureManager.h"
#include "../engine/shader/ShaderManager.h"

GLRendererWindow::GLRendererWindow(): QOpenGLWindow() {
    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setVersion(4, 3);
    format.setSamples(16);
    format.setAlphaBufferSize(8);
    setFormat(format);
}

void GLRendererWindow::initializeGL() {
    QOpenGLWindow::initializeGL();
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_world = std::make_unique<World>(ProjectionType::PERSPECTIVE, QWindow::size());
    m_timer.start();
    m_debugWindow = std::make_unique<DebugWindow>(this);
}

void GLRendererWindow::resizeGL(int w, int h) {
    QOpenGLWindow::resizeGL(w, h);
    glViewport(0, 0, w, h);
    m_world->setViewportSize(QSize{w, h});
}

void GLRendererWindow::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    long long elapsed = m_timer.elapsed();
    double delta = (elapsed - m_lastFrame) / 1000.0f;
    m_lastFrame = elapsed;
    m_world->update(delta);
    m_world->render(delta);

    m_debugWindow->render(delta);
    update();
}

void GLRendererWindow::keyPressEvent(QKeyEvent *event) {
    QWindow::keyPressEvent(event);

    if (event->key() == Qt::Key_Escape) {
        emit requestClose();
    }

    if (event->key() == Qt::Key_F1) {
        m_debugWindow->setEnabled(!m_debugWindow->isEnabled());
    }
}

GLRendererWindow::~GLRendererWindow() {
    makeCurrent();
    TextureManager::getInstance().cleanup();
    ShaderManager::getInstance().cleanup();
}
