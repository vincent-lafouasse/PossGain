set(targetName GainProcessorTest)

juce_add_console_app(${targetName}
    PROJECT_NAME "GainProcessor tests"
)
juce_generate_juce_header(${targetName})

set(testedSourceDir ${CMAKE_SOURCE_DIR}/PossGain/Source)
target_sources(${targetName} PRIVATE
    ./main.cpp
    ./GainProcessorTest.cpp

    ${testedSourceDir}/Processing/ProcessorBase/Buffer.hpp
    ${testedSourceDir}/Processing/ProcessorBase/Processor.hpp
    ${testedSourceDir}/Processing/GainProcessor.cpp
    ${testedSourceDir}/Processing/GainProcessor.hpp
)

target_include_directories(${targetName} PUBLIC
    ./
    ${testedSourceDir}
)

target_compile_definitions(${targetName} PRIVATE
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
)

target_link_libraries(${targetName} PRIVATE
    libgtest
    juce_recommended_config_flags
    juce_recommended_lto_flags
    juce_recommended_warning_flags
    juce_core
)
