# Overview

This repository contains the code for a digital delay VST plugin. This multi-tap delay utilizes four delay lines to create a rhythmic pattern with the repeats.

<p align="center">
  <img width="600" height="430" src="https://user-images.githubusercontent.com/58518865/121102697-f1fa3e00-c806-11eb-8404-15501d55cf0e.png">
</p>

### Controls

  * Time
    * The Time knob controls the second delay unit's delay length (Which is the shortest of the four). The tempos of the delay units are as follows:
      * Delay 1: Quarter Note (1/4).
      * Delay 2: Eighth Note (1/8).
      * Delay 3: Dotted Eighth.
      * Delay 4: Dotted Quarter.
  * Feedback
    * The Feedback knob controls the amount of the output that's fed back into the delay input. It as shared across all four delay units.
  * Tone
    * Just a Low-Pass Filter.
  * Mix
    * A unified WET/DRY Control.
  * The Detune Knobs
    * The detune knobs can change the pitch of the repeats up to plus or minus of 50 cents.


### Requirements -  Third Party Libraries

* The JUCE C++ framework is required in order to build this plug-in. It can be downloaded from the
[JUCE GitHub repository](https://github.com/juce-framework/JUCE) or the [JUCE Website](https://juce.com/get-juce/download)
<br><br />

* The SoundTouch library is also required to compile the Pitch modules. It can be downloaded from the
[Soundtouch GitLab Repo](https://gitlab.com/soundtouch/soundtouch).

### Building the Plug-in
1. Open with the Projucer application the file with the ".jucer" extension in the root directory of the plug-in you want to build.

2. In the exporters tab, add the exporter of your choice based on your OS.

3. The soundtouch source files need to be included in the header search paths.

3. Click the "Save and open in IDE" button on the top right to open the project. (Projucer will auto generate the appropriate library files).
