#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStack>

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

private slots:
    void on_openPortScannerButton_clicked();

    void on_openRegexSbButton_clicked();


    void on_toggleThemeButton_clicked();

    void on_backButton_clicked();

private:
    /** Init Functions **/
    void initializeMemberVariables();
    void initializePalettes();

    /** Helper Functions **/
    void openTab(QWidget* inWidget = nullptr);
    void applyColourTheme();




    /** Private Variables **/
    bool m_isDarkMode;

    QPalette darkModePalette;
    QPalette lightModePalette;

    QStack<QWidget*> navHistory;



    Ui::MainWindow *ui;



};
#endif // MAINWINDOW_H
