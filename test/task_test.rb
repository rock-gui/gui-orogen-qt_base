# frozen_string_literal: true

using_task_library 'qt_base'

describe OroGen.qt_base.Task do
    run_live

    it 'executes all the UI hooks synchronoulsy within the QT application thread' do
        task = syskit_deploy_configure_and_start(
            OroGen.qt_base.test.TestTask.deployed_as('test_task')
        )
        log_file_path = compute_log_file_path(task)

        agent = task.execution_agent
        plan.make_useless([agent, task])
        expect_execution.garbage_collect(true).to { emit agent.stop_event }

        lines = File.readlines(log_file_path)
                    .map { |line| line.chomp.split(': ') }
        qt_app = lines.shift[1]
        expected_order = %w[configure start update stop cleanup]
                         .flat_map { |p| ["#{p}Hook", "#{p}UI", "#{p}Hook"] }
        assert_equal expected_order, lines.map(&:first)

        lines.each do |phase, thread|
            assert_equal qt_app, thread if phase.end_with?('UI')
        end
    end

    it 'propagates exceptions thrown from within the UI to the component thread(s)' do
        task = syskit_deploy(
            OroGen.qt_base.test.ErrorTestTask.deployed_as('test_task')
        )
        syskit_start_all_execution_agents
        log_file_path = compute_log_file_path(task)
        expect_execution
            .scheduler(true)
            .to { fail_to_start task }

        lines = File.readlines(log_file_path)
        refute lines.grep(/ERROR in configureUI/).empty?
    end

    def compute_log_file_path(task)
        pid = task.execution_agent.pid
        log_dir = task.execution_agent.log_dir
        File.join(log_dir, "test_task-#{pid}.txt")
    end
end
