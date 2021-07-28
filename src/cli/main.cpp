#include <stdio.h>

#include <DRAMPower/command/Command.h>

#include <DRAMPower/DDR4/DDR.h>

using namespace DRAMPower;

int main()
{
	MemSpecDDR4 ddr4;

	ddr4.numberOfBanks = 4;
	ddr4.banksPerGroup = 1;
	ddr4.numberOfBankGroups = 1;

	DDR ddr(ddr4);

	Command command;
	command.type = CmdType::ACT;
	command.timestamp = 20;

	ddr.doCommand(command);

	return 0;
};
