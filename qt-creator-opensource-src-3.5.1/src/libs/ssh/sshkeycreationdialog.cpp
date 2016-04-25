/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company.  For licensing terms and
** conditions see http://www.qt.io/terms-conditions.  For further information
** use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file.  Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, The Qt Company gives you certain additional
** rights.  These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
****************************************************************************/
#include "sshkeycreationdialog.h"
#include "ui_sshkeycreationdialog.h"

#include "sshkeygenerator.h"

#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QApplication>
#include <QMessageBox>
#include <QStandardPaths>

namespace QSsh {

SshKeyCreationDialog::SshKeyCreationDialog(QWidget *parent)
    : QDialog(parent), m_keyGenerator(0), m_ui(new Ui::SshKeyCreationDialog)
{
    m_ui->setupUi(this);
    // Not using Utils::PathChooser::browseButtonLabel to avoid dependency
#ifdef Q_OS_MAC
    m_ui->privateKeyFileButton->setText(tr("Choose..."));
#else
    m_ui->privateKeyFileButton->setText(tr("Browse..."));
#endif
    const QString defaultPath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation)
        + QLatin1String("/.ssh/qtc_id");
    setPrivateKeyFile(defaultPath);

    connect(m_ui->rsa, &QRadioButton::toggled,
            this, &SshKeyCreationDialog::keyTypeChanged);
    connect(m_ui->dsa, &QRadioButton::toggled,
            this, &SshKeyCreationDialog::keyTypeChanged);
    connect(m_ui->privateKeyFileButton, &QPushButton::clicked,
            this, &SshKeyCreationDialog::handleBrowseButtonClicked);
    connect(m_ui->generateButton, &QPushButton::clicked,
            this, &SshKeyCreationDialog::generateKeys);
}

SshKeyCreationDialog::~SshKeyCreationDialog()
{
    delete m_keyGenerator;
    delete m_ui;
}

void SshKeyCreationDialog::keyTypeChanged()
{
    m_ui->comboBox->setCurrentIndex(0);
    m_ui->comboBox->setEnabled(m_ui->rsa->isChecked());
}

void SshKeyCreationDialog::generateKeys()
{
    if (userForbidsOverwriting())
        return;

    const SshKeyGenerator::KeyType keyType = m_ui->rsa->isChecked()
        ? SshKeyGenerator::Rsa
        : SshKeyGenerator::Dsa;

    if (!m_keyGenerator)
        m_keyGenerator = new SshKeyGenerator;

    QApplication::setOverrideCursor(Qt::BusyCursor);
    const bool success = m_keyGenerator->generateKeys(keyType, SshKeyGenerator::Mixed,
        m_ui->comboBox->currentText().toUShort());
    QApplication::restoreOverrideCursor();

    if (success)
        saveKeys();
    else
        QMessageBox::critical(this, tr("Key Generation Failed"), m_keyGenerator->error());
}

void SshKeyCreationDialog::handleBrowseButtonClicked()
{
    const QString filePath = QFileDialog::getSaveFileName(this, tr("Choose Private Key File Name"));
    if (!filePath.isEmpty())
        setPrivateKeyFile(filePath);
}

void SshKeyCreationDialog::setPrivateKeyFile(const QString &filePath)
{
    m_ui->privateKeyFileValueLabel->setText(filePath);
    m_ui->generateButton->setEnabled(!privateKeyFilePath().isEmpty());
    m_ui->publicKeyFileLabel->setText(filePath + QLatin1String(".pub"));
}

void SshKeyCreationDialog::saveKeys()
{
    const QString parentDir = QFileInfo(privateKeyFilePath()).dir().path();
    if (!QDir::root().mkpath(parentDir)) {
        QMessageBox::critical(this, tr("Cannot Save Key File"),
            tr("Failed to create directory: \"%1\".").arg(parentDir));
        return;
    }

    QFile privateKeyFile(privateKeyFilePath());
    if (!privateKeyFile.open(QIODevice::WriteOnly)
            || !privateKeyFile.write(m_keyGenerator->privateKey())) {
        QMessageBox::critical(this, tr("Cannot Save Private Key File"),
            tr("The private key file could not be saved: %1").arg(privateKeyFile.errorString()));
        return;
    }
    QFile::setPermissions(privateKeyFilePath(), QFile::ReadOwner | QFile::WriteOwner);

    QFile publicKeyFile(publicKeyFilePath());
    if (!publicKeyFile.open(QIODevice::WriteOnly)
            || !publicKeyFile.write(m_keyGenerator->publicKey())) {
        QMessageBox::critical(this, tr("Cannot Save Public Key File"),
            tr("The public key file could not be saved: %1").arg(publicKeyFile.errorString()));
        return;
    }

    accept();
}

bool SshKeyCreationDialog::userForbidsOverwriting()
{
    if (!QFileInfo::exists(privateKeyFilePath()) && !QFileInfo::exists(publicKeyFilePath()))
        return false;
    const QMessageBox::StandardButton reply = QMessageBox::question(this, tr("File Exists"),
            tr("There already is a file of that name. Do you want to overwrite it?"),
            QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    return reply != QMessageBox::Yes;
}

QString SshKeyCreationDialog::privateKeyFilePath() const
{
    return m_ui->privateKeyFileValueLabel->text();
}

QString SshKeyCreationDialog::publicKeyFilePath() const
{
    return m_ui->publicKeyFileLabel->text();
}

} // namespace QSsh