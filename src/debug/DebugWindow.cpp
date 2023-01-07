#include <QOpenGLWindow>
#include <imgui.h>
#include <QtImGui.h>
#include "DebugWindow.h"

DebugWindow::DebugWindow(QOpenGLWindow *window, bool enabled) {
    QtImGui::initialize(window);
    setEnabled(enabled);
}

void DebugWindow::render(const double deltaTime) {
    if (!m_enabled) {
        return;
    }

    QtImGui::newFrame();

    renderOverlay();

    ImGui::Render();
    QtImGui::render();
    m_frameTimes.push_back(deltaTime);
    if (m_frameTimes.size() > 60) {
        m_frameTimes.pop_front();
    }
}

void DebugWindow::renderOverlay() const {
    auto location = 0;

    ImGuiWindowFlags window_flags =
            ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings |
            ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;

    const float PAD = 10.0f;
    const ImGuiViewport *viewport = ImGui::GetMainViewport();
    ImVec2 work_pos = viewport->WorkPos; // Use work area to avoid menu-bar/task-bar, if any!
    ImVec2 work_size = viewport->WorkSize;
    ImVec2 window_pos, window_pos_pivot;
    window_pos.x = (location & 1) ? (work_pos.x + work_size.x - PAD) : (work_pos.x + PAD);
    window_pos.y = (location & 2) ? (work_pos.y + work_size.y - PAD) : (work_pos.y + PAD);
    window_pos_pivot.x = (location & 1) ? 1.0f : 0.0f;
    window_pos_pivot.y = (location & 2) ? 1.0f : 0.0f;
    ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
    window_flags |= ImGuiWindowFlags_NoMove;

    auto p_open = true;
    if (ImGui::Begin("Example: Simple overlay", &p_open, window_flags)) {
        auto avg = std::accumulate(m_frameTimes.begin(), m_frameTimes.end(), 0.0) / m_frameTimes.size();
        ImGui::Text("FPS: %d", (int) round(1.0 / avg));
    }
    ImGui::End();
}

void DebugWindow::setEnabled(bool enabled) {
    m_enabled = enabled;
}
