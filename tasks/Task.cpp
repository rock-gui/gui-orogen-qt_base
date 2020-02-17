/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "Task.hpp"
#include <QObject>
#include <QEvent>
#include <QApplication>

using namespace std;
using namespace qt_base;

Task::Task(std::string const& name)
    : TaskBase(name)
{
}

Task::~Task()
{
}

struct MethodInQtThreadFailed : runtime_error {
    using runtime_error::runtime_error;
};

struct MethodExecutionEvent : public QEvent {
    QMutex& mLock;
    QWaitCondition& mSignal;
    bool& mResult;
    string& mMessage;

    MethodExecutionEvent(QMutex& lock, QWaitCondition& signal,
                         bool& result, string& message)
        : QEvent(QEvent::User)
        , mLock(lock), mSignal(signal), mResult(result), mMessage(message) { }

    function<void()> f;
};

class MethodExecutionObject : public QObject {
    bool event(QEvent* event) {
        auto ev = dynamic_cast<MethodExecutionEvent*>(event);
        if (ev) {
            try {
                ev->f();

                QMutexLocker sync(&(ev->mLock));
                ev->mResult = true;
                ev->mSignal.wakeAll();
            }
            catch (exception const& e) {
                QMutexLocker sync(&(ev->mLock));
                ev->mResult = false;
                ev->mMessage = e.what();
                ev->mSignal.wakeAll();
            }
            catch (...) {
                QMutexLocker sync(&(ev->mLock));
                ev->mResult = false;
                ev->mMessage =
                    "exception thrown that is not a subclass of exception";
                ev->mSignal.wakeAll();
            }
            return true;
        }
        return false;
    }
};

/// The following lines are template definitions for the various state machine
// hooks defined by Orocos::RTT. See Task.hpp for more detailed
// documentation about them.

bool Task::configureHook()
{
    if (! TaskBase::configureHook()) {
        return false;
    }

    if (!mExecutor) {
        mExecutor = new MethodExecutionObject();
        mExecutor->moveToThread(QApplication::instance()->thread());
    }

    processInQtThread(bind(&Task::configureUI, this));
    return true;
}
void Task::configureUI()
{
}
bool Task::startHook()
{
    if (! TaskBase::startHook()) {
        return false;
    }

    processInQtThread(bind(&Task::startUI, this));
    return true;
}
void Task::startUI()
{
}
void Task::updateHook()
{
    TaskBase::updateHook();
    processInQtThread(bind(&Task::updateUI, this));
}
void Task::updateUI()
{
}
void Task::errorHook()
{
    processInQtThread(bind(&Task::errorUI, this));
    TaskBase::errorHook();
}
void Task::errorUI()
{
}
void Task::stopHook()
{
    processInQtThread(bind(&Task::stopUI, this));
    TaskBase::stopHook();
}
void Task::stopUI()
{
}
void Task::cleanupHook()
{
    processInQtThread(bind(&Task::cleanupUI, this));
    TaskBase::cleanupHook();
}
void Task::cleanupUI()
{
}
void Task::processInQtThread(function<void()> f) {
    QMutexLocker sync(&mExecutorLock);

    bool result = true;
    string message;
    auto* event = new MethodExecutionEvent(
        mExecutorLock, mExecutorSignal, result, message
    );
    event->f = f;
    QApplication::instance()->postEvent(mExecutor, event);

    mExecutorSignal.wait(&mExecutorLock);
    if (!result) {
        throw MethodInQtThreadFailed(message);
    }
}
