/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "TestTask.hpp"
#include <QThread>
#include <QApplication>

using namespace qt_base::test;

TestTask::TestTask(std::string const& name)
    : TestTaskBase(name)
{
}

TestTask::~TestTask()
{
}

bool TestTask::configureHook()
{
    std::cout << "QApplication: " << QApplication::instance()->thread() << std::endl;
    std::cout << "configureHook: " << QThread::currentThread() << std::endl;
    if (! TestTaskBase::configureHook()) {
        return false;
    }

    std::cout << "configureHook: " << QThread::currentThread() << std::endl;
    return true;
}
void TestTask::configureUI()
{
    std::cout << "configureUI: " << QThread::currentThread() << std::endl;
}
bool TestTask::startHook()
{
    std::cout << "startHook: " << QThread::currentThread() << std::endl;
    if (! TestTaskBase::startHook()) {
        return false;
    }

    std::cout << "startHook: " << QThread::currentThread() << std::endl;
    return true;
}
void TestTask::startUI()
{
    std::cout << "startUI: " << QThread::currentThread() << std::endl;
}
void TestTask::updateHook()
{
    std::cout << "updateHook: " << QThread::currentThread() << std::endl;
    TestTaskBase::updateHook();
    std::cout << "updateHook: " << QThread::currentThread() << std::endl;
}
void TestTask::updateUI()
{
    std::cout << "updateUI: " << QThread::currentThread() << std::endl;
}
void TestTask::errorHook()
{
    std::cout << "errorHook: " << QThread::currentThread() << std::endl;
    TestTaskBase::errorHook();
    std::cout << "errorHook: " << QThread::currentThread() << std::endl;
}
void TestTask::errorUI()
{
    std::cout << "errorUI: " << QThread::currentThread() << std::endl;
}
void TestTask::stopHook()
{
    std::cout << "stopHook: " << QThread::currentThread() << std::endl;
    TestTaskBase::stopHook();
    std::cout << "stopHook: " << QThread::currentThread() << std::endl;
}
void TestTask::stopUI()
{
    std::cout << "stopUI: " << QThread::currentThread() << std::endl;
}
void TestTask::cleanupHook()
{
    std::cout << "cleanupHook: " << QThread::currentThread() << std::endl;
    TestTaskBase::cleanupHook();
    std::cout << "cleanupHook: " << QThread::currentThread() << std::endl;
}
void TestTask::cleanupUI()
{
    std::cout << "cleanupUI: " << QThread::currentThread() << std::endl;
}
