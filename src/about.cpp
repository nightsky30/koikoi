#include "about.h"
#include <QIcon>
#include <QString>
#include <QVBoxLayout>
#include <QLabel>
#include <QDesktopServices>

#define version "0.0.1"
#define git "https://github.com/nightsky30/koikoi"

About::About(QWidget *parent) : QDialog (parent)
{
    //Create QWidget object pointers and assign values to their attributes
    //VBox layout with some labels, link to github, etc

    //Title and Application Icon
    this->setWindowTitle("Koi-Koi Hanafuda - About");
    this->setWindowIcon(QIcon(QString(":/icon/koi-2.svg")));
    this->setMinimumSize(QSize(150, 100));

    //Create vertical box layout
    QVBoxLayout *vBoxLayout = new QVBoxLayout(this);

    //Set up about fonts
    QFont titleFont("Noto Sans", 12, QFont::Bold);
    QFont aboutFont("Arial", 9, QFont::Normal);

    //Set up application name
    QLabel *appName = new QLabel(this);
    appName->setText(QString("Koi-Koi Hanafuda"));
    appName->setFont(titleFont);

    //Set up application version
    QLabel *appVersion = new QLabel(this);
    appVersion->setText(QString("Version: " + QString(version)));
    appVersion->setFont(aboutFont);

    //Set up Git project link
    QLabel *gitUrlLabel = new QLabel(this);
    gitUrlLabel->setTextFormat(Qt::RichText);
    gitUrlLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    gitUrlLabel->openExternalLinks();
    gitUrlLabel->setText("<a href='" + QString(git) + "'>Git Project Page</a>");
    connect(gitUrlLabel, &QLabel::linkActivated, this, &About::openGitUrl);

    //Set up the vertical box layout by adding the created widgets
    vBoxLayout->addWidget(appName);
    vBoxLayout->addWidget(appVersion);
    vBoxLayout->addWidget(gitUrlLabel);
}

About::~About()
{
}

void About::openGitUrl()
{
    QDesktopServices::openUrl(QUrl(git));
}
