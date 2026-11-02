#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QPushButton>
#include <QTextEdit>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleStartMount();
    void handleStopMount();
    void readRcloneOutput();

private:
    QPushButton *m_startBtn;
    QPushButton *m_stopBtn;
    QTextEdit *m_logOutput;
    QProcess *m_rcloneProcess;
};

#endif // MAINWINDOW_H