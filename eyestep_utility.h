#pragma once
#include "eyestep.h"

namespace EyeStep
{
	namespace util
	{
		extern DWORD setMemoryPage(uint32_t address, DWORD protect, size_t size = 0x3FF);

		extern void writeByte(uint32_t address, uint8_t value);
		extern void writeBytes(uint32_t address, uint8_t* value, size_t count);
		extern void writeShort(uint32_t address, uint16_t value);
		extern void writeInt(uint32_t address, uint32_t value);
		extern void writeFloat(uint32_t address, float value);
		extern void writeQword(uint32_t address, uint64_t value);
		extern void writeDouble(uint32_t address, double value);

		extern uint8_t readByte(uint32_t address);
		extern uint8_t* readBytes(uint32_t address, size_t count);
		extern uint16_t readShort(uint32_t address);
		extern uint32_t readInt(uint32_t address);
		extern float readFloat(uint32_t address);
		extern uint64_t readQword(uint32_t address);
		extern double readDouble(uint32_t address);

		extern void freeBytes(uint8_t* bytes);

		extern uint32_t rebase(uint32_t address);
		extern uint32_t aslr(uint32_t address);
		extern uint32_t unaslr(uint32_t address);
		extern bool isRel(uint32_t address);
		extern bool isCall(uint32_t address);
		extern bool isPrologue(uint32_t address);
		extern bool isEpilogue(uint32_t address);
		extern bool isValidCode(uint32_t address);
		extern uint32_t getRel(uint32_t address);
		extern uint32_t getPrologue(uint32_t address);
		extern uint32_t nextPrologue(uint32_t address);
		extern uint32_t nextCall(uint32_t address, bool location = false, bool prologue = false);
		extern uint32_t prevCall(uint32_t address, bool location = false, bool prologue = false);
		extern uint32_t nextRef(uint32_t start, uint32_t func_search, bool prologue = true);
		extern uint32_t prevRef(uint32_t start, uint32_t func_search, bool prologue = true);
		extern uint32_t nextPointer(uint32_t start, uint32_t ptr_search, bool prologue = true);
		extern uint32_t prevPointer(uint32_t start, uint32_t ptr_search, bool prologue = true);

		extern std::vector<uint32_t> getCalls(uint32_t address);
		extern std::vector<uint32_t> getPointers(uint32_t address);
	}

	namespace scanner
	{
		typedef std::vector<uint32_t> scan_results;

		enum
		{
			byte_equal,
			word_equal,
			int_equal,
			byte_notequal,
			word_notequal,
			int_notequal
		};

        struct scan_check
        {
            int type;
            int offset;
			void* value;
        };

		extern bool compare_bytes(const uint8_t* location, const uint8_t* aob, const char* mask);
		extern scan_results scan(const char* aob, bool code = true, int align = 1, int endresult = 0, std::vector<scan_check>checks = std::vector<scan_check>());
		extern std::string aobstring(std::string str); // converts a string to a scan-able AOB
	}
}
