#include "regexhighlighter.h"
#include "Settings.h"

RegexHighlighter::RegexHighlighter(QTextDocument* parent)
    : QSyntaxHighlighter{parent}
{
    connect(&Settings::inst(), &Settings::darkModeChanged, this, [this](bool)
    {
        setMatchFormat();
        rehighlight();
    });


    setMatchFormat();
}

void RegexHighlighter::setMatchFormat()
{
    if (Settings::inst().getDarkMode())
    {
        m_matchFormat.setBackground(Qt::yellow);
        m_matchFormat.setForeground(Qt::white);
    }
    else
    {
        m_matchFormat.setBackground(Qt::red);
        m_matchFormat.setForeground(Qt::black);
    }
}

void RegexHighlighter::highlightBlock(const QString &inText)
{
    if (m_hasError || !m_regex.isValid())
        return;

    QRegularExpressionMatchIterator i = m_regex.globalMatch(inText);
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        if (match.hasMatch()) {
            qDebug() << "Match:" << match.captured();
            setFormat(match.capturedStart(), match.capturedLength(), m_matchFormat);
        }
    }
}

void RegexHighlighter::setPattern(const QString &inPattern)
{
    QRegularExpression regex(inPattern);
    if (!regex.isValid()) {
        m_hasError = true;
        rehighlight();
        return;
    }

    m_hasError = false;
    m_regex = regex;
    rehighlight();
}

void RegexHighlighter::setHasError(bool inError)
{
    m_hasError = inError;
    rehighlight();
}

