# frozen_string_literal: true

using_task_library 'qt_base'

describe OroGen.qt_base.test.TestTask do
    run_live

    it 'executes all the UI hooks synchronoulsy within the QT application thread' do
        task = syskit_deploy_configure_and_start(OroGen.qt_base.test.TestTask)
        pid = task.execution_agent.pid
        log_dir = task.execution_agent.log_dir
        log_file = File.join(log_dir, "task_under_test-#{pid}.txt")

        agent = task.execution_agent
        plan.make_useless([agent, task])
        expect_execution.garbage_collect(true).to { emit agent.stop_event }
        lines = File.readlines(log_file)
                    .map { |line| line.chomp.split(": ") }
        qt_app = lines.shift[1]
        expected_order = %w[configure start update stop cleanup]
                         .flat_map { |p| ["#{p}Hook", "#{p}UI", "#{p}Hook"] }
        assert_equal expected_order, lines.map(&:first)

        lines.each do |phase, thread|
            assert_equal qt_app, thread if phase.end_with?('UI')
        end
    end
end
