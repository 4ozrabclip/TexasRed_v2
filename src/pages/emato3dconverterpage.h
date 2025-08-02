#ifndef EMATO3DCONVERTERPAGE_H
#define EMATO3DCONVERTERPAGE_H

#include <QWidget>
class EmaTo3dParser;
namespace Ui {
class emaTo3dConverterPage;
}

class emaTo3dConverterPage : public QWidget
{
    Q_OBJECT

public:
    explicit emaTo3dConverterPage(QWidget *parent = nullptr);
    ~emaTo3dConverterPage();

private:
    EmaTo3dParser* m_parser;

    QString m_inputPath;
    QString m_outputDir;

private slots:
    void on_browseInputButton_clicked();

    void on_browseOutputButton_clicked();

    void on_convertButton_clicked();

private:
    Ui::emaTo3dConverterPage *ui;
};

#endif // EMATO3DCONVERTERPAGE_H
