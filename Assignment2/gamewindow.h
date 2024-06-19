#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>

namespace Ui {
class GameWindow;
}

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

private slots:
    void on_GameWindow_customContextMenuRequested(const QPoint &pos);

private:
    Ui::GameWindow *ui;
};

#endif // GAMEWINDOW_H
