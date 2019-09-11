#include "preferences.h"
#include <QIcon>
#include <QString>
#include <QVBoxLayout>

Preferences::Preferences(QWidget *parent) : QDialog (parent)
{
    //Create QWidget object pointers and assign values to their attributes
    //VBox layout with some checkboxes, labels, etc

    //Title and Application Icon
    this->setWindowTitle("Koi-Koi Hanafuda - Preferences");
    this->setWindowIcon(QIcon(QString(":/icon/koi-2.svg")));

//    //Create vertical box layout
//    QVBoxLayout *vBoxLayout = new QVBoxLayout(this);

//    //Set up about fonts
//    QFont titleFont("Noto Sans", 12, QFont::Bold);
//    QFont aboutFont("Arial", 9, QFont::Normal);

//    //Set up application name
//    QLabel *appName = new QLabel(this);
//    appName->setText(QString("Koi-Koi Hanafuda"));
//    appName->setFont(titleFont);

//    //Set up application version
//    QLabel *appVersion = new QLabel(this);
//    appVersion->setText(QString("Version: " + QString(version)));
//    appVersion->setFont(aboutFont);

//    //Set up Git project link
//    QLabel *gitUrlLabel = new QLabel(this);
//    gitUrlLabel->setTextFormat(Qt::RichText);
//    gitUrlLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
//    gitUrlLabel->openExternalLinks();
//    gitUrlLabel->setText("<a href='" + QString(git) + "'>Git Project Page</a>");
//    connect(gitUrlLabel, &QLabel::linkActivated, this, &About::openGitUrl);

//    //Set up the vertical box layout by adding the created widgets
//    vBoxLayout->addWidget(appName);
//    vBoxLayout->addWidget(appVersion);
//    vBoxLayout->addWidget(gitUrlLabel);
}

Preferences::~Preferences()
{
}
