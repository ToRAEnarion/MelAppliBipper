#ifndef CHRONOMETER_H
#define CHRONOMETER_H

#include <QtQuick/QQuickPaintedItem>
#include <QColor>
#include <QBrush>
#include <QPen>
#include <QPainter>
#include <QTime>
#include <QTimer>

class Chronometer : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
    Q_PROPERTY(QColor borderActiveColor READ borderActiveColor WRITE setBorderActiveColor NOTIFY borderActiveColorChanged)
    Q_PROPERTY(QColor borderNonActiveColor READ borderNonActiveColor WRITE setBorderNonActiveColor NOTIFY borderNonActiveColorChanged)
    Q_PROPERTY(qreal angle READ angle WRITE setAngle NOTIFY angleChanged)
    Q_PROPERTY(QTime circleTime READ circleTime WRITE setCircleTime NOTIFY circleTimeChanged)
    Q_PROPERTY(int currentTime READ currentTime WRITE setCurrentTime NOTIFY currentTimeChanged)
    Q_PROPERTY(int completeTime READ completeTime WRITE setCompleteTime NOTIFY completeTimeChanged)

public:
    explicit Chronometer(QQuickItem *parent = nullptr);

    void paint(QPainter *painter) override; // Override the method in which the object will be rendered to our

    // Methods available from QML for ...
    Q_INVOKABLE void clear();   // ... time cleaning ...
    Q_INVOKABLE void start();   // ... start the timer, ...
    Q_INVOKABLE void stop();    // ... stop the timer, ...

    QString name() const;
    QColor backgroundColor() const;
    QColor borderActiveColor() const;
    QColor borderNonActiveColor() const;
    qreal angle() const;
    QTime circleTime() const;

    int currentTime() const;

    int completeTime() const;

public slots:
    void setName(const QString name);
    void setBackgroundColor(const QColor backgroundColor);
    void setBorderActiveColor(const QColor borderActiveColor);
    void setBorderNonActiveColor(const QColor borderNonActiveColor);
    void setAngle(const qreal angle);
    void setCircleTime(const QTime circleTime);
    void setCurrentTime(int currentTime);
    void setCompleteTime(int completeTime);


signals:
    void cleared();

    void nameChanged(const QString name);
    void backgroundColorChanged(const QColor backgroundColor);
    void borderActiveColorChanged(const QColor borderActiveColor);
    void borderNonActiveColorChanged(const QColor borderNonActiveColor);
    void angleChanged(const qreal angle);
    void circleTimeChanged(const QTime circleTime);
    void currentTimeChanged(int currentTime);
    void completeTimeChanged(int cplTime);

private:
    QString     m_name;                 // The name of the object
    QColor      m_backgroundColor;      // The main background color
    QColor      m_borderActiveColor;    // The color of the border, filling with the progress bezel timer
    QColor      m_borderNonActiveColor; // The color of the background of the border
    qreal       m_angle;                // The rotation angle of the pie chart type, will generate progress on the rim
    QTime       m_circleTime;           // Current time of the timer

    int         m_currentTime;
    int         m_completeTime;

    QTimer      *internalTimer;         // The timer, which will vary according to the time
};
#endif // CHRONOMETER_H
