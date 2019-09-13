#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include <QSettings>
#include <QUrl>

/*
* Class Definition, also functions as forward declaration
*/
class About : public QDialog
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
    About(QWidget* parent = 0);
    ~About();

public slots:
    void openGitUrl();
};

#endif // ABOUT_H
