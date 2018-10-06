#include "mainwindow.h"
#include <QApplication>

#include "testsuite.h"
#include "scanner.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    TestSuite::integrationTest();
//    Lexer lexer(Scanner::buildScanner("/home/tangenta/Desktop/CppLexer/lexer.cpp"));
//    try {
//        while (1) {
//            auto pair = lexer.getNext();
//            cerr << pair.first << "\t" << pair.second << endl;
//        }
//    } catch (std::out_of_range const& e) {
//        if (std::string("eof").compare(e.what()) != 0) throw e;
//    }

    return a.exec();
}
