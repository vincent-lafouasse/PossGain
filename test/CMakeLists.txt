set(tested_src_dir ${CMAKE_CURRENT_SOURCE_DIR}/PossGain/Source)

include(CTest)
enable_testing()

add_test(NAME GainProcessorTest
         COMMAND GainProcessorTest)
