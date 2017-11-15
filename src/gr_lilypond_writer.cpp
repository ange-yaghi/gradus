#include "gr_lilypond_writer.h"
#include "gr_music_snippet.h"

#include <iostream>

grRhythymCounter::grRhythymCounter()
{
    m_meterNumerator = 0;
    m_meterDenominator = 0;
}

grRhythymCounter::~grRhythymCounter()
{

}

void grRhythymCounter::SetTime(int numerator, int denominator)
{
    m_meterDenominator = denominator;
    m_meterNumerator = numerator;

    m_barLength.Numerator = numerator;
    m_barLength.Denominator = denominator;
    m_barLength.Reduce();
}

void grRhythymCounter::SplitNote(grNote *note, grNoteValue *currentBar, grNoteValue *nextBar) const
{
    grNoteValue noteEnd = grNoteValue::Add(m_cursor, note->getNoteValue());
    
    grNoteValue afterBar = grNoteValue::Subtract(noteEnd, m_barLength);
    grNoteValue beforeBar = grNoteValue::Subtract(note->getNoteValue(), afterBar);

    if (afterBar.Numerator < 0)
    {
        nextBar->Numerator = 0;
        nextBar->Denominator = 1;
    }

    else
    {
        *nextBar = afterBar;
    }

    if (grNoteValue::Compare(note->getNoteValue(), beforeBar) == -1)
    {
        *currentBar = beforeBar; 
    }

    else
    {
        *currentBar = note->getNoteValue();
    }
}

const char *grLilypondWriter::LILYPOND_VERSION = "2.18.2";

grLilypondWriter::grLilypondWriter()
{

}

grLilypondWriter::~grLilypondWriter()
{

}

void grLilypondWriter::WriteMusicSnippetToFile(grMusicSnippet *snippet, const char *fname)
{
    // First open the file
    m_file.open(fname);

    

    m_file.close();
}

void grLilypondWriter::WriteLilypondHeader()
{
	m_file << "\\version \"" << LILYPOND_VERSION << "\"";
}

void grLilypondWriter::WriteVoice(grNoteSequence *sequence, grMusicSnippet *parent, int voiceNum)
{
    m_file << "voice_" << voiceNum << " = " << std::endl;
    m_file << "\\absolute {" << std::endl;

    if (voiceNum == 0) m_file << "\\voiceOne" << std::endl;
    if (voiceNum == 1) m_file << "\\voiceThree" << std::endl;
    if (voiceNum == 2) m_file << "\\voiceTwo" << std::endl;

    m_file << "\\time " <<  parent->GetMeterNumerator() << "/" << parent->GetMeterDenominator() << std::endl;

    grKey *key = parent->GetKey();
    m_file << "\\key " <<   key->GetLilypondKeyString();

    if (key->Quality == grKey::MAJOR)
        m_file << "\\major" << std::endl;

    else if (key->Quality == grKey::MINOR)
        m_file << "\\minor" << std::endl;

    /* else it's an error */

    int noteCount = sequence->GetNoteCount();

    int currentCountNumerator = 0;
    int currentCountDenominator = 0;

    for (int i=0; i < noteCount; i++)
    {
        grNote *note = sequence->GetNote(i);
        
    }
    
}