#ifndef GR_BASE_H
#define GR_BASE_H

#include "gr_dynamic_array.h"

class grObject : public grDynamicArrayElement
{
public:
	grObject();
	grObject(const char *typeID);
	~grObject();

	void SetDebugName(const char *debugName);
	const char *GetDebugName() const { return m_debugName; }
	const char *GetTypeID() const { return m_typeID; }

protected:
	const char *m_debugName;
	const char *m_typeID;
};

#endif
