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

#ifndef QMLSYNTAXHIGHLIGHTER_H
#define QMLSYNTAXHIGHLIGHTER_H

#include <QtCore/QObject>
#include <QtGui/QTextDocument>
#include <QtGui/QSyntaxHighlighter>
#include <QtQuick/QQuickTextDocument>
#include "abstractdecorator.h"
#include "qmlsyntaxhighlighterpalette.h"

class SyntaxHighlighter;
class QmlSyntaxHighlighter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQuickTextDocument * document READ document WRITE setDocument
               NOTIFY documentChanged)
    Q_PROPERTY(QmlSyntaxHighlighterPalette * palette READ palette WRITE setPalette
               NOTIFY paletteChanged)
public:
    explicit QmlSyntaxHighlighter(QObject *parent = 0);
    QQuickTextDocument * document() const;
    void setDocument(QQuickTextDocument *document);
    QmlSyntaxHighlighterPalette * palette() const;
    void setPalette(QmlSyntaxHighlighterPalette *palette);
signals:
    void documentChanged();
    void paletteChanged();
private:
    QQuickTextDocument *m_document;
    SyntaxHighlighter *m_syntaxHighlighter;
};

#endif // QMLSYNTAXHIGHLIGHTER_H
