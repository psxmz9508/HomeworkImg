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
}

void MainWindow::paintEvent(QPaintEvent *)
{

        if(fileAddress==NULL)
        {

        }
        else
        {
            if(currentPage==2){
                drawHistogram();
                drawHistogram1();
            }
            else{
                drawHistogram();
            }
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
        temp = tempcolor[0][i];
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
    painter.drawText(xmax,oraly-3,tr("灰度"));

    for(int i=0;i<256;i++)
    {
        painter.drawLine(oralx+i,oraly,oralx+i,oraly-hist[i]);
        if(i%30==0)
            painter.drawText(oralx+i,oraly+10,tr(QString::number(i).toLocal8Bit().data()));
    }
    painter.end();
}

/***************************绘制均衡化直方图***************************/
void MainWindow::drawHistogram1()
{
    int hist[256];
    int result[256];
    float phist[256];
    float phisttemp[256];
    int eqhist[256];
    for(int i=0;i<256;i++)
    {
        hist[i]=0;
        result[i]=0;
        phist[i]=0;
        phisttemp[i]=0;
        eqhist[i]=0;
    }
    int temp;

    for(int i=0;i<imageHeight*imageWidth;i++)
    {
        temp = tempcolor[0][i];
        hist[temp]++;
    }

    for(int i=0;i<256;i++){
        phist[i]=(float)hist[i]/(float)imageHeight*imageWidth;
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
        result[i] = hist[eqhist[i]];
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
        result[i]=(int)((result[i]/(float)max)*250);
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
    painter.drawText(xmax,oraly-3,tr("灰度"));

    for(int i=0;i<256;i++)
    {
        painter.drawLine(oralx+i,oraly,oralx+i,oraly-result[i]);
        if(i%30==0)
            painter.drawText(oralx+i,oraly+10,tr(QString::number(i).toLocal8Bit().data()));
    }
    painter.end();
}
/***************************获取图片地址 处理图片数据***************************/
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


    mainLabel->setPixmap(QPixmap::fromImage(*image));
    sqLabel->setPixmap(QPixmap::fromImage(*image));


    for(int x=0;x<imageWidth;x++)
    {
        for(int y=0;y<imageHeight;y++)
        {
            imageColor[0][x*imageWidth+y]=QColor(image->pixel(x,y)).red();
            imageColor[1][x*imageWidth+y]=QColor(image->pixel(x,y)).green();
            imageColor[2][x*imageWidth+y]=QColor(image->pixel(x,y)).blue();
        }
    }
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

    for(int x=0;x<imageWidth;x++)
    {
        for(int y=0;y<imageHeight;y++)
        {
            imageColor[0][x*imageWidth+y]=QColor(image->pixel(x,y)).red();
            imageColor[1][x*imageWidth+y]=QColor(image->pixel(x,y)).green();
            imageColor[2][x*imageWidth+y]=QColor(image->pixel(x,y)).blue();
        }
    }
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
    for(int x=0;x<imageWidth;x++)
    {
        for(int y=0;y<imageHeight;y++)
        {
            imageColor[0][x*imageWidth+y]=QColor(image->pixel(x,y)).red();
            imageColor[1][x*imageWidth+y]=QColor(image->pixel(x,y)).green();
            imageColor[2][x*imageWidth+y]=QColor(image->pixel(x,y)).blue();
        }
    }

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
    for(int x=0;x<imageWidth;x++)
    {
        for(int y=0;y<imageHeight;y++)
        {
            imageColor[0][x*imageWidth+y]=QColor(image->pixel(x,y)).red();
            imageColor[1][x*imageWidth+y]=QColor(image->pixel(x,y)).green();
            imageColor[2][x*imageWidth+y]=QColor(image->pixel(x,y)).blue();
        }
    }
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
    for(int i=0;i<imageWidth;i++)
    {
        for(int j=0;j<imageHeight;j++)
        {
            int aver = (imageColor[0][i*imageWidth+j]+
                       imageColor[1][i*imageWidth+j]+
                       imageColor[2][i*imageWidth+j])/3;
            switch (a) {
            case 1:
                lineimg->setPixel(i,j,qRgb(2*aver+10,
                                          2*aver+10,
                                          2*aver+10));
                break;
            case 2:
                lineimg->setPixel(i,j,qRgb(4*aver+10,
                                          4*aver+10,
                                          4*aver+10));
                break;
            case 3:
                lineimg->setPixel(i,j,qRgb(-2*aver+10,
                                          -2*aver+10,
                                          -2*aver+10));
                break;
            case 4:
                lineimg->setPixel(i,j,qRgb(-4*aver+10,
                                          -4*aver+10,
                                          -4*aver+10));
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
                unlineimg->setPixel(i,j,qRgb(aver*aver/255+10,
                                          aver*aver/255+10,
                                          aver*aver/255+10));
                break;
            case 2:
                unlineimg->setPixel(i,j,qRgb(sqrt(aver)+100,
                                          sqrt(aver)+100,
                                          sqrt(aver)+100));
                break;
            case 3:
                unlineimg->setPixel(i,j,qRgb(log(aver)+50,
                                          log(aver)+50,
                                          log(aver)+50));
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
            tempcolor[0][i*imageWidth+j]=QColor(paintimg->pixel(i,j)).red();
            tempcolor[1][i*imageWidth+j]=QColor(paintimg->pixel(i,j)).green();
            tempcolor[2][i*imageWidth+j]=QColor(paintimg->pixel(i,j)).blue();
        }
    }

}
