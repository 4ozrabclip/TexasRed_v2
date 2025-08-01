#include "regexsandboxpage.h"
#include "ui_regexsandboxpage.h"

RegexSandboxPage::RegexSandboxPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RegexSandboxPage)
{
    ui->setupUi(this);

    m_highlighter = new RegexHighlighter(ui->testTextEdit->document());

    connect(ui->patternLineEdit, &QLineEdit::textChanged, this, &RegexSandboxPage::onPatternChanged);

}

RegexSandboxPage::~RegexSandboxPage()
{
    delete ui;
}

void RegexSandboxPage::onPatternChanged(const QString &text)
{
    if (!m_highlighter) return;

    QRegularExpression regex(text);
    if (!regex.isValid())
    {
        ui->errorLabel->setText("Invalid pattern: " + regex.errorString());
        m_highlighter->setHasError(true);
    }
    else
    {
        ui->errorLabel->clear();
        m_highlighter->setPattern(text);
        m_highlighter->setHasError(false);
    }
    m_highlighter->rehighlight();
}
