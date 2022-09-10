#include "image.h"

Image::Image()
{

}

QByteArray Image::imageToBase64(QString imgPath)
{
    QImage img(imgPath);
    QByteArray ba;
    QBuffer buf(&ba);                   //用QByteArray构造QBuffer
    buf.open(QIODevice::WriteOnly);
    img.save(&buf, "JPG");              //把img写入QBuffer
    QByteArray base64 = ba.toBase64();  //对图片做base64编码(不包含编码头)

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    //对图片urlencode
    QByteArray imgData = codec->fromUnicode(base64).toPercentEncoding();

    return imgData;
}
