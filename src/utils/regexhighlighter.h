#ifndef REGEXHIGHLIGHTER_H
#define REGEXHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QTextCharFormat>

class RegexHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    explicit RegexHighlighter(QTextDocument* parent = nullptr);

protected:
    /** Overrides **/
    virtual void highlightBlock(const QString& inText) override;

public:
    /** Setters **/
    void setPattern(const QString& inPattern);
    void setHasError(bool inError);

    void setMatchFormat();

private:
    QRegularExpression m_regex;
    QTextCharFormat m_matchFormat;

    bool m_hasError = false;
};

#endif // REGEXHIGHLIGHTER_H
