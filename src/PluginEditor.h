#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include <GUIGraphics.h>

#define PAGE_ONE_KNOBS 8

//==============================================================================
/**
*/
class Multitap_delayAudioProcessorEditor  : public juce::AudioProcessorEditor, 
                                            public juce::Slider::Listener,
                                            public juce::ComboBox::Listener,
                                            public juce::TextEditor::Listener
{
public:
    Multitap_delayAudioProcessorEditor (Multitap_delayAudioProcessor&);
    ~Multitap_delayAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(juce::Slider* slider) override;
    void comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged) override;
    void textEditorTextChanged (TextEditor& textEditor) override;

    juce::String getTimeByValue(int delayMs);
    int getTimeBySelection(int comboBoxIndex);
    void recalculateDelayTimes();

    enum KnobsP1
    {
      Time1 = 0,
      Fbk1,
      Time2,
      Fbk2,
      Time3,
      Fbk3,
      Time4,
      Fbk4
    };

    enum TextBoxesP1
    {
      TextBox1 = 0,
      TextBox2,
      TextBox3,
      TextBox4
    };

    enum TimeDivisions
    {
      Quarter = 0,
      QuarterDotted,
      Eighth,
      EigthDotted      
    };

private:
    
    std::unique_ptr<juce::Slider> page1Knobs[PAGE_ONE_KNOBS];
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> page1Attachments[PAGE_ONE_KNOBS];

    std::unique_ptr<juce::ComboBox> timeComboBoxes[4];
    std::unique_ptr<juce::TextEditor> timeTextBoxes[4];

    std::unique_ptr<juce::TextEditor> bpmTextBox;

    juce::TooltipWindow tooltipWindow{ this, 200 };

    juce::Image screensImage = juce::ImageFileFormat::loadFrom(BinaryData::labels1_png, BinaryData::labels1_pngSize);

    GUIGraphics graphics;
    juce::LookAndFeel_V4 boxLNF;

    juce::Font labelFont{Font{juce::Typeface::createSystemTypefaceFor(BinaryData::varelaround_regular_ttf, BinaryData::varelaround_regular_ttfSize)}};

    Multitap_delayAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Multitap_delayAudioProcessorEditor)
};
