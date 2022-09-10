#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include "Image.h"
#include "http.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <Qdebug>
#include <QJsonArray>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void openImageSlot();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QString imgPath;
};

#endif // MAINWINDOW_H
