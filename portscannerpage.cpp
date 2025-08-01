#include "portscannerpage.h"
#include "ui_portscannerpage.h"

PortScannerPage::PortScannerPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PortScannerPage)
{
    ui->setupUi(this);
}

PortScannerPage::~PortScannerPage()
{
    delete ui;
}
