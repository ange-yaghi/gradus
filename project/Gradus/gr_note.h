#ifndef GR_NOTE_H
#define GR_NOTE_H

#include "gr_object.h"

class grNote : public grObject
{
public:
	grNote();
	~grNote();

	enum ACCIDENTAL
	{
		NATURAL,
		FLAT,
		SHARP,
		DOUBLE_FLAT,
		DOUBLE_SHARP
	};

	enum NOTE
	{
		C,
		D,
		E,
		F,
		G,
		A,
		B
	};

	// Get the accidental for this note
	ACCIDENTAL getAccidental() { return m_accidental; }

	// Set the accidental for this note
	void setAccidental(ACCIDENTAL accidental) { m_accidental = accidental; }

	// Get the note name
	NOTE getNote() { return m_note; }

	// Set the note name
	void setNote(NOTE note) { m_note = note; }

	// Get the octave number
	int getOctave() { return m_octave; }

	// Set the octave number
	void setOctave(int octave) { m_octave = octave; }

private:
	// Accidental applied to this note
	ACCIDENTAL m_accidental;

	// The note name
	NOTE m_note;

	// The octave of the note
	int m_octave;
};

#endif	// GR_NOTE_H
