#ifndef IMAGE_H
#define IMAGE_H

#include <QString>
#include <QImage>
#include <QBuffer>
#include <QTextCodec>
#include <QByteArray>

class Image
{
public:
    Image();
    static QByteArray imageToBase64(QString imgPath);

};

#endif // IMAGE_H
