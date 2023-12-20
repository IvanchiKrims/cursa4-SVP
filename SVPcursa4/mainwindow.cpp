#include "mainwindow.h"
#include <QtMath>
#include <QTextStream>
#include <QDebug>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), signalGenerated(false)
{
    frequencyLabel = new QLabel("Частота:", this);
    frequencySpinBox = new QDoubleSpinBox(this);
    amplitudeLabel = new QLabel("Амплитуда:", this);
    amplitudeSpinBox = new QDoubleSpinBox(this);
    phaseLabel = new QLabel("Фазовый сдвиг:", this);
    phaseSpinBox = new QDoubleSpinBox(this);
    generateButton = new QPushButton("Сгенерировать сигнал", this);
    saveButton = new QPushButton("Сохранить сигнал", this);

    connect(generateButton, &QPushButton::clicked, this, &MainWindow::generateSignal);
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::saveSignal);

    // Инициализация chart и chartView
    chart = new QChart();
    chartView = new QChartView(chart, this);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(frequencyLabel);
    layout->addWidget(frequencySpinBox);
    layout->addWidget(amplitudeLabel);
    layout->addWidget(amplitudeSpinBox);
    layout->addWidget(phaseLabel);
    layout->addWidget(phaseSpinBox);
    layout->addWidget(generateButton);
    layout->addWidget(saveButton);
    layout->addWidget(chartView);

    QWidget *centralWidget = new QWidget;
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{
    delete frequencyLabel;
    delete frequencySpinBox;
    delete amplitudeLabel;
    delete amplitudeSpinBox;
    delete phaseLabel;
    delete phaseSpinBox;
    delete generateButton;
    delete saveButton;
    delete chartView;
    delete chart;
}

void MainWindow::generateSignal()
{
    const double frequency = frequencySpinBox->value();
    const double amplitude = amplitudeSpinBox->value();
    const double phaseShift = phaseSpinBox->value();

    qDebug() << "Частота:" << frequency;
    qDebug() << "Амплитуда:" << amplitude;
    qDebug() << "Фазовый сдвиг:" << phaseShift;

    // Удаление предыдущего графика
    chart->removeAllSeries();

    drawAxes();
    drawGraph(frequency, amplitude, phaseShift);
    signalGenerated = true;
}

void MainWindow::saveSignal()
{
    if (!signalGenerated) {
        QMessageBox::critical(this, "Ошибка", "Сначала сгенерируйте сигнал!");
        return;
    }

    const QString fileName = QFileDialog::getSaveFileName(this, "Сохранить изображение сигнала", "", "Изображения (*.png *.jpg *.bmp)");

    if (!fileName.isEmpty()) {
        QPixmap pixmap(chartView->size());
        pixmap.fill(Qt::white);

        QPainter painter(&pixmap);
        chartView->render(&painter);

        if (pixmap.save(fileName)) {
            qDebug() << "Изображение успешно сохранено!";
        } else {
            qDebug() << "Ошибка сохранения изображения!";
        }
    }
}

void MainWindow::drawAxes()
{
    // Рисование осей X и Y
    QLineSeries *xAxisLine = new QLineSeries();
    xAxisLine->append(0, chartView->height() / 2);
    xAxisLine->append(chartView->width(), chartView->height() / 2);
    chart->addSeries(xAxisLine);

    QLineSeries *yAxisLine = new QLineSeries();
    yAxisLine->append(chartView->width() / 2, 0);
    yAxisLine->append(chartView->width() / 2, chartView->height());
    chart->addSeries(yAxisLine);

    // Установка диапазона для Y-оси
    QValueAxis *axisY = new QValueAxis;
    axisY->setTitleText("Амплитуда");
    axisY->setRange(-amplitudeSpinBox->maximum(), amplitudeSpinBox->maximum()); // Set the range
    chart->addAxis(axisY, Qt::AlignLeft);
}

// Modify drawGraph to make sure the graph starts from 0 on the X-axis
void MainWindow::drawGraph(double frequency, double amplitude, double phaseShift)
{
    // Рисование дискретного синусоидального сигнала
    QLineSeries *series = new QLineSeries();
    series->setName("Синусоида");

    const int numPoints = 1000;
    const double step = 2 * M_PI / numPoints;

    for (int i = 0; i < numPoints; ++i)
    {
        double x = i * step;
        double y = amplitude * qSin(frequency * x + phaseShift);
        series->append(x, y);
    }

    // Очистка предыдущих осей
    QList<QAbstractAxis*> allAxes = chart->axes();
    for (QAbstractAxis* axis : allAxes) {
        chart->removeAxis(axis);
    }

    chart->addSeries(series);

    QValueAxis *axisX = new QValueAxis;
    axisX->setTitleText("Время");
    axisX->setRange(0, 2 * M_PI); // Set the range to start from 0
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis;
    axisY->setTitleText("Амплитуда");
    axisY->setRange(-amplitudeSpinBox->maximum(), amplitudeSpinBox->maximum());
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
}
