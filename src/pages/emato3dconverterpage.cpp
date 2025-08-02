#include "emato3dconverterpage.h"
#include "ui_emato3dconverterpage.h"

emaTo3dConverterPage::emaTo3dConverterPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::emaTo3dConverterPage)
{
    ui->setupUi(this);
}

emaTo3dConverterPage::~emaTo3dConverterPage()
{
    delete ui;
}
