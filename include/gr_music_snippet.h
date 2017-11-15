#ifndef GR_MUSIC_SNIPPET_H
#define GR_MUSIC_SNIPPET_H

#include "gr_note_sequence.h"

#include <string>

class grKey
{
public:
    enum QUALITY
    {
        MAJOR,
        MINOR,
        UNDEFINED_QUALITY
    };

    enum NOTE
    {
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        UNDEFINED_NOTE
    };

    enum ACCIDENTAL
    {
        SHARP,
        FLAT,
        NATURAL,
        UNDEFINED_ACCIDENTAL
    };

public:

    grKey();
    ~grKey();

    QUALITY     Quality;
    NOTE        Note;
    ACCIDENTAL  Accidental;

    std::string GetLilypondKeyString() const;

};

class grMusicSnippet
{
public:
    enum KEY_QUALITY
    {
        MAJOR,
        MINOR
    };

public:
    grMusicSnippet();
    ~grMusicSnippet();

    // Create a new voice
    grNoteSequence *NewVoice();

    // Get the voice count
    int GetVoiceCount();

    // Get a voice at a particular index
    grNoteSequence *GetVoice(int index);

    // Get the key associated with this snippet
    grKey *GetKey() { return &m_key; }

    // Set the meter numerator
    void SetMeterNumerator(int numerator) { m_meterNumerator = numerator; }

    // Get the meter numerator
    int GetMeterNumerator() const { return m_meterNumerator; }

    // Set the meter denominator
    void SetMeterDenominator(int denominator) { m_meterDenominator = denominator; }

    // Get the meter denominator
    int GetMeterDenominator() const { return m_meterDenominator; }
    
private:
    // Store all the voices for this snippet
    grDynamicArray<grNoteSequence, 4> m_voices;

    // The key of this snippet
    grKey m_key;

    // Meter numerator
    int m_meterNumerator;

    // Meter denominator
    int m_meterDenominator;

};

#endif // GR_MUSIC_SNIPPET_H