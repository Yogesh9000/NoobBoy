#include "cpu.hpp"
#include "dummy_bus.hpp"
#include "timer.hpp"
#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include "test_helper.hpp"

DEFINE_TEST(BLARGG_CPU_INDIVIDUAL, 01_SPECIAL, "01-special");
DEFINE_TEST(BLARGG_CPU_INDIVIDUAL, 02_INTERRUPTS, "02-interrupts");
DEFINE_TEST(BLARGG_CPU_INDIVIDUAL, 03_SP_HL, "03-op sp,hl");
DEFINE_TEST(BLARGG_CPU_INDIVIDUAL, 04_R_IMM, "04-op r,imm");
DEFINE_TEST(BLARGG_CPU_INDIVIDUAL, 05_RP, "05-op rp");
DEFINE_TEST(BLARGG_CPU_INDIVIDUAL, 06_LD_R_R, "06-ld r,r");
DEFINE_TEST(BLARGG_CPU_INDIVIDUAL, 07_JR_JP_CALL_RET_RST, "07-jr,jp,call,ret,rst");
DEFINE_TEST(BLARGG_CPU_INDIVIDUAL, 08_MIST, "08-misc instrs");
DEFINE_TEST(BLARGG_CPU_INDIVIDUAL, 09_R_R, "09-op r,r");
DEFINE_TEST(BLARGG_CPU_INDIVIDUAL, 10_BIT, "10-bit ops");
DEFINE_TEST(BLARGG_CPU_INDIVIDUAL, 11_A_HL, "11-op a,(hl)");
