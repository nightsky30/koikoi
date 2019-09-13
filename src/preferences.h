#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QDialog>
#include <QSettings>

/*
* Class Definition, also functions as forward declaration
*/
class Preferences : public QDialog
{
    Q_OBJECT

private:
    /*
    * Member Initialization List
    */
    QSettings settings;

public:
    /*
    * Constructors / Destructors
    */
    Preferences(QWidget* parent = 0);
    ~Preferences();
};

#endif // PREFERENCES_H
