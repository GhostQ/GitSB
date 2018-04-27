/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the test suite of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL21$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** As a special exception, The Qt Company gives you certain additional
** rights. These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
****************************************************************************/
/* NOTE: This file is AUTO GENERATED by qtokenautomaton2cpp.xsl. */

#ifndef q_noNamespace_h
#define q_noNamespace_h

#include <QtCore/QString>

QT_BEGIN_NAMESPACE

class NoNamespace
                {
                public:
                enum Token

                {
                NoKeyword,
AReallyLongTokenIFreakinMeanItUKnowUKnowKnow,
ColonInName,
FFFF,
FFFG,
FFGF,
FFGG,
FFLM,
WeHaveDashes,
WeHaveDashes2,
_,
_111,
wobbly
                };

                static inline Token toToken(const QString &value);
static inline Token toToken(const QStringRef &value);
static Token toToken(const QChar *data, int length);
static QString toString(Token token);


                private:
                    static inline Token classifier3(const QChar *data);
static inline Token classifier4(const QChar *data);
static inline Token classifier14(const QChar *data);
static inline Token classifier15(const QChar *data);
static inline Token classifier44(const QChar *data);

                };

                inline NoNamespace::Token NoNamespace::toToken(const QString &value)
                {
                    return toToken(value.constData(), value.length());
                }

                inline NoNamespace::Token NoNamespace::toToken(const QStringRef &value)
                {
                    return toToken(value.constData(), value.length());
                }

                
QT_END_NAMESPACE

#endif
