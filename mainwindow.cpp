#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <QDebug>
#include <QFileDialog>
#include "lexer.h"
#include "scanner.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->textBrowser->resize(ui->centralWidget->size() - QSize(10, 10));
    ui->textBrowser->move(ui->centralWidget->pos() + QPoint(5, 5));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent* event) {
    QMainWindow::resizeEvent(event);
    ui->textBrowser->resize(ui->centralWidget->size() - QSize(10, 10));
    ui->textBrowser->move(ui->centralWidget->pos() + QPoint(5, 5));
}


void MainWindow::on_actionLoad_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Load", ".",
        tr("C++ file (*.cpp *.cc *.hpp *.h *.cxx)"));
    if (filename.isEmpty()) return;
    Lexer lexer(Scanner::buildScanner(filename.toStdString()));
    try {
        while (1) {
            auto pair = lexer.getNext();
            ui->textBrowser->append(QString() + pair.first.c_str() + "\t" + pair.second.c_str());
        }
    } catch (std::out_of_range const& e) {
        if (QString("eof").compare(e.what()) != 0) throw e;
        /* ignore eof exception */
    }
}

void MainWindow::on_textBrowser_textChanged()
{
}

void MainWindow::on_actionTrim_blanks_triggered() {
    QString filename = QFileDialog::getOpenFileName(this, "Load", ".",
        tr("C++ file (*.cpp *.cc *.hpp *.h *.cxx)"));
    if (filename.isEmpty()) return;
    Lexer lexer(Scanner::buildScanner(filename.toStdString()));
    try {
        while (1) {
            auto pair = lexer.getNext();
            ui->textBrowser->moveCursor(QTextCursor::End);
            ui->textBrowser->insertPlainText(pair.first.c_str());
        }
    } catch (std::out_of_range const& e) {
        if (QString("eof").compare(e.what()) != 0) throw e;
        /* ignore eof exception */
    }

}

void MainWindow::on_actionSave_As_triggered()
{
    static const std::vector<QString> type = {".cpp", ".cc", ".cxx", ".hpp", ".h"};
    QString filename = QFileDialog::getSaveFileName(this, "Save As", ".",
        tr("C++ file (*.cpp *.cc *.hpp *.h *.cxx)"));
    if (filename.isEmpty()) return;
    bool needsAppend = true;
    for (auto t : type) {
        if (filename.endsWith(t)) {
            needsAppend = false;
            break;
        }
    }
    if (needsAppend) filename.append(".cpp");
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(nullptr, tr("Cpp Lexer"),tr("Cannot read file %1, error: %2")
                             .arg(file.fileName())
                             .arg(file.errorString()));
        return;
    }
    QTextStream out(&file);
    out << ui->textBrowser->toPlainText();
}
