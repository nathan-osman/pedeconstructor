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

#include <QAction>
#include <QApplication>
#include <QDesktopWidget>
#include <QDir>
#include <QFileDialog>
#include <QIcon>
#include <QKeySequence>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QRect>
#include <QTabWidget>
#include <QToolBar>

#include "mainwindow.h"

MainWindow::MainWindow()
    : mFile(nullptr),
      mGeneralWidget(new GeneralWidget),
      mSectionsWidget(new SectionsWidget),
      mImportsWidget(new ImportsWidget)
{
    setWindowTitle(tr("PE Deconstructor"));

    QAction *open = new QAction(QIcon::fromTheme("document-open"), tr("&Open"), this);
    open->setShortcut(QKeySequence::Open);
    connect(open, &QAction::triggered, this, &MainWindow::onOpenClicked);

    QMenu *file = menuBar()->addMenu(tr("&File"));
    file->addAction(open);
    file->addSeparator();
    file->addAction(tr("&Quit"), QApplication::instance(), &QApplication::quit);

    QToolBar *toolbar = addToolBar(tr("File"));
    toolbar->addAction(open);

    QTabWidget *tabWidget = new QTabWidget;
    tabWidget->addTab(mGeneralWidget, tr("&General"));
    tabWidget->addTab(mSectionsWidget, tr("&Sections"));
    tabWidget->addTab(mImportsWidget, tr("&Imports"));

    setCentralWidget(tabWidget);

    QRect rect = geometry();
    rect.moveCenter(QApplication::desktop()->screenGeometry().center());
    setGeometry(rect);
}

MainWindow::~MainWindow()
{
    if (mFile) {
        delete mFile;
    }
}

void MainWindow::openFile(const QString &filename)
{
    if (mFile) {
        delete mFile;
    }

    mFile = new win32pe::File;

    if (!mFile->load(filename.toStdString())) {
        QMessageBox::critical(
            this,
            tr("Error"),
            tr("An error has occurred: %1").arg(QString::fromStdString(mFile->errorString()))
        );
        return;
    }

    mGeneralWidget->update(mFile);
    mSectionsWidget->update(mFile);
}

void MainWindow::onOpenClicked()
{
    QString filename = QFileDialog::getOpenFileName(
        this,
        tr("Select File"),
        QDir::homePath(),
        QString("PE files (*.exe *.dll);;All files (*.*)")
    );

    if (!filename.isNull()) {
        openFile(filename);
    }
}
