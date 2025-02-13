// license:BSD-3-Clause
// copyright-holders:AJR
/***************************************************************************

    VTech Intelligence Advance E/R Lerncomputer

    TODO: dyndesk writes to low memory go to external RAM instead? It also
    eventually runs off into nonexistent memory.

***************************************************************************/

#include "emu.h"
#include "cpu/m6502/st2204.h"
#include "cpu/m6502/st2205u.h"

class inteladv_state : public driver_device
{
public:
	inteladv_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag)
		, m_maincpu(*this, "maincpu")
	{
	}

	void inteladv(machine_config &config);
	void dyndesk(machine_config &config);

private:
	void inteladv_map(address_map &map);
	void dyndesk_map(address_map &map);

	required_device<cpu_device> m_maincpu;
};

void inteladv_state::inteladv_map(address_map &map)
{
	map(0x000000, 0x7fffff).rom().region("maincpu", 0);
}

void inteladv_state::dyndesk_map(address_map &map)
{
	map(0x000000, 0x1fffff).rom().region("maincpu", 0).nopw();
}

static INPUT_PORTS_START( inteladv )
INPUT_PORTS_END

void inteladv_state::inteladv(machine_config &config)
{
	ST2205U(config, m_maincpu, 32768 * 122);
	m_maincpu->set_addrmap(AS_DATA, &inteladv_state::inteladv_map);
}

void inteladv_state::dyndesk(machine_config &config)
{
	ST2204(config, m_maincpu, 32768 * 122);
	m_maincpu->set_addrmap(AS_DATA, &inteladv_state::dyndesk_map);
}

ROM_START( inteladv )
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD( "vtechinteladv.bin", 0x000000, 0x800000, CRC(e24dbbcb) SHA1(7cb7f25f5eb123ae4c46cd4529aafd95508b2210) )
ROM_END

ROM_START( dyndesk )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD( "27-07710-000.u9", 0x000000, 0x200000, CRC(092b0303) SHA1(e3a58cac9b0a1c68f1bdb5ea0af0b0dd223fb340) )
	// PCB also has Hynix HY62WT081ED70C (32Kx8 CMOS SRAM) at U2
ROM_END

ROM_START( cars2lap )
	ROM_REGION( 0x200000, "maincpu", 0 )
	// Flash dump contains some 65C02 code starting at $000D6A, but mostly appears to be custom bytecode or non-executable data banked in 32K blocks
	ROM_LOAD("n25s16.u6", 0x00000, 0x200000, CRC(ec1ba96e) SHA1(51b8844ae77adf20f74f268d380d268c9ce19785))
ROM_END

//    YEAR  NAME      PARENT  COMPAT  MACHINE   INPUT     CLASS           INIT        COMPANY  FULLNAME                              FLAGS
COMP( 2005, inteladv, 0,      0,      inteladv, inteladv, inteladv_state, empty_init, "VTech", "Intelligence Advance E/R (Germany)", MACHINE_IS_SKELETON )
COMP( 2003, dyndesk,  0,      0,      dyndesk,  inteladv, inteladv_state, empty_init, "VTech", "DynamiDesk (Germany)",               MACHINE_IS_SKELETON )
COMP( 2012, cars2lap, 0,      0,      dyndesk,  inteladv, inteladv_state, empty_init, "VTech", "CARS 2 Laptop (Germany)",            MACHINE_IS_SKELETON ) // probably doesn't belong here
