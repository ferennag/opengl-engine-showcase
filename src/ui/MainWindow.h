#ifndef ENGINE_SHOWCASE_MAINWINDOW_H
#define ENGINE_SHOWCASE_MAINWINDOW_H

#include <memory>
#include <QMainWindow>
#include <QKeyEvent>
#include "GLRendererWindow.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void handleClose();
private:
    Ui::MainWindow *ui;
    std::unique_ptr<GLRendererWindow> glRendererWindow;
};


#endif //ENGINE_SHOWCASE_MAINWINDOW_H
