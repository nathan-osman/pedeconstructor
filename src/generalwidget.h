/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2017 Nathan Osman
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#ifndef GENERALWIDGET_H
#define GENERALWIDGET_H

#include <QCheckBox>
#include <QLabel>
#include <QWidget>

#include <win32pe/file.h>

class GeneralWidget : public QWidget
{
    Q_OBJECT

public:

    GeneralWidget();

    void update(win32pe::File *file);

private:

    QLabel *mMachine;
    QLabel *mTimestamp;

    QCheckBox *mRelocsStripped;
    QCheckBox *mExecutableImage;
    QCheckBox *mLineNumsStripped;
    QCheckBox *mLocalSymsStripped;
    QCheckBox *mLargeAddressAware;
    QCheckBox *mThirtyTwoBitMachine;
    QCheckBox *mDebugStripped;
    QCheckBox *mRemovableRunFromSwap;
    QCheckBox *mNetRunFromSwap;
    QCheckBox *mSystem;
    QCheckBox *mDLL;
    QCheckBox *mUPSystemOnly;
};

#endif // GENERALWIDGET_H
