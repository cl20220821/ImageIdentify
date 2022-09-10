#include "mainwindow.h"
#include "ui_mainwindow.h"

const QString baiduTokenUrl = "https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id=%1&client_secret=%2&";
const char *client_id = "fBPY6dr96VmN91Oe9tz8Leeg";
const char *secret_id = "r3uRbGt1UpGp6CZ2ZsQMispEYNAM1TTy";
const QString baiduImageUrl = "https://aip.baidubce.com/rest/2.0/image-classify/v1/animal?access_token=%1";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->action, &QAction::triggered, this, &MainWindow::openImageSlot);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openImageSlot()
{
    imgPath = QFileDialog::getOpenFileName(this, "选择图片", QCoreApplication::applicationFilePath());
    if (imgPath.isEmpty())
    {
        QMessageBox::warning(this, "提示", "选择一张图片");
    }

    QPixmap pix(imgPath);
    ui->label->setPixmap(pix);
}


void MainWindow::on_pushButton_clicked()
{
    QByteArray img = Image::imageToBase64(imgPath);    //image=xxxxxxx
    QByteArray imgData = "image=" + img;               //body

    //获取access_token
    QByteArray replyData;                 //保存回复信息

    QString url = QString(baiduTokenUrl).arg(client_id).arg(secret_id);

    QMap<QString, QString> header;        //封装头部信息
    header.insert(QString("Content-Type"), QString("application/x-www-form-urlencoded"));

    QString accessToken;

    bool result = Http::post_sync(url, header, imgData, replyData);
    if (result)
    {
        QJsonObject obj = QJsonDocument::fromJson(replyData).object();
        accessToken = obj.value("access_token").toString();
    }

    replyData.clear();
    QString imgUrl = baiduImageUrl.arg(accessToken);
    result = Http::post_sync(imgUrl, header, imgData, replyData);
    if (result)
    {
        QJsonObject obj = QJsonDocument::fromJson(replyData).object();
        QJsonValue val = obj.value("result");
        if (val.isArray())
        {
            QJsonValue first = val.toArray().at(0);
            if (first.isObject())
            {
                QString name = first.toObject().value("name").toString();
                ui->lineEdit->setText(name);
                return;
            }
        }
    }

    ui->lineEdit->setText("unkown");
}
