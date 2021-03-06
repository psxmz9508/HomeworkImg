#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    //主布局
    this->setFixedSize(WIDTH,HEIGHT);

    for(int i=0;i<MAX_PAGES;i++)
    {
        pages[i] = new QWidget(this);
        pages[i]->hide();
    }


    //八幅二值图
    for(int i=0;i<8;i++)
    {
        bitChartLabel[i] = new QLabel(pages[1]);
        bitChartLabel[i]->setScaledContents(true);

    }
    bitChartLabel[0]->setGeometry(330,70,120,120);
    bitChartLabel[1]->setGeometry(460,70,120,120);
    bitChartLabel[2]->setGeometry(590,70,120,120);
    bitChartLabel[3]->setGeometry(720,70,120,120);
    bitChartLabel[4]->setGeometry(330,200,120,120);
    bitChartLabel[5]->setGeometry(460,200,120,120);
    bitChartLabel[6]->setGeometry(590,200,120,120);
    bitChartLabel[7]->setGeometry(720,200,120,120);

    //页面转换相关
    currentPage = 0;
    pageSlider = new QSlider(Qt::Horizontal,this);
    pageSlider->setRange(0,MAX_PAGES-1);
    pageSlider->setGeometry(90,10,50,28);
    pageLabel = new QLabel(tr("页面转换："),this);
    pageLabel->setGeometry(20,10,70,28);

    //地址栏
    addressLineEdit = new QLineEdit("请打开图片",this);
    addressButtton = new QPushButton("打开",this);
    addressLineEdit->setGeometry(320,10,300,25);
    addressButtton->setGeometry(620,10,60,28);

    //原始图片
    mainLabel = new QLabel(this);
    mainLabel->setGeometry(20,50,300,300);
    mainLabel->setScaledContents(true);

    image = new QImage();

    //采样率
    sqLabel = new QLabel(pages[0]);
    sqLabel->setScaledContents(true);
    sqLabel->setGeometry(330,50,300,300);
    samplingSlider = new QSlider(pages[0]);
    samplingSlider->setRange(1,128);
    samplingLabel = new QLabel("采样率",pages[0]);
    samplingLabel->setGeometry(732,50,35,20);
    samplingSlider->setGeometry(742,80,20,200);
    //量化率
    quantizationLabel = new QLabel("量化率",pages[0]);
    quantizationSlider = new QSlider(pages[0]);
    quantizationSlider->setRange(1,32);
    saveButton = new QPushButton("保存",pages[0]);
    quantizationLabel->setGeometry(780,50,35,20);
    quantizationSlider->setGeometry(790,80,20,200);
    saveButton->setGeometry(680,10,60,30);
    image0 = new QImage();

    //二值化标签
    binarizationLabel = new QLabel(pages[0]);
    binarizationLabel->setGeometry(330,360,300,300);
    binarizationLabel->setScaledContents(true);
    thresholdLabel = new QLabel("阈值",pages[0]);
    thresholdSlider = new QSlider(pages[0]);
    thresholdSlider->setRange(0,255);
    thresholdLabel->setGeometry(765,600,50,30);
    thresholdSlider->setGeometry(765,380,20,200);
    image1 = new QImage();


    //线性变换
    lineLabel = new QLabel(pages[2]);
    lineLabel->setScaledContents(true);
    lineLabel->setGeometry(330,50,300,300);
    lineSlider= new QSlider(pages[2]);
    lineSlider->setRange(1,4);
    linetransLabel = new QLabel("线性",pages[2]);
    linetransLabel->setGeometry(650,400,35,20);
    lineSlider->setGeometry(650,420,20,200);

    //线性变换
    unlineLabel = new QLabel(pages[2]);
    unlineLabel->setScaledContents(true);
    unlineLabel->setGeometry(640,50,300,300);
    unlineSlider= new QSlider(pages[2]);
    unlineSlider->setRange(1,3);
    unlinetransLabel = new QLabel("非线性",pages[2]);
    unlinetransLabel->setGeometry(700,400,35,20);
    unlineSlider->setGeometry(700,420,20,200);
    
    //几何变换
    moveLabel = new QLabel(pages[3]);
    moveLabel->setScaledContents(true);
    movex = new QLineEdit("横向",pages[3]);
    movey = new QLineEdit("纵向",pages[3]);
    scaleLabel = new QLabel(pages[3]);
    scaleLabel->setScaledContents(true);
    xscale = new QLineEdit("x缩放",pages[3]);
    yscale = new QLineEdit("y缩放",pages[3]);
    circleLabel = new QLabel(pages[3]);
    circleLabel->setScaledContents(true);
    circle = new QLineEdit("旋转角度",pages[3]);
    domove = new QPushButton("平移",pages[3]);
    doscale = new QPushButton("缩放",pages[3]);
    docircle = new QPushButton("旋转",pages[3]);
    deleteall = new QPushButton("清空",pages[3]);
    moveimg = new QImage();
    scaleimg = new QImage();
    circleimg = new QImage();
    moveLabel->setGeometry(330,50,300,300);
    scaleLabel->setGeometry(20,360,300,300);
    circleLabel->setGeometry(330,360,300,300);

    domove->setGeometry(640,50,50,30);
    doscale->setGeometry(640,90,50,30);
    docircle->setGeometry(640,130,50,30);

    movex->setGeometry(690,55,50,20);
    movey->setGeometry(740,55,50,20);
    xscale->setGeometry(690,95,60,20);
    yscale->setGeometry(750,95,60,20);
    circle->setGeometry(690,135,60,20);
    deleteall->setGeometry(640,170,50,30);


    //平滑 锐化

    midsmooth = new QPushButton("中值平滑",pages[4]);
    midsmooth->setGeometry(640,50,100,20);
    ksmooth = new QPushButton("K均值平滑",pages[4]);
    ksmooth->setGeometry(640,70,100,20);
    avesmooth = new QPushButton("超限像素平滑",pages[4]);
    avesmooth->setGeometry(640,90,100,20);
    smoothimg = new QLabel(pages[4]);
    smoothimg->setScaledContents(true);
    smoothimg->setGeometry(20,360,300,300);

    sobsharpen = new QPushButton("Sobel锐化",pages[4]);
    sobsharpen->setGeometry(740,50,100,20);
    robsharpen = new QPushButton("Roberts锐化",pages[4]);
    robsharpen->setGeometry(740,70,100,20);
    lapsharpen = new QPushButton("拉普拉斯锐化",pages[4]);
    lapsharpen->setGeometry(740,90,100,20);
    sharpenLabel=new QLabel(pages[4]);
    sharpenLabel->setGeometry(330,360,300,300);
    sharpenLabel->setScaledContents(true);


    //开始时在第一页
    pages[0]->show();

    connect(addressButtton,SIGNAL(clicked(bool)),this,SLOT(addressButttonSlot()));
    connect(samplingSlider,SIGNAL(valueChanged(int)),this,SLOT(samplingSlot(int)));
    connect(quantizationSlider,SIGNAL(valueChanged(int)),this,SLOT(quantizationSlot(int)));
    connect(saveButton,SIGNAL(clicked(bool)),this,SLOT(saveButtonSlot()));
    connect(thresholdSlider,SIGNAL(valueChanged(int)),this,SLOT(thresholdSliderSlot(int)));
    connect(pageSlider,SIGNAL(valueChanged(int)),this,SLOT(pageSliderSlot(int)));
    connect(lineSlider,SIGNAL(valueChanged(int)),this,SLOT(lineSliderSlot(int)));
    connect(unlineSlider,SIGNAL(valueChanged(int)),this,SLOT(unlineSliderSlot(int)));
    connect(domove,SIGNAL(clicked(bool)),this,SLOT(domoveSlot()));
    connect(doscale,SIGNAL(clicked(bool)),this,SLOT(doscaleSlot()));
    connect(docircle,SIGNAL(clicked(bool)),this,SLOT(docircleSlot()));
    connect(deleteall,SIGNAL(clicked(bool)),this,SLOT(deleteallSlot()));
//    connect(switchHis,SIGNAL(valueChanged(int)),this,SLOT(switchHisSlot(int)));
    connect(midsmooth,SIGNAL(clicked()),this,SLOT(drawMid()));
    connect(ksmooth,SIGNAL(clicked()),this,SLOT(drawKmean()));
    connect(avesmooth,SIGNAL(clicked()),this,SLOT(drawAverage()));
    connect(sobsharpen,SIGNAL(clicked()),this,SLOT(drawSobel()));
    connect(robsharpen,SIGNAL(clicked()),this,SLOT(drawRoberts()));
    connect(lapsharpen,SIGNAL(clicked()),this,SLOT(drawAplace()));
}

void MainWindow::paintEvent(QPaintEvent *)
{
    if (currentPage==0)
    {
        if(fileAddress==NULL)
        {

        }
        else
        {
            drawHistogram();
        }
    }
    if(currentPage ==2){
        drawHistogram();
        changeimg(paintimg,330,660);
        drawHistogram1();

    }
}



/***************************绘制直方图***************************/
void MainWindow::drawHistogram()
{
    int hist[256];
    for(int i=0;i<256;i++)
    {
        hist[i]=0;
    }
    int temp;

    for(int i=0;i<imageHeight*imageWidth;i++)
    {
        temp = imageColor[0][i];
        hist[temp]++;
    }

    int sum=0;
    for(int i=0;i<256;i++)
    {
       sum+=hist[i]*i;
    }
    int aver = (int)(sum/(imageHeight*imageWidth));
    temp=0;
    int mid;
    int sum1=imageHeight*imageWidth;
    int halfSum = int(sum1*0.5);
    for(int i=0;i<256;i++)
    {
        temp+=hist[i];
        if(temp>=halfSum)
        {
            mid = i;
            break;
        }
    }
    int stdDev;
    int sum0=0;
    for(int i=0;i<256;i++)
    {
        sum0+=hist[i]*(i-aver)*(i-aver);
    }
    stdDev=(int)(sqrt(sum0/sum1));


    int max=0;
    for(int i=0;i<256;i++)
    {
        if(hist[i]>max)
            max=hist[i];
    }
    for(int i=0;i<256;i++)
    {
        hist[i]=(int)((hist[i]/(float)max)*250);
    }

    QPainter painter(this);
    QPen pen;
    pen.setColor(Qt::black);
    painter.setPen(pen);

    painter.drawText(oralx,ymax+20,tr("平均灰度："));
    painter.drawText(oralx+60,ymax+20,tr(QString::number(aver).toLocal8Bit().data()));
    painter.drawText(oralx,ymax+40,tr("中值灰度："));
    painter.drawText(oralx+60,ymax+40,tr(QString::number(mid).toLocal8Bit().data()));
    painter.drawText(oralx,ymax+60,tr("标准差："));
    painter.drawText(oralx+60,ymax+60,tr(QString::number(stdDev).toLocal8Bit().data()));
    painter.drawText(oralx,ymax+80,tr("像素总数："));
    painter.drawText(oralx+60,ymax+80,tr(QString::number(sum1).toLocal8Bit().data()));

    //纵轴
    painter.drawLine(oralx,oraly,oralx,ymax);
    painter.drawLine(oralx,ymax,oralx-5,ymax+5);
    painter.drawLine(oralx,ymax,oralx+5,ymax+5);
    painter.drawText(oralx+3,ymax,tr("像素个数"));

    //横轴
    painter.drawLine(oralx,oraly,xmax,oraly);
    painter.drawLine(xmax,oraly,xmax-5,oraly-5);
    painter.drawLine(xmax,oraly,xmax-5,oraly+5);
    painter.drawText(xmax-10,oraly-3,tr("灰度"));

    for(int i=0;i<256;i++)
    {
        painter.drawLine(oralx+i,oraly,oralx+i,oraly-hist[i]);
        if(i%30==0)
            painter.drawText(oralx+i,oraly+10,tr(QString::number(i).toLocal8Bit().data()));
    }
    painter.end();
}

/***************************绘制均衡化直方图**********************/
void MainWindow::drawHistogram1()
{
    float hist[256];
    float result[256];
    float phist[256];
    float phisttemp[256];
    float eqhist[256];
    for(int i=0;i<256;i++)
    {
        hist[i]=0;
        result[i]=0;
        phist[i]=0;
        phisttemp[i]=0;
        eqhist[i]=0;
    }

    int temp;
    //计算灰度
    for(int i=0;i<imageHeight*imageWidth;i++)
    {
        temp = imageColor[0][i]*imageColor[0][i]/255;
        if(temp>255) temp=255;
        hist[temp]++;
    }

    //归一化
    for(int i=0;i<256;i++){
        phist[i]=hist[i]/(double)(imageHeight*imageWidth);
    }
    for(int i =1;i<256;i++){
        if(i==0)
            phisttemp[i]=phist[i];
        else
            phisttemp[i]=phisttemp[i-1]+phist[i];
    }
    for(int i =1;i<256;i++){
        eqhist[i]=int(255.0*phisttemp[i]+0.5);
    }
    for(int i=0;i<255;i++){
        result[i] = hist[(int)eqhist[i]];
    }

    int sum=0;
    for(int i=0;i<256;i++)
    {
       sum+=result[i]*i;
    }
    int aver = (int)(sum/(imageHeight*imageWidth));
    temp=0;
    int mid;
    int sum1=imageHeight*imageWidth;
    int halfSum = int(sum1*0.5);
    for(int i=0;i<256;i++)
    {
        temp+=result[i];
        if(temp>=halfSum)
        {
            mid = i;
            break;
        }
    }
    int stdDev;
    int sum0=0;
    for(int i=0;i<256;i++)
    {
        sum0+=result[i]*(i-aver)*(i-aver);
    }
    stdDev=(int)(sqrt(sum0/sum1));


    int max=0;
    for(int i=0;i<256;i++)
    {
        if(result[i]>max)
            max=result[i];
    }
    for(int i=0;i<256;i++)
    {
        result[i]=(int)((hist[i]/(float)max)*250);
    }

    QPainter painter(this);
    QPen pen;
    pen.setColor(Qt::black);
    painter.setPen(pen);

    //纵轴
    painter.drawLine(oralx,oraly,oralx,ymax);
    painter.drawLine(oralx,ymax,oralx-5,ymax+5);
    painter.drawLine(oralx,ymax,oralx+5,ymax+5);
    painter.drawText(oralx+3,ymax,tr("像素个数"));

    //横轴
    painter.drawLine(oralx,oraly,xmax,oraly);
    painter.drawLine(xmax,oraly,xmax-5,oraly-5);
    painter.drawLine(xmax,oraly,xmax-5,oraly+5);
    painter.drawText(xmax-10,oraly-3,tr("灰度"));

    for(int i=0;i<256;i++)
    {
        painter.drawLine(oralx+i,oraly,oralx+i,oraly-result[i]);
        if(i%30==0)
            painter.drawText(oralx+i,oraly+10,tr(QString::number(i).toLocal8Bit().data()));
    }
    painter.end();
}
/********************获取图片地址 处理图片数据*********************/
void MainWindow::addressButttonSlot()
{
    fileAddress = QFileDialog::getOpenFileName(this,
                                               tr("打开图片"),
                                               "",
                                               "Image Files(*.jpg *.png)");
    addressLineEdit->setText(fileAddress);
    image->load(fileAddress);

    //读取原始图片数据
    imageWidth = image->width();
    imageHeight = image->height();


    mainLabel->setPixmap(QPixmap::fromImage(*image).scaled(150,150,Qt::KeepAspectRatio, Qt::SmoothTransformation));
    sqLabel->setPixmap(QPixmap::fromImage(*image).scaled(150,150,Qt::KeepAspectRatio, Qt::SmoothTransformation));


    resetcolor(image);

    delete image1;
    image1 = new QImage(imageWidth,imageHeight,QImage::Format_ARGB32);
    for(int i=0;i<imageWidth;i++)
    {
        for(int j=0;j<imageHeight;j++)
        {
            int aver = (imageColor[0][i*imageWidth+j]+
                       imageColor[1][i*imageWidth+j]+
                       imageColor[2][i*imageWidth+j])/3;
            image1->setPixel(i,j,qRgb(aver,
                                      aver,
                                      aver));
        }
    }
    tempimg=image1;
    binarizationLabel->setPixmap(QPixmap::fromImage(*image1));

    for(int i=0;i<8;i++)
    {
        bitImage[i] = new QImage(imageWidth,imageHeight,QImage::Format_ARGB32);
        for(int k=0;k<imageWidth;k++)
        {
            for(int j=0;j<imageHeight;j++)
            {
                int aver = (imageColor[0][k*imageWidth+j]+
                           imageColor[1][k*imageWidth+j]+
                           imageColor[2][k*imageWidth+j])/3;
                aver = aver & int(pow(double(2),double(i))+0.001);
                aver = aver==0?0:255;
                bitImage[i]->setPixel(k,j,qRgb(aver,
                                          aver,
                                          aver));
            }
        }
        bitChartLabel[i]->setPixmap(QPixmap::fromImage(*bitImage[i]));
    }


    changeimg(image,20,660);
    this->update();

}


/***************************采样**************************/
void MainWindow::samplingSlot(int samplingInt)
{
    int d = (int)(256/samplingInt);
    int dd=d*d;

    resetcolor(image);
    for(int i=0;i<imageHeight;i=i+d)
    {
        for(int j=0;j<imageWidth;j=j+d)
        {
            int r=0,g=0,b=0;
            for(int k=0;k<d;k++)
            {
                for(int l=0;l<d;l++)
                {
                    r = r + imageColor[0][(i+k)*imageWidth+(j+l)];
                    g = g + imageColor[1][(i+k)*imageWidth+(j+l)];
                    b = b + imageColor[2][(i+k)*imageWidth+(j+l)];
                }
            }
            r = (int)(r/dd);
            g = (int)(g/dd);
            b = (int)(b/dd);
            for(int k=0;k<d;k++)
            {
                for(int l=0;l<d;l++)
                {
                    imageColor[0][(i+k)*imageWidth+(j+l)]=r;
                    imageColor[1][(i+k)*imageWidth+(j+l)]=g;
                    imageColor[2][(i+k)*imageWidth+(j+l)]=b;

                }
            }
        }
    }
    delete image0;//必须delete掉上次申请的image0，不然随着改变次数的增加，内存越来越大
    image0 = new QImage(imageWidth,imageHeight,QImage::Format_ARGB32);
    for(int i=0;i<imageWidth;i++)
    {
        for(int j=0;j<imageHeight;j++)
            image0->setPixel(i,j,qRgb(imageColor[0][i*imageWidth+j],
                                      imageColor[1][i*imageWidth+j],
                                      imageColor[2][i*imageWidth+j]));
    }
    sqLabel->setPixmap(QPixmap::fromImage(*image0));
    changeimg(image0,20,660);
    this->update();
}


/***************************量化***************************/
void MainWindow::quantizationSlot(int quantizationInt)
{
    resetcolor(image);

    int greyScope = 256/quantizationInt;
    int r,g,b,temp;
    for(int i=0;i<imageHeight*imageWidth;i++)
    {
        r = imageColor[0][i];
        temp = r/greyScope;
        r = temp*greyScope;

        g = imageColor[1][i];
        temp = g/greyScope;
        g = temp*greyScope;

        b = imageColor[2][i];
        temp = b/greyScope;
        b = temp*greyScope;

        imageColor[0][i]=r;
        imageColor[1][i]=g;
        imageColor[2][i]=b;
    }
    delete image0;
    image0 = new QImage(imageWidth,imageHeight,QImage::Format_ARGB32);
    for(int i=0;i<imageWidth;i++)
    {
        for(int j=0;j<imageHeight;j++)
            image0->setPixel(i,j,qRgb(imageColor[0][i*imageWidth+j],
                                      imageColor[1][i*imageWidth+j],
                                      imageColor[2][i*imageWidth+j]));
    }
    sqLabel->setPixmap(QPixmap::fromImage(*image0));
    changeimg(image0,20,660);
    this->update();
}


/***************************保存***************************/
void MainWindow::saveButtonSlot()
{
    QString fileName =QFileDialog::getSaveFileName(this,
                                                   tr("保存图片"),
                                                   "image0.jpg",
                                                   tr("Config Files (*.png *.jpg)")
                                                   );
    if(!fileName.isNull())
    {
        image0->save(fileName);
    }
    else
    {

    };
}


/***************************二值化图片***************************/
void MainWindow::thresholdSliderSlot(int threshold)
{
    resetcolor(image);
    delete image1;
    image1 = new QImage(imageWidth,imageHeight,QImage::Format_ARGB32);
    for(int i=0;i<imageWidth;i++)
    {
        for(int j=0;j<imageHeight;j++)
        {
            int aver = (imageColor[0][i*imageWidth+j]+
                       imageColor[1][i*imageWidth+j]+
                       imageColor[2][i*imageWidth+j])/3;
            if(aver>threshold)
                image1->setPixel(i,j,qRgb(255,255,255));
            else
                image1->setPixel(i,j,qRgb(0,0,0));
        }
    }
    binarizationLabel->setPixmap(QPixmap::fromImage(*image1));
    changeimg(image1,20,660);
    this->update();
}


/***************************线性变化***************************/
void MainWindow::lineSliderSlot(int a)//y=ax+10
{

    lineimg = new QImage(imageWidth,imageHeight,QImage::Format_ARGB32);
    resetcolor(image);
    for(int i=0;i<imageWidth;i++)
    {
        for(int j=0;j<imageHeight;j++)
        {
            int aver = (imageColor[0][i*imageWidth+j]+
                       imageColor[1][i*imageWidth+j]+
                       imageColor[2][i*imageWidth+j])/3;
            switch (a) {
            case 1:
                lineimg->setPixel(i,j,qRgb(0.9*aver,
                                          0.9*aver,
                                          0.9*aver));
                break;
            case 2:
                lineimg->setPixel(i,j,qRgb(0.2*aver,
                                          0.2*aver,
                                          0.2*aver));
                break;
            case 3:
                lineimg->setPixel(i,j,qRgb(-0.2*aver,
                                          -0.2*aver,
                                          -0.2*aver));
                break;
            case 4:
                lineimg->setPixel(i,j,qRgb(-0.9*aver,
                                          -0.9*aver,
                                          -0.9*aver));

                break;
            default:
                break;
            }

        }
    }
    lineLabel->setPixmap(QPixmap::fromImage(*lineimg));
    changeimg(lineimg,20,660);
    this->update();
}

/***************************非线性变化***************************/
void MainWindow::unlineSliderSlot(int a)
{
    resetcolor(image);
    unlineimg = new QImage(imageWidth,imageHeight,QImage::Format_ARGB32);
    for(int i=0;i<imageWidth;i++)
    {
        for(int j=0;j<imageHeight;j++)
        {
            int aver = (imageColor[0][i*imageWidth+j]+
                       imageColor[1][i*imageWidth+j]+
                       imageColor[2][i*imageWidth+j])/3;
            switch (a) {
            case 1:
                //  x*x/255
               unlineimg->setPixel(i,j,qRgb(aver*aver/255,
                                          aver*aver/255,
                                          aver*aver/255));
                break;
            case 2:
                //  x开方+10
                unlineimg->setPixel(i,j,qRgb(sqrt(aver)+10,
                                          sqrt(aver)+10,
                                          sqrt(aver)+10));
                break;
            case 3:
                //  logx
                unlineimg->setPixel(i,j,qRgb(log(aver),
                                          log(aver),
                                          log(aver)));
                break;

            default:
                break;
            }


        }
    }
    unlineLabel->setPixmap(QPixmap::fromImage(*unlineimg));
    changeimg(unlineimg,20,660);
    this->update();
}

/***************************平移***************************/
void MainWindow::domoveSlot(){
    resetcolor(image);
    xmove=movex->text().toInt();
    ymove=movey->text().toInt();
    moveimg = new QImage(imageWidth,imageHeight,QImage::Format_ARGB32);
    for(int x=0;x<imageWidth;x++){
        for(int y=0;y<imageHeight;y++){
            if(x-xmove<0||x-xmove>imageWidth||y-ymove<0||y-ymove>imageHeight)   //超出范围设为黑
                moveimg->setPixel(x,y,qRgb(0,0,0));
            else
                moveimg->setPixel(x,y,image->pixel(x-xmove,y-ymove));
//            moveimg->setPixel(x,y,qRgb(150,150,150));
        }
    }
    moveLabel->setPixmap(QPixmap::fromImage(*moveimg));
    this->update();
}

/***************************缩放***************************/
void MainWindow::doscaleSlot(){
    resetcolor(image);
    scalekx=xscale->text().toDouble();
    scaleky=yscale->text().toDouble();
    scaleimg = new QImage(imageWidth,imageHeight,QImage::Format_ARGB32);
    for(int x=0;x<imageWidth;x++){
        for(int y=0;y<imageHeight;y++){
            if((x/scalekx)<0||(x/scalekx)>imageWidth||(y/scaleky)<0||(y/scaleky)>imageHeight)
                scaleimg->setPixel(x,y,qRgb(0,0,0));
            else
                scaleimg->setPixel(x,y,image->pixel(int(x/scalekx+0.5),int(y/scaleky+0.5)));//最近邻
        }
    }
    scaleLabel->setPixmap(QPixmap::fromImage(*scaleimg));
    this->update();
}


/**************************旋转****************************/
void MainWindow::docircleSlot(){
    resetcolor(image);
    degree=circle->text().toDouble();
    double xo;
    double yo;
    double truedre;
    truedre=(double)(degree*PAI)/180;
    circleimg = new QImage(imageWidth,imageHeight,QImage::Format_ARGB32);
    for(int x=0;x<imageWidth;x++){
        for(int y=0;y<imageHeight;y++){
            xo=x*cos(truedre)+y*sin(truedre);
            yo=-x*sin(truedre)+y*cos(truedre);

            if(xo<0||xo>imageWidth||yo<0||yo>imageHeight)
                circleimg->setPixel(x,y,qRgb(0,0,0));
            else
                circleimg->setPixel(x,y,image->pixel(int(xo+0.5),int(yo+0.5)));
        }
    }
    circleLabel->setPixmap(QPixmap::fromImage(*circleimg));
    this->update();
}


/**************************清空输入信息****************************/
void MainWindow::deleteallSlot(){

}



/***************************页面转换***************************/
void MainWindow::pageSliderSlot(int page)
{
    pages[currentPage]->hide();
    pages[page]->show();
    currentPage = page;

}

/***************************改变直方图所绘制的图像***************************/
void MainWindow::changeimg(QImage *a, int xo, int yo){

    oralx = xo;
    oraly = yo;
    xmax = xo+300;
    ymax = yo-300;
    paintimg = a;
    for(int i=0;i<imageWidth;i++)
    {
        for(int j=0;j<imageHeight;j++)
        {
            imageColor[0][i*imageWidth+j]=QColor(paintimg->pixel(i,j)).red();
            imageColor[1][i*imageWidth+j]=QColor(paintimg->pixel(i,j)).green();
            imageColor[2][i*imageWidth+j]=QColor(paintimg->pixel(i,j)).blue();
        }
    }

}

/**************************获取原图像的像素信息**************************/
void MainWindow::resetcolor(QImage* pic){
    for(int x=0;x<imageWidth;x++)
    {
        for(int y=0;y<imageHeight;y++)
        {
            imageColor[0][x*imageWidth+y]=QColor(pic->pixel(x,y)).red();
            imageColor[1][x*imageWidth+y]=QColor(pic->pixel(x,y)).green();
            imageColor[2][x*imageWidth+y]=QColor(pic->pixel(x,y)).blue();
        }
    }
}



//中值平衡算法
void MainWindow::drawMid()
{
    int midArray[30];
    int temp,gray;

    goalImage=new QImage(imageWidth,imageHeight,QImage::Format_ARGB32);

    for(int i=0;i<imageWidth;i++)
        for(int j=0;j<imageHeight;j++)
        {
            if(i<=1||j<=1||i>=imageHeight-2||j>=imageWidth-2)
            {
                gray=QColor(tempimg->pixel(i,j)).red();
                goalImage->setPixel(i,j,qRgb(gray,gray,gray));
            }
            else
            {
                memset(midArray,0,sizeof(midArray));
                for(int ia=-2;ia<=2;ia++)
                    for(int ja=-2;ja<=2;ja++)
                    {
                        temp=QColor(tempimg->pixel(i+ia,j+ja)).red();
                        //排序求中值
                        for(int k=0;k<25;k++)
                        {
                            if(temp>midArray[k])
                            {
                                //数据后移一位
                                for(int ka=24;ka>k;ka--)
                                {
                                    midArray[ka]=midArray[ka-1];
                                }
                                midArray[k]=temp;
                                break;
                            }

                        }
                    }

                gray=midArray[13];
                goalImage->setPixel(i,j,qRgb(gray,gray,gray));
            }
        }

    smoothimg->setPixmap(QPixmap::fromImage(*goalImage));
}

//K均值平滑
void MainWindow::drawKmean()
{
    int midArray[30];
    int temp,gray;

    goalImage=new QImage(imageWidth,imageHeight,QImage::Format_ARGB32);
    for(int i=0;i<imageWidth;i++)
        for(int j=0;j<imageHeight;j++)
        {
            if(i<=1||j<=1||i>=imageWidth-2||j>=imageHeight-2)
            {
                gray=QColor(tempimg->pixel(i,j)).red();
                goalImage->setPixel(i,j,qRgb(gray,gray,gray));
            }
            else
            {
                memset(midArray,0,sizeof(midArray));
                for(int ia=-2;ia<=2;ia++)
                    for(int ja=-2;ja<=2;ja++)
                    {
                        temp=QColor(tempimg->pixel(i+ia,j+ja)).red();
                        //排序求中值
                        for(int k=0;k<25;k++)
                        {
                            if(temp>midArray[k])
                            {
                                //数据后移一位
                                for(int ka=24;ka>k;ka--)
                                {
                                    midArray[ka]=midArray[ka-1];
                                }
                                midArray[k]=temp;
                                break;
                            }

                        }
                    }

                gray=(midArray[13]+midArray[12]+midArray[11])/3;
                goalImage->setPixel(i,j,qRgb(gray,gray,gray));
            }
        }

    smoothimg->setPixmap(QPixmap::fromImage(*goalImage));
}

//超限均值平滑
void MainWindow::drawAverage()
{
    int midArray[30];
    int temp,gray;

    goalImage=new QImage(imageWidth,imageHeight,QImage::Format_ARGB32);

    for(int i=0;i<imageWidth;i++)
        for(int j=0;j<imageHeight;j++)
        {
            if(i<=1||j<=1||i>=imageWidth-2||j>=imageHeight-2)
            {
                gray=QColor(tempimg->pixel(i,j)).red();
                goalImage->setPixel(i,j,qRgb(gray,gray,gray));
            }
            else
            {
                temp=0;
                memset(midArray,0,sizeof(midArray));
                gray=QColor(tempimg->pixel(i,j)).red();

                //求均值
                for(int ia=-2;ia<=2;ia++)
                    for(int ja=-2;ja<=2;ja++)
                    {
                        temp+=QColor(tempimg->pixel(i+ia,j+ja)).red();
                    }

                //取阈值为48
                temp=temp/25;
                if(fabs(temp-gray)>48)
                    gray=temp;

                goalImage->setPixel(i,j,qRgb(gray,gray,gray));
            }
        }

    smoothimg->setPixmap(QPixmap::fromImage(*goalImage));
}

//Roberts锐化
void MainWindow::drawRoberts()
{
    int temp,gray;

    goalImage=new QImage(imageWidth,imageHeight,QImage::Format_ARGB32);

    for(int i=0;i<imageWidth;i++)
        for(int j=0;j<imageHeight;j++)
        {
            if(i>imageWidth-2||j>imageHeight-2)
            {
                gray=QColor(tempimg->pixel(i,j)).red();
                goalImage->setPixel(i,j,qRgb(gray,gray,gray));
            }
            else
            {
                //找出最大梯度
                temp=fabs(QColor(tempimg->pixel(i,j)).red()
                          -QColor(tempimg->pixel(i+1,j+1)).red());
                if(temp<fabs(QColor(tempimg->pixel(i+1,j)).red()
                             -QColor(tempimg->pixel(i,j+1)).red()))
                    temp=fabs(QColor(tempimg->pixel(i+1,j)).red()
                              -QColor(tempimg->pixel(i,j+1)).red());

                if(temp>24)
                    gray=temp;
                else
                    gray=128;
                goalImage->setPixel(i,j,qRgb(gray,gray,gray));
            }
        }

    sharpenLabel->setPixmap(QPixmap::fromImage(*goalImage));
}

//拉普拉斯锐化
void MainWindow::drawAplace()
{
    int gray;
    double aplArray[5][5]={{0,-1,0},{-1,4,-1},{0,-1,0}};

    goalImage=new QImage(imageWidth,imageHeight,QImage::Format_ARGB32);

    for(int i=0;i<imageWidth;i++)
        for(int j=0;j<imageHeight;j++)
        {
            gray=convolution(aplArray,i,j,3,3)+128;
            if(gray>255)
                gray=255;
            else if(gray<0)
                gray=0;
            goalImage->setPixel(i,j,qRgb(gray,gray,gray));
        }

    sharpenLabel->setPixmap(QPixmap::fromImage(*goalImage));
}

//Sobel锐化
void MainWindow::drawSobel()
{
    int gray;
    int dx,dy;
    double sobXArray[5][5]={{1,0,-1},{2,0,-2},{1,0,-1}};
    double sobYArray[5][5]={{-1,-2,-1},{0,0,0},{1,2,1}};

    goalImage=new QImage(imageWidth,imageHeight,QImage::Format_ARGB32);

    for(int i=0;i<imageWidth;i++)
        for(int j=0;j<imageHeight;j++)
        {
            dx=convolution(sobXArray,i,j,3,3);
            dy=convolution(sobYArray,i,j,3,3);
            gray=sqrt(dx*dx+dy*dy);
//            qDebug()<<gray;
            goalImage->setPixel(i,j,qRgb(gray,gray,gray));
        }

    sharpenLabel->setPixmap(QPixmap::fromImage(*goalImage));
}

//算子运算
int MainWindow::convolution(double array[5][5], int xSrc, int ySrc, int x, int y)
{
    int xTemp=x/2;
    int yTemp=y/2;
    int sum;

    x=xTemp*2+1;
    y=yTemp*2+1;

    if(xSrc-xTemp<0||ySrc-yTemp<0||xSrc+xTemp>imageWidth-1||ySrc+yTemp>imageHeight-1)
    {
        return QColor(tempimg->pixel(xSrc,ySrc)).red();
    }
    else
    {
        sum=0;
        for(int i=-xTemp;i<=xTemp;i++)
            for(int j=-yTemp;j<=yTemp;j++)
            {
                sum+=(QColor(tempimg->pixel(xSrc+i,ySrc+j)).red())*array[i+xTemp][j+yTemp];
            }


        return sum;
    }

}

/**************************双线性**************************/
//void MainWindow::doubleline(QImage* imgl,double x,double y)//变换后图片；变换后x；变换后y
//{
//    int r0,r1;
//    int g0,g1;
//    int b0,b1;
//    double kx,ky;

//    r0=QColor(image->pixel((int)x,(int)y)).red();
//    g0=QColor(image->pixel((int)x,(int)y)).green();
//    b0=QColor(image->pixel((int)x,(int)y)).blue();
//    r1=QColor(image->pixel((int)x+1,(int)y+1)).red();
//    g1=QColor(image->pixel((int)x+1,(int)y+1)).green();
//    b1=QColor(image->pixel((int)x+1,(int)y+1)).blue();
//    kx=x%1;
//    ky=y%1;
//    imgl->setPixel(x,y,qRgb(r0+(r1-r0)*kx+(r1-r0)*ky,g0+(g1-g0)*kx+(g1-g0)*ky,b0+(b1-b0)*kx+(b1-b0)*ky));

//}
