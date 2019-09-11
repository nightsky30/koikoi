#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QDialog>
#include <QSettings>

class Preferences : public QDialog
{
    Q_OBJECT
public:
    Preferences(QWidget* parent = 0);
    ~Preferences();
private:
    QSettings settings;
};

#endif // PREFERENCES_H
