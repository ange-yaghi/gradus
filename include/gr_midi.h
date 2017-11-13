#ifndef TOCCATA_MIDI_FILE_H
#define TOCCATA_MIDI_FILE_H

#include <Windows.h>

#include <fstream>

#include "gr_dynamic_array.h"

struct grMidiChunkHeader
{

	BYTE Type[4];
	UINT32 Length;

};

// Formats
#define FORMAT_0 0x0000
#define FORMAT_1 0x0001
#define FORMAT_2 0x0002

struct alignas(2) grMidiHeaderChunkData
{

	UINT16 Format;
	UINT16 Ntrks;
	UINT16 Division;

};

struct alignas(2) grMidiMTrkEventHeader
{

	UINT16 DeltaTime;

};

class grMidiTrack;
class grMidiPianoSegment;
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

private:

	NOTE_CLASS_TYPE m_classType;

};

class grMidiAnalysisNote : public grMidiNote
{

public:

	enum NOTE_TYPE
	{

		NOTE_UNKNOWN,
		NOTE_REFERENCE,
		NOTE_PLAYED

	};

	enum NOTE_ERROR_TYPE
	{

		NOTE_ERROR_NONE,
		NOTE_ERROR_MISSED,
		NOTE_ERROR_WRONG,
		NOTE_ERROR_NONSENSE

	};

public:

	grMidiAnalysisNote();
	virtual ~grMidiAnalysisNote();

	double m_timingError;
	double m_realTimeError;
	
	NOTE_TYPE m_type;
	NOTE_ERROR_TYPE m_errorType;

	virtual void CopyTo(grMidiNote *midiNote) const;

};

class grMidiTrack
{

	friend class grMidiPianoSegment;

public:

	grMidiTrack();
	~grMidiTrack();

	void PrintDebug(int tempo = 0);

	grMidiNote *AddNote();
	grMidiAnalysisNote *AddAnalysisNote();
	void TransferNote(grMidiNote *note, grMidiTrack *target);
	void DeleteNote(grMidiNote *note);

	grMidiNote *FindLastNote(int midiKey, int timeStamp);
	grMidiNote *FindClosestNote(int midiKey, int timeStamp, int timeThreshold, int startIndex = 0);

	grMidiPianoSegment *GetSegment() { return m_parent; }
	void SetSegment(grMidiPianoSegment *segment) { m_parent = segment; }

	bool IsEmpty() const { return m_notes.GetNumObjects() > 0; }
	void Clear() { m_notes.Clear(); }

	grMidiNote **GetBuffer() { return m_notes.GetBuffer(); }
	int GetNoteCount() const { return m_notes.GetNumObjects(); }

	int GetStartDeltaTime() const;
	int GetEndDeltaTime() const;

	void MergeTrack(grMidiTrack *alternateTrack);

protected:

	grMidiPianoSegment *m_parent;
	grDynamicArray<grMidiNote, 4> m_notes;

};

class grMidiPianoSegment : public grDynamicArrayElement
{

	friend class grMidiFile;

public:

	enum TIME_FORMAT
	{


		TIME_FORMAT_METRICAL,
		TIME_FORMAT_TIME_CODE,

	};

public:

	grMidiPianoSegment();
	~grMidiPianoSegment();

	grMidiTrack m_leftHand;
	grMidiTrack m_rightHand;

	int ConvertDeltaTimeToNote(int deltaTime) const;
	int ConvertDeltaTimeToMilliseconds(int deltaTime, int tempoBPM) const;
	int ConvertMillisecondsToDeltaTime(int ms, int tempoBPM) const;
	int ConvertSecondsToDeltaTime(double s, int tempoBPM) const;

	int GetStartDeltaTime() const;
	int GetEndDeltaTime() const;

	void SetTimeFormat(TIME_FORMAT timeFormat) { m_timeFormat = timeFormat; }
	TIME_FORMAT GetTimeFormat() const { return m_timeFormat; }

	void SetTicksPerQuarterNote(int value) { m_ticksPerQuarterNote = value; }
	void SetNegativeSMPTEFormat(int value) { m_negativeSMPTEFormat = value; }
	void SetTicksPerFrame(int value) { m_ticksPerFrame = value; }

	void SetTimeSignature(int numerator, int denominator) { m_timeSignatureNumerator = numerator;  m_timeSignatureDenominator = denominator; }
	int GetTimeSignatureDenominator() const { return m_timeSignatureDenominator; }
	int GetTimeSignatureNumerator() const { return m_timeSignatureNumerator; }

	void SetTempo(int tempo) { m_tempo = tempo; }
	void SetTempoBPM(int bpm);
	int GetTempo() const { return m_tempo; }
	int GetTempoBPM() const;

	bool IsEmpty() const { return (m_leftHand.IsEmpty() && m_rightHand.IsEmpty()); }

	void CopySettingsTo(grMidiPianoSegment *targetSegment) const;

protected:

	TIME_FORMAT m_timeFormat;

	union
	{

		int m_ticksPerQuarterNote;

		struct
		{

			int m_negativeSMPTEFormat;
			int m_ticksPerFrame;

		};

	};

	// Tempo in microseconds per MIDI quarter-note
	int m_tempo;

	// Time Signature
	int m_timeSignatureNumerator;
	int m_timeSignatureDenominator;

};

class grMidiChunk_Track;
class grMidiFile
{

public:

	grMidiFile();
	~grMidiFile();

	void Write(const char *fname, grMidiPianoSegment *segment);
	grMidiPianoSegment *Read(const char *fname);

	static void ByteSwap32(UINT32 *data);
	static void ByteSwap24(UINT32 *data);
	static void ByteSwap16(UINT16 *data);

protected:

	void WriteTrackData(grMidiChunk_Track *target, grMidiTrack *source, grMidiPianoSegment *segment, int channel);

	void ReadChunk(grMidiChunkHeader *header);
	UINT32 ReadTrackEvent(UINT32 currentTime);

	UINT32 ReadVariableLengthQuantity();

	std::fstream m_file;

	grMidiTrack *m_targetTrack;
	grMidiPianoSegment *m_generatedSegment;
	unsigned int m_chunkDataRemaining;

protected:

	// Midi Data
	int m_nTracks;
	int m_format;

};

#endif