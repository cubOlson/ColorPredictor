#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColor>
#include <QFrame>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void previewColor();
    void updatePredictions();

private:
    Ui::MainWindow *ui;
    QColor currentColor;
    QList<QFrame*> predictionFrames;

    // Color parsing methods
    bool parseRGB(const QString &input, QColor &color);
    bool parseHSL(const QString &input, QColor &color);
    bool parseHSV(const QString &input, QColor &color);
    bool parseHEX(const QString &input, QColor &color);

    // Display update
    void updateColorPreview();

    // Prediction algorithms
    QList<QColor> predictForSRGB(int r, int g, int b);
    QList<QColor> predictForAdobeRGB(int r, int g, int b);
    QList<QColor> predictForDCIP3(int r, int g, int b);
    QList<QColor> predictForNTSC(int r, int g, int b);
    QList<QColor> predictForRec2020(int r, int g, int b);
    QColor adjustColorTemperature(int r, int g, int b, int kelvinOffset);
};
#endif // MAINWINDOW_H
