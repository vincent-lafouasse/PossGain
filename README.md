# PossGain

PossGain, a revolutionary plugin to control a signal's gain for proper gain staging.

Special thanks to @eyalamirmusic for the project template, and @sammithy for the guidance

## Build

- Run `cmake -B build` from the root of the repository.
- Run `cmake --build build` to build all targets

Alternatively, you can build specific targets with `cmake --build build --target $TARGET_NAME`, with `TARGET_NAME` being among:
- `PossGain_All`
- `PossGain_VST3`
- `PossGain_AU`
- `PossGain_Standalone`

You will find the binaries in `./build/Plugins/PossGain/PossGain_artefacts/`
