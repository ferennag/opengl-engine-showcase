#include <QKeyEvent>
#include "MainWindow.h"
#include "ui_MainWindow.h"


MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    glRendererWindow = std::make_unique<GLRendererWindow>();
    QWidget *centralWidgetContainer = QWidget::createWindowContainer(glRendererWindow.get());
    setCentralWidget(centralWidgetContainer);

    QObject::connect(glRendererWindow.get(), &GLRendererWindow::requestClose, this, &MainWindow::handleClose);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    QWidget::keyPressEvent(event);

    if (event->key() == Qt::Key_Escape) {
        handleClose();
    }
}

void MainWindow::handleClose() {
    close();
}
