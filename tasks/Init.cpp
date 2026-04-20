#include <pthread.h>
#include <QApplication>

static int QT_ARGC = 1;
static char const* QT_ARGV[] = { "orogen", nullptr };
static void* qt_thread_main(void*)
{
    QApplication *qapp = new QApplication(QT_ARGC, const_cast<char**>(QT_ARGV));
    qapp->setQuitOnLastWindowClosed(false);
    // NOTE: we do NOT need to explicitely synchronize with the QApplication
    // startup. The only safe way to interact with parts of Qt that require
    // an event loop is through postEvent, which is safe to use even before
    // the QApplication gets created

    qapp->exec();
    return NULL;
}

pthread_t qt_thread;

namespace qt_base {
    void globalInitializerInit() {
        pthread_create(&qt_thread, NULL, qt_thread_main, NULL);
    }

    void globalInitializerExit() {
        QApplication::instance()->exit();
        pthread_join(qt_thread, NULL);
    }
}