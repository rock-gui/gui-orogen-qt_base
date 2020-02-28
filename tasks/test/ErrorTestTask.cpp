/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "ErrorTestTask.hpp"

using namespace qt_base::test;

ErrorTestTask::ErrorTestTask(std::string const& name)
    : ErrorTestTaskBase(name)
{
}

ErrorTestTask::~ErrorTestTask()
{
}

/// The following lines are template definitions for the various state machine
// hooks defined by Orocos::RTT. See ErrorTestTask.hpp for more detailed
// documentation about them.

bool ErrorTestTask::configureHook()
{
    if (! ErrorTestTaskBase::configureHook()) {
        return false;
    }
    return true;
}
void ErrorTestTask::configureUI() {
    throw std::runtime_error("ERROR in configureUI");
}
bool ErrorTestTask::startHook()
{
    if (! ErrorTestTaskBase::startHook()) {
        return false;
    }
    return true;
}
void ErrorTestTask::updateHook()
{
    ErrorTestTaskBase::updateHook();
}
void ErrorTestTask::errorHook()
{
    ErrorTestTaskBase::errorHook();
}
void ErrorTestTask::stopHook()
{
    ErrorTestTaskBase::stopHook();
}
void ErrorTestTask::cleanupHook()
{
    ErrorTestTaskBase::cleanupHook();
}
