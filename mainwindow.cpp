#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setAutoFillBackground(true);

    openTab(ui->frontPage);


    initializeMemberVariables();

    initializePalettes();

    applyColourTheme();

}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializeMemberVariables()
{
    m_isDarkMode = false;
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
    darkModePalette.setColor(QPalette::Button, QColor(64, 64, 64));
    darkModePalette.setColor(QPalette::ButtonText, Qt::white);
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
    qApp->setPalette(m_isDarkMode ? darkModePalette : lightModePalette);
}



void MainWindow::on_openPortScannerButton_clicked()
{
    openTab(ui->portScannerPage);

}


void MainWindow::on_openRegexSbButton_clicked()
{
    openTab(ui->regexSbPage);
}



void MainWindow::on_toggleThemeButton_clicked()
{
    m_isDarkMode = !m_isDarkMode;
    applyColourTheme();
}


void MainWindow::on_backButton_clicked()
{
    navHistory.pop();
    openTab(navHistory.back());
}

