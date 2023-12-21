#include "UITest.h"
#include <QApplication>
#include <QString>
#include <QUrl>


UITest::UITest(QWidget* parent)
    : QMainWindow(parent), engine(new QWebEngineView(this)), 
    exitHotkey(new QShortcut(QKeySequence(Qt::Key_Escape), this))
{
    //engine = new QWebEngineView(this);
    setWindowTitle("智能安检分析系统");
    setWindowState(Qt::WindowState::WindowFullScreen);

    setCentralWidget(engine.get());
    
    QString path = QApplication::applicationDirPath() + "/index.html";
    
    engine->page()->load(QUrl::fromLocalFile(path));
    //engine->load();

    QString channelPath = QApplication::applicationDirPath() + "/qwebchannel.js";
    engine->page()->runJavaScript(channelPath);

    connect(exitHotkey.get(), &QShortcut::activated, this, &QMainWindow::close);
}

UITest::~UITest()
{
   
}