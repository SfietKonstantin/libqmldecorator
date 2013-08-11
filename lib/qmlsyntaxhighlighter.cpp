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

class SyntaxHighlighter: public QSyntaxHighlighter, private AbstractDecorator
{
    Q_OBJECT
public:
    explicit SyntaxHighlighter(QObject *parent = 0);
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
};

SyntaxHighlighter::SyntaxHighlighter(QObject *parent):
    QSyntaxHighlighter(parent), AbstractDecorator()
{
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
    QTextCharFormat keyword;
    keyword.setForeground(Qt::darkYellow);
    setFormat(begin, length, keyword);
}

void SyntaxHighlighter::addComponent(int begin, int length)
{
    QTextCharFormat keyword;
    keyword.setForeground(Qt::darkMagenta);
    setFormat(begin, length, keyword);
}

void SyntaxHighlighter::addIdentifier(int begin, int length)
{
    QTextCharFormat keyword;
    keyword.setForeground(Qt::darkRed);
    setFormat(begin, length, keyword);
}

void SyntaxHighlighter::addMacro(int begin, int length)
{
    QTextCharFormat keyword;
    keyword.setForeground(Qt::cyan);
    setFormat(begin, length, keyword);
}

void SyntaxHighlighter::addString(int begin, int length)
{
    QTextCharFormat keyword;
    keyword.setForeground(Qt::darkGreen);
    setFormat(begin, length, keyword);
}

void SyntaxHighlighter::addComment(int begin, int length)
{
    QTextCharFormat keyword;
    keyword.setForeground(Qt::gray);
    setFormat(begin, length, keyword);
}

void SyntaxHighlighter::addNumber(int begin, int length)
{
    QTextCharFormat keyword;
    keyword.setForeground(Qt::blue);
    setFormat(begin, length, keyword);
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

#include "qmlsyntaxhighlighter.moc"
