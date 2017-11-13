#include "gr_midi_output.h"
#include "gr_midi.h"

/* MidiTop */
grMidiTop::grMidiTop()
{
}

grMidiTop::~grMidiTop()
{
}

void grMidiTop::WriteToFile(std::ofstream *file)
{
	
	int nChunks = m_chunks.GetNumObjects();

	for (int i = 0; i < nChunks; i++)
	{

		m_chunks.Get(i)->WriteToFile(file);

	}

}

/* MidiChunk */
grMidiChunk::grMidiChunk(CHUNK_TYPE chunkType) : grObject("MidiChunk")
{

	m_chunkType = chunkType;

}

grMidiChunk::~grMidiChunk()
{
}

void grMidiChunk::WriteToFile(std::ofstream *file)
{

	grMidiChunkHeader chunkHeader;
	
	if (m_chunkType == CHUNK_TYPE_HEADER)
	{

		chunkHeader.Type[0] = 'M';
		chunkHeader.Type[1] = 'T';
		chunkHeader.Type[2] = 'h';
		chunkHeader.Type[3] = 'd';

	}

	else if (m_chunkType == CHUNK_TYPE_TRACK)
	{

		chunkHeader.Type[0] = 'M';
		chunkHeader.Type[1] = 'T';
		chunkHeader.Type[2] = 'r';
		chunkHeader.Type[3] = 'k';

	}

	chunkHeader.Length = GetLength();
	grMidiFile::ByteSwap32(&chunkHeader.Length);

	file->write((const char *)&chunkHeader, sizeof(grMidiChunkHeader));

}

int grMidiChunk::GetLength()
{

	return 0;

}

/* MidiChunk_Header */
grMidiChunk_Header::grMidiChunk_Header() : grMidiChunk(CHUNK_TYPE_HEADER)
{

	m_ticksPerQuarterNote = 0;
	m_trackCount = 0;

}

grMidiChunk_Header::~grMidiChunk_Header()
{
}

int grMidiChunk_Header::GetLength()
{

	return sizeof(grMidiHeaderChunkData) + grMidiChunk::GetLength();

}

void grMidiChunk_Header::WriteToFile(std::ofstream *file)
{

	grMidiChunk::WriteToFile(file);

	grMidiHeaderChunkData chunkData;

	// Change to 0x8000 if using the other division format
	chunkData.Division = 0x0000 | (m_ticksPerQuarterNote & 0x7FFF);
	chunkData.Format = FORMAT_1;
	chunkData.Ntrks = m_trackCount;

	grMidiFile::ByteSwap16(&chunkData.Format);
	grMidiFile::ByteSwap16(&chunkData.Division);
	grMidiFile::ByteSwap16(&chunkData.Ntrks);

	file->write((const char *)&chunkData, sizeof(grMidiHeaderChunkData));

}

/* MidiChunk_Track */
grMidiChunk_Track::grMidiChunk_Track() : grMidiChunk(CHUNK_TYPE_TRACK)
{
}

grMidiChunk_Track::~grMidiChunk_Track()
{
}

int grMidiChunk_Track::GetLength()
{

	int trackEventSize = 0;

	int nTrackEvents = m_trackEvents.GetNumObjects();

	for (int i = 0; i < nTrackEvents; i++)
	{

		trackEventSize += m_trackEvents.Get(i)->GetSize();

	}

	return grMidiChunk::GetLength() + trackEventSize;

}

int grMidiChunk_Track::GetIndex(UINT32 deltaTime)
{

	// TEMP: basic slow implementation
	int trackEventSize = 0;

	int nTrackEvents = m_trackEvents.GetNumObjects();

	int left = 0;

	for (int i = 0; i < nTrackEvents - 1; i++)
	{

		if (deltaTime < m_trackEvents.Get(i)->m_absDeltaTime)
		{

			return left;

		}

		if (deltaTime >= m_trackEvents.Get(i)->m_absDeltaTime)
		{

			left = i + 1;

		}

	}

	return left;

}

void grMidiChunk_Track::WriteToFile(std::ofstream *file)
{

	CalculateDeltaTimes();

	grMidiChunk::WriteToFile(file);

	int nTrackEvents = m_trackEvents.GetNumObjects();

	for (int i = 0; i < nTrackEvents; i++)
	{

		m_trackEvents.Get(i)->WriteToFile(file);

	}

}

void grMidiChunk_Track::CalculateDeltaTimes()
{

	UINT32 lastDeltaTime = 0;

	int nTrackEvents = m_trackEvents.GetNumObjects();

	if (nTrackEvents > 0)
	{

		lastDeltaTime = m_trackEvents.Get(0)->m_absDeltaTime;

	}

	for (int i = 0; i < nTrackEvents; i++)
	{

		m_trackEvents.Get(i)->m_deltaTime = m_trackEvents.Get(i)->m_absDeltaTime - lastDeltaTime;

		lastDeltaTime = m_trackEvents.Get(i)->m_absDeltaTime;

	}

	//if (nTrackEvents > 0)
	//{

	//	m_trackEvents.Get(nTrackEvents - 1)->m_deltaTime = 0;

	//}

}

/* MidiTrackEvent */
grMidiTrackEvent::grMidiTrackEvent(TRACK_EVENT_TYPE eventType) : grObject("MidiTrackEvent")
{

	m_eventType = eventType;

	m_absDeltaTime = 0;
	m_deltaTime = 0;
	m_type = 0;

}

grMidiTrackEvent::~grMidiTrackEvent()
{
}

void grMidiTrackEvent::WriteVariableLengthQuantity(std::ofstream *file, UINT32 vlq)
{

	bool done = false;

	int bytesNeeded = grMidiTrackEvent::GetSizeForVLQ(vlq);

	for (int i = 0; i < bytesNeeded; i++)
	{

		int shift = 7 * (bytesNeeded - i - 1);
		BYTE data = (BYTE)((vlq & (0x7F << shift)) >> shift);

		if (i != bytesNeeded - 1) data |= 0x80;

		file->write((const char *)&data, sizeof(BYTE));

	}

}

int grMidiTrackEvent::GetSizeForVLQ(UINT32 vlq)
{

	if (vlq < 128) return 1;
	if (vlq < 16384) return 2;
	if (vlq < 2097152) return 3;
	if (vlq < 268435456) return 4;
	return 0;

}


void grMidiTrackEvent::WriteToFile(std::ofstream *file)
{

	WriteVariableLengthQuantity(file, m_deltaTime);
	file->write((const char *)&m_type, sizeof(BYTE));

}

int grMidiTrackEvent::GetSize() const
{

	return sizeof(BYTE) + GetSizeForVLQ(m_deltaTime);

}

/* MidiTrackEvent_Meta */

grMidiTrackEvent_Meta::grMidiTrackEvent_Meta(META_EVENT_TYPE eventType) : grMidiTrackEvent(EVENT_TYPE_META)
{

	m_metaEventType = eventType;
	m_length = 0;
	m_type = 0xFF;

}

grMidiTrackEvent_Meta::~grMidiTrackEvent_Meta()
{
}

void grMidiTrackEvent_Meta::WriteToFile(std::ofstream *file)
{

	grMidiTrackEvent::WriteToFile(file);

	file->write((const char *)&m_metaEventType, sizeof(BYTE));
	
	// Write the length
	WriteVariableLengthQuantity(file, m_length);

}

int grMidiTrackEvent_Meta::GetSize() const
{

	return sizeof(BYTE) + GetSizeForVLQ(m_length) + m_length + grMidiTrackEvent::GetSize();

}

/* MidiTrackEvent_Meta_Text */

grMidiTrackEvent_Meta_Text::grMidiTrackEvent_Meta_Text() : grMidiTrackEvent_Meta(META_EVENT_TEXT)
{

	m_length = 0;
	m_text = NULL;

}

grMidiTrackEvent_Meta_Text::~grMidiTrackEvent_Meta_Text()
{

	if (m_text != NULL) delete[] m_text;

}

void grMidiTrackEvent_Meta_Text::WriteToFile(std::ofstream *file)
{

	grMidiTrackEvent_Meta::WriteToFile(file);

	if (m_text != NULL)
		file->write((const char *)m_text, m_length);

}

void grMidiTrackEvent_Meta_Text::SetText(const char *text)
{

	if (m_text != NULL) delete[] text;
	m_text = NULL;
	m_length = 0;

	if (text != NULL)
	{

		int length = strlen(text);

		m_length = length;
		m_text = new char[m_length + 1];
		strcpy(m_text, text);

	}

}

/* MidiTrackEvent_Meta_TrackName */

grMidiTrackEvent_Meta_TrackName::grMidiTrackEvent_Meta_TrackName() : grMidiTrackEvent_Meta(META_EVENT_TRACK_NAME)
{

	m_length = 0;
	m_trackName = NULL;

}

grMidiTrackEvent_Meta_TrackName::~grMidiTrackEvent_Meta_TrackName()
{

	if (m_trackName != NULL) delete[] m_trackName;

}

void grMidiTrackEvent_Meta_TrackName::WriteToFile(std::ofstream *file)
{

	grMidiTrackEvent_Meta::WriteToFile(file);

	if (m_trackName != NULL)
		file->write((const char *)m_trackName, m_length);

}

void grMidiTrackEvent_Meta_TrackName::SetTrackName(const char *text)
{

	if (m_trackName != NULL) delete[] m_trackName;
	m_trackName = NULL;
	m_length = 0;

	if (text != NULL)
	{

		int length = strlen(text);

		m_length = length;
		m_trackName = new char[m_length + 1];
		strcpy(m_trackName, text);

	}

}

/* MidiTrackEvent_Meta_ChangeTempo */

grMidiTrackEvent_Meta_ChangeTempo::grMidiTrackEvent_Meta_ChangeTempo() : grMidiTrackEvent_Meta(META_EVENT_CHANGE_TEMPO)
{

	m_tempo = 0;
	m_length = sizeof(BYTE) * 3;

}

grMidiTrackEvent_Meta_ChangeTempo::~grMidiTrackEvent_Meta_ChangeTempo()
{
}

void grMidiTrackEvent_Meta_ChangeTempo::WriteToFile(std::ofstream *file)
{

	grMidiTrackEvent_Meta::WriteToFile(file);

	UINT32 tempo = m_tempo;
	grMidiFile::ByteSwap24(&tempo);

	file->write((const char *)&tempo, sizeof(BYTE) * 3);

}

/* MidiTrackEvent_Meta_EndOfTrack */

grMidiTrackEvent_Meta_EndOfTrack::grMidiTrackEvent_Meta_EndOfTrack() : grMidiTrackEvent_Meta(META_EVENT_END_OF_TRACK)
{

	m_length = 0;

}

grMidiTrackEvent_Meta_EndOfTrack::~grMidiTrackEvent_Meta_EndOfTrack()
{
}

void grMidiTrackEvent_Meta_EndOfTrack::WriteToFile(std::ofstream *file)
{

	grMidiTrackEvent_Meta::WriteToFile(file);

}

/* MidiTrackEvent_Meta_TimeSignature */

grMidiTrackEvent_Meta_TimeSignature::grMidiTrackEvent_Meta_TimeSignature() : grMidiTrackEvent_Meta(META_EVENT_TIME_SIGNATURE)
{

	m_numerator = 0;
	m_denominator = 0;

	m_length = sizeof(BYTE) * 4;

}

grMidiTrackEvent_Meta_TimeSignature::~grMidiTrackEvent_Meta_TimeSignature()
{
}

void grMidiTrackEvent_Meta_TimeSignature::WriteToFile(std::ofstream *file)
{

	grMidiTrackEvent_Meta::WriteToFile(file);

	UINT8 ts[4] = { m_numerator, m_denominator, 0x12, 0x08 };

	file->write((const char *)&ts, sizeof(BYTE)*4);

}

/* MidiTrackEvent_ChannelVoice */

grMidiTrackEvent_ChannelVoice::grMidiTrackEvent_ChannelVoice(CHANNEL_VOICE_EVENT_TYPE type) : grMidiTrackEvent(EVENT_TYPE_META)
{

	m_channelVoiceEventType = type;

	m_channel = 0;
	m_status = 0;
	m_type = 0;

}

grMidiTrackEvent_ChannelVoice::~grMidiTrackEvent_ChannelVoice()
{
}

void grMidiTrackEvent_ChannelVoice::WriteToFile(std::ofstream *file)
{

	grMidiTrackEvent::WriteToFile(file);

	file->write((const char *)&m_byte1, sizeof(BYTE));
	file->write((const char *)&m_byte2, sizeof(BYTE));

}

void grMidiTrackEvent_ChannelVoice::SetChannel(int channel)
{

	m_channel = channel;

	m_type &= 0xF0;
	m_type |= (channel & 0x0F);

}

void grMidiTrackEvent_ChannelVoice::SetStatus(BYTE status)
{

	m_status = status;

	m_type &= 0x0F;
	m_type |= (status & 0xF0);

}

int grMidiTrackEvent_ChannelVoice::GetSize() const
{

	return (2 * sizeof(BYTE)) + grMidiTrackEvent::GetSize();

}

grMidiTrackEvent_ChannelVoice_KeyDown::grMidiTrackEvent_ChannelVoice_KeyDown() 
	: grMidiTrackEvent_ChannelVoice(CHANNEL_VOICE_EVENT_KEY_DOWN)
{

	SetStatus(0x90);

}

grMidiTrackEvent_ChannelVoice_KeyDown::~grMidiTrackEvent_ChannelVoice_KeyDown()
{
}