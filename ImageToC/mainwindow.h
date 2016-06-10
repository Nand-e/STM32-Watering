#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent * event );



private slots:
    void on_actionLoad_Image_triggered();

    void on_actionConvert_triggered();

    void on_toolButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QPixmap * image;

};

#endif // MAINWINDOW_H
