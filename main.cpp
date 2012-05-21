/****************************************************************************
**
** Copyright (c) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Yoann Lopes (yoann.lopes@nokia.com)
**
** This file is part of the MeeSpot project.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions
** are met:
**
** Redistributions of source code must retain the above copyright notice,
** this list of conditions and the following disclaimer.
**
** Redistributions in binary form must reproduce the above copyright
** notice, this list of conditions and the following disclaimer in the
** documentation and/or other materials provided with the distribution.
**
** Neither the name of Nokia Corporation and its Subsidiary(-ies) nor the names of its
** contributors may be used to endorse or promote products derived from
** this software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
** FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
** TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
** PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
** LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
** NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
** SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
****************************************************************************/


#include <QtGui/QApplication>
#include <QtDeclarative>
#include <MDeclarativeCache>

#include "src/hardwarekeyshandler.h"
#include "src/lastfmscrobbler.h"
#include <QtSpotify>
#include <qspotify_qmlplugin.h>

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QApplication::setOrganizationName("MeeSpot");
    QApplication::setOrganizationDomain("qt.nokia.com");
    QApplication::setApplicationName("MeeSpot");
    QApplication::setApplicationVersion("1.3.0");

    QSettings::setPath(QSettings::NativeFormat, QSettings::UserScope, QLatin1String("/home/user/MyDocs/.meespotconf"));

    QApplication *app = MDeclarativeCache::qApplication(argc, argv);
    QDeclarativeView *view = MDeclarativeCache::qDeclarativeView();

    registerQmlTypes();
    view->rootContext()->setContextProperty(QLatin1String("spotifySession"), QSpotifySession::instance());
    view->engine()->addImageProvider(QLatin1String("spotify"), new QSpotifyImageProvider);

    HardwareKeysHandler keyHandler;

    LastFmScrobbler scrobbler;
    view->rootContext()->setContextProperty(QLatin1String("lastfm"), &scrobbler);

    view->setSource(QUrl("qrc:/qml/main.qml"));
    view->showFullScreen();

    return app->exec();
}
