#include <QtWidgets>

class Thread : public QThread
{
    public:
        Thread(QSlider* s) { slider = s; }
    protected:
        void run() {
            for (int i = 0; i <= 10; ++i) {
                slider->setValue(i);
                msleep(200);
            }
        }
    private:
        QSlider* slider;
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget* window = new QWidget;
    window->setWindowTitle("QThread");
    QSlider* slider = new QSlider(Qt::Horizontal);
    slider->setRange(0, 10);
    slider->setValue(5);
    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(slider);
    window->setLayout(layout);
    window->show();
    Thread th(slider);
    th.start();
    return app.exec();
}
