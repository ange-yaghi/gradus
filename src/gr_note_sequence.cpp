#include "gr_note_sequence.h"

grNoteSequence::grNoteSequence()
{
}

grNoteSequence::~grNoteSequence()
{
}

grNote *grNoteSequence::AddNote()
{
	return m_notes.New();
}