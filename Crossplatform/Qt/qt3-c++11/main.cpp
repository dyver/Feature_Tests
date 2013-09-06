#include <qslider.h>
#include <qlcdnumber.h>
#include <qapplication.h>
#include <qpushbutton.h>
#include <qfont.h>
#include <qvbox.h>
#include <qgrid.h>

#include "main.h"

LCDRange::LCDRange( QWidget *parent, const char *name )
        : QVBox( parent, name )
{
    QLCDNumber *lcd  = new QLCDNumber( 2, this, "lcd"  );
    slider = new QSlider( Horizontal, this, "slider" );
    slider->setRange( 0, 99 );
    slider->setValue( 0 );
    connect( slider, SIGNAL(valueChanged(int)),
             lcd, SLOT(display(int)) );
    connect( slider, SIGNAL(valueChanged(int)),
             SIGNAL(valueChanged(int)) );
}

int LCDRange::value() const
{
    return slider->value();
}

void LCDRange::setValue( int value )
{
    slider->setValue( value );
}

class MyWidget : public QVBox
{
public:
    MyWidget( QWidget *parent=0, const char *name=0 );
};


MyWidget::MyWidget( QWidget *parent, const char *name )
        : QVBox( parent, name )
{
    QPushButton *quit = new QPushButton( "Quit", this, "quit" );
    quit->setFont( QFont( "Times", 18, QFont::Bold ) );

    connect( quit, SIGNAL(clicked()), qApp, SLOT(quit()) );

    QGrid *grid = new QGrid( 4, this );

    LCDRange *previous = 0;
    for( int r = 0 ; r < 4 ; r++ ) {
        for( int c = 0 ; c < 4 ; c++ ) {
            LCDRange* lr = new LCDRange( grid );
            if ( previous )
                connect( lr, SIGNAL(valueChanged(int)),
                         previous, SLOT(setValue(int)) );
            previous = lr;
        }
    }
}


int main( int argc, char **argv )
{
    QApplication a( argc, argv );

    MyWidget w;
    a.setMainWidget( &w );
    w.show();
    return a.exec();
}
