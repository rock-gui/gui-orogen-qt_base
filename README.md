# Rock-Qt integration within components

This oroGen project provides a base component, `qt_base::Task` which is meant to
ease the integration of Qt-using code within a Rock component.

The main issue this is trying to solve is that Qt has strong threading
requirements, namely that widgets must be run within the same thread as the
QApplication. This projects maps Rock component hooks (`configureHook`,
`startHook`, ...) into equivalents that get executed within the Qt thread
(`configureUI`, ...). The `*UI` variants are all returning `void`, and should
use exceptions to report errors (which are then propagated to the Rock side).

To use this, simply subclass the `qt_base::Task` component and use the UI hooks:

~~~ruby
using_task_library 'qt_base'
task_context 'Task', subclasses: 'qt_base::Task' do
end
~~~

Don't forget to add `gui/orogen/qt_base` to the package's manifest.xml

~~~
<depend name="gui/orogen/qt_base" />
~~~
