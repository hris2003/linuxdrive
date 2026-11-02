#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QDir>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Proton Drive Qt Manager (Fedora)");

    // Setup Central Widget & Layouts
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    m_startBtn = new QPushButton("Mount Proton Drive", this);
    m_stopBtn = new QPushButton("Unmount", this);
    m_stopBtn->setEnabled(false);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addWidget(m_startBtn);
    btnLayout->addWidget(m_stopBtn);

    m_logOutput = new QTextEdit(this);
    m_logOutput->setReadOnly(true);
    m_logOutput->setPlaceholderText("Rclone logs and status will appear here...");

    mainLayout->addLayout(btnLayout);
    mainLayout->addWidget(m_logOutput);
    setCentralWidget(centralWidget);

    // Initialize QProcess
    m_rcloneProcess = new QProcess(this);
    m_rcloneProcess->setProcessChannelMode(QProcess::MergedChannels);

    // Connect Signals
    connect(m_startBtn, &QPushButton::clicked, this, &MainWindow::handleStartMount);
    connect(m_stopBtn, &QPushButton::clicked, this, &MainWindow::handleStopMount);
    connect(m_rcloneProcess, &QProcess::readyReadStandardOutput, this, &MainWindow::readRcloneOutput);
}

MainWindow::~MainWindow() {
    if (m_rcloneProcess->state() == QProcess::Running) {
        m_rcloneProcess->terminate();
        m_rcloneProcess->waitForFinished(3000);
    }
}

void MainWindow::handleStartMount() {
    QString mountPath = QDir::homePath() + "/ProtonDrive";
    QDir().mkpath(mountPath);

    QStringList args;
    args << "mount" << "proton-drive:" << mountPath << "--vfs-cache-mode" << "writes";

    m_logOutput->append("Starting rclone mount at: " + mountPath);
    m_rcloneProcess->start("rclone", args);

    m_startBtn->setEnabled(false);
    m_stopBtn->setEnabled(true);
}

void MainWindow::handleStopMount() {
    if (m_rcloneProcess->state() == QProcess::Running) {
        m_logOutput->append("Stopping rclone mount...");
        m_rcloneProcess->terminate();
        m_rcloneProcess->waitForFinished(3000);
    }
    m_startBtn->setEnabled(true);
    m_stopBtn->setEnabled(false);
}

void MainWindow::readRcloneOutput() {
    QByteArray data = m_rcloneProcess->readAllStandardOutput();
    m_logOutput->append(QString::fromUtf8(data));
}