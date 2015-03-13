#ifndef LowerRack_H
#define LowerRack_H

#include "Commands/CommandGroup.h"
#include "WPILib.h"

//THIS SHOULD ONLY BE CALLED WHEN RACK IS IN UPRIGHT POSITION
class LowerRack: public CommandGroup
{
public:
	LowerRack();
};

#endif
