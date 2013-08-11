/*
 * Copyright (C) 2013 Lucien XU <sfietkonstantin@free.fr>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <QtQml/QQmlExtensionPlugin>
#include <QtQml/qqml.h>
#include "qmlsyntaxhighlighter.h"

class QtQuickControlsPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.SfietKonstantin.qmldecorator/1.0")

public:
    void registerTypes(const char *uri);
};

void QtQuickControlsPlugin::registerTypes(const char *uri)
{
    // @uri org.SfietKonstantin.qmldecorator
    qmlRegisterType<QmlSyntaxHighlighter>(uri, 1, 0, "QmlSyntaxHighlighter");
}

#include "plugin.moc"
