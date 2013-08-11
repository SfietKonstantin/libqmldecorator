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
 *   * The names of its contributors may not be used to endorse or promote 
 *     products derived from this software without specific prior written 
 *     permission.
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

#include "abstractdecorator.h"
#include <QtCore/QCoreApplication>
#include <QtCore/QStringList>
#include <QtCore/QTextStream>
#include <QtCore/QFile>
#include <QtCore/QDebug>

class LatexDecorator: public AbstractDecorator
{
public:
    explicit LatexDecorator();
    QString decoratedText() const;
    int state() const;
protected:
    void prepare(const QString &text);
    void addKeyword(int begin, int length);
    void addComponent(int begin, int length);
    void addIdentifier(int begin, int length);
    void addMacro(int begin, int length);
    void addString(int begin, int length);
    void addComment(int begin, int length);
    void addNumber(int begin, int length);
    void setState(int state);
private:
    void addDecoration(int begin, const QString &prefix,
                       int length, const QString &suffix);
    QString m_decoratedText;
    int m_state;
    int m_delta;
};

LatexDecorator::LatexDecorator()
{
    m_delta = 0;
}

QString LatexDecorator::decoratedText() const
{
    return m_decoratedText;
}

int LatexDecorator::state() const
{
    return m_state;
}

void LatexDecorator::prepare(const QString &text)
{
    m_decoratedText = text;
    m_delta = 0;
}

void LatexDecorator::addKeyword(int begin, int length)
{
    addDecoration(begin, "\\codeKeyword|", length, "&");
}

void LatexDecorator::addComponent(int begin, int length)
{
    addDecoration(begin, "\\codeComponent|", length, "&");
}

void LatexDecorator::addIdentifier(int begin, int length)
{
    addDecoration(begin, "\\codeIdentifier|", length, "&");
}

void LatexDecorator::addMacro(int begin, int length)
{
    addDecoration(begin, "\\codeMacro|", length, "&");
}

void LatexDecorator::addString(int begin, int length)
{
    addDecoration(begin, "\\codeString|", length, "&");
}

void LatexDecorator::addComment(int begin, int length)
{
    addDecoration(begin, "\\codeComment|", length, "&");
}

void LatexDecorator::addNumber(int begin, int length)
{
    addDecoration(begin, "\\codeNumber|", length, "&");
}

void LatexDecorator::setState(int state)
{
    m_state = state;
}

void LatexDecorator::addDecoration(int begin, const QString &prefix,
                                   int length, const QString &suffix)
{
    m_decoratedText.insert(m_delta + begin, prefix);
    m_delta += prefix.count();
    m_decoratedText.insert(m_delta + begin + length, suffix);
    m_delta += suffix.count();
}

void help()
{
    qDebug() << "qmldecorator: generate LaTeX files of syntax highlighted QML code.";
    qDebug() << "";
    qDebug() << "qmldecorator uses the fancyvrb module to generate syntax highlighted";
    qDebug() << "QML code that are suited for inclusion in LaTeX documents. You will ";
    qDebug() << "have to define custom commands, using, for example textcolor, to decorate";
    qDebug() << "the code. Pass the --commands to get an example of these commands.";
    qDebug() << "";
    qDebug() << "Usage: ";
    qDebug() << "qmldecorator INPUT OUTPUT";
    qDebug() << "qmldecorator --commands";
}

int main(int argc, char **argv)
{
    QCoreApplication app (argc, argv);
    if (app.arguments().count() != 3 && app.arguments().count() != 2) {
        help();
        return 1;
    }

    if (app.arguments().count() == 2) {
        if (app.arguments().at(1) != "--commands") {
            help();
            return 1;
        } else {
            qDebug() << "\\usepackage{fancyvrb}";
            qDebug() << "...";
            qDebug() << "\\begin{document}";
            qDebug() << "\\newcommand*{\\codeKeyword}[1]{\\textcolor[RGB]{227,173,0}{#1}}";
            qDebug() << "\\newcommand*{\\codeComponent}[1]{\\textcolor[RGB]{70,40,134}{#1}} ";
            qDebug() << "\\newcommand*{\\codeIdentifier}[1]{\\textcolor[RGB]{89,0,0}{#1}}";
            qDebug() << "\\newcommand*{\\codeMacro}[1]{\\textcolor[RGB]{0,87,174}{#1}}";
            qDebug() << "\\newcommand*{\\codeString}[1]{\\textcolor[RGB]{55,164,44}{#1}}";
            qDebug() << "\\newcommand*{\\codeComment}[1]{\\textcolor[RGB]{136,136,136}{#1}}";
            qDebug() << "\\newcommand*{\\codeNumber}[1]{\\textcolor[RGB]{0,0,128}{#1}}";
            return 0;
        }
    }

    QString input = app.arguments().at(1);
    QString output = app.arguments().at(2);

    QFile inputFile (input);
    if (!inputFile.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open input file:" << input;
        return 2;
    }
    QTextStream inputStream (&inputFile);
    QString inputCode = inputStream.readAll();
    inputFile.close();

    LatexDecorator decorator;
    QStringList splittedInputCode = inputCode.split("\n");
    QString outputCode;
    int state = QmlJS::Scanner::Normal;
    foreach (QString line, splittedInputCode) {
        decorator.decorate(line, state);
        state = decorator.state();
        outputCode.append(decorator.decoratedText());
        outputCode.append("\n");
    }

    outputCode.prepend("\\begin{Verbatim}[commandchars=\\\\|&]\n");
    outputCode.append("\\end{Verbatim}");

    QFile outputFile (output);
    if (!outputFile.open(QIODevice::WriteOnly)) {
        qWarning() << "Failed to open output file:" << output;
        return 2;
    }
    QTextStream outputStream (&outputFile);
    outputStream << outputCode;
    outputFile.close();

    return 0;
}
