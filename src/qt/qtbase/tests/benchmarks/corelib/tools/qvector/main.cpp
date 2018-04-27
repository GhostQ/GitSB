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

#include <QVector>
#include <QDebug>
#include <QtTest>

#include "qrawvector.h"

#include <vector>

/*

Code generated by g++ 4.3.3.  The lines marked with '!' are the ones that get
executed inside the loop. Using the external 's' causes some load making the
loop resembling a 'simple inner loop' in 'real' applications.


qvector_mutable_read_access:

.L166:
!       movl    -16(%ebp), %edx
!       movl    (%edx), %eax
!       subl    $1, %eax
!       je      .L165
            movl    4(%edx), %eax
            movl    %eax, 8(%esp)
            movl    8(%edx), %eax
            movl    %esi, (%esp)
            movl    %eax, 4(%esp)
            call    _ZN4myns7QVectorIdE7reallocEii
.L165:
!       movl    -16(%ebp), %eax
!       fldl    s
!       faddl   16(%eax,%ebx,8)
!       addl    $1, %ebx
!       cmpl    $10000, %ebx
!       fstpl   s
!       jne     .L166


qvector_const_read_access:

        movl    -16(%ebp), %edx
        xorl    %eax, %eax
.L183:
!       fldl    s
!       faddl   16(%edx,%eax,8)
!       addl    $1, %eax
!       cmpl    $10000, %eax
!       fstpl   s
!       jne     .L183


stdvector_const_read_access and stdvector_mutable_read_access and
qrawvector_const_read_access and qrawvector_mutable_read_access:

        xorl    %eax, %eax
.L64:
!       fldl    s
!       faddl   (%ebx,%eax,8)
!       addl    $1, %eax
!       cmpl    $10000, %eax
!       fstpl   s
!       jne     .L64



Behaviour varies with small modifications, but total is more or
less stable:

qrawvector_mutable_read_access, using  size() instead of N:

.L145:
!       faddl   (%edx,%eax,8)
!       addl    $1, %eax
!       cmpl    %ecx, %eax
!       fstl    s
!       jne     .L145
!       fstp    %st(0)


qrawvector_mutable_read_access, counting backward:

.L145:
!       faddl   (%edx,%eax,8)
!       subl    $1, %eax
!       cmpl    $-1, %eax
!       fstl    s
!       jne     .L145


qrawvector_mutable_read_access, counting backward, using size():

.L146:
!       faddl   (%edx)
!       addl    $1, %eax
!       subl    $8, %edx
!       cmpl    %ecx, %eax
!       fstl    s
!       jne     .L146



*/


/*

////////////////////////////////////////////////////////////////////

time ./tst_vector qvector_const_read_access
real    0m12.912s
user    0m12.401s
sys     0m0.016s

time ./tst_vector qvector_mutable_read_access
real    0m38.566s
user    0m36.754s
sys     0m0.008s


time ./tst_vector stdvector_mutable_read_access
real    0m12.736s
user    0m12.665s
sys     0m0.004s


////////////////////////////////////////////////////////////////////

time ./tst_vector qvector_fill_and_return
real    0m28.778s
user    0m28.522s
sys     0m0.012s

time ./tst_vector stdvector_fill_and_return
real    0m26.675s
user    0m26.558s
sys     0m0.012s

time ./tst_vector qrawvector_fill_and_return
real    0m23.370s
user    0m23.269s
sys     0m0.008s



*/



#define TEST_RETURN 1

// For some reason, both 'plain' and '-callgrind' create strange results
// (like varying instruction count for the same assembly code)
// So replace it by a plain loop and measure wall clock time.
//#undef QBENCHMARK
//#define QBENCHMARK for (int j = 0; j != 10000; ++j)

class tst_QVector: public QObject
{
    Q_OBJECT

private slots:
    void calibration();

    // Pure Qt solution
    void qvector_separator() { qWarning() << "QVector results: "; }
    void qvector_const_read_access();
    void qvector_mutable_read_access();
    void qvector_pop_back();
    #ifdef TEST_RETURN
    void qvector_fill_and_return();
    #endif

    // Purre Standard solution
    void stdvector() { qWarning() << "std::vector results: "; }
    void stdvector_const_read_access();
    void stdvector_mutable_read_access();
    void stdvector_pop_back();

    #ifdef TEST_RETURN
    void stdvector_fill_and_return();
    #endif

    // Build using std, pass as QVector
    void mixedvector() { qWarning() << "mixed results: "; }
    #ifdef TEST_RETURN
    void mixedvector_fill_and_return();
    #endif

    // Alternative implementation
    void qrawvector_separator() { qWarning() << "QRawVector results: "; }
    void qrawvector_const_read_access();
    void qrawvector_mutable_read_access();
    #ifdef TEST_RETURN
    void qrawvector_fill_and_return();
    #endif
};

const int N = 1000000;
extern double s;

void tst_QVector::calibration()
{
    QVector<double> v(N);
    for (int i = 0; i != N; ++i)
        v[i] = i;
    QBENCHMARK {
        for (int i = 0; i != N; ++i)
            s += i;
    }
}

///////////////////// QVector /////////////////////

void tst_QVector::qvector_const_read_access()
{
    QVector<double> v(N);
    for (int i = 0; i != N; ++i)
        v[i] = i;

    const QVector<double> &vc = v;
    QBENCHMARK {
        for (int i = 0; i != N; ++i)
            s += vc[i];
    }
}

void tst_QVector::qvector_mutable_read_access()
{
    QVector<double> v(N);
    for (int i = 0; i != N; ++i)
        v[i] = i;

    QBENCHMARK {
        for (int i = 0; i != N; ++i)
            s += v[i];
    }
}

#ifdef TEST_RETURN
extern QVector<double> qvector_fill_and_return_helper();

void tst_QVector::qvector_fill_and_return()
{
    QBENCHMARK {
        QVector<double> v = qvector_fill_and_return_helper();
        s += v[1];
    }
}

#endif


///////////////////// QRawVector /////////////////////

void tst_QVector::qrawvector_const_read_access()
{
    QRawVector<double> v(N);
    for (int i = 0; i != N; ++i)
        v[i] = i;

    const QRawVector<double> &vc = v;
    QBENCHMARK {
        for (int i = vc.size(); --i >= 0;)
            s += vc[i];
    }
}

void tst_QVector::qrawvector_mutable_read_access()
{
    QRawVector<double> v(N);
    for (int i = 0; i != N; ++i)
        v[i] = i;

    QBENCHMARK {
        for (int i = 0; i != N; ++i)
            s += v[i];
    }
}

void tst_QVector::qvector_pop_back()
{
    const int c1 = 100000;
    QVERIFY(N % c1 == 0);

    QVector<int> v;
    v.resize(N);

    QBENCHMARK {
        for (int i = 0; i < c1; ++i)
            v.pop_back();
        if (v.size() == 0)
            v.resize(N);
    }
}



#ifdef TEST_RETURN
extern QVector<double> qrawvector_fill_and_return_helper();

void tst_QVector::qrawvector_fill_and_return()
{
    QBENCHMARK {
        QVector<double> v = qrawvector_fill_and_return_helper();
        s += v[1];
    }
}

#endif


///////////////////// std::vector /////////////////////

void tst_QVector::stdvector_const_read_access()
{
    std::vector<double> v(N);
    for (int i = 0; i != N; ++i)
        v[i] = i;

    const std::vector<double> &vc = v;
    QBENCHMARK {
        for (int i = 0; i != N; ++i)
            s += vc[i];
    }
}

void tst_QVector::stdvector_mutable_read_access()
{
    std::vector<double> v(N);
    for (int i = 0; i != N; ++i)
        v[i] = i;

    QBENCHMARK {
        for (int i = 0; i != N; ++i)
            s += v[i];
    }
}

void tst_QVector::stdvector_pop_back()
{
    const int c1 = 100000;
    QVERIFY(N % c1 == 0);

    std::vector<int> v;
    v.resize(N);

    QBENCHMARK {
        for (int i = 0; i < c1; ++i)
            v.pop_back();
        if (v.size() == 0)
            v.resize(N);
    }
}

#ifdef TEST_RETURN
extern std::vector<double> stdvector_fill_and_return_helper();

void tst_QVector::stdvector_fill_and_return()
{
    QBENCHMARK {
        std::vector<double> v = stdvector_fill_and_return_helper();
        s += v[1];
    }
}

#endif

///////////////////// mixed vector /////////////////////


#ifdef TEST_RETURN
extern QVector<double> mixedvector_fill_and_return_helper();

void tst_QVector::mixedvector_fill_and_return()
{
    QBENCHMARK {
        std::vector<double> v = stdvector_fill_and_return_helper();
        s += v[1];
    }
}

#endif

QTEST_MAIN(tst_QVector)

#include "main.moc"
