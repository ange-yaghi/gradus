#include <global_settings.h>

#include "gr_midi.h"

int main()
{

	grMidiFile midi;
	grMidiSegment *segment = midi.Read("phrase_1_bach.mid");

	grMidiTrack *track1 = segment->GetTrack(1);
	grMidiTrack *track2 = segment->GetTrack(2);
	grMidiTrack *track3 = segment->GetTrack(3);
	grMidiTrack *track4 = segment->GetTrack(4);

	return 0;
}