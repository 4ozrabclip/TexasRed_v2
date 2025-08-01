#include <QStyleHints>
#include <QTimer>

#include "mainwindow.h"
#include "../utils/Settings.h"
#include "../pages/emato3dconverterpage.h"
#include "../pages/regexsandboxpage.h"
#include "../pages/portscannerpage.h"
#include "src/core/ui_mainwindow.h"
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setAutoFillBackground(true);


    // Initialize Members
    initializePages();
    initializeSettings();
    initializeTitle();

    // Apply Settings
    applyColourTheme();

    openTab(ui->frontPage);
}

MainWindow::~MainWindow()
{
    m_typingTimer->stop();
    delete m_typingTimer;
    delete ui;
}


void MainWindow::initializePages()
{
    regexSbPage = new RegexSandboxPage(this);
    ui->stackedWidget->addWidget(regexSbPage);
    portScannerPage = new PortScannerPage(this);
    ui->stackedWidget->addWidget(portScannerPage);
    emaTo3dPage = new emaTo3dConverterPage(this);
    ui->stackedWidget->addWidget(emaTo3dPage);
}


QString MainWindow::loadStyle(const QString &inPath)
{
    QFile file(inPath);
    if (file.open(QFile::ReadOnly | QFile::Text))
        return QString::fromUtf8(file.readAll());
    return {};
}
void MainWindow::initializeSettings()
{
    bool isSysDarkMode = qApp->styleHints()->colorScheme() == Qt::ColorScheme::Dark;
    Settings::inst().setDarkMode(isSysDarkMode);


}

void MainWindow::initializeTitle()
{
    const QString fullTitle =
R"(  ****           *                                                     ***** ***                 **
     *  *************                                                   ******  * **                  **
    *     *********                                                    **   *  *  **                  **
    *     *  *                                                        *    *  *   **                  **
     **  *  **                    ***    ***                  ****        *  *    *                   **
        *  ***            ***    * ***  **** *     ****      * **** *    ** **   *       ***      *** **
       **   **           * ***      *** *****     * ***  *  **  ****     ** **  *       * ***    *********
       **   **          *   ***      ***  **     *   ****  ****          ** ****       *   ***  **   ****
       **   **         **    ***      ***       **    **     ***         ** **  ***   **    *** **    **
       **   **         ********      * ***      **    **       ***       ** **    **  ********  **    **
        **  **         *******      *   ***     **    **         ***     *  **    **  *******   **    **
         ** *      *   **          *     ***    **    **    ****  **        *     **  **        **    **
          ***     *    ****    *  *       *** * **    **   * **** *     ****      *** ****    * **    **
           *******      *******  *         ***   ***** **     ****     *  ****    **   *******   *****
             ***         *****                    ***   **            *    **     *     *****     ***
                                                                      *
                                                                       **


                                                                                                           )";

    m_titleIndex = 0;

    m_typingTimer = new QTimer(this);
    connect(m_typingTimer, &QTimer::timeout, this, [this, fullTitle]() {
        if (m_titleIndex <= fullTitle.size()) {
            ui->titleLabel->setText(fullTitle.left(m_titleIndex));
            m_titleIndex++;
        } else {
            m_typingTimer->stop();
        }
    });
    m_typingTimer->start(m_titleTimerSpeed);

}

void MainWindow::openTab(QWidget *inWidget)
{
    if (!ui || !ui->stackedWidget)
    {
        qDebug() << "ui is nullptr";
        return;
    }
    if (!inWidget)
    {
        qDebug() << "page to open is nullptr";
        return;
    }

    if (inWidget == ui->frontPage)
    {
        ui->backButton->setVisible(false);
        navHistory.empty();
        navHistory.push(inWidget);
    }
    else
    {
        if (!ui->backButton->isVisible())
            ui->backButton->setVisible(true);
        QWidget* currentPage = ui->stackedWidget->currentWidget();
        navHistory.push(currentPage);
    }

    ui->stackedWidget->setCurrentWidget(inWidget);

}
void MainWindow::applyColourTheme()
{
    const bool isDarkMode = Settings::inst().getDarkMode();

    QString styleSheetPath = isDarkMode ? ":/styles/darkmode" : ":/styles/lightmode";

    qApp->setStyleSheet(loadStyle(styleSheetPath));

}



/** Button Slots  **/

void MainWindow::on_toggleThemeButton_clicked()
{
    const bool current = Settings::inst().getDarkMode();

    Settings::inst().setDarkMode(!current);

    applyColourTheme();
}

void MainWindow::on_backButton_clicked()
{
    if (navHistory.isEmpty()) return;

    QWidget* lastPage = navHistory.pop();
    ui->stackedWidget->setCurrentWidget(lastPage);
    ui->backButton->setVisible(lastPage != ui->frontPage);
}

void MainWindow::on_openPortScannerButton_clicked()
{
    openTab(portScannerPage);
}
void MainWindow::on_openRegexSbButton_clicked()
{
    openTab(regexSbPage);
}
void MainWindow::on_openEmaToObjButton_clicked()
{
    openTab(emaTo3dPage);
}
void MainWindow::on_openRegexToolsButton_clicked()
{
    openTab(ui->regexToolsPage);
}
void MainWindow::on_openConverterToolsButton_clicked()
{
    openTab(ui->converterToolsPage);
}
