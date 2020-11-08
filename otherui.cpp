#include "otherui.h"

SongQTableWidgetItem::SongQTableWidgetItem(SongModel song,const QString &text,int type)
    :QTableWidgetItem(text,type), song(song)
{
}

QPushButtonPause::QPushButtonPause(QWidget *parrent)
    :QPushButton(parrent)
{
    //设置默认模式
    this->state = QMediaPlayer::PausedState;
    this->setIcon(QIcon(":/icon/ICONS/暂停.svg"));
    //点击时改变模式并发送信号
    connect(this,&QPushButton::clicked,[=]()mutable{
        if(state == QMediaPlayer::PlayingState){
            state = QMediaPlayer::PausedState;
            this->setIcon(QIcon(":/icon/ICONS/暂停.svg"));
        }
        else{
            state = QMediaPlayer::PlayingState;
            this->setIcon(QIcon(":/icon/ICONS/开始.svg"));
        }
        emit stateChanged(state);
        return;
    });
}

void QPushButtonPause::slot_stateChanged(QMediaPlayer::State status)
{
    this->state = status;
    switch (status) {
    case QMediaPlayer::PlayingState:
        this->setIcon(QIcon(":/icon/ICONS/开始.svg"));
        break;
    case QMediaPlayer::PausedState:
        this->setIcon(QIcon(":/icon/ICONS/暂停.svg"));
        break;
    case QMediaPlayer::StoppedState:
        this->setIcon(QIcon(":/icon/ICONS/暂停.svg"));
        break;
    }
}

QPushButtonPlaybackMode::QPushButtonPlaybackMode(QWidget *parrent)
    :QPushButton(parrent)
{
    //设置默认模式
    this->playbackMode = QMediaPlaylist::PlaybackMode::Loop;
    this->setIcon(QIcon(":/icon/ICONS/列表循环.svg"));
    connect(this,&QPushButton::clicked,[=]()mutable{
        switch (playbackMode) {
        //顺序播放切列表循环
        case QMediaPlaylist::PlaybackMode::Sequential:
            this->playbackMode = QMediaPlaylist::PlaybackMode::Loop;
            this->setIcon(QIcon(":/icon/ICONS/列表循环.svg"));
            break;
        //列表循环切随机播放
        case QMediaPlaylist::PlaybackMode::Loop:
            this->playbackMode = QMediaPlaylist::PlaybackMode::Random;
            this->setIcon(QIcon(":/icon/ICONS/随机播放.svg"));
            break;
        //随机播放切单曲循环
        case QMediaPlaylist::PlaybackMode::Random:
            this->playbackMode = QMediaPlaylist::PlaybackMode::CurrentItemInLoop;
            this->setIcon(QIcon(":/icon/ICONS/单曲循环.svg"));
            break;
        //单曲循环切顺序播放
        case QMediaPlaylist::PlaybackMode::CurrentItemInLoop:
            this->playbackMode = QMediaPlaylist::PlaybackMode::Sequential;
            this->setIcon(QIcon(":/icon/ICONS/顺序播放.svg"));
            break;
        default:
            break;
        }
        //发送信号
        emit playbackModeChanged(this->playbackMode);
    });
}

void QPushButtonPlaybackMode::slot_playbackModeChanged(QMediaPlaylist::PlaybackMode mode)
{
    switch (mode) {
    case QMediaPlaylist::PlaybackMode::Sequential:
        this->setIcon(QIcon(":/icon/ICONS/顺序播放.svg"));
        break;
    //列表循环切随机播放
    case QMediaPlaylist::PlaybackMode::Loop:
        this->setIcon(QIcon(":/icon/ICONS/列表循环.svg"));
        break;
    //随机播放切单曲循环
    case QMediaPlaylist::PlaybackMode::Random:
        this->setIcon(QIcon(":/icon/ICONS/随机播放.svg"));
        break;
    //单曲循环切顺序播放
    case QMediaPlaylist::PlaybackMode::CurrentItemInLoop:
        this->setIcon(QIcon(":/icon/ICONS/单曲循环.svg"));
        break;
    default:
        break;
    }
}

void ImageLabel::setPixmap(const QPixmap &p)
{
    this->m_size = p.size();
    if(!round){
        if(m_TimerId)
            this->killTimer(m_TimerId);
        return QLabel::setPixmap(p);
    }
    this->m_pixmap = PixmapToRound(p,p.width()/2);
    m_TimerId = this->startTimer(10);
    return QLabel::setPixmap(m_pixmap);

}

void ImageLabel::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == m_TimerId){
        QMatrix matrix;
        QSize size_Temp = m_pixmap.size();
        m_rotateAngle += 0.1;
        //设置旋转的操作.
        matrix.rotate(m_rotateAngle);
        //获取旋转后的图片.
        QPixmap temp = m_pixmap.transformed(matrix);
        //旋转后的图片需要裁减大小。。。
        temp = temp.copy((temp.size().height() - m_size.height())/2,(temp.size().width() - m_size.width())/2,size_Temp.width(),size_Temp.height());
        QLabel::setPixmap(temp);

        //当转到一圈后.
        if (m_rotateAngle >= 360)
            //归零
            m_rotateAngle = 0;
        }
}

QPixmap ImageLabel::PixmapToRound(const QPixmap &src, int radius)
{
    if(src.isNull())
        return QPixmap();

    QSize size(radius * 2,radius * 2);
    QBitmap mask(size);
    QPainter painter(&mask);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.fillRect(0, 0, size.width(), size.height(), Qt::white);
    painter.setBrush(QColor(0, 0, 0));
    painter.drawRoundedRect(0, 0, size.width(), size.height(), radius, radius);

    QPixmap image = src.scaled(size);
    image.setMask(mask);
    return image;
}

void ImageLabel::slot_pauseTimer()
{
    if(m_TimerId){
        this->killTimer(m_TimerId);
        m_TimerId = 0;
    }
}

void ImageLabel::slot_continueTimer()
{
    if(!m_TimerId)
        m_TimerId = this->startTimer(10);

}

void MyPushButton::setText(const QString &text,int len)
{
    if(text.length() >= len)
        return QPushButton::setText(text.mid(0,len-2) + "……");
    return QPushButton::setText(text);
}
