#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QValueAxis>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void generateSignal();
    void saveSignal();

private:
    QLabel *frequencyLabel;
    QDoubleSpinBox *frequencySpinBox;
    QLabel *amplitudeLabel;
    QDoubleSpinBox *amplitudeSpinBox;
    QLabel *phaseLabel;
    QDoubleSpinBox *phaseSpinBox;
    QPushButton *generateButton;
    QPushButton *saveButton;
    QChart *chart;
    QChartView *chartView;

    bool signalGenerated;
    void drawAxes();
    void drawGraph(double frequency, double amplitude, double phaseShift);
};

#endif // MAINWINDOW_H
