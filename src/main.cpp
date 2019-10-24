/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * Koi-Koi Hanafuda - Card Game
 * Copyright (C) 2019  nightsky30 @ github
 */

#include "config.h"
#include "koikoi.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QCommandLineParser>
#include <QDebug>
#include <QTranslator>

/*
* Main Function
*/
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QApplication::setApplicationName("Koi-Koi Hanafuda");
    QApplication::setApplicationDisplayName("Koi-Koi Hanafuda");
    QApplication::setApplicationVersion(KOIKOI_VERSION);
    QApplication::setOrganizationName("Koi-Koi Hanafuda"); // for QSettings

//    //Set stylesheet
//    QFile file(":/dark.qss");
//    file.open(QFile::ReadOnly | QFile::Text);
//    QTextStream stream(&file);
//    app.setStyleSheet(stream.readAll());

    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addVersionOption();

    parser.process(app);

    QTranslator translator;
    bool ret = translator.load(QLocale::system(), QString(), QString(), QString(KOIKOI_DATADIR) + "/translations/");
    qDebug() << "Translation loaded:" << ret;
    app.installTranslator(&translator);

    KoiKoi window;
    window.show();

    return app.exec();
}
