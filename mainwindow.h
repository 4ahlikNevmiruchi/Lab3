#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void storePassword(); // Slot for btnStore
    void retrievePassword(); // Slot for btnRetrieve

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;

    // Helper functions
    QString hashPassword(const QString &password); // Hash password using OpenSSL
    void showError(const QString &message); // Display error in lbMessage
    void showSuccess(const QString &message); // Display success in lbMessage
};

#endif // MAINWINDOW_H
