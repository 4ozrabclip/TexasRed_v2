#ifndef PORTSCANNERPAGE_H
#define PORTSCANNERPAGE_H

#include <QWidget>

namespace Ui {
class PortScannerPage;
}

class PortScannerPage : public QWidget
{
    Q_OBJECT

public:
    explicit PortScannerPage(QWidget *parent = nullptr);
    ~PortScannerPage();

private:
    Ui::PortScannerPage *ui;
};

#endif // PORTSCANNERPAGE_H
