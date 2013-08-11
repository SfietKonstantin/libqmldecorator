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

#include "qmlsyntaxhighlighter.h"
#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include "qmlsyntaxhighlighterpalette.h"

class SyntaxHighlighter: public QSyntaxHighlighter, private AbstractDecorator
{
    Q_OBJECT
public:
    explicit SyntaxHighlighter(QObject *parent = 0);
    QmlSyntaxHighlighterPalette * palette() const;
    void setPalette(QmlSyntaxHighlighterPalette *palette);
protected:
    bool event(QEvent *e);
private:
    void highlightBlock(const QString &text);
    void addKeyword(int begin, int length);
    void addComponent(int begin, int length);
    void addIdentifier(int begin, int length);
    void addMacro(int begin, int length);
    void addString(int begin, int length);
    void addComment(int begin, int length);
    void addNumber(int begin, int length);
    void setState(int state);
    QmlSyntaxHighlighterPalette *m_palette;
};

SyntaxHighlighter::SyntaxHighlighter(QObject *parent):
    QSyntaxHighlighter(parent), AbstractDecorator(), m_palette(0)
{
}

QmlSyntaxHighlighterPalette * SyntaxHighlighter::palette() const
{
    return m_palette;
}

void SyntaxHighlighter::setPalette(QmlSyntaxHighlighterPalette *palette)
{
    m_palette = palette;
}

bool SyntaxHighlighter::event(QEvent *e)
{
    if (e->type() == QEvent::User) {
        rehighlight();
        return true;
    }
    return QObject::event(e);
}

void SyntaxHighlighter::highlightBlock(const QString &text)
{
    int previousState = previousBlockState();
    if (previousState == -1) {
        decorate(text);
    } else {
        decorate(text, previousBlockState());
    }
}

void SyntaxHighlighter::addKeyword(int begin, int length)
{
    QColor color;
    if (m_palette) {
        color = m_palette->keyword();
    } else {
        color = QColor(Qt::darkYellow);
    }
    setFormat(begin, length, color);
}

void SyntaxHighlighter::addComponent(int begin, int length)
{
    QColor color;
    if (m_palette) {
        color = m_palette->component();
    } else {
        color = QColor(Qt::darkMagenta);
    }
    setFormat(begin, length, color);
}

void SyntaxHighlighter::addIdentifier(int begin, int length)
{
    QColor color;
    if (m_palette) {
        color = m_palette->identifier();
    } else {
        color = QColor(Qt::darkRed);
    }
    setFormat(begin, length, color);
}

void SyntaxHighlighter::addMacro(int begin, int length)
{
    QColor color;
    if (m_palette) {
        color = m_palette->macro();
    } else {
        color = QColor(Qt::cyan);
    }
    setFormat(begin, length, color);
}

void SyntaxHighlighter::addString(int begin, int length)
{
    QColor color;
    if (m_palette) {
        color = m_palette->string();
    } else {
        color = QColor(Qt::darkGreen);
    }
    setFormat(begin, length, color);
}

void SyntaxHighlighter::addComment(int begin, int length)
{
    QColor color;
    if (m_palette) {
        color = m_palette->comment();
    } else {
        color = QColor(Qt::gray);
    }
    setFormat(begin, length, color);
}

void SyntaxHighlighter::addNumber(int begin, int length)
{
    QColor color;
    if (m_palette) {
        color = m_palette->number();
    } else {
        color = QColor(Qt::blue);
    }
    setFormat(begin, length, color);
}

void SyntaxHighlighter::setState(int state)
{
    if (state != currentBlockState()) {
        setCurrentBlockState(state);
        QCoreApplication::instance()->postEvent(this, new QEvent(QEvent::User));
    }
}

QmlSyntaxHighlighter::QmlSyntaxHighlighter(QObject *parent) :
    QObject(parent), m_document(0), m_syntaxHighlighter(new SyntaxHighlighter(this))
{
}

QQuickTextDocument *QmlSyntaxHighlighter::document() const
{
    return m_document;
}

void QmlSyntaxHighlighter::setDocument(QQuickTextDocument *document)
{
    if (m_document != document) {
        m_document = document;
        emit documentChanged();

        m_syntaxHighlighter->setDocument(document->textDocument());
    }
}

QmlSyntaxHighlighterPalette * QmlSyntaxHighlighter::palette() const
{
    return m_syntaxHighlighter->palette();
}

void QmlSyntaxHighlighter::setPalette(QmlSyntaxHighlighterPalette *palette)
{
    if (m_syntaxHighlighter->palette() != palette) {
        m_syntaxHighlighter->setPalette(palette);
        emit paletteChanged();
    }
}

#include "qmlsyntaxhighlighter.moc"
