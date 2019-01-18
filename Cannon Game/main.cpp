#include <QApplication>

#include "gameboard.h"
#include "dialog.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    GameBoard board;
    Dialog d;

    board.setGeometry(220, 190, 800, 250);

    board.show();
    d.show();

    return app.exec();
}
