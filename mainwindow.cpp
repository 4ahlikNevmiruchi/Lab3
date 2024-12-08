#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCryptographicHash>
#include <openssl/sha.h>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Connect buttons to slots
    connect(ui->btnStore, &QPushButton::clicked, this, &MainWindow::storePassword);
    connect(ui->btnRetrieve, &QPushButton::clicked, this, &MainWindow::retrievePassword);

    // Initialize SQLite database
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("password_manager.db");

    if (!db.open()) {
        showError("Failed to open database.");
    } else {
        QSqlQuery query;
        query.exec("CREATE TABLE IF NOT EXISTS passwords ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "account TEXT UNIQUE, "
                   "encrypted_password TEXT)");
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::storePassword() {
    QString account = ui->accountLineEdit->text().trimmed();
    QString password = ui->passwordLineEdit->text();

    if (account.isEmpty() || password.isEmpty()) {
        showError("Account and password fields cannot be empty!");
        return;
    }

    QString hashedPassword = hashPassword(password);

    QSqlQuery query;
    query.prepare("INSERT OR REPLACE INTO passwords (account, encrypted_password) VALUES (:account, :password)");
    query.bindValue(":account", account);
    query.bindValue(":password", hashedPassword);

    if (!query.exec()) {
        showError("Failed to store password: " + query.lastError().text());
        return;
    }

    showSuccess("Password stored successfully!");
}

void MainWindow::retrievePassword() {
    QString account = ui->accountLineEdit->text().trimmed();

    if (account.isEmpty()) {
        showError("Account field cannot be empty!");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT encrypted_password FROM passwords WHERE account = :account");
    query.bindValue(":account", account);

    if (!query.exec() || !query.next()) {
        showError("Account not found!");
        return;
    }

    QString hashedPassword = query.value(0).toString();
    showSuccess("Password for account '" + account + "': " + hashedPassword);
}

QString MainWindow::hashPassword(const QString &password) {
    // Hash using OpenSSL's SHA-256
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char *>(password.toUtf8().data()), password.length(), hash);

    QString hashedPassword;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        hashedPassword.append(QString::asprintf("%02x", hash[i]));
    }

    return hashedPassword;
}

void MainWindow::showError(const QString &message) {
    ui->lbMessage->setStyleSheet("QLabel { color: red; }");
    ui->lbMessage->setText(message);
}

void MainWindow::showSuccess(const QString &message) {
    ui->lbMessage->setStyleSheet("QLabel { color: green; }");
    ui->lbMessage->setText(message);
}

