#ifndef GR_NOTE_H
#define GR_NOTE_H

#include "gr_object.h"

class grNoteValue
{

public:
    grNoteValue();
    ~grNoteValue();

    // Reduce this note value to the simplest form
    void Reduce();

    // Subtract two note lengths
    static grNoteValue Subtract(const grNoteValue &a, const grNoteValue &b);

    // Add two note lengths
	static grNoteValue Add(const grNoteValue &a, const grNoteValue &b);
	
	// Determine if one is greater than the other
	static int Compare(const grNoteValue &a, const grNoteValue &b);

    // The numerator of the note length
    int Numerator;

    // The denominator of the note length
    int Denominator;

private:

    // Calculate the greatest commond divisor of two numbers
    static int CalculateGCD(int a, int b);

};

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
		REST,
		BLANK
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

	// Set the note value
	void setNoteValue(grNoteValue &value) { m_noteValue = value; }

	// Get the note value
	grNoteValue getNoteValue() { return m_noteValue; }

private:
	// Accidental applied to this note
	ACCIDENTAL m_accidental;

	// The note name
	NOTE m_note;

	// The octave of the note
	int m_octave;

	// Note value
	grNoteValue m_noteValue;

};

#endif	// GR_NOTE_H
