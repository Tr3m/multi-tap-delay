#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Multitap_delayAudioProcessorEditor::Multitap_delayAudioProcessorEditor (Multitap_delayAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
   
    setSize (600, 430);

    int startX = 7;
    int startY = 120;
    int knobSize = 84;

    graphics.setColour (Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
    graphics.setColour (Slider::textBoxBackgroundColourId, juce::Colours::transparentBlack);
    graphics.setColour (Slider::textBoxTextColourId, juce::Colours::ivory.withAlpha(0.85f));
    graphics.setColour (Slider::textBoxTextColourId, juce::Colours::hotpink);

    boxLNF.setColour(TextEditor::textColourId, Colours::hotpink);
    boxLNF.setColour(TextEditor::backgroundColourId, Colours::transparentBlack);
    boxLNF.setColour(TextEditor::outlineColourId, Colours::transparentBlack);
    boxLNF.setColour(PopupMenu::backgroundColourId, Colours::grey.withAlpha(0.6f));
    boxLNF.setColour(ComboBox::backgroundColourId, Colours::darkgrey.withAlpha(0.0f));
    boxLNF.setColour(ComboBox::outlineColourId, Colours::grey.withAlpha(0.0f));
    boxLNF.setColour(ComboBox::textColourId, Colours::grey.withAlpha(0.0f));

    //tooltipWindow.setLookAndFeel(&graphics);

    for(int knob = 1; knob <= PAGE_ONE_KNOBS; ++knob)
    {
        page1Knobs[knob - 1].reset(new juce::Slider("knob" + std::to_string(knob)));
        addAndMakeVisible(page1Knobs[knob - 1].get());
        page1Knobs[knob - 1]->setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
        page1Knobs[knob - 1]->setLookAndFeel(&graphics);
        page1Knobs[knob - 1]->addListener(this);

        if (knob % 2 != 0)
        {
            page1Knobs[knob - 1]->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
            page1Knobs[knob - 1]->setTextValueSuffix(" ms");
            page1Knobs[knob - 1]->setBounds(startX + (knob - 1) * 70, startY, knobSize + 15, knobSize + 15);

            //page1Attachments[knob - 1] = std::make_unique<juce::AudioProcessorValueTreeState::
            //    SliderAttachment>(audioProcessor.apvts, "DELAY_TIME_" + std::to_string((knob + 1) / 2) + "_ID", *page1Knobs[knob - 1]);

            timeTextBoxes[((knob + 1) / 2) - 1].reset(new juce::TextEditor("time" + std::to_string((knob + 1) / 2)));
            addAndMakeVisible(timeTextBoxes[((knob + 1) / 2) - 1].get());
            timeTextBoxes[((knob + 1) / 2) - 1]->setLookAndFeel(&boxLNF);
            timeTextBoxes[((knob + 1) / 2) - 1]->setReadOnly(true);
            timeTextBoxes[((knob + 1) / 2) - 1]->setText("1/16.");

            timeTextBoxes[((knob + 1) / 2) - 1]->setBounds(page1Knobs[knob - 1]->getX() + page1Knobs[knob - 1]->getWidth() - 7, 
                page1Knobs[knob - 1]->getY() + page1Knobs[knob - 1]->getHeight() / 2 - 20, 55, 18);

            timeComboBoxes[((knob + 1) / 2) - 1].reset (new juce::ComboBox ("combobox" + std::to_string((knob + 1) / 2)));
            addAndMakeVisible (timeComboBoxes[((knob + 1) / 2) - 1].get());
            timeComboBoxes[((knob + 1) / 2) - 1]->setEditableText (false);
            timeComboBoxes[((knob + 1) / 2) - 1]->setJustificationType (juce::Justification::centredLeft);
            timeComboBoxes[((knob + 1) / 2) - 1]->setTextWhenNothingSelected (TRANS("-"));
            //timeComboBoxes[((knob + 1) / 2) - 1]->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
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
            page1Knobs[knob - 1]->setTextBoxStyle(juce::Slider::NoTextBox, false, 70, 20);
            page1Knobs[knob - 1]->setPopupDisplayEnabled(true, true, getTopLevelComponent());
            page1Knobs[knob - 1]->setBounds(page1Knobs[knob - 2]->getX() + page1Knobs[knob - 2]->getWidth() - 11,
                 startY + 110, knobSize - 20, knobSize - 22); //y +70

            //page1Attachments[knob - 1] = std::make_unique<juce::AudioProcessorValueTreeState::
            //    SliderAttachment>(audioProcessor.apvts, "FEEDBACK_" + std::to_string(knob / 2) + "_ID", *page1Knobs[knob - 1]);
        }
        
    } 

    // Attach paramters
    for(int knob = 1; knob <= PAGE_ONE_KNOBS; ++knob)
    {
        if (knob % 2 != 0)
        {
            page1Attachments[knob - 1] = std::make_unique<juce::AudioProcessorValueTreeState::
                SliderAttachment>(audioProcessor.apvts, "DELAY_TIME_" + std::to_string((knob + 1) / 2) + "_ID", *page1Knobs[knob - 1]);
        }
        else
        {
            page1Attachments[knob - 1] = std::make_unique<juce::AudioProcessorValueTreeState::
                SliderAttachment>(audioProcessor.apvts, "FEEDBACK_" + std::to_string(knob / 2) + "_ID", *page1Knobs[knob - 1]);
        }
    }

    bpmTextBox.reset(new juce::TextEditor("BPM_BOX"));
    addAndMakeVisible(bpmTextBox.get());
    bpmTextBox->setLookAndFeel(&boxLNF);
    bpmTextBox->setText(std::to_string(audioProcessor.getBPM()));
    bpmTextBox->setColour(TextEditor::textColourId, Colours::hotpink);
    bpmTextBox->setColour(TextEditor::backgroundColourId, Colours::transparentBlack);
    bpmTextBox->setColour(TextEditor::outlineColourId, Colours::white.withAlpha(0.55f));
    bpmTextBox->addListener(this);
    bpmTextBox->setInputRestrictions(3, "0123456789");
    bpmTextBox->onReturnKey = [this]
    {
        audioProcessor.setBPM(bpmTextBox->getText().getIntValue());
    };

    bpmTextBox->setBounds(40, 3, 50, 20);

}

Multitap_delayAudioProcessorEditor::~Multitap_delayAudioProcessorEditor()
{
    for(int att = 0; att < PAGE_ONE_KNOBS; ++att)
        page1Attachments[att] = nullptr;
}

//==============================================================================
void Multitap_delayAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.drawImageAt(graphics.getBackground(), 0, 0);
    g.drawImageAt(screensImage, 0, 0);

    g.setColour(juce::Colours::ivory);
    g.drawFittedText("BPM", bpmTextBox->getBounds().withHeight(24).translated(-bpmTextBox->getWidth() + 2, -1), Justification::centred, 1);
}

void Multitap_delayAudioProcessorEditor::resized()
{
    
   
}

void Multitap_delayAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{    
    if(slider == page1Knobs[KnobsP1::Time1].get())
    {
        timeTextBoxes[TextBoxesP1::TextBox1]->setText(getTimeByValue(slider->getValue()));
        timeComboBoxes[TextBoxesP1::TextBox1]->setSelectedItemIndex(-1, juce::NotificationType::sendNotification);
    }
    else if (slider == page1Knobs[KnobsP1::Time2].get())
    {
        timeTextBoxes[TextBoxesP1::TextBox2]->setText(getTimeByValue(slider->getValue()));
        timeComboBoxes[TextBoxesP1::TextBox2]->setSelectedItemIndex(-1, juce::NotificationType::sendNotification);
    }
    else if (slider == page1Knobs[KnobsP1::Time3].get())
    {
        timeTextBoxes[TextBoxesP1::TextBox3]->setText(getTimeByValue(slider->getValue()));
        timeComboBoxes[TextBoxesP1::TextBox3]->setSelectedItemIndex(-1, juce::NotificationType::sendNotification);
    }
    else if (slider == page1Knobs[KnobsP1::Time4].get())
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
            page1Knobs[KnobsP1::Time1]->setValue(getTimeBySelection(comboBoxThatHasChanged->getSelectedItemIndex()), juce::NotificationType::sendNotificationSync);
        }
        else if(comboBoxThatHasChanged == timeComboBoxes[TextBoxesP1::TextBox2].get())
        {
            page1Knobs[KnobsP1::Time2]->setValue(getTimeBySelection(comboBoxThatHasChanged->getSelectedItemIndex()), juce::NotificationType::sendNotificationSync);
        }
        else if(comboBoxThatHasChanged == timeComboBoxes[TextBoxesP1::TextBox3].get())
        {
            page1Knobs[KnobsP1::Time3]->setValue(getTimeBySelection(comboBoxThatHasChanged->getSelectedItemIndex()), juce::NotificationType::sendNotificationSync);
        }
        else if(comboBoxThatHasChanged == timeComboBoxes[TextBoxesP1::TextBox4].get())
        {
            page1Knobs[KnobsP1::Time4]->setValue(getTimeBySelection(comboBoxThatHasChanged->getSelectedItemIndex()), juce::NotificationType::sendNotificationSync);
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

void Multitap_delayAudioProcessorEditor::textEditorTextChanged (TextEditor& textEditor)
{

}