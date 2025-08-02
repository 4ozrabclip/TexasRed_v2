#ifndef EMATO3DCONVERTERPAGE_H
#define EMATO3DCONVERTERPAGE_H

#include <QWidget>

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
    Ui::emaTo3dConverterPage *ui;
};

#endif // EMATO3DCONVERTERPAGE_H
