#include <QStyleHints>

#include "mainwindow.h"
#include "../utils/Settings.h"
#include "../pages/emato3dconverterpage.h"
#include "../pages/regexsandboxpage.h"
#include "../pages/portscannerpage.h"
#include "src/core/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setAutoFillBackground(true);


    // Initialize Members
    initializePages();
    initializePalettes();
    initializeSettings();

    // Apply Settings
    applyColourTheme();

    openTab(ui->frontPage);
}

MainWindow::~MainWindow()
{
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

void MainWindow::initializePalettes()
{
    darkModePalette.setColor(QPalette::Window, QColor(43, 43, 43));
    darkModePalette.setColor(QPalette::WindowText, Qt::white);
    darkModePalette.setColor(QPalette::Base, QColor(64, 64, 64));
    darkModePalette.setColor(QPalette::AlternateBase, QColor(80, 80, 80));
    darkModePalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkModePalette.setColor(QPalette::ToolTipText, Qt::white);
    darkModePalette.setColor(QPalette::Text, Qt::white);
    darkModePalette.setColor(QPalette::Button, QColor(42, 43, 43));
    darkModePalette.setColor(QPalette::ButtonText, Qt::black);
    darkModePalette.setColor(QPalette::BrightText, Qt::red);
    darkModePalette.setColor(QPalette::Link, QColor(42, 130, 218));
    darkModePalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkModePalette.setColor(QPalette::HighlightedText, Qt::black);

    lightModePalette.setColor(QPalette::Window, Qt::white);
    lightModePalette.setColor(QPalette::WindowText, Qt::black);
    lightModePalette.setColor(QPalette::Base, Qt::white);
    lightModePalette.setColor(QPalette::AlternateBase, QColor(245, 245, 245));
    lightModePalette.setColor(QPalette::ToolTipBase, Qt::black);
    lightModePalette.setColor(QPalette::ToolTipText, Qt::white);
    lightModePalette.setColor(QPalette::Text, Qt::black);
    lightModePalette.setColor(QPalette::Button, QColor(240, 240, 240));
    lightModePalette.setColor(QPalette::ButtonText, Qt::black);
    lightModePalette.setColor(QPalette::BrightText, Qt::red);
    lightModePalette.setColor(QPalette::Link, QColor(0, 122, 204));
    lightModePalette.setColor(QPalette::Highlight, QColor(0, 122, 204));
    lightModePalette.setColor(QPalette::HighlightedText, Qt::white);

}
void MainWindow::initializeSettings()
{
    bool isSysDarkMode = qApp->styleHints()->colorScheme() == Qt::ColorScheme::Dark;
    Settings::inst().setDarkMode(isSysDarkMode);


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
    qApp->setPalette(isDarkMode ? darkModePalette : lightModePalette);
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
