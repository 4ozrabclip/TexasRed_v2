#ifndef REGEXHIGHLIGHTER_H
#define REGEXHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QTextCharFormat>

/**
 * - Constructor(QTextDocument* parent)
 *  - Connects to global settings updates (dark mode)
 *  - Initializes match formatting
 *
 * - virtual void highlightBlock(const QString& in) override
 *  - overrided to apply match formatting to all occurences of the current regex pattern in the text block
 *  - Skips processing if theres a regex error or no valid pattern.
 *
 * - void setMatchFormat()
 *  - Sets the QTextCharFormat for matched regex patterns based on global theme (darkmode)
 *
 * - void setPattern(const QString& in)
 *  - Checks and stores regex pattern
 *  - Triggers rehighlighting if pattern valid
 *  - Clears formatting if invalid + sets error state.
 *
 * - void setHasError(bool inHasError)
 *  - Force rehighight on error state change.
 *
 *
 */

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
