#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include <QSettings>
#include <QUrl>

class About : public QDialog
{
    Q_OBJECT
public:
    About(QWidget* parent = 0);
    ~About();
    void openGitUrl();

private:
    QSettings settings;
};

#endif // ABOUT_H
