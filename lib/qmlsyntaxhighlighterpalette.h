/*
 * Copyright (C) 2013 Lucien XU <sfietkonstantin@free.fr>
 *
 * You may use this file under the terms of the BSD license as follows:
 *
 * "Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *   * Neither the name of Nemo Mobile nor the names of its contributors
 *     may be used to endorse or promote products derived from this
 *     software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
 */

#ifndef QMLSYNTAXHIGHLIGHTERPALETTE_H
#define QMLSYNTAXHIGHLIGHTERPALETTE_H

#include <QtCore/QObject>
#include <QtGui/QColor>

class QmlSyntaxHighlighterPalette: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QColor keyword READ keyword WRITE setKeyword NOTIFY keywordChanged)
    Q_PROPERTY(QColor component READ component WRITE setComponent NOTIFY componentChanged)
    Q_PROPERTY(QColor identifier READ identifier WRITE setIdentifier NOTIFY identifierChanged)
    Q_PROPERTY(QColor macro READ macro WRITE setMacro NOTIFY macroChanged)
    Q_PROPERTY(QColor string READ string WRITE setString NOTIFY stringChanged)
    Q_PROPERTY(QColor comment READ comment WRITE setComment NOTIFY commentChanged)
    Q_PROPERTY(QColor number READ number WRITE setNumber NOTIFY numberChanged)
public:
    QmlSyntaxHighlighterPalette(QObject *parent = 0);
    QColor keyword() const;
    void setKeyword(const QColor &keyword);
    QColor component() const;
    void setComponent(const QColor &component);
    QColor identifier() const;
    void setIdentifier(const QColor &identifier);
    QColor macro() const;
    void setMacro(const QColor &macro);
    QColor string() const;
    void setString(const QColor &string);
    QColor comment() const;
    void setComment(const QColor &comment);
    QColor number() const;
    void setNumber(const QColor &number);
signals:
    void keywordChanged();
    void componentChanged();
    void identifierChanged();
    void macroChanged();
    void stringChanged();
    void commentChanged();
    void numberChanged();
private:
    QColor m_keyword;
    QColor m_component;
    QColor m_identifier;
    QColor m_macro;
    QColor m_string;
    QColor m_comment;
    QColor m_number;
};

#endif // QMLSYNTAXHIGHLIGHTERPALETTE_H
