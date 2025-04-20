set (Plugin PossGain)

juce_add_plugin("${Plugin}"
        # VERSION ...                               # Set this if the plugin version is different to the project version
        # ICON_BIG ...                              # ICON_* arguments specify a path to an image file to use as an icon for the Standalone
        # ICON_SMALL ...
        COMPANY_NAME "Poss"
        IS_SYNTH FALSE
        NEEDS_MIDI_INPUT TRUE
        NEEDS_MIDI_OUTPUT FALSE
        IS_MIDI_EFFECT FALSE
        EDITOR_WANTS_KEYBOARD_FOCUS FALSE
        COPY_PLUGIN_AFTER_BUILD TRUE
        PLUGIN_MANUFACTURER_CODE Juce
        PLUGIN_CODE MIpl
        FORMATS AU VST3 Standalone
        PRODUCT_NAME "PossGain"
)

target_sources(${Plugin} PRIVATE
        Source/PossGain.cpp
        Source/PossGain.hpp

        Source/Processing/ProcessorBase/Processor.hpp
        Source/Processing/ProcessorBase/Buffer.hpp

        Source/Processing/GainProcessor.cpp
        Source/Processing/GainProcessor.hpp
        Source/Processing/PanProcessor.cpp
        Source/Processing/PanProcessor.hpp
        Source/Processing/InputSelectionProcessor.cpp
        Source/Processing/InputSelectionProcessor.hpp

        Source/Gui/PluginEditor.cpp
        Source/Gui/PluginEditor.hpp

        Source/Gui/OutputPanel.cpp
        Source/Gui/OutputPanel.hpp
        Source/Gui/InputPanel.cpp
        Source/Gui/InputPanel.hpp

        Source/Gui/Knobs/GainKnob.hpp
        Source/Gui/Knobs/BalanceKnob.hpp
        Source/Gui/Knobs/PercentageKnob.hpp

        Source/Modules/Smoothed/Smoothed.hpp
)

target_include_directories(${Plugin}
        PUBLIC
        Source/
)

target_compile_definitions(${Plugin}
        PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
)

target_link_libraries(${Plugin}
        PRIVATE
        juce_audio_utils
        juce_recommended_config_flags
        juce_recommended_lto_flags
        juce_recommended_warning_flags
)
