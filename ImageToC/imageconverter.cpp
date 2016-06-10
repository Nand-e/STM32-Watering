#include "imageconverter.h"

#include <iostream>
#include <iomanip>

#include <QImage>
#include <QRgb>

#include <sstream>
#include <string>

using namespace std;

ImageConverter::ImageConverter ( QImage * image1, QString & fname) :
    filename (fname) , image( image1)
{


}

void ImageConverter::convert(QPlainTextEdit * textEdit , QString &name) {
    int w = image->width();
    int h = image->height();
    short outpixel;
    QRgb pixel;

    std::stringstream ss;
    ss.str ("");
    ss << "#define " << name.toStdString() << "_W " << image->width() << " \n";
    ss << "#define " << name.toStdString() << "_H " << image->height() << " \n";
    ss << "  [] PROGMEM = { \n";
    textEdit->appendPlainText(QString::fromStdString( ss.str()));

    for ( int y=0; y < h; y++ ) {

        for ( int x=0; x < w; x++ ) {
            pixel = image->pixel(x,y );
            //swap
            // pixel = (( pixel & 0x000000ff ) << 16 ) | (( pixel & 0x00ff0000) >> 16 ) | ( pixel & 0x0000ff00 );

            outpixel = (( pixel >> 3) &0x0000001f ) |
                       (( pixel >> 2) &0x00003f00 ) >> 3  |
                       (( pixel >> 3) &0x001f0000 ) >> 5;

            ss.str ("");
            ss << "0x" <<  setbase(16) << setfill('0') << setw(4) << outpixel;

          //  cout << "0x" <<  setbase(16) << outpixel;
            if ( x != w-1 ){  //cout << ",";
                ss << ',';
            }
            textEdit->insertPlainText(QString::fromStdString( ss.str()));

        }
        ss.str("");
        if ( y != h-1 ) ss << ",";
            ss << "/* line " << setbase( 10 ) << setw(2) << y+1 << "*/" << endl;
            textEdit->insertPlainText(QString::fromStdString( ss.str()));
    }
    ss.str("};");
    textEdit->appendPlainText(QString::fromStdString( ss.str()));
   // cout << "};"  << endl;


}


