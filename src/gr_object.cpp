#include "gr_object.h"

#include <stdarg.h>
#include <stdio.h>

grObject::grObject()
{
	m_typeID = "GR_OBJECT";
	m_debugName = "NO_NAME";
}

grObject::grObject(const char *typeID)
{
	m_typeID = typeID;
	m_debugName = "NO_NAME";
}

grObject::~grObject()
{
}

void grObject::SetDebugName(const char *debugName)
{
	m_debugName = debugName;
}