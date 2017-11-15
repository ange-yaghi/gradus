#include "gr_music_snippet.h"

grKey::grKey()
{
    Note = UNDEFINED_NOTE;
    Accidental = UNDEFINED_ACCIDENTAL;
    Quality = UNDEFINED_QUALITY;
}

grKey::~grKey()
{

}

std::string grKey::GetLilypondKeyString() const
{
    std::string s = "";
    s += ('a' + (int)Note);

    if (Accidental == FLAT)
        s += "es";
    else if (Accidental == SHARP)
        s += "is";

    return s;
}

grMusicSnippet::grMusicSnippet()
{

}

grMusicSnippet::~grMusicSnippet()
{

}

grNoteSequence *grMusicSnippet::NewVoice()
{
    return m_voices.New();
}

int grMusicSnippet::GetVoiceCount()
{
    return m_voices.GetNumObjects();
}

grNoteSequence *grMusicSnippet::GetVoice(int index)
{
    return m_voices.Get(index);
}