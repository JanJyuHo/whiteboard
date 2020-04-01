#ifndef BGRAPHICSSCENE_H
#define BGRAPHICSSCENE_H

#include <QQuickItem>
#include <QVector>
#include <QPointer>
#include <QTcpSocket>
#include <QTcpServer>
#include <QRegExp>
#include <QHostInfo>

enum SceneMode
{
    Unknown,
    Normal,
    Pen,
    Light,
    Eraser,
    Text,
    Line,
    Rect,
    Ellipse,
};
enum State {conn, disconn, painted};


class BGraphicsAbstractItem;
class netAddr
{
public:
    unsigned char srcIP[4];
    unsigned char desIP[4];
};

class Point
{
public:
    int x;
    int y;
};

class userOp
{
public:
    int opKind;
    Point startPoint;
    Point endPoint;
};

class MessageStruct
{
public:
    netAddr messageHeader;
    userOp userOpInfo;
};

class BGraphicsScene : public QQuickItem
{
    Q_OBJECT
    //Q_PROPERTY(qreal m_sceneScale READ sceneScale WRITE setSceneScale NOTIFY sceneScaleChanged)
public:


public:
    BGraphicsScene(QQuickItem *parent = nullptr);
    ~BGraphicsScene();

public:
    Q_INVOKABLE void setNormalMode();
    Q_INVOKABLE void setPenMode(int width, const QColor &color);
    Q_INVOKABLE void setLightMode();
    Q_INVOKABLE void setShapeMode(int type, int width, const QColor &color);
    Q_INVOKABLE void setTextMode(int width, const QString &name, const QColor &color);
    Q_INVOKABLE void setEraserMode();
    Q_INVOKABLE void addPixmap(float x, float y, const QString &pixmap);
    Q_INVOKABLE void setSceneScale(qreal scale, qreal x, qreal y);
    //Q_INVOKABLE qreal sceneScale() const {return m_sceneScale;}

private:
    void onDealEraser(const QPointF &pos);
    void setItemsAcceptedMouse(bool enabled);
    void setItemsNormal();
    void connectToServer();
    void paint();

private slots:
    void getData();
    void sendRequest();
    void error();

protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE Q_DECL_FINAL;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE Q_DECL_FINAL;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE Q_DECL_FINAL;
    void hoverMoveEvent(QHoverEvent *event) Q_DECL_OVERRIDE Q_DECL_FINAL;
    void wheelEvent(QWheelEvent* event) Q_DECL_OVERRIDE Q_DECL_FINAL;
    void paintEvent(QPaintEvent* event);
    //void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry);

signals:
    //void sceneScaleChanged();

private:
    MessageStruct m_message;
    QTcpSocket *m_tcpSocket;
    SceneMode m_mode;
    QPointer<BGraphicsAbstractItem> m_pItem;
    QPoint m_posPressed;
    QColor m_penColor;
    int m_penWidth;
    QColor m_shapeColor;
    int m_shapeWidth;
    qreal m_sceneScale;        // 场景缩放
};

#endif // BGRAPHICSSCENE_H
