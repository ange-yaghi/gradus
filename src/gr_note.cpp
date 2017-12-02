#include "gr_note.h"

#include "gr_midi.h"

grNoteValue::grNoteValue()
{

}

grNoteValue::~grNoteValue()
{

}

void grNoteValue::Reduce()
{
    int gcd = CalculateGCD(Numerator, Denominator);

    Numerator /= gcd;
    Denominator /= gcd;
}

int grNoteValue::CalculateGCD(int a, int b)
{
    int t=0;
    while (b != 0)
    {
        t = b;
        b = a % b;
        a = t;
    }

    return a;
}

grNoteValue grNoteValue::Subtract(const grNoteValue &a, const grNoteValue &b)
{
    grNoteValue result;

    result.Denominator = a.Denominator * b.Denominator;
    result.Numerator = (a.Numerator * b.Denominator) - (a.Numerator * b.Denominator);

    result.Reduce();

    return result;
}

grNoteValue grNoteValue::Add(const grNoteValue &a, const grNoteValue &b)
{
    grNoteValue result;

    result.Denominator = a.Denominator * b.Denominator;
    result.Numerator = (a.Numerator * b.Denominator) + (a.Numerator * b.Denominator);

    result.Reduce();

    return result;
}

int grNoteValue::Compare(const grNoteValue &a, const grNoteValue &b)
{
    grNoteValue delta = grNoteValue::Subtract(a, b);
    if (delta.Numerator == 0) return 0;
    else if (delta.Numerator > 0) return 1;
    else if (delta.Numerator < 0) return -1;
	return -2;
}

grNote::grNote() : grObject("grNote")
{

}

grNote::~grNote()
{

}

void grNote::generateFromMidi(grMidiNote *note, grKey *key)
{
	bool accidental;
	char letter;
	int octave;

	note->GetNaturalNotation(&letter, &accidental, &octave);
}

grNote::NOTE grNote::getPreviousTone(grNote::NOTE tone)
{
	int value = (int)tone;
	value--;
	if (value == -1) return G;
	else return (NOTE)value;
}

grNote::NOTE grNote::getEnharmonicEquivalent(grNote::ACCIDENTAL targetAccidental, grNote::NOTE note, grNote::ACCIDENTAL accidental)
{
	if (targetAccidental == DOUBLE_SHARP)
	{
		if (accidental == DOUBLE_SHARP)
			return note;
		if (accidental == SHARP)
		{
			if (note == C)
				return B;
			else if (note == F)
				return E;
			else
				return UNDEFINED_NOTE;
		}
		if (accidental == FLAT)
		{
			if (note == D)
				return B;
			else if (note == G)
				return E;
			else
				return UNDEFINED_NOTE;
		}

		if (accidental == DOUBLE_FLAT)
		{
			return UNDEFINED_NOTE;
		}

	}

	else if (targetAccidental == DOUBLE_FLAT)
	{
		if (accidental == DOUBLE_FLAT)
			return note;
		if (accidental == SHARP)
		{
			if (note == A)
				return C;
			else if (note == D)
				return F;
			else
				return UNDEFINED_NOTE;
		}
		if (accidental == FLAT)
		{
			if (note == B)
				return C;
			else if (note == E)
				return F;
			else
				return UNDEFINED_NOTE;
		}

		if (accidental == DOUBLE_SHARP)
		{
			return UNDEFINED_NOTE;
		}
	}

	else if (targetAccidental == SHARP)
	{
		if (accidental == SHARP)
			return note;
		else if (accidental == FLAT)
		{
			switch (note)
			{
			case A:
				return G;
			case B:
				return A;
			case C:
				return UNDEFINED_NOTE;
			case D:
				return C;
			case E:
				return D;
			case F:
				return UNDEFINED_NOTE;
			case G:
				return F;
			};
		}

		else if (accidental == DOUBLE_FLAT)
		{
			if (note == F)
				return D;
			else if (note == C)
				return A;
			else
				return UNDEFINED_NOTE;
		}

		else if (accidental == DOUBLE_SHARP)
		{
			if (note == B)
				return C;
			else if (note == E)
				return F;
			else
				return UNDEFINED_NOTE;
		}
	}

	else if (targetAccidental == FLAT)
	{
		if (accidental == FLAT)
			return note;
		else if (accidental == SHARP)
		{
			switch (note)
			{
			case A:
				return B;
			case B:
				return UNDEFINED_NOTE;
			case C:
				return D;
			case D:
				return E;
			case E:
				return UNDEFINED_NOTE;
			case F:
				return G;
			case G:
				return A;
			};
		}

		else if (accidental == DOUBLE_FLAT)
		{
			if (note == F)
				return D;
			else if (note == C)
				return A;
			else
				return UNDEFINED_NOTE;
		}

		else if (accidental == DOUBLE_SHARP)
		{
			if (note == B)
				return C;
			else if (note == E)
				return F;
			else
				return UNDEFINED_NOTE;
		}
	}
}

void grNote::transpose(grNote::NOTE note, grNote::ACCIDENTAL accidental, grNote::NOTE *newNote, grNote::NOTE *newAccidental, int semitones)
{
	if (semitones == 1)
	{
		if (accidental == grNote::SHARP)
		{

		}
	}
}