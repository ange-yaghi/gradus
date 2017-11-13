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
		DOUBLE_SHARP,
		NONE
	};

	enum NOTE
	{
		C,
		D,
		E,
		F,
		G,
		A,
		B,
		REST
	};

	// Get the accidental for this note
	ACCIDENTAL getAccidental() const { return m_accidental; }

	// Set the accidental for this note
	void setAccidental(ACCIDENTAL accidental) { m_accidental = accidental; }

	// Get the note name
	NOTE getNote() const { return m_note; }

	// Set the note name
	void setNote(NOTE note) { m_note = note; }

	// Get the octave number
	int getOctave() const { return m_octave; }

	// Set the octave number
	void setOctave(int octave) { m_octave = octave; }

	// Get the length numerator
	int getNumLength() const { return m_nLength; }

	// Set the length numerator
	void setNumLength(int numerator) { m_nLength = numerator; }

	// Get the length denominator
	int getDenLength() const { return m_dLength; }

	// Set the length denominator
	void setDenLength(int denominator) { m_dLength = denominator; }

private:
	// Accidental applied to this note
	ACCIDENTAL m_accidental;

	// The note name
	NOTE m_note;

	// The octave of the note
	int m_octave;

	// Note denominator
	int m_dLength;

	// Note numerator
	int m_nLength;
};

#endif	// GR_NOTE_H
