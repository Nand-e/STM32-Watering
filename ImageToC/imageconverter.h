#ifndef IMAGECONVERTER_H
#define IMAGECONVERTER_H

#include <QString>
#include <QPlainTextEdit>

class QImage;

class ImageConverter
{
public:
    ImageConverter( QImage * image1, QString & filename  );

    void convert( QPlainTextEdit * textEdit, QString & name );

    QString filename;
    QImage * image;
};

#endif // IMAGECONVERTER_H
