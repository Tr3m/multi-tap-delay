#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Multitap_delayAudioProcessorEditor::Multitap_delayAudioProcessorEditor (Multitap_delayAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
   
    setSize (600, 430);

    int startX = 7;
    int startY = 100;
    int knobSize = 84;

    graphics.setColour (Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
    graphics.setColour (Slider::textBoxBackgroundColourId, juce::Colours::transparentBlack);
    graphics.setColour (Slider::textBoxTextColourId, juce::Colours::ivory.withAlpha(0.85f));
    graphics.setColour (Slider::textBoxTextColourId, juce::Colours::ivory);

    reverseKnobLNF.setColour (Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
    reverseKnobLNF.setColour (Slider::textBoxBackgroundColourId, juce::Colours::transparentBlack);
    reverseKnobLNF.setColour (Slider::textBoxTextColourId, juce::Colours::ivory.withAlpha(0.85f));
    reverseKnobLNF.setColour (Slider::textBoxTextColourId, juce::Colours::ivory);

    boxLNF.setColour(TextEditor::textColourId, Colours::ivory);
    boxLNF.setColour(TextEditor::backgroundColourId, Colours::transparentBlack);
    boxLNF.setColour(TextEditor::outlineColourId, Colours::transparentBlack);
    boxLNF.setColour(PopupMenu::backgroundColourId, Colours::grey.withAlpha(0.6f));
    boxLNF.setColour(ComboBox::backgroundColourId, Colours::darkgrey.withAlpha(0.0f));
    boxLNF.setColour(ComboBox::outlineColourId, Colours::grey.withAlpha(0.0f));
    boxLNF.setColour(ComboBox::textColourId, Colours::grey.withAlpha(0.0f));

    // Time and Feedback Knobs
    for(int knob = 1; knob <= NUM_DELAY_KNOBS; ++knob)
    {
        delayKnobs[knob - 1].reset(new juce::Slider("knob" + std::to_string(knob)));
        addAndMakeVisible(delayKnobs[knob - 1].get());
        delayKnobs[knob - 1]->setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
        delayKnobs[knob - 1]->setLookAndFeel(&graphics);
        delayKnobs[knob - 1]->addListener(this);

        if (knob % 2 != 0)
        {
            delayKnobs[knob - 1]->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
            delayKnobs[knob - 1]->setTextValueSuffix(" ms");
            delayKnobs[knob - 1]->setBounds(startX + (knob - 1) * 70, startY, knobSize + 15, knobSize + 15);

            timeTextBoxes[((knob + 1) / 2) - 1].reset(new juce::TextEditor("time" + std::to_string((knob + 1) / 2)));
            addAndMakeVisible(timeTextBoxes[((knob + 1) / 2) - 1].get());
            timeTextBoxes[((knob + 1) / 2) - 1]->setLookAndFeel(&boxLNF);
            timeTextBoxes[((knob + 1) / 2) - 1]->setReadOnly(true);
            timeTextBoxes[((knob + 1) / 2) - 1]->setText("1/16.");

            timeTextBoxes[((knob + 1) / 2) - 1]->setBounds(delayKnobs[knob - 1]->getX() + delayKnobs[knob - 1]->getWidth() - 7, 
                delayKnobs[knob - 1]->getY() + delayKnobs[knob - 1]->getHeight() / 2 - 20, 55, 18);

            timeComboBoxes[((knob + 1) / 2) - 1].reset (new juce::ComboBox ("combobox" + std::to_string((knob + 1) / 2)));
            addAndMakeVisible (timeComboBoxes[((knob + 1) / 2) - 1].get());
            timeComboBoxes[((knob + 1) / 2) - 1]->setEditableText (false);
            timeComboBoxes[((knob + 1) / 2) - 1]->setJustificationType (juce::Justification::centredLeft);
            timeComboBoxes[((knob + 1) / 2) - 1]->setTextWhenNothingSelected (TRANS("-"));
            timeComboBoxes[((knob + 1) / 2) - 1]->addItem (TRANS("1/4"), 1);
            timeComboBoxes[((knob + 1) / 2) - 1]->addItem (TRANS("1/4."), 2);
            timeComboBoxes[((knob + 1) / 2) - 1]->addItem (TRANS("1/8"), 3);
            timeComboBoxes[((knob + 1) / 2) - 1]->addItem (TRANS("1/8."), 4);
            timeComboBoxes[((knob + 1) / 2) - 1]->setLookAndFeel(&boxLNF);    
            timeComboBoxes[((knob + 1) / 2) - 1]->addListener(this);
            timeComboBoxes[((knob + 1) / 2) - 1]->setAlpha(0.7f);
            
            timeComboBoxes[((knob + 1) / 2) - 1]->setBounds(timeTextBoxes[((knob + 1) / 2) - 1]->getX(), 
                timeTextBoxes[((knob + 1) / 2) - 1]->getY(), timeTextBoxes[((knob + 1) / 2) - 1]->getWidth() + 8, 
                    timeTextBoxes[((knob + 1) / 2) - 1]->getHeight());
        }
        else
        {
            delayKnobs[knob - 1]->setTextBoxStyle(juce::Slider::NoTextBox, false, 70, 20);
            delayKnobs[knob - 1]->setPopupDisplayEnabled(true, true, getTopLevelComponent());
            delayKnobs[knob - 1]->setBounds(delayKnobs[knob - 2]->getX() + delayKnobs[knob - 2]->getWidth() - 2,
                 startY + 60, knobSize - 40, knobSize - 42);
        }
        
    } 

    // Attach paramters for Time and Feedback
    for(int knob = 1; knob <= NUM_DELAY_KNOBS; ++knob)
    {
        if (knob % 2 != 0)
        {
            delayKnobAttachments[knob - 1] = std::make_unique<juce::AudioProcessorValueTreeState::
                SliderAttachment>(audioProcessor.apvts, "DELAY_TIME_" + std::to_string((knob + 1) / 2) + "_ID", *delayKnobs[knob - 1]);
        }
        else
        {
            delayKnobAttachments[knob - 1] = std::make_unique<juce::AudioProcessorValueTreeState::
                SliderAttachment>(audioProcessor.apvts, "FEEDBACK_" + std::to_string(knob / 2) + "_ID", *delayKnobs[knob - 1]);
        }
    }

    // BPM TextBox
    bpmTextBox.reset(new juce::TextEditor("BPM_BOX"));
    addAndMakeVisible(bpmTextBox.get());
    bpmTextBox->setLookAndFeel(&boxLNF);
    bpmTextBox->setText(std::to_string(audioProcessor.getBPM()));
    bpmTextBox->setColour(TextEditor::textColourId, Colours::ivory);
    bpmTextBox->setColour(TextEditor::backgroundColourId, Colours::transparentBlack);
    bpmTextBox->setColour(TextEditor::outlineColourId, Colours::white.withAlpha(0.35f));
    bpmTextBox->addListener(this);
    bpmTextBox->setInputRestrictions(3, "0123456789");
    bpmTextBox->onReturnKey = [this]
    {
        audioProcessor.setBPM(bpmTextBox->getText().getIntValue());
        recalculateDelayTimes();
    };

    bpmTextBox->setBounds(40, 3, 50, 20);

    // Detune Knobs
    for(int dtknob = 0; dtknob < 4; ++dtknob)
    {
        detuneKnobs[dtknob].reset(new juce::Slider("dtknob" + std::to_string(dtknob)));
        addAndMakeVisible(detuneKnobs[dtknob].get());
        detuneKnobs[dtknob]->setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
        detuneKnobs[dtknob]->setLookAndFeel(&graphics);
        detuneKnobs[dtknob]->setTextBoxStyle(juce::Slider::TextBoxRight, false, 55, 20);
        detuneKnobs[dtknob]->setTextValueSuffix(" ct");
        detuneKnobAttachments[dtknob] = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, 
            "DETUNE_" + std::to_string(dtknob + 1) + "_ID", *detuneKnobs[dtknob]);
    }

    detuneKnobs[0]->setBounds(14, 281, knobSize + 32, knobSize - 30);
    detuneKnobs[1]->setBounds(detuneKnobs[0]->getX() + detuneKnobs[0]->getWidth() + 15, detuneKnobs[0]->getY(), knobSize + 32, knobSize - 30);
    detuneKnobs[2]->setBounds(65, 342, knobSize + 32, knobSize - 30);
    detuneKnobs[3]->setBounds(detuneKnobs[2]->getX() + detuneKnobs[2]->getWidth() + 15, detuneKnobs[2]->getY(), knobSize + 32, knobSize - 30);

    // Mix and Filter Knobs
    for(int knob = 0; knob < 3; ++knob)
    {
        filterKnobs[knob].reset(new juce::Slider("filterKnob" + std::to_string(knob)));
        addAndMakeVisible(filterKnobs[knob].get());
        filterKnobs[knob]->setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
        filterKnobs[knob]->setLookAndFeel(&graphics);
        filterKnobs[knob]->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
        if(knob > 1)
            filterKnobs[knob]->setTextValueSuffix(" %");
        else
            filterKnobs[knob]->setTextValueSuffix(" Hz");

        filterKnobs[knob]->setBounds(delayKnobs[KnobsP1::Time3]->getX() + 35 + (knob * 90), startY + 189, knobSize + 15, knobSize + 15);        
    }

    filterKnobs[1]->setLookAndFeel(&reverseKnobLNF);

    filterKnobAttachments[0] = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, 
        "LOWCUT_ID", *filterKnobs[0]);
    
    filterKnobAttachments[1] = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, 
        "HIGHCUT_ID", *filterKnobs[1]);

    filterKnobAttachments[2] = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, 
        "MIX_ID", *filterKnobs[2]);
}

Multitap_delayAudioProcessorEditor::~Multitap_delayAudioProcessorEditor()
{
    for(int att = 0; att < NUM_DELAY_KNOBS; ++att)
        delayKnobAttachments[att] = nullptr;

    for(int dtknob = 0; dtknob < 3; ++dtknob)
        detuneKnobAttachments[dtknob] = nullptr;

    for(int dtknob = 0; dtknob < 2; ++dtknob)
        filterKnobAttachments[dtknob] = nullptr;
}

//==============================================================================
void Multitap_delayAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.drawImageAt(graphics.getBackground(), 0, 0);
    g.drawImageAt(screensImage, 0, 0);

    labelFont.setBold(false);
    labelFont.setStyleFlags(juce::Font::FontStyleFlags::plain);
    g.setFont(labelFont);
    labelFont.setHeight(14);

    g.setColour(juce::Colours::ivory);
    g.drawFittedText("BPM", bpmTextBox->getBounds().withHeight(24).translated(-bpmTextBox->getWidth() + 3, -1), Justification::centred, 1);  

    labelFont.setHeight(14);
    g.setFont(labelFont); 

    g.drawFittedText("LOW-CUT", filterKnobs[0]->getBounds().withHeight(24).translated(-1, -27), Justification::centred, 1);
    g.drawFittedText("HIGH-CUT", filterKnobs[1]->getBounds().withHeight(24).translated(-1, -27), Justification::centred, 1);
    g.drawFittedText("MIX", filterKnobs[2]->getBounds().withHeight(24).translated(-1, -27), Justification::centred, 1);

    for(int knob = 1; knob <= NUM_DELAY_KNOBS; ++knob)
    {
        if (knob % 2 != 0)
        {
            labelFont.setHeight(16);
            g.setFont(labelFont); 
            g.drawFittedText("TIME " + std::to_string((knob + 1) / 2), delayKnobs[knob - 1]->getBounds().withHeight(24).translated(-1, -27), Justification::centred, 1);
        }
            
        else
        {
            labelFont.setHeight(12);
            g.setFont(labelFont); 
            g.drawFittedText("FDBK " + std::to_string(knob / 2), delayKnobs[knob - 1]->getBounds().withHeight(24).translated(0, 40), Justification::centred, 1);
        }
    }

    labelFont.setHeight(11);
    g.setFont(labelFont);   

    for(int knob = 1; knob <= 4; ++knob)
        g.drawFittedText("DETUNE  " + std::to_string(knob), detuneKnobs[knob - 1]->getBounds().withHeight(7).translated(21, 2), Justification::centred, 1);
     
}

void Multitap_delayAudioProcessorEditor::resized()
{
    
   
}

void Multitap_delayAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{    
    if(slider == delayKnobs[KnobsP1::Time1].get())
    {
        timeTextBoxes[TextBoxesP1::TextBox1]->setText(getTimeByValue(slider->getValue()));
        timeComboBoxes[TextBoxesP1::TextBox1]->setSelectedItemIndex(-1, juce::NotificationType::sendNotification);
    }
    else if (slider == delayKnobs[KnobsP1::Time2].get())
    {
        timeTextBoxes[TextBoxesP1::TextBox2]->setText(getTimeByValue(slider->getValue()));
        timeComboBoxes[TextBoxesP1::TextBox2]->setSelectedItemIndex(-1, juce::NotificationType::sendNotification);
    }
    else if (slider == delayKnobs[KnobsP1::Time3].get())
    {
        timeTextBoxes[TextBoxesP1::TextBox3]->setText(getTimeByValue(slider->getValue()));
        timeComboBoxes[TextBoxesP1::TextBox3]->setSelectedItemIndex(-1, juce::NotificationType::sendNotification);
    }
    else if (slider == delayKnobs[KnobsP1::Time4].get())
    {
        timeTextBoxes[TextBoxesP1::TextBox4]->setText(getTimeByValue(slider->getValue()));
        timeComboBoxes[TextBoxesP1::TextBox4]->setSelectedItemIndex(-1, juce::NotificationType::sendNotification);
    }
}

void Multitap_delayAudioProcessorEditor::comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged)
{
    if(comboBoxThatHasChanged->getSelectedItemIndex() != -1)
    {
        if(comboBoxThatHasChanged == timeComboBoxes[TextBoxesP1::TextBox1].get())
        {
            delayKnobs[KnobsP1::Time1]->setValue(getTimeBySelection(comboBoxThatHasChanged->getSelectedItemIndex()), juce::NotificationType::sendNotificationSync);
        }
        else if(comboBoxThatHasChanged == timeComboBoxes[TextBoxesP1::TextBox2].get())
        {
            delayKnobs[KnobsP1::Time2]->setValue(getTimeBySelection(comboBoxThatHasChanged->getSelectedItemIndex()), juce::NotificationType::sendNotificationSync);
        }
        else if(comboBoxThatHasChanged == timeComboBoxes[TextBoxesP1::TextBox3].get())
        {
            delayKnobs[KnobsP1::Time3]->setValue(getTimeBySelection(comboBoxThatHasChanged->getSelectedItemIndex()), juce::NotificationType::sendNotificationSync);
        }
        else if(comboBoxThatHasChanged == timeComboBoxes[TextBoxesP1::TextBox4].get())
        {
            delayKnobs[KnobsP1::Time4]->setValue(getTimeBySelection(comboBoxThatHasChanged->getSelectedItemIndex()), juce::NotificationType::sendNotificationSync);
        }
    }
}

juce::String Multitap_delayAudioProcessorEditor::getTimeByValue(int delayMs)
{
    int quarterMs = 60000 / audioProcessor.getBPM();

    if(delayMs == quarterMs)
        return "1/4";
    else if (delayMs == quarterMs + quarterMs / 2)
        return "1/4.";
    else if (delayMs == quarterMs / 2)
        return "1/8";
    else if(delayMs == quarterMs / 2 + quarterMs / 4)
        return "1/8.";
    else
        return "-";

}

int Multitap_delayAudioProcessorEditor::getTimeBySelection(int comboBoxIndex)
{

    // Calculate based on BPM
    int quarterMs = 60000 / audioProcessor.getBPM();

    switch(comboBoxIndex)
    {
    case TimeDivisions::Quarter:
        return quarterMs;
        break;
    case TimeDivisions::QuarterDotted:
        return quarterMs + quarterMs / 2;
        break;
    case TimeDivisions::Eighth: 
        return quarterMs / 2;
        break;
    case TimeDivisions::EigthDotted:
        return quarterMs / 2 + quarterMs / 4;
        break;
    }
}

void Multitap_delayAudioProcessorEditor::recalculateDelayTimes()
{
    int quarterMs = 60000 / audioProcessor.getBPM();

    for(int delay = 0; delay < 3; ++delay)
    {
        auto timeDiv = timeTextBoxes[delay]->getText();

        if(timeDiv == "1/4")
            delayKnobs[2*delay]->setValue(quarterMs, juce::NotificationType::sendNotification);
        else if(timeDiv == "1/4.")
            delayKnobs[2*delay]->setValue(quarterMs + quarterMs / 2, juce::NotificationType::sendNotification);
        else if(timeDiv == "1/8")
            delayKnobs[2*delay]->setValue(quarterMs / 2, juce::NotificationType::sendNotification);
        else if(timeDiv == "1/8.")
            delayKnobs[2*delay]->setValue(quarterMs / 2 + quarterMs / 4, juce::NotificationType::sendNotification);
    }
}

void Multitap_delayAudioProcessorEditor::textEditorTextChanged (TextEditor& textEditor)
{

}