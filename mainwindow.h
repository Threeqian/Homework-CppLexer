#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QPlainTextEdit;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
protected:
    void resizeEvent(QResizeEvent* event) override;
private:
    Ui::MainWindow *ui;
private slots:
    void on_actionLoad_triggered();
    void on_textBrowser_textChanged();
    void on_actionTrim_blanks_triggered();
    void on_actionSave_As_triggered();
};

#endif // MAINWINDOW_H
