#ifndef GR_MIDI_NOTE_H
#define GR_MIDI_NOTE_H

#include <Windows.h>

#include "gr_dynamic_array.h"

class grMidiNote : public grDynamicArrayElement
{

protected:

	enum NOTE_CLASS_TYPE
	{

		NOTE_CLASS_UNKNOWN,
		NOTE_CLASS_STANDARD,
		NOTE_CLASS_ANALYSIS,

	};

public:

	grMidiNote();
	grMidiNote(NOTE_CLASS_TYPE classType);
	virtual ~grMidiNote();

	BYTE m_midiKey;
	BYTE m_velocity;

	uint64_t m_realTime;
	int m_noteLength;
	int m_timeStamp;

	void GetNaturalNotation(char *letter, bool *accidental, int *octave);

	void SetValid(bool valid) { m_valid = valid; }
	bool GetValid() const { return m_valid; }

	void Copy(const grMidiNote *source) { source->CopyTo(this); }
	virtual void CopyTo(grMidiNote *target) const;

	NOTE_CLASS_TYPE GetClassType() const { return m_classType; }

protected:

	bool m_valid;
	grMidiNote *m_parent;

private:

	NOTE_CLASS_TYPE m_classType;

};

#endif