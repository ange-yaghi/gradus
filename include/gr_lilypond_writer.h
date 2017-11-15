#ifndef GR_LILYPOND_WRITER_H
#define GR_LILYPOND_WRITER_H

#include <fstream>

#include "gr_note.h"
#include "gr_note_sequence.h"

class grRhythymCounter
{

public:
    grRhythymCounter();
    ~grRhythymCounter();

    // Increment the rhythym counter
    void Increment(int numerator, int demoninator);

    // Set the time signature
    void SetTime(int numerator, int demoninator);

    // Split a note (should it cross the next bar line)
    void SplitNote(grNote *note, grNoteValue *currentBar, grNoteValue *nextBar) const;

private:

    // The numerator of the current meter
    int m_meterNumerator;

    // The denominator of the current meter
    int m_meterDenominator;

    // Current location of the cursor
	grNoteValue m_cursor;

    // Store the length of one bar
	grNoteValue m_barLength;

    // The current bar of the counter
    int m_currentBar;
    
};

class grMusicSnippet;
class grLilypondWriter
{

public:

    static const char *LILYPOND_VERSION;

public:
    grLilypondWriter();
    ~grLilypondWriter();

    void WriteMusicSnippetToFile(grMusicSnippet *snippet, const char *fname);

private:
    // The file currently being written to
    std::fstream m_file;

private:

    void WriteLilypondHeader();
    void WriteVoice(grNoteSequence *sequence, grMusicSnippet *parent, int voiceNum);

};

#endif // GR_LILYPOND_WRITER_H