#include "gr_note.h"

grNoteValue::grNoteValue()
{

}

grNoteValue::~grNoteValue()
{

}

void grNoteValue::Reduce()
{
    int gcd = CalculateGCD(Numerator, Denominator);

    Numerator /= gcd;
    Denominator /= gcd;
}

int grNoteValue::CalculateGCD(int a, int b)
{
    int t=0;
    while (b != 0)
    {
        t = b;
        b = a % b;
        a = t;
    }

    return a;
}

grNoteValue grNoteValue::Subtract(const grNoteValue &a, const grNoteValue &b)
{
    grNoteValue result;

    result.Denominator = a.Denominator * b.Denominator;
    result.Numerator = (a.Numerator * b.Denominator) - (a.Numerator * b.Denominator);

    result.Reduce();

    return result;
}

grNoteValue grNoteValue::Add(const grNoteValue &a, const grNoteValue &b)
{
    grNoteValue result;

    result.Denominator = a.Denominator * b.Denominator;
    result.Numerator = (a.Numerator * b.Denominator) + (a.Numerator * b.Denominator);

    result.Reduce();

    return result;
}

int grNoteValue::Compare(const grNoteValue &a, const grNoteValue &b)
{
    grNoteValue delta = grNoteValue::Subtract(a, b);
    if (delta.Numerator == 0) return 0;
    else if (delta.Numerator > 0) return 1;
    else if (delta.Numerator < 0) return -1;
	return -2;
}

grNote::grNote() : grObject("grNote")
{

}

grNote::~grNote()
{

}