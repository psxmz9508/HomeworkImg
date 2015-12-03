#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define MAX_PAGES 5
#define WIDTH 960
#define HEIGHT 700
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QFileDialog>
#include <QImage>
#include <QPixmap>
#include <QColor>
#include <QPainter>
#include <QPen>
#include <math.h>


class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
private:

    //主界面
    QWidget *pages[MAX_PAGES];
    int currentPage;
    QSlider *pageSlider;
    QLabel *pageLabel;
    QLabel *bitChartLabel[8];
    QImage *bitImage[8];

    //地址栏
    QLineEdit *addressLineEdit;
    QPushButton *addressButtton;
    QString fileAddress;

    //原始图片标签
    QLabel *mainLabel;
    QImage *image;//原始图片
    int imageWidth;
    int imageHeight;

    //采样量化标签

    QLabel *sqLabel;
    QSlider *samplingSlider;
    QSlider *quantizationSlider;

    QLabel *samplingLabel;
    QLabel *quantizationLabel;

    QPushButton *saveButton;

    QImage *image0;//改变采样率和量化率的图片
    int imageColor[3][100000];

    //直方图
    void drawHistogram();
    void drawHistogram1();//均衡化直方图
    void changeimg(QImage*,int,int);
    int oralx;
    int oraly;
    int xmax;
    int ymax;
    QImage *paintimg;
    QSlider *switchHis;
//    int tempcolor[3][100000];

    //二值化标签
    QLabel *binarizationLabel;
    QSlider *thresholdSlider;
    QLabel *thresholdLabel;
    QImage *image1;//二值化图片

    //线性运算
    QLabel *linetransLabel;
    QSlider *lineSlider;
    QLabel *lineLabel;
    QImage *lineimg;

    //非线性运算
    QLabel *unlinetransLabel;
    QSlider *unlineSlider;
    QLabel *unlineLabel;
    QImage *unlineimg;

    //几何运算
    QImage *moveimg;
    QImage *scaleimg;
    QImage *circleimg;
    QLabel *moveLabel;
    QLineEdit *movex;
    QLineEdit *movey;
    QLabel *scaleLabel;
    QLineEdit *scale;
    QLabel *circleLabel;
    QLineEdit *circle;
    QPushButton *domove;
    QPushButton *doscale;
    QPushButton *docircle;
    QPushButton *deleteall;
    void clearall();

    int xmove;
    int ymove;
    int kscale;
    int degree;


    void resetcolor();
private slots:
    void addressButttonSlot();
    void samplingSlot(int);
    void quantizationSlot(int);
    void saveButtonSlot();
    void thresholdSliderSlot(int);
    void pageSliderSlot(int);
    void lineSliderSlot(int);
    void unlineSliderSlot(int);
//    void switchHisSlot(int);
    void domoveSlot();
    void doscaleSlot();
    void docircleSlot();
    void deleteallSlot();
signals:

public slots:
};

#endif // MAINWINDOW_H
