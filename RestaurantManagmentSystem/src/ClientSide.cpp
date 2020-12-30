#include "ClientSide.h"

void ClientSide::ClientSide::start()
{
	while (1)
	{
		size_t clientChoice = ClientScreenM::start();

		if (clientChoice == 101)
			break;
		else
		{
			continue;
		}
	}
}