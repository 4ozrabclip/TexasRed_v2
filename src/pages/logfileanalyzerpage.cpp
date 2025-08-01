#include "logfileanalyzerpage.h"
#include "src/pages/ui_logfileanalyzerpage.h"

LogFileAnalyzerPage::LogFileAnalyzerPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LogFileAnalyzerPage)
{
    ui->setupUi(this);
}

LogFileAnalyzerPage::~LogFileAnalyzerPage()
{
    delete ui;
}
