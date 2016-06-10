#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QPainter>
#include <QFileDialog>
#include <QDebug>
#include <QString>

#include "imageconverter.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    image (0)
{
    ui->setupUi(this);
    connect( ui->toolButton, SIGNAL(clicked()),ui->plainTextEdit, SLOT(clear()));
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent * event ) {
   /* QPainter painter(this);
    if ( image !=0 ) {
        painter.drawPixmap ( 20,40, image->width(), image->height(), *image );
    }*/
}

void MainWindow::on_actionLoad_Image_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                              tr("Load Image"), "", tr(" (*.bmp),(*.png)"));

    if ( fileName.isNull() ) return;
    if ( image != 0 ) {
        delete image;
    }

    image = new QPixmap (fileName);
    if ( image != 0) ui->label->setPixmap( *image );


}

void MainWindow::on_actionConvert_triggered()
{
    if ( image == 0 ) { qDebug() << "File not oppened file!"; }
    else {
       // qDebug() << " Filed oppened!";
        ImageConverter conv ( & image->toImage(), QString ( "Valam.txt")  );
        conv.convert ( ui->plainTextEdit, QString( "name" ));

        QImage image2 = image->toImage();
        ui->label_2->setPixmap(  QPixmap::fromImage(image2.convertToFormat(QImage::Format_RGB16)));
    }
}

void MainWindow::on_toolButton_2_clicked()
{
    ui->plainTextEdit->selectAll();
    ui->plainTextEdit->copy();

}
