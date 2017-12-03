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

#include <QDateTime>
#include <QFrame>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QVBoxLayout>

#include <win32pe/fileheader.h>

#include "generalwidget.h"

GeneralWidget::GeneralWidget()
    : mMachine(new QLabel),
      mTimestamp(new QLabel),
      mRelocsStripped(new QCheckBox(tr("Relocation information stripped"))),
      mExecutableImage(new QCheckBox(tr("File is executable"))),
      mLineNumsStripped(new QCheckBox(tr("Line numbers stripped"))),
      mLocalSymsStripped(new QCheckBox(tr("Symbol table entries stripped"))),
      mLargeAddressAware(new QCheckBox(tr("Large address aware"))),
      mThirtyTwoBitMachine(new QCheckBox(tr("32-bit words"))),
      mDebugStripped(new QCheckBox(tr("Debug information stripped"))),
      mRemovableRunFromSwap(new QCheckBox(tr("Copy to swap when run from removable media"))),
      mNetRunFromSwap(new QCheckBox(tr("Copy to swap when run from the network"))),
      mSystem(new QCheckBox(tr("System file"))),
      mDLL(new QCheckBox(tr("Image is a DLL"))),
      mUPSystemOnly(new QCheckBox(tr("Run on uniprocessor system")))
{
    QFrame *frame = new QFrame;
    frame->setFrameShape(QFrame::HLine);
    frame->setFrameShadow(QFrame::Sunken);

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(new QLabel(tr("Machine:")), 0, 0);
    gridLayout->addWidget(mMachine, 0, 1);
    gridLayout->addWidget(new QLabel(tr("Timestamp:")), 1, 0);
    gridLayout->addWidget(mTimestamp, 1, 1);
    gridLayout->setColumnStretch(1, 1);

    QVBoxLayout *col1Layout = new QVBoxLayout;
    col1Layout->addWidget(mRelocsStripped);
    col1Layout->addWidget(mExecutableImage);
    col1Layout->addWidget(mLineNumsStripped);
    col1Layout->addWidget(mLocalSymsStripped);
    col1Layout->addWidget(mLargeAddressAware);
    col1Layout->addWidget(mThirtyTwoBitMachine);

    QVBoxLayout *col2Layout = new QVBoxLayout;
    col2Layout->addWidget(mDebugStripped);
    col2Layout->addWidget(mRemovableRunFromSwap);
    col2Layout->addWidget(mNetRunFromSwap);
    col2Layout->addWidget(mSystem);
    col2Layout->addWidget(mDLL);
    col2Layout->addWidget(mUPSystemOnly);

    QHBoxLayout *hboxLayout = new QHBoxLayout;
    hboxLayout->addLayout(col1Layout);
    hboxLayout->addLayout(col2Layout);

    QVBoxLayout *vboxLayout = new QVBoxLayout;
    vboxLayout->addLayout(gridLayout);
    vboxLayout->addWidget(frame);
    vboxLayout->addLayout(hboxLayout);
    vboxLayout->addStretch(1);

    setLayout(vboxLayout);
}

void GeneralWidget::update(win32pe::File *file)
{
    switch (file->fileHeader().machine()) {
    case win32pe::FileHeader::i386:
        mMachine->setText(tr("i386"));
        break;
    case win32pe::FileHeader::amd64:
        mMachine->setText(tr("amd64"));
        break;
    default:
        mMachine->setText(tr("unknown"));
        break;
    }

    mTimestamp->setText(QDateTime::fromMSecsSinceEpoch(
        static_cast<qint64>(file->fileHeader().timeDateStamp()) * 1000
    ).toString(Qt::DefaultLocaleLongDate));

    auto flags = file->fileHeader().characteristics();
    mRelocsStripped->setChecked(flags & win32pe::FileHeader::RelocsStripped);
    mExecutableImage->setChecked(flags & win32pe::FileHeader::ExecutableImage);
    mLineNumsStripped->setChecked(flags & win32pe::FileHeader::LineNumsStripped);
    mLocalSymsStripped->setChecked(flags & win32pe::FileHeader::LocalSymsStripped);
    mLargeAddressAware->setChecked(flags & win32pe::FileHeader::LargeAddressAware);
    mThirtyTwoBitMachine->setChecked(flags & win32pe::FileHeader::ThirtyTwoBitMachine);
    mDebugStripped->setChecked(flags & win32pe::FileHeader::DebugStripped);
    mRemovableRunFromSwap->setChecked(flags & win32pe::FileHeader::RemovableRunFromSwap);
    mNetRunFromSwap->setChecked(flags & win32pe::FileHeader::NetRunFromSwap);
    mSystem->setChecked(flags & win32pe::FileHeader::System);
    mDLL->setChecked(flags & win32pe::FileHeader::DLL);
    mUPSystemOnly->setChecked(flags & win32pe::FileHeader::UPSystemOnly);
}
