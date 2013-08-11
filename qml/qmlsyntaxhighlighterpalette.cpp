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

#include "qmlsyntaxhighlighterpalette.h"

QmlSyntaxHighlighterPalette::QmlSyntaxHighlighterPalette(QObject *parent):
    QObject(parent)
{
}

QColor QmlSyntaxHighlighterPalette::keyword() const
{
    return m_keyword;
}

void QmlSyntaxHighlighterPalette::setKeyword(const QColor &keyword)
{
    if (m_keyword != keyword) {
        m_keyword = keyword;
        emit keywordChanged();
    }
}

QColor QmlSyntaxHighlighterPalette::component() const
{
    return m_component;
}

void QmlSyntaxHighlighterPalette::setComponent(const QColor &component)
{
    if (m_component != component) {
        m_component = component;
        emit componentChanged();
    }
}

QColor QmlSyntaxHighlighterPalette::identifier() const
{
    return m_identifier;
}

void QmlSyntaxHighlighterPalette::setIdentifier(const QColor &identifier)
{
    if (m_identifier != identifier) {
        m_identifier = identifier;
        emit identifierChanged();
    }
}

QColor QmlSyntaxHighlighterPalette::macro() const
{
    return m_macro;
}

void QmlSyntaxHighlighterPalette::setMacro(const QColor &macro)
{
    if (m_macro != macro) {
        m_macro = macro;
        emit macroChanged();
    }
}

QColor QmlSyntaxHighlighterPalette::string() const
{
    return m_string;
}

void QmlSyntaxHighlighterPalette::setString(const QColor &string)
{
    if (m_string != string) {
        m_string = string;
        emit stringChanged();
    }
}

QColor QmlSyntaxHighlighterPalette::comment() const
{
    return m_comment;
}

void QmlSyntaxHighlighterPalette::setComment(const QColor &comment)
{
    if (m_comment != comment) {
        m_comment = comment;
        emit commentChanged();
    }
}

QColor QmlSyntaxHighlighterPalette::number() const
{
    return m_number;
}

void QmlSyntaxHighlighterPalette::setNumber(const QColor &number)
{
    if (m_number != number) {
        m_number = number;
        emit numberChanged();
    }
}

