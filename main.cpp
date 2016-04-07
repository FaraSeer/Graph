
#include "AllUnits.h"
#include "Circuit.h"

int main()
{
	new Junction(CTSource, 1, CTWire, 2);
	new Junction(CTWire, 1, CTWire, 3);
	new Junction(CTWire, 1, CTWire, 4);
	new Junction(CTWire, 2, CTSource, 6);
	new Junction(CTWire, 2, CTWire, 5);
	new Junction(CTWire, 2, CTWire, 3);

	Circuit::getPtr()->clk();
}
