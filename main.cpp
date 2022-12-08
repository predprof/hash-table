#include "mainwindow.h"
#include "htable.h"
#include "htable.cpp"
#include <string>
#include <iostream>
#include <assert.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    HTable<std::string, int> test1;
    HTable<std::string, int> test2;
    HTable<std::string, int> test3;

    assert(test1.getSize() == 0);

    test2.insert("one", 100);
    assert(test2.getSize() == 1);
    test2.insert("two", 123);
    test2.insert("free", 303);
    test2.insert("Hel", 12);
    test2.insert("Cau", 34);
    test2.insert("one", 100);
    assert(test2.getSize() == 5);
    assert(test2.getSum() == 572);

    assert(test2.isKey("free") == true);
    assert(test2.isKey("no") == false);

    assert(test2["Hel"] == 12);

    test2.remove("no");
    assert(test2.getSize() == 5);

    test2.remove("free");
    assert(test2.getSize() == 4);

    std::string path = "C:/Qt/MyProjects/oop-lab-work-2/output.txt";

    test2.writeToFile(path);
    test3.loadFromFile(path);
    assert((test2 == test3) == true);

    HTable<std::string, int> test4 = test2;
    assert((test2 == test4) == true);

    test4.insert("one", 101);
    assert((test2 == test4) == false);

    test2.clear();
    assert((test1 == test2) == true);

    std::cout << "All tests passed successfuly!" << std::endl;

    auto k = test4.getKey(3);
    auto v = test4.getValue(k);

    std::cout << k << "  " << v << std::endl;

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
    return 0;
}
