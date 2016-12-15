#include <QApplication>
#include <QCommandLineParser>

#include <QtWidgets/QMainWindow>

#include "qt5-node-editor/src/qnodewidget.h"
#include "qt5-node-editor/src/graphicsnode.hpp"
#include "Qt-Color-Widgets/include/ColorWheel"

class MyObject1 : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(int prop1 READ prop1 WRITE setProp1 NOTIFY prop1Changed USER true)
    Q_PROPERTY(QString prop2 READ prop2 WRITE setProp2 NOTIFY prop2Changed USER true)
    Q_PROPERTY(int prop3 READ prop3 WRITE setProp3 NOTIFY prop3Changed USER true)

    int prop1() const;
    int prop3() const;
    QString prop2() const;

    void setProp1(int p);
    void setProp3(int p);
    void setProp2(QString& p);

signals:
    void prop1Changed(int);
    void prop2Changed(const QString&);
    void prop3Changed(int);

private:
    int m_Prop1;
    int m_Prop3;
    QString m_Prop2;
};

int MyObject1::prop1() const { return m_Prop1;}
int MyObject1::prop3() const { return m_Prop3;}
QString MyObject1::prop2() const { return m_Prop2;}
void MyObject1::setProp1(int p) {if (m_Prop1 == p) return; m_Prop1 = p; emit prop1Changed(p);}
void MyObject1::setProp3(int p) {if (m_Prop3 == p) return; m_Prop3 = p; emit prop3Changed(p);}
void MyObject1::setProp2(QString& p) {if (m_Prop2 == p) return; m_Prop2 = p; emit prop2Changed(p);}

#include "ui_mainwindow.h" //not used in this stripped down project

int main (int argc, char *argv[])
{
    QApplication app(argc, argv);

    QMainWindow* m = new QMainWindow();

    MyObject1 o1;
    MyObject1 o2;
    MyObject1 o3;

    QNodeWidget* n = new QNodeWidget(m);
    m->setCentralWidget(n);

    n->addObject(&o1, "one");
    n->addObject(&o2, "two");
    GraphicsNode* node = n->addObject(&o3, "three");

    color_widgets::ColorWheel* cw = new color_widgets::ColorWheel();
    cw->setStyleSheet("background-color: transparent");
    cw->setMinimumSize(100,100);
    node->setCentralWidget(cw);
    node->setSize(300,300);
    node->graphicsItem()->setPos(100,100);

    m->show();

    return app.exec();
}

#include "main.moc"
