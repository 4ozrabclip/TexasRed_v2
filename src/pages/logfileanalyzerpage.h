#ifndef LOGFILEANALYZERPAGE_H
#define LOGFILEANALYZERPAGE_H

#include <QWidget>

namespace Ui {
class LogFileAnalyzerPage;
}

class LogFileAnalyzerPage : public QWidget
{
    Q_OBJECT

public:
    explicit LogFileAnalyzerPage(QWidget *parent = nullptr);
    ~LogFileAnalyzerPage();

private:
    Ui::LogFileAnalyzerPage *ui;
};

#endif // LOGFILEANALYZERPAGE_H
