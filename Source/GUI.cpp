/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.0.4

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "GUI.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
GUI::GUI ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    timeSlider.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (timeSlider.get());
    timeSlider->setRange (0, 2, 0.001);
    timeSlider->setSliderStyle (juce::Slider::Rotary);
    timeSlider->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    timeSlider->addListener (this);

    timeSlider->setBounds (31, 56, 160, 112);

    feedbackSlider.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (feedbackSlider.get());
    feedbackSlider->setRange (0, 1, 0.01);
    feedbackSlider->setSliderStyle (juce::Slider::Rotary);
    feedbackSlider->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    feedbackSlider->addListener (this);

    feedbackSlider->setBounds (189, 56, 160, 112);

    juce__label.reset (new juce::Label ("new label",
                                        TRANS("Time\n")));
    addAndMakeVisible (juce__label.get());
    juce__label->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label->setJustificationType (juce::Justification::centredLeft);
    juce__label->setEditable (false, false, false);
    juce__label->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label->setBounds (87, 32, 48, 24);

    juce__label2.reset (new juce::Label ("new label",
                                         TRANS("Feedback")));
    addAndMakeVisible (juce__label2.get());
    juce__label2->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label2->setJustificationType (juce::Justification::centredLeft);
    juce__label2->setEditable (false, false, false);
    juce__label2->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label2->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label2->setBounds (235, 32, 72, 24);

    detune1Sluder.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (detune1Sluder.get());
    detune1Sluder->setRange (-50, 50, 1);
    detune1Sluder->setSliderStyle (juce::Slider::Rotary);
    detune1Sluder->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    detune1Sluder->addListener (this);

    detune1Sluder->setBounds (31, 248, 160, 112);

    juce__label3.reset (new juce::Label ("new label",
                                         TRANS("Delay 1 Detune\n")));
    addAndMakeVisible (juce__label3.get());
    juce__label3->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label3->setJustificationType (juce::Justification::centredLeft);
    juce__label3->setEditable (false, false, false);
    juce__label3->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label3->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label3->setBounds (81, 218, 72, 24);

    detune2Sluder.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (detune2Sluder.get());
    detune2Sluder->setRange (-50, 50, 1);
    detune2Sluder->setSliderStyle (juce::Slider::Rotary);
    detune2Sluder->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    detune2Sluder->addListener (this);

    detune2Sluder->setBounds (189, 248, 160, 112);

    juce__label4.reset (new juce::Label ("new label",
                                         TRANS("Delay 2 Detune\n")));
    addAndMakeVisible (juce__label4.get());
    juce__label4->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label4->setJustificationType (juce::Justification::centredLeft);
    juce__label4->setEditable (false, false, false);
    juce__label4->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label4->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label4->setBounds (239, 218, 72, 24);

    detune3Sluder.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (detune3Sluder.get());
    detune3Sluder->setRange (-50, 50, 1);
    detune3Sluder->setSliderStyle (juce::Slider::Rotary);
    detune3Sluder->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    detune3Sluder->addListener (this);

    detune3Sluder->setBounds (348, 248, 160, 112);

    juce__label5.reset (new juce::Label ("new label",
                                         TRANS("Delay 3 Detune\n")));
    addAndMakeVisible (juce__label5.get());
    juce__label5->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label5->setJustificationType (juce::Justification::centredLeft);
    juce__label5->setEditable (false, false, false);
    juce__label5->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label5->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label5->setBounds (398, 218, 72, 24);

    detune4Sluder.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (detune4Sluder.get());
    detune4Sluder->setRange (-50, 50, 1);
    detune4Sluder->setSliderStyle (juce::Slider::Rotary);
    detune4Sluder->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    detune4Sluder->addListener (this);

    detune4Sluder->setBounds (506, 248, 160, 112);

    juce__label6.reset (new juce::Label ("new label",
                                         TRANS("Delay 4 Detune\n")));
    addAndMakeVisible (juce__label6.get());
    juce__label6->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label6->setJustificationType (juce::Justification::centredLeft);
    juce__label6->setEditable (false, false, false);
    juce__label6->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label6->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label6->setBounds (556, 218, 72, 24);

    toneSlider.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (toneSlider.get());
    toneSlider->setRange (0, 2, 0.001);
    toneSlider->setSliderStyle (juce::Slider::Rotary);
    toneSlider->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    toneSlider->addListener (this);

    toneSlider->setBounds (348, 56, 160, 112);

    mixSlider.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (mixSlider.get());
    mixSlider->setRange (0, 1, 0.01);
    mixSlider->setSliderStyle (juce::Slider::Rotary);
    mixSlider->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    mixSlider->addListener (this);

    mixSlider->setBounds (506, 56, 160, 112);

    juce__label7.reset (new juce::Label ("new label",
                                         TRANS("Tone")));
    addAndMakeVisible (juce__label7.get());
    juce__label7->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label7->setJustificationType (juce::Justification::centredLeft);
    juce__label7->setEditable (false, false, false);
    juce__label7->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label7->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label7->setBounds (404, 32, 48, 24);

    juce__label8.reset (new juce::Label ("new label",
                                         TRANS("Mix")));
    addAndMakeVisible (juce__label8.get());
    juce__label8->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label8->setJustificationType (juce::Justification::centredLeft);
    juce__label8->setEditable (false, false, false);
    juce__label8->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label8->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label8->setBounds (570, 32, 72, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (990, 560);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

GUI::~GUI()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    timeSlider = nullptr;
    feedbackSlider = nullptr;
    juce__label = nullptr;
    juce__label2 = nullptr;
    detune1Sluder = nullptr;
    
    juce__label3 = nullptr;
    detune2Sluder = nullptr;
    juce__label4 = nullptr;
    detune3Sluder = nullptr;
    juce__label5 = nullptr;
    detune4Sluder = nullptr;
    juce__label6 = nullptr;
    toneSlider = nullptr;
    mixSlider = nullptr;
    juce__label7 = nullptr;
    juce__label8 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void GUI::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void GUI::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void GUI::sliderValueChanged (juce::Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == timeSlider.get())
    {
        //[UserSliderCode_timeSlider] -- add your slider handling code here..
        //[/UserSliderCode_timeSlider]
    }
    else if (sliderThatWasMoved == feedbackSlider.get())
    {
        //[UserSliderCode_feedbackSlider] -- add your slider handling code here..
        //[/UserSliderCode_feedbackSlider]
    }
    else if (sliderThatWasMoved == detune1Sluder.get())
    {
        //[UserSliderCode_detune1Sluder] -- add your slider handling code here..
        //[/UserSliderCode_detune1Sluder]
    }
    else if (sliderThatWasMoved == detune2Sluder.get())
    {
        //[UserSliderCode_detune2Sluder] -- add your slider handling code here..
        //[/UserSliderCode_detune2Sluder]
    }
    else if (sliderThatWasMoved == detune3Sluder.get())
    {
        //[UserSliderCode_detune3Sluder] -- add your slider handling code here..
        //[/UserSliderCode_detune3Sluder]
    }
    else if (sliderThatWasMoved == detune4Sluder.get())
    {
        //[UserSliderCode_detune4Sluder] -- add your slider handling code here..
        //[/UserSliderCode_detune4Sluder]
    }
    else if (sliderThatWasMoved == toneSlider.get())
    {
        //[UserSliderCode_toneSlider] -- add your slider handling code here..
        //[/UserSliderCode_toneSlider]
    }
    else if (sliderThatWasMoved == mixSlider.get())
    {
        //[UserSliderCode_mixSlider] -- add your slider handling code here..
        //[/UserSliderCode_mixSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="GUI" componentName="" parentClasses="public juce::Component"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="990"
                 initialHeight="560">
  <BACKGROUND backgroundColour="ff323e44"/>
  <SLIDER name="new slider" id="88f85530cefa2473" memberName="timeSlider"
          virtualName="" explicitFocusOrder="0" pos="31 56 160 112" min="0.0"
          max="2.0" int="0.001" style="Rotary" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="new slider" id="7e82ff243d85f553" memberName="feedbackSlider"
          virtualName="" explicitFocusOrder="0" pos="189 56 160 112" min="0.0"
          max="1.0" int="0.01" style="Rotary" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="new label" id="feffdc090ee64bfe" memberName="juce__label"
         virtualName="" explicitFocusOrder="0" pos="87 32 48 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Time&#10;" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="2abba5840f922987" memberName="juce__label2"
         virtualName="" explicitFocusOrder="0" pos="235 32 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Feedback" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="4b834392d22c768c" memberName="detune1Sluder"
          virtualName="" explicitFocusOrder="0" pos="31 248 160 112" min="-50.0"
          max="50.0" int="1.0" style="Rotary" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="new label" id="7eb4c5baae0e528d" memberName="juce__label3"
         virtualName="" explicitFocusOrder="0" pos="81 218 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Delay 1 Detune&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="fed6ce7383dead4c" memberName="detune2Sluder"
          virtualName="" explicitFocusOrder="0" pos="189 248 160 112" min="-50.0"
          max="50.0" int="1.0" style="Rotary" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="new label" id="e944b738ca30b2bc" memberName="juce__label4"
         virtualName="" explicitFocusOrder="0" pos="239 218 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Delay 2 Detune&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="3d3239fa12147977" memberName="detune3Sluder"
          virtualName="" explicitFocusOrder="0" pos="348 248 160 112" min="-50.0"
          max="50.0" int="1.0" style="Rotary" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="new label" id="df0291087626cf16" memberName="juce__label5"
         virtualName="" explicitFocusOrder="0" pos="398 218 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Delay 3 Detune&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="22988227edee0d7a" memberName="detune4Sluder"
          virtualName="" explicitFocusOrder="0" pos="506 248 160 112" min="-50.0"
          max="50.0" int="1.0" style="Rotary" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="new label" id="951cc0f16141b69" memberName="juce__label6"
         virtualName="" explicitFocusOrder="0" pos="556 218 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Delay 4 Detune&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="723fd7792b0141c5" memberName="toneSlider"
          virtualName="" explicitFocusOrder="0" pos="348 56 160 112" min="0.0"
          max="2.0" int="0.001" style="Rotary" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="new slider" id="4cdd89d9ee2e2eb" memberName="mixSlider"
          virtualName="" explicitFocusOrder="0" pos="506 56 160 112" min="0.0"
          max="1.0" int="0.01" style="Rotary" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="new label" id="c2919ce1e8c01fb" memberName="juce__label7"
         virtualName="" explicitFocusOrder="0" pos="404 32 48 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Tone" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="b4d6debbed254192" memberName="juce__label8"
         virtualName="" explicitFocusOrder="0" pos="570 32 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Mix" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

