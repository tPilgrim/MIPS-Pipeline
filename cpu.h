#ifndef CPU_H
#define CPU_H

#endif // CPU_H

#pragma once
#include <bitset>
#include <vector>
#include <string>

using namespace std;

struct UnitControl {
    bool RegDst = 0, ALUSrc = 0, Branch = 0, Jump = 0;
    bool MemWrite = 0, MemtoReg = 0, RegWrite = 0;
    bitset<3> ALUOp;
};

struct IF_ID {
    bitset<32> instr;
    int PC = 0;
    bool valid = false;
};

struct ID_EX {
    bitset<32> RD1, RD2, imm;
    bitset<5> rt, rd, sa;
    bitset<6> func;
    bitset<26> address;
    int PC = 0;
    UnitControl control;
    bool valid = false;
};

struct EX_MEM {
    bitset<32> ALURes, RD2;
    bitset<5> WriteReg;
    UnitControl control;
    bool Zero = false;
    int BranchAddress = 0;
    int JumpAddress = 0;
    int PC = 0;
    bool valid = false;
};

struct MEM_WB {
    bitset<32> ALURes, MemData;
    bitset<5> WriteReg;
    UnitControl control;
    int PC = 0;
    bool valid = false;
};

class PipelineCPU {
public:
    std::vector<std::string> asmLines;

    std::bitset<32> Instr[32];
    std::bitset<32> Regs[32];
    std::bitset<32> Mem[32];

    int instrCount = 0;
    int memCount = 0;
    int PC = 0;
    int cycle = 0;

    IF_ID IF_ID_Reg;
    ID_EX ID_EX_Reg;
    EX_MEM EX_MEM_Reg;
    MEM_WB MEM_WB_Reg;

    void load(const std::string& filename);
    bool step();

    int IF_PC = -1;
    int ID_PC = -1;
    int EX_PC = -1;
    int MEM_PC = -1;
    int WB_PC = -1;

private:
    void IF(IF_ID& next_IF_ID, int pc);
    void ID(IF_ID& old_IF_ID, ID_EX& next_ID_EX);
    void EX(ID_EX& old_ID_EX, EX_MEM& next_EX_MEM);
    void MEM(EX_MEM& old_EX_MEM, MEM_WB& next_MEM_WB, int& pc_next);
    void WB(MEM_WB& old_MEM_WB);
    UnitControl mainControl(std::bitset<6> opcode);
};

