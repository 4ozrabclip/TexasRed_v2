#ifndef REGEXSANDBOXPAGE_H
#define REGEXSANDBOXPAGE_H

#include "regexhighlighter.h"

#include <QWidget>

namespace Ui {
class RegexSandboxPage;
}

class RegexSandboxPage : public QWidget
{
    Q_OBJECT

public:
    explicit RegexSandboxPage(QWidget *parent = nullptr);
    ~RegexSandboxPage();

protected slots:
    void onPatternChanged(const QString &text);
private:
    RegexHighlighter* m_highlighter;
private slots:



private:
    Ui::RegexSandboxPage *ui;
};

#endif // REGEXSANDBOXPAGE_H
