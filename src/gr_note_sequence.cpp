#include "gr_note_sequence.h"

#include "gr_midi.h"

grNoteSequence::grNoteSequence() : grObject("grNoteSequence")
{
}

grNoteSequence::~grNoteSequence()
{
}

grNote *grNoteSequence::AddNote()
{
	return m_notes.New();
}

void grNoteSequence::Generate(grMidiTrack *track)
{
	int noteCount = track->GetNoteCount();

	for (int i = 0; i < noteCount; i++)
	{
		grNote *newNote = AddNote();
		grMidiNote *midiNote = track->GetBuffer()[i];

		midiNote->GetNaturalNotation		
	}

}