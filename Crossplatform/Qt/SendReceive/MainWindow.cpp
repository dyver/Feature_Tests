#include <MainWindow.h>
#include <ui_MainWindow.h>

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    localAddress(QHostAddress::LocalHost),
    remoteAddress(QHostAddress::LocalHost)
{
    ui->setupUi(this);
    ui->chSender->setChecked(true);
    connect(
        &socket, &QAbstractSocket::readyRead,
        this, &MainWindow::receiveMessage
    );
    updateAddresses();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setSender(bool state) {
    if (isSender == state) return;
    isSender = state;
    configureSocket();
}

void MainWindow::configureSocket() {
    socket.close();
    if (not socket.bind(
        isSender ? localAddress : remoteAddress,
        isSender ? localPort : remotePort,
        QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint
    )) {
        qCritical() << "Can't bind";
    }
}

void MainWindow::sendMessage() {
    static int messageCounter = 0;
    QString message;
    message = QString(isSender ? "Sender" : "Receiver")
        + tr(" Message #%1:\n").arg(messageCounter++)
        + ui->txtMessage->toPlainText();
    QByteArray datagram(message.toLatin1());
    socket.writeDatagram(
        datagram,
        isSender ? remoteAddress : localAddress,
        isSender ? remotePort : localPort
    );
}

void MainWindow::receiveMessage() {
    while (socket.hasPendingDatagrams()) {
        QHostAddress senderIp;
        quint16 senderPort;
        QByteArray datagram;
        datagram.resize(socket.pendingDatagramSize());
        if (socket.readDatagram(datagram.data(), datagram.size(), &senderIp, &senderPort) == -1) {
            continue;
        }
        QString str(datagram);
        ui->txtMessage->setText(str);
    }
}

void MainWindow::on_btnSend_clicked() {
    sendMessage();
}

void MainWindow::updateAddresses() {
    QList<QHostAddress> ipAddresses;
    ipAddresses.clear();
    for (const auto& interface : QNetworkInterface::allInterfaces()) {
        for (const auto& entry : interface.addressEntries()) {
            QHostAddress broadcastAddress = entry.broadcast();
            if (broadcastAddress != QHostAddress::Null
                && entry.ip() != QHostAddress::LocalHost)
            {
                ipAddresses << broadcastAddress;
            }
        }
    }
    qDebug() << "List of broadcasts:";
    for (const auto& address : ipAddresses) {
        qDebug() << address;
    }
}
