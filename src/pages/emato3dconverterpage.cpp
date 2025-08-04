#include "emato3dconverterpage.h"
#include "../utils/emato3dparser.h"
#include "src/pages/ui_emato3dconverterpage.h"
#include <QFileDialog>
#include <QMessageBox>

emaTo3dConverterPage::emaTo3dConverterPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::emaTo3dConverterPage)
{
    ui->setupUi(this);

    m_parser = new EmaTo3dParser();
}

emaTo3dConverterPage::~emaTo3dConverterPage()
{
    delete ui;
    delete m_parser;
}

void emaTo3dConverterPage::on_browseInputButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Select .ema File", "", "EMA Files (*.ema)");
    if (!fileName.isEmpty())
    {
        m_inputPath = fileName;
        ui->inputFileLineEdit->setText(m_inputPath);
    }
}

void emaTo3dConverterPage::on_browseOutputButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, "Select Output Directory");
    if (!dir.isEmpty())
    {
        m_outputDir = dir;
        ui->outputDirLineEdit->setText(m_outputDir);
    }
}


void emaTo3dConverterPage::on_convertButton_clicked()
{
    if (m_inputPath.isEmpty() || m_outputDir.isEmpty()) return;

    QFile inputFile(m_inputPath);
    if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    QString rawData = QString::fromUtf8(inputFile.readAll());
    inputFile.close();

    QString objContent;

    if (m_parser->processEmaFile(rawData, objContent))
    {

        QFileInfo inputInfo(m_inputPath);
        QString baseName = inputInfo.completeBaseName();
        QString outputPath = m_outputDir + "/" + baseName + ".obj";

        QFile outputFile(outputPath);
        if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Text)) return;

        QTextStream out(&outputFile);
        out << objContent;
        outputFile.close();

        QMessageBox::information(this, "Success", "Conversion complete. OBJ file saved to:\n" + outputPath);
    }


}

