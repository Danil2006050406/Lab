#include <QApplication>
#include "mainwindow.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    MainWindow w;
    w.setGeometry(120, 120, 900, 560);   // задаём положение и размер на экране
    w.show();                            // ВАЖНО: показать окно

    return app.exec();                   // ВАЖНО: цикл сообщений
}

