#ifndef ENGINE_SHOWCASE_DEBUGWINDOW_H
#define ENGINE_SHOWCASE_DEBUGWINDOW_H

#include <deque>
#include <QOpenGLWindow>

class DebugWindow {
public:
    explicit DebugWindow(QOpenGLWindow *window, bool enabled = true);
    virtual ~DebugWindow() = default;
    void render(double deltaTime);
    void setEnabled(bool enabled);

    [[nodiscard]] bool isEnabled() const { return m_enabled; }

private:
    std::deque<double> m_frameTimes;
    bool m_enabled;

    void renderOverlay() const;
};


#endif //ENGINE_SHOWCASE_DEBUGWINDOW_H
