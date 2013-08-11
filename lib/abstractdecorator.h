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

#ifndef ABSTRACTDECORATOR_H
#define ABSTRACTDECORATOR_H

#include <QtCore/QString>
#include "qmljsscanner.h"

class AbstractDecorator
{
public:
    AbstractDecorator();
    void decorate(const QString &text, int state = QmlJS::Scanner::Normal);
protected:
    virtual void prepare();
    virtual void addKeyword(int begin, int length);
    virtual void addComponent(int begin, int length);
    virtual void addIdentifier(int begin, int length);
    virtual void addMacro(int begin, int length);
    virtual void addString(int begin, int length);
    virtual void addComment(int begin, int length);
    virtual void addNumber(int begin, int length);
    virtual void setState(int state);
    virtual void finalize();
private:
    bool maybeQmlKeyword(const QString &text) const;
    bool maybeQmlBuiltinType(const QString &text) const;
    bool maybeMacro(const QString &text) const;
};


#endif // ABSTRACTDECORATOR_H
