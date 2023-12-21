#pragma once

#include <QMainWindow>
#include <QWebEngineView>

#include <QSharedPointer>
#include <QShortcut>

class UITest : public QMainWindow {
    Q_OBJECT
    
public:
    UITest(QWidget* parent = nullptr);
    ~UITest();
private:
    QSharedPointer<QWebEngineView> engine;
    QSharedPointer<QShortcut>   exitHotkey;
};