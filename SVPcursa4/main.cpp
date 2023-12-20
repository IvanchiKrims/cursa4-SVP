#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setStyle("fusion");

    MainWindow mainWindow;
    mainWindow.show();

    QPalette m_pal;

    // Стиль виджета
    m_pal.setColor(QPalette::Window, QColor(173, 216, 230));  // голубой фон
    m_pal.setColor(QPalette::WindowText, QColor(0, 0, 0));     // черный цвет текста
    m_pal.setColor(QPalette::Button, QColor(197, 239, 252));   // светло-голубая кнопка
    m_pal.setColor(QPalette::ButtonText, QColor(0, 0, 0));     // черный цвет текста на кнопке
    m_pal.setColor(QPalette::Highlight, QColor(70, 130, 180)); // голубое выделение
    m_pal.setColor(QPalette::HighlightedText, QColor(255, 255, 255));

    app.setPalette(m_pal);
    return app.exec();
}
