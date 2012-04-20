#include "SFZeroEditor.h"
#include "SFZeroAudioProcessor.h"


SFZeroEditor::SFZeroEditor(SFZeroAudioProcessor* ownerFilter)
	: AudioProcessorEditor(ownerFilter),
		fileLabel(String::empty, "File..."),
		pathLabel(String::empty),
		midiKeyboard(ownerFilter->keyboardState, MidiKeyboardComponent::horizontalKeyboard)
{
	setSize(500, 300);

	addAndMakeVisible(&fileLabel);
	fileLabel.setFont(Font(18.0, Font::bold));
	fileLabel.setColour(Label::textColourId, Colours::grey);
	fileLabel.addClickListener(this);

	addAndMakeVisible(&pathLabel);
	pathLabel.setFont(Font(14.0));

	addAndMakeVisible(&infoLabel);
	infoLabel.setFont(Font(14.0));

	addAndMakeVisible(&midiKeyboard);

	startTimer(200);

	File sfzFile = ownerFilter->getSfzFile();
	if (sfzFile != File::nonexistent)
		updateFile(&sfzFile);
}


SFZeroEditor::~SFZeroEditor()
{
}


void SFZeroEditor::paint(Graphics& g)
{
	g.fillAll(Colours::white);
}


void SFZeroEditor::resized()
{
	enum {
		hMargin = 10,
		vMargin = 10,
		buttonHeight = 25,
		labelHeight = 25,
		keyboardHeight = 70,
		};
	int marginedWidth = getWidth() - 2 * hMargin;

	fileLabel.setBounds(
		hMargin, vMargin, marginedWidth, labelHeight);
	pathLabel.setBounds(
		hMargin, vMargin + buttonHeight, marginedWidth, labelHeight);
	infoLabel.setBounds(
		hMargin, vMargin + buttonHeight + labelHeight,
		marginedWidth, labelHeight);
	midiKeyboard.setBounds(
		hMargin, getHeight() - keyboardHeight - vMargin,
		marginedWidth, keyboardHeight);
}


void SFZeroEditor::labelClicked(Label* clickedLabel)
{
	if (clickedLabel == &fileLabel)
		chooseFile();
}


void SFZeroEditor::timerCallback()
{
}


void SFZeroEditor::chooseFile()
{
	SFZeroAudioProcessor* processor = getProcessor();
	FileChooser chooser(
		"Select an SFZ file...",
		File::nonexistent,
		"*.sfz;*.SFZ");
	if (chooser.browseForFileToOpen()) {
		File sfzFile(chooser.getResult());
		setFile(&sfzFile);
		}
}


void SFZeroEditor::setFile(File* newFile)
{
	getProcessor()->setSfzFile(newFile);
	updateFile(newFile);
}


void SFZeroEditor::updateFile(File* file)
{
	fileLabel.setText(file->getFileName(), false);
	fileLabel.setColour(Label::textColourId, Colours::black);
	pathLabel.setText(file->getParentDirectory().getFullPathName(), false);
}



