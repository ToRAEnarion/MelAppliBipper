#ifndef BIPPERITEM_H
#define BIPPERITEM_H

#include <QObject>

class BipperItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int Seconds READ seconds WRITE setSeconds NOTIFY secondsChanged)
    Q_PROPERTY(int Occurences READ occurences WRITE setOccurences NOTIFY occurencesChanged)
public:
    explicit BipperItem(QObject *parent = nullptr);

    int seconds() const;
    void setSeconds(int value);

    int occurences() const;
    void setOccurences(int value);

signals:
    void secondsChanged();
    void occurencesChanged();
public slots:

private:
    int Seconds;
    int Occurences;
};

#endif // BIPPERITEM_H
