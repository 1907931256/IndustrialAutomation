#pragma once
#include "action.h"
#include "Object.h"

class CActionPlaySound :
	public CAction
{
public:
	CActionPlaySound(CObject* Owner_);
	~CActionPlaySound(void);

	//������� "����������"
	virtual void Update();
};
