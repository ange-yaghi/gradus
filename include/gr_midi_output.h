#ifndef GR_MIDI_OUTPUT_H
#define GR_MIDI_OUTPUT_H

#include "gr_dynamic_array.h"
#include "gr_object.h"

#include <Windows.h>
#include <iostream>
#include <fstream>

class grMidiChunk : public grObject
{

public:

	enum CHUNK_TYPE
	{

		CHUNK_TYPE_HEADER,
		CHUNK_TYPE_TRACK

	};

public:

	grMidiChunk(CHUNK_TYPE chunkType);
	virtual ~grMidiChunk();

	virtual void WriteToFile(std::ofstream *file);

	virtual int GetLength();

protected:

	CHUNK_TYPE m_chunkType;

};

class grMidiTop
{

public:

	grMidiTop();
	~grMidiTop();

	template<typename ChunkType>
	ChunkType *NewChunk() { return m_chunks.NewGeneric<ChunkType>(); }

	void WriteToFile(std::ofstream *file);

protected:

	grDynamicArray<grMidiChunk, 4> m_chunks;

};

class grMidiChunk_Header : public grMidiChunk
{

public:

	grMidiChunk_Header();
	virtual ~grMidiChunk_Header();

	virtual void WriteToFile(std::ofstream *file);

	UINT16 m_ticksPerQuarterNote;
	UINT16 m_trackCount;

	virtual int GetLength();

};

class grMidiTrackEvent : public grObject
{

public:

	enum TRACK_EVENT_TYPE
	{

		EVENT_TYPE_SYSTEM_EXCLUSIVE,
		EVENT_TYPE_SYSTEM_EXCLUSIVE_RESUME,

		EVENT_TYPE_META,
		EVENT_TYPE_CHANNEL_VOICE,

	};

public:

	grMidiTrackEvent(TRACK_EVENT_TYPE eventType);
	virtual ~grMidiTrackEvent();

	static int GetSizeForVLQ(UINT32 vlq);
	static void WriteVariableLengthQuantity(std::ofstream *file, UINT32 vlq);

	virtual void WriteToFile(std::ofstream *file);
	virtual int GetSize() const;

	UINT32 m_deltaTime;
	UINT32 m_absDeltaTime;
	BYTE m_type;

	TRACK_EVENT_TYPE m_eventType;

};

class grMidiChunk_Track : public grMidiChunk
{

public:

	grMidiChunk_Track();
	virtual ~grMidiChunk_Track();

	virtual void WriteToFile(std::ofstream *file);

	virtual int GetLength();

	int GetIndex(UINT32 deltaTime);

	template<typename TrackEventType>
	TrackEventType *NewTrackEvent(int deltaTime) 
	{ 
		
		TrackEventType *newEvent = m_trackEvents.NewGeneric<TrackEventType>();
		int offset = GetIndex(deltaTime);

		m_trackEvents.Move(newEvent, offset);

		newEvent->m_absDeltaTime = deltaTime;

		return newEvent;

	}

protected:

	void CalculateDeltaTimes();

	grDynamicArray<grMidiTrackEvent, 4> m_trackEvents;

};

class grMidiTrackEvent_Meta : public grMidiTrackEvent
{

public:

	enum META_EVENT_TYPE
	{

		META_EVENT_TEXT = 0x01,
		META_EVENT_TRACK_NAME = 0x03,
		META_EVENT_CHANGE_TEMPO = 0x51,
		META_EVENT_END_OF_TRACK = 0x2F,
		META_EVENT_TIME_SIGNATURE = 0x58,

	};

public:

	grMidiTrackEvent_Meta(META_EVENT_TYPE metaEventType);
	virtual ~grMidiTrackEvent_Meta();

	virtual void WriteToFile(std::ofstream *file);
	virtual int GetSize() const;

	BYTE m_metaType;
	UINT32 m_length;

	META_EVENT_TYPE m_metaEventType;

};

class grMidiTrackEvent_Meta_Text : public grMidiTrackEvent_Meta
{

public:

	grMidiTrackEvent_Meta_Text();
	~grMidiTrackEvent_Meta_Text();

	virtual void WriteToFile(std::ofstream *file);

	void SetText(const char *text);

	char *m_text;

};

class grMidiTrackEvent_Meta_TrackName : public grMidiTrackEvent_Meta
{

public:

	grMidiTrackEvent_Meta_TrackName();
	~grMidiTrackEvent_Meta_TrackName();

	virtual void WriteToFile(std::ofstream *file);

	void SetTrackName(const char *text);

	char *m_trackName;

};

class grMidiTrackEvent_Meta_ChangeTempo : public grMidiTrackEvent_Meta
{

public:

	grMidiTrackEvent_Meta_ChangeTempo();
	~grMidiTrackEvent_Meta_ChangeTempo();

	virtual void WriteToFile(std::ofstream *file);

	UINT32 m_tempo;

};

class grMidiTrackEvent_Meta_EndOfTrack : public grMidiTrackEvent_Meta
{

public:

	grMidiTrackEvent_Meta_EndOfTrack();
	~grMidiTrackEvent_Meta_EndOfTrack();

	virtual void WriteToFile(std::ofstream *file);

};

class grMidiTrackEvent_Meta_TimeSignature: public grMidiTrackEvent_Meta
{

public:

	grMidiTrackEvent_Meta_TimeSignature();
	~grMidiTrackEvent_Meta_TimeSignature();

	virtual void WriteToFile(std::ofstream *file);

	UINT8 m_numerator;
	UINT8 m_denominator;

};

class grMidiTrackEvent_ChannelVoice : public grMidiTrackEvent
{

public:

	enum CHANNEL_VOICE_EVENT_TYPE
	{

		CHANNEL_VOICE_EVENT_KEY_DOWN,

	};

public:

	grMidiTrackEvent_ChannelVoice(CHANNEL_VOICE_EVENT_TYPE eventType);
	~grMidiTrackEvent_ChannelVoice();

	virtual void WriteToFile(std::ofstream *file);

	BYTE m_byte1;
	BYTE m_byte2;

	void SetChannel(int channel);
	void SetStatus(BYTE status);

	virtual int GetSize() const;

protected:

	CHANNEL_VOICE_EVENT_TYPE m_channelVoiceEventType;

	BYTE m_status;
	int m_channel;

};

class grMidiTrackEvent_ChannelVoice_KeyDown : public grMidiTrackEvent_ChannelVoice
{

public:

	grMidiTrackEvent_ChannelVoice_KeyDown();
	~grMidiTrackEvent_ChannelVoice_KeyDown();

	void SetVelocity(BYTE velocity) { m_byte2 = velocity; }
	void SetKey(BYTE key) { m_byte1 = key; }

};

#endif /* GR_MIDI_OUTPUT_H */