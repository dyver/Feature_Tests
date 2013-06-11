#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow),
        localAddress("192.168.10.254"),
        remoteAddress("192.168.10.100")
    //    localAddress("10.255.255.255"),
    //    remoteAddress("10.255.255.255")
    //    localAddress("255.255.255.255"),
    //    remoteAddress("255.255.255.255")
{
    ui->setupUi(this);

    ui->chSender->setChecked(true);
    connect(&socket, SIGNAL(readyRead()), this, SLOT(receiveMessage()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setSender(bool state)
{
    if (isSender == state) return;
    isSender = state;
    configureSocket();
}

void MainWindow::configureSocket()
{
    socket.close();
    socket.bind(isSender ? localAddress : remoteAddress,
            isSender ? localPort : remotePort,
            QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
}

void MainWindow::sendMessage()
{
    static int messageCounter = 0;
    QString message;
    message = QString(isSender ? "Sender" : "Receiver")
            + tr(" Message %1").arg(messageCounter++);
    QByteArray datagram(message.toLatin1());
    socket.writeDatagram(datagram,
            isSender ? remoteAddress : localAddress,
            isSender ? remotePort : localPort);
}

void MainWindow::receiveMessage()
{
    while (socket.hasPendingDatagrams()) {
        QHostAddress senderIp;
        quint16 senderPort;
        QByteArray datagram;
        datagram.resize(socket.pendingDatagramSize());
        if (socket.readDatagram(datagram.data(), datagram.size(),
                &senderIp, &senderPort) == -1)
            continue;

        QString str(datagram);
        ui->txtMessage->setText(str);
    }
}

void MainWindow::on_btnSend_clicked()
{
    sendMessage();
}

void MainWindow::updateAddresses()
{
    QList<QHostAddress> ipAddresses;
    ipAddresses.clear();
    //foreach (QNetworkInterface interface, QNetworkInterface::allInterfaces()) {
    for (const auto &interface : QNetworkInterface::allInterfaces()) {
        foreach (QNetworkAddressEntry entry, interface.addressEntries()) {
            QHostAddress broadcastAddress = entry.broadcast();
            if (broadcastAddress != QHostAddress::Null
                    && entry.ip() != QHostAddress::LocalHost) {
                ipAddresses << broadcastAddress;//entry.ip();
            }
        }
    }
}
