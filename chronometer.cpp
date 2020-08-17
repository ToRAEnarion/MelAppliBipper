#include "chronometer.h"

Chronometer::Chronometer(QQuickItem *parent) :
    QQuickPaintedItem(parent),
    m_backgroundColor(Qt::white),
    m_borderActiveColor(Qt::blue),
    m_borderNonActiveColor(Qt::gray),
    m_angle(0),
    m_circleTime(QTime(0,0,0,0)),
    m_completeTime(60)
{
    internalTimer = new QTimer(this);   // Initialize timer
    /* Also connected to the timer signal from the lambda function
     * Structure lambda functions [object] (arguments) {body}
     * */

    connect(internalTimer, &QTimer::timeout, [=](){
        setAngle(angle() - 0.3);   // Adding to the current time of 50 milliseconds
        update();                                   // redraws the object
    });
  //  internalTimer->start(50);

}

void Chronometer::paint(QPainter *painter)
{
    // Отрисовка объекта
    QBrush  brush(m_backgroundColor);               // Choose a background color, ...
    QBrush  brushActive(m_borderActiveColor);       // active color of border, ...
    QBrush  brushNonActive(m_borderNonActiveColor); // not active color of border

    painter->setPen(Qt::NoPen);                             // remove the outline
    painter->setRenderHints(QPainter::Antialiasing, true);  // Enable antialiasing

    painter->setBrush(brushNonActive);                          // Draw the lowest background in a circle
    painter->drawEllipse(boundingRect().adjusted(1,1,-1,-1));   // with adjustment to the current dimensions, which
                                                                // will be determined in QML-layer.
                                                                // It will not be an active background rim

    // The progress bar will be formed by drawing Pie chart
    painter->setBrush(brushActive);                         // Draw rim active in the background, depending on the angle of rotation
    painter->drawPie(boundingRect().adjusted(1,1,-1,-1),    // to fit to the size of the layer in QML
                     90*16,         // The starting point
                     m_angle*16);   // the angle of rotation, which is necessary to render the object

    painter->setBrush(brush);       // the basic background of the timer, which overlap on top
    painter->drawEllipse(boundingRect().adjusted(10,10,-10,-10));   // Border (aka the progress bar) will be formed
}

void Chronometer::clear()
{
    setCircleTime(QTime(0,0,0,0));  // Clean up time
    setAngle(0);                    // Expose turn to zero
    update();                       // update object
    emit cleared();                 // Emits a clear signal
}

void Chronometer::start()
{
    internalTimer->start(50);       // Start the timer in increments of 50 ms
}

void Chronometer::stop()
{
    internalTimer->stop();          // stops the timer
}

QString Chronometer::name() const
{
    return m_name;
}

QColor Chronometer::backgroundColor() const
{
    return m_backgroundColor;
}

QColor Chronometer::borderActiveColor() const
{
    return m_borderActiveColor;
}

QColor Chronometer::borderNonActiveColor() const
{
    return m_borderNonActiveColor;
}

qreal Chronometer::angle() const
{
    return m_angle;
}

QTime Chronometer::circleTime() const
{
    return m_circleTime;
}

void Chronometer::setName(const QString name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged(name);
}

void Chronometer::setBackgroundColor(const QColor backgroundColor)
{
    if (m_backgroundColor == backgroundColor)
        return;

    m_backgroundColor = backgroundColor;
    emit backgroundColorChanged(backgroundColor);
}

void Chronometer::setBorderActiveColor(const QColor borderActiveColor)
{
    if (m_borderActiveColor == borderActiveColor)
        return;

    m_borderActiveColor = borderActiveColor;
    emit borderActiveColorChanged(borderActiveColor);
}

void Chronometer::setBorderNonActiveColor(const QColor borderNonActiveColor)
{
    if (m_borderNonActiveColor == borderNonActiveColor)
        return;

    m_borderNonActiveColor = borderNonActiveColor;
    emit borderNonActiveColorChanged(borderNonActiveColor);
}

void Chronometer::setAngle(const qreal angle)
{
    if (m_angle == angle)
        return;

    m_angle = angle;

    /* This addition is made to reset the rotation when the timer 60 seconds
     * */
    if(m_angle <= -360) m_angle = 0;
    emit angleChanged(m_angle);
}

void Chronometer::setCircleTime(const QTime circleTime)
{
    if (m_circleTime == circleTime)
        return;

    m_circleTime = circleTime;
    emit circleTimeChanged(circleTime);
}

int Chronometer::currentTime() const
{
    return m_currentTime;
}

void Chronometer::setCurrentTime(int currentTime)
{
    if (m_currentTime == currentTime)
        return;

    m_currentTime = currentTime;
    emit currentTimeChanged(m_currentTime);
    QTime nTime(0,0);
    nTime = nTime.addSecs(currentTime);
    setCircleTime(nTime);
    setAngle(-360*currentTime/completeTime());
    update();
}

void Chronometer::setCompleteTime(int completeTime)
{

    qDebug()<<"set cpl time "<<completeTime;
    if(m_completeTime != completeTime)
    {
        m_completeTime = completeTime;


        setAngle(-360*currentTime()/completeTime);
        emit completeTimeChanged(completeTime);
        update();
    }
}

int Chronometer::completeTime() const
{
    return m_completeTime;
}
