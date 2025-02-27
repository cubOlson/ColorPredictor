#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColorDialog>
#include <QMessageBox>
#include <cmath>
#include <QRegularExpression>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialize format combo box
    ui->formatComboBox->addItem("RGB: 0-255, 0-255, 0-255");
    ui->formatComboBox->addItem("HSL: 0-360, 0-100%, 0-100%");
    ui->formatComboBox->addItem("HSV: 0-360, 0-100%, 0-100%");
    ui->formatComboBox->addItem("HEX: #RRGGBB");

    // Initialize monitor type combo box
    ui->monitorTypeComboBox->addItem("sRGB (Standard)");
    ui->monitorTypeComboBox->addItem("Adobe RGB");
    ui->monitorTypeComboBox->addItem("DCI-P3");
    ui->monitorTypeComboBox->addItem("NTSC");
    ui->monitorTypeComboBox->addItem("Rec. 2020");

    // Connect signals and slots
    connect(ui->previewButton, &QPushButton::clicked, this, &MainWindow::previewColor);
    connect(ui->monitorTypeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::updatePredictions);

    // Set default color
    currentColor = QColor(128, 128, 128);
    updateColorPreview();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::previewColor()
{
    QString input = ui->colorInputEdit->text().trimmed();
    int format = ui->formatComboBox->currentIndex();

    bool validColor = false;
    QColor newColor;

    switch(format) {
    case 0: // RGB
        validColor = parseRGB(input, newColor);
        break;
    case 1: // HSL
        validColor = parseHSL(input, newColor);
        break;
    case 2: // HSV
        validColor = parseHSV(input, newColor);
        break;
    case 3: // HEX
        validColor = parseHEX(input, newColor);
        break;
    }

    if (validColor) {
        currentColor = newColor;
        updateColorPreview();
        updatePredictions();
    } else {
        QMessageBox::warning(this, "Invalid Input",
                             "Please check your color format and try again.");
    }
}

bool MainWindow::parseRGB(const QString &input, QColor &color)
{
    // Parse RGB format: "R, G, B" or "R G B" or "R,G,B"
    QRegularExpression rx("(\\d+)\\s*,?\\s*(\\d+)\\s*,?\\s*(\\d+)");
    QRegularExpressionMatch match = rx.match(input);

    if (match.hasMatch()) {
        int r = match.captured(1).toInt();
        int g = match.captured(2).toInt();
        int b = match.captured(3).toInt();

        if (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255) {
            color = QColor(r, g, b);
            return true;
        }
    }
    return false;
}

bool MainWindow::parseHSL(const QString &input, QColor &color)
{
    // Parse HSL format: "H, S%, L%" or "H S% L%"
    QRegularExpression rx("(\\d+)\\s*,?\\s*(\\d+)\\s*%?\\s*,?\\s*(\\d+)\\s*%?");
    QRegularExpressionMatch match = rx.match(input);

    if (match.hasMatch()) {
        int h = match.captured(1).toInt();
        int s = match.captured(2).toInt();
        int l = match.captured(3).toInt();

        if (h >= 0 && h <= 360 && s >= 0 && s <= 100 && l >= 0 && l <= 100) {
            color = QColor::fromHsl(h, (s * 255) / 100, (l * 255) / 100);
            return true;
        }
    }
    return false;
}

bool MainWindow::parseHSV(const QString &input, QColor &color)
{
    // Parse HSV format: "H, S%, V%" or "H S% V%"
    QRegularExpression rx("(\\d+)\\s*,?\\s*(\\d+)\\s*%?\\s*,?\\s*(\\d+)\\s*%?");
    QRegularExpressionMatch match = rx.match(input);

    if (match.hasMatch()) {
        int h = match.captured(1).toInt();
        int s = match.captured(2).toInt();
        int v = match.captured(3).toInt();

        if (h >= 0 && h <= 360 && s >= 0 && s <= 100 && v >= 0 && v <= 100) {
            color = QColor::fromHsv(h, (s * 255) / 100, (v * 255) / 100);
            return true;
        }
    }
    return false;
}

bool MainWindow::parseHEX(const QString &input, QColor &color)
{
    // Parse HEX format: "#RRGGBB" or "RRGGBB"
    QString hexValue = input;
    if (!hexValue.startsWith("#")) {
        hexValue.prepend("#");
    }

    if (QColor::isValidColorName(hexValue)) {
        color = QColor(hexValue);
        return true;
    }
    return false;
}

void MainWindow::updateColorPreview()
{
    // Update color preview for user's monitor
    QString styleSheet = QString("background-color: %1;").arg(currentColor.name());
    ui->colorPreviewFrame->setStyleSheet(styleSheet);

    // Show color values
    int r, g, b;
    currentColor.getRgb(&r, &g, &b);

    ui->statusbar->showMessage(QString("RGB: %1, %2, %3 | HEX: %4")
                                   .arg(r).arg(g).arg(b).arg(currentColor.name()));
}

void MainWindow::updatePredictions()
{
    int monitorType = ui->monitorTypeComboBox->currentIndex();

    // Get base color values
    int r, g, b;
    currentColor.getRgb(&r, &g, &b);

    // Create prediction frames if not already created
    if (!predictionFrames.size()) {
        predictionFrames.append(ui->prediction1Frame);
        //add prediction frames
    }

    // Calculate predictions based on selected monitor type
    QList<QColor> predictions;

    switch(monitorType) {
    case 0: // sRGB (standard)
        predictions = predictForSRGB(r, g, b);
        break;
    case 1: // Adobe RGB
        predictions = predictForAdobeRGB(r, g, b);
        break;
    case 2: // DCI-P3
        predictions = predictForDCIP3(r, g, b);
        break;
    case 3: // NTSC
        predictions = predictForNTSC(r, g, b);
        break;
    case 4: // Rec. 2020
        predictions = predictForRec2020(r, g, b);
        break;
    }

    // Update prediction displays
    for (int i = 0; i < predictions.size() && i < predictionFrames.size(); i++) {
        QString styleSheet = QString("background-color: %1;").arg(predictions[i].name());
        predictionFrames[i]->setStyleSheet(styleSheet);
    }
}

QList<QColor> MainWindow::predictForSRGB(int r, int g, int b)
{
    // For sRGB, create variations based on typical monitor differences
    QList<QColor> predictions;

    // Lower brightness/contrast monitor
    QColor dim(
        qBound(0, int(r * 0.9), 255),
        qBound(0, int(g * 0.9), 255),
        qBound(0, int(b * 0.9), 255)
        );

    // Higher brightness/contrast monitor
    QColor bright(
        qBound(0, int(r * 1.1), 255),
        qBound(0, int(g * 1.1), 255),
        qBound(0, int(b * 1.1), 255)
        );

    // Cooler temperature monitor
    QColor cool = adjustColorTemperature(r, g, b, -300); // Cooler

    predictions << dim << bright << cool;
    return predictions;
}

QList<QColor> MainWindow::predictForAdobeRGB(int r, int g, int b)
{
    // Adobe RGB has wider gamut, especially in greens
    QList<QColor> predictions;

    // Convert sRGB to Adobe RGB (simplified)
    QColor adobeRGB(
        qBound(0, int(r * 0.95), 255),
        qBound(0, int(g * 1.15), 255), // Greens more vibrant
        qBound(0, int(b * 0.98), 255)
        );

    // Variations
    QColor adobeVar1 = adjustColorTemperature(adobeRGB.red(), adobeRGB.green(), adobeRGB.blue(), 200);
    QColor adobeVar2(
        qBound(0, int(adobeRGB.red() * 1.05), 255),
        qBound(0, int(adobeRGB.green() * 0.97), 255),
        qBound(0, int(adobeRGB.blue() * 1.02), 255)
        );

    predictions << adobeRGB << adobeVar1 << adobeVar2;
    return predictions;
}

QList<QColor> MainWindow::predictForDCIP3(int r, int g, int b)
{
    // DCI-P3 has wider gamut, especially in reds
    QList<QColor> predictions;

    // Convert sRGB to DCI-P3 (simplified)
    QColor dciP3(
        qBound(0, int(r * 1.15), 255), // Reds more vibrant
        qBound(0, int(g * 1.05), 255),
        qBound(0, int(b * 1.08), 255)
        );

    // Variations
    QColor dciVar1 = adjustColorTemperature(dciP3.red(), dciP3.green(), dciP3.blue(), -150);
    QColor dciVar2(
        qBound(0, int(dciP3.red() * 0.95), 255),
        qBound(0, int(dciP3.green() * 1.02), 255),
        qBound(0, int(dciP3.blue() * 0.98), 255)
        );

    predictions << dciP3 << dciVar1 << dciVar2;
    return predictions;
}

QList<QColor> MainWindow::predictForNTSC(int r, int g, int b)
{
    // NTSC has different gamma and color characteristics
    QList<QColor> predictions;

    // Convert sRGB to NTSC (simplified)
    QColor ntsc(
        qBound(0, int(pow(r/255.0, 1.1) * 255), 255),
        qBound(0, int(pow(g/255.0, 0.9) * 255), 255),
        qBound(0, int(pow(b/255.0, 1.0) * 255), 255)
        );

    // Variations
    QColor ntscVar1 = adjustColorTemperature(ntsc.red(), ntsc.green(), ntsc.blue(), 300);
    QColor ntscVar2(
        qBound(0, int(ntsc.red() * 0.9), 255),
        qBound(0, int(ntsc.green() * 1.1), 255),
        qBound(0, int(ntsc.blue() * 1.05), 255)
        );

    predictions << ntsc << ntscVar1 << ntscVar2;
    return predictions;
}

QList<QColor> MainWindow::predictForRec2020(int r, int g, int b)
{
    // Rec. 2020 has much wider gamut
    QList<QColor> predictions;

    // Convert sRGB to Rec. 2020 (simplified)
    QColor rec2020(
        qBound(0, int(r * 1.2), 255),
        qBound(0, int(g * 1.2), 255),
        qBound(0, int(b * 1.2), 255)
        );

    // Variations
    QColor recVar1 = adjustColorTemperature(rec2020.red(), rec2020.green(), rec2020.blue(), -200);
    QColor recVar2(
        qBound(0, int(rec2020.red() * 0.92), 255),
        qBound(0, int(rec2020.green() * 0.95), 255),
        qBound(0, int(rec2020.blue() * 1.1), 255)
        );

    predictions << rec2020 << recVar1 << recVar2;
    return predictions;
}

QColor MainWindow::adjustColorTemperature(int r, int g, int b, int kelvinOffset)
{
    // Simple color temperature adjustment
    double factor = kelvinOffset / 1000.0;

    int newR = qBound(0, int(r * (1 + factor * 0.1)), 255);
    int newB = qBound(0, int(b * (1 - factor * 0.1)), 255);

    return QColor(newR, g, newB);
}
