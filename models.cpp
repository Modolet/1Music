#include "models.h"

Models::Models(QObject *parent) : QObject(parent)
{

}

ListModel::ListModel(QString url, bool isLocalList)
{
    //检查文件是否存在
    if((!QFileInfo(url).isFile()) && isLocalList)
    {
        IsExist = false;
    }
    else
        IsExist = true;
    this->Url = url;
    this->IsLocalList = isLocalList;
    if(isLocalList && IsExist)
        ReadJson();
}

ListModel::~ListModel()
{

}

void ListModel::setName(const QString &name)
{
    this->Name = name;
}

void ListModel::setCreateTime(const QDateTime &time)
{
    this->CreateTime = time;
}

void ListModel::insertSong(const SongModel &song)
{
    this->Songs.append(song);
}

void ListModel::deleteSong(const SongModel &song)
{
    this->Songs.removeOne(song);
}

void ListModel::setInfo(const QString &info)
{
    this->Info = info;
}

void ListModel::saveJson()
{
    QJsonArray json_list;
    QJsonObject json_doc;

    //插入歌单信息
    json_doc.insert("Info",this->Info);
    //如果是本地歌单，需要单独设置Name和Author
    if(this->IsLocalList)
    {
        if(this->Url == "./lists/locallist.json")
            json_doc.insert("Name","本地音乐");
        json_doc.insert("Author","localuser");
    }
    else
    {
        json_doc.insert("Name",this->Name);
        json_doc.insert("Author",this->Author);
    }
    json_doc.insert("Url",this->Url);
    json_doc.insert("Info",this->Info);
    //插入时间
    QDateTime* local = new QDateTime(QDateTime::currentDateTime());
    json_doc.insert("CreateTime",local->toString("yyyy-MM-dd"));
    delete local;
    //在json_list中插入每一首歌曲的信息
    for(SongModel song:this->Songs)
    {
        QJsonObject json_object;
        json_object.insert("Url",song.Url);
        json_object.insert("Title",song.Title);
        json_object.insert("Singer",song.Singer);
        json_object.insert("Album",song.Album);
        if(!song.IsLocalSong)
        {
            json_object.insert("id",song.Id);
            json_object.insert("Source",song.Source);
        }
        else
            json_object.insert("Source","本地音乐");
        json_list.append(json_object);
    }
    json_doc.insert("Song",json_list);

    //写入到文件
        QJsonDocument json_file(json_doc);
        QFile* file;
        if(this->IsLocalList)
            file = new QFile(this->Url);
        else
            file = new QFile("./lists/" + this->Name + ".json");
        file->open(QIODevice::ReadWrite);
        file->write(json_file.toJson());
        file->close();
}

void ListModel::ReadJson()
{
    QFile* file;
    QJsonDocument json_file;
    QJsonObject json_doc;
    QJsonArray json_array;
    if(this->IsLocalList)
        file = new QFile(this->Url);
    else
        file = new QFile("./lists/" + this->Name + ".json");
    file->open(QIODevice::ReadOnly);

    json_file = QJsonDocument::fromJson(file->readAll());
    file->close();
    json_doc = json_file.object();
    try {
        this->Author = json_doc.value("Author").toString();
        this->Info = json_doc.value("Info").toString();
        this->Name = json_doc.value("Name").toString();
        this->CreateTime.fromString(json_doc.value("CreateTime").toString(),"yyyy-MM-dd");
        this->Url= json_doc.value("Url").toString();
        json_array = json_doc.value("Song").toArray();
        for(auto obj:json_array)
        {
            SongModel song(obj.toObject().value("Url").toString(),true,true);
            song.Album = obj.toObject().value("Album").toString();
            song.Singer = obj.toObject().value("Singer").toString();
            song.Source = obj.toObject().value("Source").toString();
            song.Title = obj.toObject().value("Title").toString();
            this->insertSong(song);
        }
    }  catch (const char* msg) {

    }
}

bool ListModel::isExist()
{
    return IsExist;
}

SongModel::SongModel(QString url,bool IsLocalSong,bool IsSaved)
{
    this->Url = url;
    this->IsLocalSong = IsLocalSong;
    if(IsLocalSong && (!IsSaved))
    {
        FileName = url.split("/").last();
        TagLib::FileRef file(Url.toUtf8());
        this->Album = QString::fromStdWString(file.tag()->album().toWString());
        this->Singer = QString::fromStdWString(file.tag()->artist().toWString());
        this->Title = QString::fromStdWString(file.tag()->title().toWString());
        this->times = file.audioProperties()->length();
        this->seconds = file.audioProperties()->length() % 60;
        this->minutes = (file.audioProperties()->length() - seconds) / 60;
        this->Source = "本地文件";
    }
}

SongModel::~SongModel()
{

}

bool SongModel::operator==(const SongModel &obj)
{
    if(this->Url == obj.Url)
        return true;
    return false;
}

QImage SongModel::getID3v2Image()
{

    TagLib::MPEG::File file(Url.toUtf8());
    TagLib::ID3v2::Tag *m_tag = file.ID3v2Tag(true);
    TagLib::ID3v2::FrameList frameList = m_tag->frameList("APIC");
    if(frameList.isEmpty()) {
        return QImage();
    }

    TagLib::ID3v2::AttachedPictureFrame *coverImg = static_cast<TagLib::ID3v2::AttachedPictureFrame *>(frameList.front());

    QImage coverQImg;
    coverQImg.loadFromData((const uchar *) coverImg->picture().data(), coverImg->picture().size());

    return coverQImg;
}
