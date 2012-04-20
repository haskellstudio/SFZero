#ifndef __PLUGINEDITOR_H_A8E24640__
#define __PLUGINEDITOR_H_A8E24640__

#include "../JuceLibraryCode/JuceHeader.h"
#include "SFZeroAudioProcessor.h"
#include "ClickableLabel.h"


class SFZeroEditor  :
	public AudioProcessorEditor, public Timer,
	public ClickableLabel::ClickListener
{
	public:
		SFZeroEditor(SFZeroAudioProcessor* ownerFilter);
		~SFZeroEditor();

		void	paint(Graphics& g);
		void	resized();
		void	labelClicked(Label* clickedLabel);
		void	timerCallback();

	protected:
		ClickableLabel	fileLabel;
		Label 	pathLabel;
		Label 	infoLabel;
		MidiKeyboardComponent	midiKeyboard;

		SFZeroAudioProcessor* getProcessor() const {
			return static_cast<SFZeroAudioProcessor*> (getAudioProcessor());
			}

		void	chooseFile();
		void	setFile(File* newFile);
		void	updateFile(File* file);
	};


#endif  // __PLUGINEDITOR_H_A8E24640__
