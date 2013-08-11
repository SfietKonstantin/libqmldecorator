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

#include "abstractdecorator.h"
#include <QtCore/QDebug>

AbstractDecorator::AbstractDecorator()
{
}

void AbstractDecorator::decorate(const QString &text, int state)
{
    if (text.contains("\n")) {
        qDebug() << "Wrong block found";
        return;
    }

    prepare();

    QmlJS::Scanner scanner;
    QList<QmlJS::Token> tokens = scanner(text, state);
    for (int i = 0; i < tokens.count(); i++) {
        const QmlJS::Token token = tokens.at(i);

        switch (token.kind) {
        case QmlJS::Token::Keyword:
            addKeyword(token.offset, token.length);
            break;
        case QmlJS::Token::Identifier: {
                QString entry = text.mid(token.offset, token.length);

                if (maybeQmlKeyword(entry)) {
                    // check the previous token
                    if (i == 0 || tokens.at(i - 1).isNot(QmlJS::Token::Dot)) {
                        if (i + 1 == tokens.count() || tokens.at(i + 1).isNot(QmlJS::Token::Colon)) {
                            addKeyword(token.offset, token.length);
                            break;
                        }
                    }
                } else if (i > 0 && maybeQmlBuiltinType(entry)) {
                    const QmlJS::Token &previousToken = tokens.at(i - 1);
                    if (previousToken.is(QmlJS::Token::Identifier)
                        && text.mid(previousToken.offset, previousToken.length) == QLatin1String("property")) {
                        addKeyword(token.offset, token.length);
                        break;
                    }
                }

                if (maybeMacro(entry)) {
                    addMacro(token.offset, token.length);
                    break;
                }

                if (entry.at(0).isUpper()) {
                    // Check if we are importing a module
                    if (i > 0) {
                        const QmlJS::Token &previousToken = tokens.at(i - 1);
                        if (previousToken.is(QmlJS::Token::Identifier)
                            && text.mid(previousToken.offset, previousToken.length) == QLatin1String("import")) {
                            addKeyword(token.offset, token.length);
                            break;
                        }
                    }

                    addComponent(token.offset, token.length);
                    break;
                }

                // Try to find if it is a property
                // The easy ones are followed by a { or a :
                if (i + 1 < tokens.count()) {
                    const QmlJS::Token &nextToken = tokens.at(i + 1);
                    if (nextToken.is(QmlJS::Token::Colon)
                        || nextToken.is(QmlJS::Token::LeftBrace)) {
                        addIdentifier(token.offset, token.length);
                        break;
                    }
                }

                // A harder one is anchors.fill:
                if (i + 3 < tokens.count()) {
                    const QmlJS::Token &next1Token = tokens.at(i + 1);
                    const QmlJS::Token &next2Token = tokens.at(i + 2);
                    const QmlJS::Token &next3Token = tokens.at(i + 3);

                    if (next1Token.is(QmlJS::Token::Dot)
                        && next2Token.is(QmlJS::Token::Identifier)
                        && (next3Token.is(QmlJS::Token::Colon)
                            || next3Token.is(QmlJS::Token::LeftBrace))) {
                        addIdentifier(token.offset, token.length);
                        break;
                    }
                }
            }
            break;
        case QmlJS::Token::String:
            addString(token.offset, token.length);
            break;
        case QmlJS::Token::Comment:
            addComment(token.offset, token.length);
            break;
        case QmlJS::Token::Number:
            addNumber(token.offset, token.length);
            break;
        default:
            break;
        }
    }

    setState(scanner.state());
    finalize();
}

void AbstractDecorator::prepare()
{
}

void AbstractDecorator::addKeyword(int begin, int length)
{
    Q_UNUSED(begin)
    Q_UNUSED(length)
}

void AbstractDecorator::addComponent(int begin, int length)
{
    Q_UNUSED(begin)
    Q_UNUSED(length)
}

void AbstractDecorator::addIdentifier(int begin, int length)
{
    Q_UNUSED(begin)
    Q_UNUSED(length)
}

void AbstractDecorator::addMacro(int begin, int length)
{
    Q_UNUSED(begin)
    Q_UNUSED(length)
}

void AbstractDecorator::addString(int begin, int length)
{
    Q_UNUSED(begin)
    Q_UNUSED(length)
}

void AbstractDecorator::addComment(int begin, int length)
{
    Q_UNUSED(begin)
    Q_UNUSED(length)
}

void AbstractDecorator::addNumber(int begin, int length)
{
    Q_UNUSED(begin)
    Q_UNUSED(length)
}

void AbstractDecorator::setState(int state)
{
    Q_UNUSED(state)
}

void AbstractDecorator::finalize()
{
}

bool AbstractDecorator::maybeQmlKeyword(const QString &text) const
{
    // Rewrite this code
    if (text.isEmpty()) {
        return false;
    }

    if (text == QLatin1String("property")) {
        return true;
    } else if (text == QLatin1String("alias")) {
        return true;
    } else if (text == QLatin1String("signal")) {
        return true;
    } else if (text == QLatin1String("property")) {
        return true;
    } else if (text == QLatin1String("readonly")) {
        return true;
    } else if (text == QLatin1String("import")) {
        return true;
    } else if (text == QLatin1String("on")) {
        return true;
    } else {
        return false;
    }
}

bool AbstractDecorator::maybeQmlBuiltinType(const QString &text) const
{
    // Rewrite this code
    if (text.isEmpty()) {
        return false;
    }

    if (text == QLatin1String("action")) {
            return true;
    } else if (text == QLatin1String("bool")) {
        return true;
    } else if (text == QLatin1String("color")) {
        return true;
    } else if (text == QLatin1String("date")) {
        return true;
    } else if (text == QLatin1String("double")) {
        return true;
    } else if (text == QLatin1String("enumeration")) {
        return true;
    } else if (text == QLatin1String("font")) {
        return true;
    } else if (text == QLatin1String("int")) {
        return true;
    } else if (text == QLatin1String("list")) {
        return true;
    } else if (text == QLatin1String("point")) {
        return true;
    } else if (text == QLatin1String("real")) {
        return true;
    } else if (text == QLatin1String("rect")) {
        return true;
    } else if (text == QLatin1String("size")) {
        return true;
    } else if (text == QLatin1String("string")) {
        return true;
    } else if (text == QLatin1String("time")) {
        return true;
    } else if (text == QLatin1String("url")) {
        return true;
    } else if (text == QLatin1String("variant")) {
        return true;
    } else if (text == QLatin1String("var")) {
        return true;
    } else if (text == QLatin1String("vector3d")) {
        return true;
    } else {
        return false;
    }
}

bool AbstractDecorator::maybeMacro(const QString &text) const
{
    if (text == QLatin1String("console")) {
        return true;
    } else {
        return false;
    }
}
