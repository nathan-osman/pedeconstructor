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
#include <QGridLayout>
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
    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(new QLabel(tr("Machine:")), 0, 0);
    gridLayout->addWidget(mMachine, 0, 1);
    gridLayout->addWidget(new QLabel(tr("Timestamp:")), 1, 0);
    gridLayout->addWidget(mTimestamp, 1, 1);
    gridLayout->setColumnStretch(1, 1);

    QVBoxLayout *vboxLayout = new QVBoxLayout;
    vboxLayout->addLayout(gridLayout);
    vboxLayout->addWidget(mRelocsStripped);
    vboxLayout->addWidget(mExecutableImage);
    vboxLayout->addWidget(mLineNumsStripped);
    vboxLayout->addWidget(mLocalSymsStripped);
    vboxLayout->addWidget(mLargeAddressAware);
    vboxLayout->addWidget(mThirtyTwoBitMachine);
    vboxLayout->addWidget(mDebugStripped);
    vboxLayout->addWidget(mRemovableRunFromSwap);
    vboxLayout->addWidget(mNetRunFromSwap);
    vboxLayout->addWidget(mSystem);
    vboxLayout->addWidget(mDLL);
    vboxLayout->addWidget(mUPSystemOnly);
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
