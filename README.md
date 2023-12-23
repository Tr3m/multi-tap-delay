# Multi-Tap Delay

A Multi-Tap delay audio plug-in that utilizes four delay lines to create a rhythmic pattern with the repeats.

<p align="center">
  <img width="600" height="430" src="https://cdn.discordapp.com/attachments/580466872169005066/1188166865705500772/screenshot.png?ex=6599899f&is=6587149f&hm=145e7590ea66503d7ee7c422373bee26771137f2da27338640404481c69dee99&">
</p>

### Controls

  * Time
    * The Time knobs control delay time for each delay line.
  * Feedback
    * The Feedback knobs control the amount of the output that's fed back into each delay line.
  * Low-Cut and Hight-Cut
    * High and Low Pass filters respectively
  * Mix
    * A unified WET/DRY Control.
  * Detune
    * The detune knobs can change the pitch of the repeats up to plus or minus of 50 cents.
  * Sync
    * Syncs the plug-in's BPM with the host DAW.


## Building


### Prerequisites


A global installation of [JUCE](https://github.com/juce-framework/JUCE) is required in order to build the project using CMake. After cloning the JUCE repo, a global installation can be built by running:

```bash
cmake -B cmake-build-install -DCMAKE_INSTALL_PREFIX=/path/to/JUCE/install
cmake --build cmake-build-install --target install
```

### Building on Windows

```bash
git submodule update --init --recursive
cmake -B build -DCMAKE_PREFIX_PATH=/path/to/JUCE/install
cmake --build build --config Release
```

### Building on MacOS/Linux

```bash
git submodule update --init --recursive
cmake -B build -DCMAKE_PREFIX_PATH=/path/to/JUCE/install -DCMAKE_BUILD_TYPE=Release
cmake --build build
```
