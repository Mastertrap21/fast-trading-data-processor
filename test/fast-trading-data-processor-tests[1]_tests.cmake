add_test( main.Always_ReturnSuccess /mnt/d/VisualStudioProjects/fast-trading-data-processor/bin/fast-trading-data-processor-tests [==[--gtest_filter=main.Always_ReturnSuccess]==] --gtest_also_run_disabled_tests)
set_tests_properties( main.Always_ReturnSuccess PROPERTIES WORKING_DIRECTORY /mnt/d/VisualStudioProjects/fast-trading-data-processor/test)
set( fast-trading-data-processor-tests_TESTS main.Always_ReturnSuccess)
