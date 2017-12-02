#ifndef GR_NOTE_SEQUENCE_H
#define GR_NOTE_SEQUENCE_H

#include "gr_object.h"
#include "gr_note.h"

#include <gr_dynamic_array.h>

class grMidiTrack;
class grNoteSequence : public grObject
{

public:

	grNoteSequence();
	~grNoteSequence();

	grNote *AddNote();

	// Get the note count of this sequence
	int GetNoteCount() const { return m_notes.GetNumObjects(); }
	
	// Get a note at a specific index
	grNote *GetNote(int index) const { return m_notes.Get(index); }

	// Generate a note sequence based on a midi track
	void Generate(grMidiTrack *track);

private:

	// Stores all notes in the sequence
	grDynamicArray<grNote, 4> m_notes;

};

#endif /* GR_NOTE_SEQUENCE */