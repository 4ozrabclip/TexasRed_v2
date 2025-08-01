#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
class Settings : public QObject
{
    Q_OBJECT
public:
    static Settings& inst()
    {
        static Settings settings;
        return settings;
    }
    bool getDarkMode() const { return m_isDarkMode; }

    void setDarkMode(bool inIsDarkMode)
    {
        m_isDarkMode = inIsDarkMode;
        emit darkModeChanged(m_isDarkMode);
    }

signals:
    void darkModeChanged(bool isDarkMode);

private:
    Settings() = default;
    Settings(const Settings&) = delete;
    Settings& operator=(const Settings&) = delete;

    bool m_isDarkMode = false;
};

#endif // SETTINGS_H
