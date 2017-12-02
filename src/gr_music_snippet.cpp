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

const grNote::ACCIDENTAL *grKey::SIGNATURES[] = {
	// Natural keys
	{
		// A major
		{
			grNote::NATURAL,	// A
			grNote::NATURAL,	// B
			grNote::SHARP,		// C
			grNote::NATURAL,	// D
			grNote::NATURAL,	// E
			grNote::SHARP,		// F
			grNote::SHARP,		// G
		},

		// B major
		{
			grNote::SHARP,		// A
			grNote::NATURAL,	// B
			grNote::SHARP,		// C
			grNote::SHARP,		// D
			grNote::NATURAL,	// E
			grNote::SHARP,		// F
			grNote::SHARP,		// G
		},

		// C major
		{
			grNote::NATURAL,	// A
			grNote::NATURAL,	// B
			grNote::NATURAL,	// C
			grNote::NATURAL,	// D
			grNote::NATURAL,	// E
			grNote::NATURAL,	// F
			grNote::NATURAL,	// G
		},

		// D major
		{
			grNote::NATURAL,	// A
			grNote::NATURAL,	// B
			grNote::SHARP,		// C
			grNote::NATURAL,	// D
			grNote::NATURAL,	// E
			grNote::SHARP,		// F
			grNote::NATURAL,	// G
		},

		// E major
		{
			grNote::NATURAL,	// A
			grNote::NATURAL,	// B
			grNote::SHARP,		// C
			grNote::SHARP,		// D
			grNote::NATURAL,	// E
			grNote::SHARP,		// F
			grNote::SHARP,		// G
		},

		// F major
		{
			grNote::NATURAL,	// A
			grNote::FLAT,		// B
			grNote::NATURAL,	// C
			grNote::NATURAL,	// D
			grNote::NATURAL,	// E
			grNote::NATURAL,	// F
			grNote::NATURAL,	// G
		},

		// G major
		{
			grNote::NATURAL,	// A
			grNote::NATURAL,	// B
			grNote::NATURAL,	// C
			grNote::NATURAL,	// D
			grNote::NATURAL,	// E
			grNote::SHARP,		// F
			grNote::NATURAL,	// G
		},

	},

	// Sharp keys
	{
		// A sharp major
		{
			grNote::SHARP,			// A
			grNote::SHARP,			// B
			grNote::DOUBLE_SHARP,	// C
			grNote::SHARP,			// D
			grNote::SHARP,			// E
			grNote::DOUBLE_SHARP,	// F
			grNote::DOUBLE_SHARP,	// G
		},

		// B sharp major
		{
			grNote::DOUBLE_SHARP,	// A
			grNote::SHARP,			// B
			grNote::DOUBLE_SHARP,	// C
			grNote::DOUBLE_SHARP,	// D
			grNote::SHARP,			// E
			grNote::DOUBLE_SHARP,	// F
			grNote::DOUBLE_SHARP,	// G
		},

		// C sharp major
		{
			grNote::SHARP,		// A
			grNote::SHARP,		// B
			grNote::SHARP,		// C
			grNote::SHARP,		// D
			grNote::SHARP,		// E
			grNote::SHARP,		// F
			grNote::SHARP,		// G
		},

		// D sharp major
		{
			grNote::SHARP,			// A
			grNote::SHARP,			// B
			grNote::DOUBLE_SHARP,	// C
			grNote::SHARP,			// D
			grNote::SHARP,			// E
			grNote::DOUBLE_SHARP,	// F
			grNote::SHARP,			// G
		},

		// E sharp major
		{
			grNote::SHARP,			// A
			grNote::SHARP,			// B
			grNote::DOUBLE_SHARP,	// C
			grNote::DOUBLE_SHARP,	// D
			grNote::SHARP,			// E
			grNote::DOUBLE_SHARP,	// F
			grNote::DOUBLE_SHARP,	// G
		},

		// F sharp major
		{
			grNote::SHARP,		// A
			grNote::NATURAL,	// B
			grNote::SHARP,		// C
			grNote::SHARP,		// D
			grNote::SHARP,		// E
			grNote::SHARP,		// F
			grNote::SHARP,		// G
		},

		// G sharp major
		{
			grNote::SHARP,			// A
			grNote::SHARP,			// B
			grNote::SHARP,			// C
			grNote::SHARP,			// D
			grNote::SHARP,			// E
			grNote::DOUBLE_SHARP,	// F
			grNote::SHARP,			// G
		},

	},

	// Flat keys
	{
		// A flat major
		{
			grNote::FLAT,		// A
			grNote::FLAT,		// B
			grNote::NATURAL,	// C
			grNote::FLAT,		// D
			grNote::FLAT,		// E
			grNote::NATURAL,	// F
			grNote::NATURAL,	// G
		},

		// B flat major
		{
			grNote::NATURAL,	// A
			grNote::FLAT,		// B
			grNote::NATURAL,	// C
			grNote::NATURAL,	// D
			grNote::FLAT,		// E
			grNote::NATURAL,	// F
			grNote::NATURAL,	// G
		},

		// C flat major
		{
			grNote::FLAT,		// A
			grNote::FLAT,		// B
			grNote::FLAT,		// C
			grNote::FLAT,		// D
			grNote::FLAT,		// E
			grNote::FLAT,		// F
			grNote::FLAT,		// G
		},

		// D flat major
		{
			grNote::FLAT,		// A
			grNote::FLAT,		// B
			grNote::NATURAL,	// C
			grNote::FLAT,		// D
			grNote::FLAT,		// E
			grNote::NATURAL,	// F
			grNote::FLAT,		// G
		},

		// E flat major
		{
			grNote::FLAT,		// A
			grNote::FLAT,		// B
			grNote::NATURAL,	// C
			grNote::NATURAL,	// D
			grNote::FLAT,		// E
			grNote::NATURAL,	// F
			grNote::NATURAL,	// G
		},

		// F flat major
		{
			grNote::FLAT,			// A
			grNote::DOUBLE_FLAT,	// B
			grNote::FLAT,			// C
			grNote::FLAT,			// D
			grNote::FLAT,			// E
			grNote::FLAT,			// F
			grNote::FLAT,			// G
		},

		// G flat major
		{
			grNote::FLAT,		// A
			grNote::FLAT,		// B
			grNote::FLAT,		// C
			grNote::FLAT,		// D
			grNote::FLAT,		// E
			grNote::NATURAL,	// F
			grNote::FLAT,		// G
		},
	}
};

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

grNote::ACCIDENTAL *grKey::lookupKeySignature(grKey::NOTE note, grKey::ACCIDENTAL accidental)
{
	return grKey::SIGNATURES[accidental][(int)note];
}

grNote::ACCIDENTAL *grKey::getKeySignature()
{
	if (Quality == MAJOR)
	{
		return lookupKeySignature(Note, Accidental);
	}

	else if (Quality == MINOR)
	{
		if (Accidental == SHARP)
		{
			switch (Note)
			{
			case A:
				return lookupKeySignature(C, SHARP);
				break;
			case B:
				return lookupKeySignature(D, SHARP);
				break;
			case C:
				return lookupKeySignature(E, NATURAL);
				break;
			case D:
				return lookupKeySignature(F, SHARP);
				break;
			case E:
				return lookupKeySignature(G, SHARP);
				break;
			case F:
				return lookupKeySignature(A, NATURAL);
				break;
			case G:
				return lookupKeySignature(B, NATURAL);
				break;
			}
		}

		else if (Accidental == FLAT)
		{
			switch (Note)
			{
			case A:
				return lookupKeySignature(C, FLAT);
				break;
			case B:
				return lookupKeySignature(D, FLAT);
				break;
			case C:
				return lookupKeySignature(D, NATURAL);
				break;
			case D:
				return lookupKeySignature(F, FLAT);
				break;
			case E:
				return lookupKeySignature(G, FLAT);
				break;
			case F:
				return lookupKeySignature(G, NATURAL);
				break;
			case G:
				return lookupKeySignature(A, NATURAL);
				break;
			}
		}

		else if (Accidental == NATURAL)
		{
			switch (Note)
			{
			case A:
				return lookupKeySignature(C, NATURAL);
				break;
			case B:
				return lookupKeySignature(D, NATURAL);
				break;
			case C:
				return lookupKeySignature(E, FLAT);
				break;
			case D:
				return lookupKeySignature(F, NATURAL);
				break;
			case E:
				return lookupKeySignature(G, NATURAL);
				break;
			case F:
				return lookupKeySignature(A, FLAT);
				break;
			case G:
				return lookupKeySignature(B, FLAT);
				break;
			}
		}
	}
}

void grKey::resolveNote(grNote::NOTE note, grNote::ACCIDENTAL accidental, grNote::NOTE *correctedNote, grNote::ACCIDENTAL *correctedAccidental)
{

	grNote::NOTE leadingTone = grNote::getPreviousTone((grNote::NOTE)Note);
	grNote::ACCIDENTAL keyAccidental = getKeySignature()[note];

	if (keyAccidental == accidental)
	{
		*correctedNote = note;
		*correctedAccidental = accidental;
	}

	if (accidental == grNote::SHARP)
	{
		if (keyAccidental == grNote::SHARP)
		{
			*correctedNote = note;
			*correctedAccidental = accidental;
		}
		else if (keyAccidental == grNote::FLAT)
		{

		}
	}

	if (leadingTone == note)
	{
		grNote::ACCIDENTAL leadingToneAccidental =

		if (Accidental == SHARP)
			return grNote::DOUBLE_SHARP;
		else if (Accidental == FLAT)
			return grNote::
	}

	return getKeySignature()[(int)note];
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