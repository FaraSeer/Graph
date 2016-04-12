
#include "AllUnits.h"
#include "Circuit.h"

void createUnits(int _num)
{
	for (int i = 0; i < _num; i++)
	{
		Unit* u = new Unit(i);
		u->doON();
	}
}


int main()
{
	int units_num = 10;
	createUnits(units_num);

	new Junction(CTSource, 1, CTWire, 2);
	new Junction(CTWire, 1, CTWire, 3);
	new Junction(CTWire, 1, CTWire, 4);
	new Junction(CTWire, 2, CTSource, 6);
	new Junction(CTWire, 2, CTWire, 5);
	new Junction(CTWire, 2, CTWire, 3);
	new Junction(CTSource, 6, CTWire, 7);
	new Junction(CTSource, 6, CTWire, 8);

	int unit = 0;
	int action = 0;
	while (true)
	{
		printf("=================================\n");
		printf("Enter Unit number and action...\n");
		printf("Units quantity: %d, enter -1 to skip\n", units_num);
		printf("Actions: 1 - select, 2 - on, 3 - off, 4 - otm, 0 - exit\n");
		scanf_s("%d %d", &unit, &action);
		if (unit == -1) continue;
		switch (action)
		{
		case 0:
			exit(0);
			break;
		case 1:
			AllUnits::getPtr()->getUnitById(unit)->doSELECT();
			break;
		case 2:
			AllUnits::getPtr()->getUnitById(unit)->doON();
			break;
		case 3:
			AllUnits::getPtr()->getUnitById(unit)->doOFF();
			break;
		case 4:
			AllUnits::getPtr()->getUnitById(unit)->doOTM();
			break;
		}
		AllUnits::getPtr()->clk();
	}
}
