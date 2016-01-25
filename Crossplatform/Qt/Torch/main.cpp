#include <thread>
#include <condition_variable>
#include <chrono>
#include <list>

#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QLayout>
#include <QPixmap>
#include <QCamera>
#include <QCameraInfo>
#include <QCameraExposure>
#include <QDebug>

using namespace std;
using namespace chrono;

static list<QPushButton*> buttons;

template<typename Action> auto makeButton(const QString image, Action action) -> QPushButton* {
    auto button = new QPushButton;
    buttons.push_back(button);
    button->setCheckable(true);
    auto setCheckedButtonStyle = [=] {
        button->setStyleSheet(
            "background-color: green;"
            "image: url(:/images/" + image + ");"
            "border: none;"
            "height: 96px;"
            "min-width: 96px;"
        );
    };
    auto setUncheckedButtonStyle = [=] {
        button->setStyleSheet(
            "background-color: white;"
            "image: url(:/images/" + image +");"
            "border: none;"
            "height: 96px;"
            "min-width: 96px;"
        );
    };
    button->setChecked(true);
    QObject::connect(
        button, &QPushButton::toggled,
        [=](bool on) {
            if (on) {
                for (auto* item : buttons) {
                    if (item != button) item->setChecked(false);
                }
                action(true);
                setCheckedButtonStyle();
            } else {
                action(false);
                setUncheckedButtonStyle();
            }
        }
    );
    button->setChecked(false);
    /*
    QObject::connect(
        button, &QPushButton::pressed,
        [=] {
            button->setStyleSheet(
                "background-color: white;"
                "image: url(:/images/ok.png);"
                "border: none;"
                "height: 84px;"
           );
        }
    );
    */
    return button;
}

int main(int argc, char* argv[]) {
    QApplication application(argc, argv);

    auto camera = new QCamera(QCamera::BackFace);
    camera->load();

    auto onLight = [&] { camera->exposure()->setFlashMode(QCameraExposure::FlashVideoLight); };
    auto offLight = [&] { camera->exposure()->setFlashMode(QCameraExposure::FlashOff); };
    auto blink = [&] { onLight(); offLight(); };

    auto toggleLightButton = makeButton(
        "ok.svg",
        [&](bool on) { if (on) onLight(); else offLight(); }
    );

    condition_variable condition;
    auto stroboscope = [&] {
        mutex m;
        while (true) {
            unique_lock<mutex> locker{m};
            for (int i = 0; i < 3; ++i) {
                blink();
                if (condition.wait_for(locker, milliseconds{100}) == cv_status::no_timeout) return;
            }
            if (condition.wait_for(locker, milliseconds{1000}) == cv_status::no_timeout) return;
        }
    };
    thread* stroboscopeThread = nullptr;
    auto toggleStroboscopeButton = makeButton(
        "cool.svg",
        [&](bool on) {
            if (on) {
                stroboscopeThread = new thread{stroboscope};
            } else {
                if (not stroboscopeThread) return;
                condition.notify_one();
                stroboscopeThread->join();
                delete stroboscopeThread;
            }
        }
    );

    auto closeButton = new QPushButton{"Закрыть"};
    QObject::connect(closeButton, &QPushButton::clicked, &application, &QApplication::exit);

    auto layout = new QVBoxLayout;
    layout->addWidget(toggleLightButton);
    layout->addWidget(toggleStroboscopeButton);
    layout->addStretch();
    layout->addWidget(closeButton);
    closeButton->setDefault(true);

    auto window = new QWidget;
    window->setWindowTitle("Torch!");
    window->setWindowIcon(QIcon(":/images/icon.png"));
    window->setLayout(layout);
    window->show();
    return application.exec();
}
