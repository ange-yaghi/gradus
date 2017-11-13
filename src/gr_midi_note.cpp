#include "gr_midi_note.h"

grMidiNote::grMidiNote()
{

	m_timeStamp = 0;
	m_realTime = 0;
	m_midiKey = 0;
	m_noteLength = 0;

	m_valid = true;

	m_classType = NOTE_CLASS_STANDARD;

}

grMidiNote::grMidiNote(NOTE_CLASS_TYPE classType)
{

	m_timeStamp = 0;
	m_realTime = 0;
	m_midiKey = 0;
	m_noteLength = 0;

	m_valid = true;

	m_classType = classType;

}

grMidiNote::~grMidiNote()
{
}

void grMidiNote::GetNaturalNotation(char *letter, bool *accidental, int *octave)
{
	int delta = m_midiKey - 12;

	*octave = delta / 12;

	int natural = (m_midiKey - 21) % 12;

	int c_offset = delta % 12;

	if (c_offset == 1 ||
		c_offset == 3 ||
		c_offset == 6 ||
		c_offset == 8 ||
		c_offset == 10)
	{

		*accidental = true;
		c_offset -= 1;
		natural -= 1;

	}

	else *accidental = false;

	if (c_offset > 10) c_offset -= 5;
	else if (c_offset > 8) c_offset -= 4;
	else if (c_offset > 6) c_offset -= 3;
	else if (c_offset > 3) c_offset -= 2;
	else if (c_offset > 1) c_offset -= 1;

	*letter = 'A' + (2 + c_offset) % 7;
}

/*
void grMidiNote::PrintDebug(int tempo)
{

	char letter;
	bool accidental;
	int octave;

	GetNaturalNotation(&letter, &accidental, &octave);

	if (tempo == 0)
	{

		if (accidental)
			printf("%c#%d | %d\n", letter, octave, m_parent->GetSegment()->ConvertDeltaTimeToNote(m_noteLength));

		else
			printf("%c%d | %d\n", letter, octave, m_parent->GetSegment()->ConvertDeltaTimeToNote(m_noteLength));

	}

	else
	{

		if (accidental)
			printf("%c#%d | %d : %d\n", letter, octave, m_parent->GetSegment()->ConvertDeltaTimeToMilliseconds(m_timeStamp, tempo),
				m_parent->GetSegment()->ConvertDeltaTimeToMilliseconds(m_noteLength, tempo));

		else
			printf("%c%d | %d : %d\n", letter, octave, m_parent->GetSegment()->ConvertDeltaTimeToMilliseconds(m_timeStamp, tempo),
				m_parent->GetSegment()->ConvertDeltaTimeToMilliseconds(m_noteLength, tempo));

	}

}
*/

/* TODO: REMOVE
int grMidiNote::GetTimeStampMilliseconds(int offset, int tempo) const
{

	int timeStamp_ms = m_parent->GetSegment()->ConvertDeltaTimeToMilliseconds(m_timeStamp + offset, tempo);

	return timeStamp_ms;

}
*/

void grMidiNote::CopyTo(grMidiNote *midiNote) const
{

	midiNote->m_midiKey = m_midiKey;
	midiNote->m_timeStamp = m_timeStamp;
	midiNote->m_valid = m_valid;
	midiNote->m_noteLength = m_noteLength;
	midiNote->m_realTime = m_realTime;
	midiNote->m_velocity = m_velocity;

}