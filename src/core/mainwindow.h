#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QStack>
class RegexSandboxPage;
class PortScannerPage;
class emaTo3dConverterPage;
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void openTab(QWidget* inWidget = nullptr);


private:
    /** Init Functions **/
    void initializePages();
    void initializeSettings();
    void initializePalettes();

    /** Helper Functions **/
    QString loadStyle(const QString& inPath);
    void applyColourTheme();


    /** Pages **/
    RegexSandboxPage* regexSbPage;
    PortScannerPage* portScannerPage;
    emaTo3dConverterPage* emaTo3dPage;

    QStack<QWidget*> navHistory;



private slots:
    void on_openPortScannerButton_clicked();

    void on_openRegexSbButton_clicked();

    void on_toggleThemeButton_clicked();

    void on_backButton_clicked();

    void on_openRegexToolsButton_clicked();

    void on_openConverterToolsButton_clicked();

    void on_openEmaToObjButton_clicked();

private:
    Ui::MainWindow *ui;



};
#endif // MAINWINDOW_H
