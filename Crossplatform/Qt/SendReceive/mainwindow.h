#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QHostAddress>
#include <QtNetwork/QNetworkInterface>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    static const int localPort = 5556;
    static const int remotePort = 5555;

    bool isSender;
    QUdpSocket socket;
    QHostAddress localAddress;
    QHostAddress remoteAddress;

    void configureSocket();
    void sendMessage();
    void updateAddresses();

    void setRemoteAddress(const QHostAddress &address) {
        remoteAddress = address;
    }
    void setLocalAddress(const QHostAddress &address) {
        localAddress = address;
    }

private slots:
    void setSender(bool);
    void receiveMessage();
    void on_btnSend_clicked();
};

#endif // MAINWINDOW_H
