#include <fstream>
#include <bitset>
#include <string>
#include "cpu.h"
#include <fstream>
#include <cstdlib>
#include <cstdint>

using namespace std;

UnitControl PipelineCPU:: mainControl(bitset<6> opcode)
{
    UnitControl c;
    string op = opcode.to_string();

    if (op == "000000")
    {
        c.RegDst = 1; c.RegWrite = 1; c.ALUOp = bitset<3>("010"); // R
    }
    else if (op == "001000")
    {
        c.ALUSrc = 1; c.RegWrite = 1; c.ALUOp = bitset<3>("000"); // ADDI
    }
    else if (op == "100011")
    {
        c.ALUSrc = 1; c.MemtoReg = 1; c.RegWrite = 1; c.ALUOp = bitset<3>("000"); // LW
    }
    else if (op == "101011")
    {
        c.ALUSrc = 1; c.MemWrite = 1; c.ALUOp = bitset<3>("000"); // SW
    }
    else if (op == "000100")
    {
        c.Branch = 1; c.ALUOp = bitset<3>("001");  // BEQ
    }
    else if (op == "001100")
    {
        c.ALUSrc = 1; c.RegWrite = 1; c.ALUOp = bitset<3>("100");  // ANDI
    }
    else if (op == "001101")
    {
        c.ALUSrc = 1; c.RegWrite = 1; c.ALUOp = bitset<3>("011");  // ORI
    }
    else if (op == "000010")
    {
        c.Jump = 1;  // J
    }
    return c;
}

void PipelineCPU::WB(MEM_WB& old_MEM_WB)
{
    WB_PC = old_MEM_WB.PC;

    bitset<32> result;
    UnitControl ctrl = old_MEM_WB.control;

    if (ctrl.RegWrite)
    {
        if (ctrl.MemtoReg)
        {
            result = old_MEM_WB.MemData;
        }
        else
        {
            result = old_MEM_WB.ALURes;
        }
        Regs[old_MEM_WB.WriteReg.to_ulong()] = result;
    }
}

void PipelineCPU::MEM(EX_MEM& old_EX_MEM, MEM_WB& next_MEM_WB, int& pc_next)
{
    MEM_PC = old_EX_MEM.PC;

    next_MEM_WB.control = old_EX_MEM.control;
    next_MEM_WB.WriteReg = old_EX_MEM.WriteReg;
    next_MEM_WB.ALURes = old_EX_MEM.ALURes;
    UnitControl ctrl = old_EX_MEM.control;
    next_MEM_WB.PC = old_EX_MEM.PC;

    if (ctrl.MemWrite)
    {
        Mem[old_EX_MEM.ALURes.to_ulong()] = old_EX_MEM.RD2.to_ulong();
    }
    else if (ctrl.MemtoReg)
    {
        next_MEM_WB.MemData = Mem[old_EX_MEM.ALURes.to_ulong()];
    }

    next_MEM_WB.valid = true;

    if (ctrl.Branch && old_EX_MEM.Zero)
    {
        pc_next = old_EX_MEM.BranchAddress;
    }
    else if (ctrl.Jump)
    {
        pc_next = old_EX_MEM.JumpAddress;
    }
}

void PipelineCPU::EX(ID_EX& old_ID_EX, EX_MEM& next_EX_MEM)
{
    EX_PC = old_ID_EX.PC;

    bitset<32> ALURes, ALUIn;
    bitset<5> WriteReg;
    UnitControl ctrl = old_ID_EX.control;
    bitset<3> aluOp = ctrl.ALUOp;
    bitset<32> operandRD1 = old_ID_EX.RD1;

    if (ctrl.ALUSrc)
    {
        ALUIn = old_ID_EX.imm.to_ulong();
    }
    else
    {
        ALUIn = old_ID_EX.RD2;
    }

    if (aluOp == bitset<3>("010"))
    {
        switch (old_ID_EX.func.to_ulong())
        {
        case 0b100000: ALURes = operandRD1.to_ulong() + ALUIn.to_ulong(); break;
        case 0b100010: ALURes = operandRD1.to_ulong() - ALUIn.to_ulong(); break;
        case 0b100101: ALURes = operandRD1.to_ulong() | ALUIn.to_ulong(); break;
        case 0b100100: ALURes = operandRD1.to_ulong() & ALUIn.to_ulong(); break;
        case 0b000000: ALURes = ALUIn.to_ulong() << old_ID_EX.sa.to_ulong(); break;
        case 0b000010: ALURes = ALUIn.to_ulong() >> old_ID_EX.sa.to_ulong(); break;
        case 0b101010: ALURes = (operandRD1.to_ulong() < ALUIn.to_ulong()) ? 1 : 0; break;
        case 0b000011:
        {
            int32_t sVal = static_cast<int32_t>(ALUIn.to_ulong());
            ALURes = static_cast<unsigned long>(sVal >> old_ID_EX.sa.to_ulong());
            break;
        }
        default: ALURes = operandRD1.to_ulong() + ALUIn.to_ulong();
        }
    }
    else if (aluOp == bitset<3>("000"))
    {
        ALURes = operandRD1.to_ulong() + ALUIn.to_ulong();
    }
    else if (aluOp == bitset<3>("001"))
    {
        ALURes = operandRD1.to_ulong() - ALUIn.to_ulong();
        next_EX_MEM.Zero = (ALURes.to_ulong() == 0);
    }
    else if (aluOp == bitset<3>("011"))
    {
        ALURes = operandRD1.to_ulong() | ALUIn.to_ulong();
    }
    else
    {
        ALURes = operandRD1.to_ulong() & ALUIn.to_ulong();
    }

    if (ctrl.RegDst)
    {
        WriteReg = old_ID_EX.rd;
    }
    else
    {
        WriteReg = old_ID_EX.rt;
    }

    next_EX_MEM.ALURes = ALURes;
    next_EX_MEM.RD2 = old_ID_EX.RD2;
    next_EX_MEM.control = old_ID_EX.control;
    next_EX_MEM.WriteReg = WriteReg;
    next_EX_MEM.BranchAddress = old_ID_EX.PC + old_ID_EX.imm.to_ulong();
    next_EX_MEM.JumpAddress = old_ID_EX.address.to_ulong();
    next_EX_MEM.Zero = next_EX_MEM.Zero;
    next_EX_MEM.PC = old_ID_EX.PC;
    next_EX_MEM.valid = true;
}

void PipelineCPU::ID(IF_ID& old_IF_ID, ID_EX& next_ID_EX)
{
    ID_PC = old_IF_ID.PC;

    bitset<32> instr = old_IF_ID.instr;
    bitset<6> opcode = (instr.to_ulong() >> 26);
    bitset<5> rs = (instr.to_ulong() >> 21);
    bitset<5> rt = (instr.to_ulong() >> 16);
    bitset<5> rd = (instr.to_ulong() >> 11);
    bitset<5> sa = (instr.to_ulong() >> 6);
    bitset<6> func = instr.to_ulong();
    bitset<16> imm = instr.to_ulong();
    bitset<26> address = instr.to_ulong();

    bitset<32> Ext_Imm;

    for (int i = 0; i < 16; i++)
    {
        Ext_Imm[i] = imm[i];
    }

    for (int i = 16; i < 32; i++)
    {
        Ext_Imm[i] = imm[15];
    }

    UnitControl c = mainControl(opcode);

    next_ID_EX.RD1 = Regs[rs.to_ulong()];
    next_ID_EX.RD2 = Regs[rt.to_ulong()];
    next_ID_EX.rt = rt;
    next_ID_EX.rd = rd;
    next_ID_EX.sa = sa;
    next_ID_EX.func = func;
    next_ID_EX.imm = Ext_Imm;
    next_ID_EX.address = address;
    next_ID_EX.PC = old_IF_ID.PC;
    next_ID_EX.control = c;
    next_ID_EX.valid = true;
}

void PipelineCPU::IF(IF_ID& next_IF_ID, int pc)
{
    IF_PC = pc;
    next_IF_ID.instr = Instr[pc];
    next_IF_ID.PC = pc;
    next_IF_ID.valid = true;
}

bool PipelineCPU::step()
{
    int pc_next = PC + 1;

    IF_ID next_IF_ID;
    ID_EX next_ID_EX;
    EX_MEM next_EX_MEM;
    MEM_WB next_MEM_WB;

    if (MEM_WB_Reg.valid)
    {
        WB(MEM_WB_Reg);
    }

    if (EX_MEM_Reg.valid)
    {
        MEM(EX_MEM_Reg, next_MEM_WB, pc_next);
    }

    if (ID_EX_Reg.valid)
    {
        EX(ID_EX_Reg, next_EX_MEM);
    }

    if (IF_ID_Reg.valid)
    {
        ID(IF_ID_Reg, next_ID_EX);
    }

    if (PC < instrCount)
    {
        IF(next_IF_ID, PC);
    }
    else
    {
        next_IF_ID.valid = false;
    }

    MEM_WB_Reg  = next_MEM_WB;
    EX_MEM_Reg  = next_EX_MEM;
    ID_EX_Reg   = next_ID_EX;
    IF_ID_Reg   = next_IF_ID;

    PC = pc_next;

    cycle++;

    return !(PC >= instrCount &&
             !IF_ID_Reg.valid &&
             !ID_EX_Reg.valid &&
             !EX_MEM_Reg.valid &&
             !MEM_WB_Reg.valid);
}

void PipelineCPU::load(const string& filename)
{
    instrCount = 0;
    memCount = 0;
    PC = 0;
    cycle = 0;
    asmLines.clear();

    IF_PC = ID_PC = EX_PC = MEM_PC = WB_PC = -1;

    IF_ID_Reg.valid = false;
    ID_EX_Reg.valid = false;
    EX_MEM_Reg.valid = false;
    MEM_WB_Reg.valid = false;

    for (int i = 0; i < 32; ++i)
        Regs[i] = 0;

    for (int i = 0; i < 32; ++i)
        Mem[i] = 0;

    ifstream fin(filename);
    string line;

    while (getline(fin, line)) {
        if (line == "STOP") break;
        Instr[instrCount++] = bitset<32>(line);
    }

    while (getline(fin, line)) {
        if (line == "STOP") break;
        Mem[memCount++] = bitset<32>(line);
    }

    while (getline(fin, line)) {
        if (line == "STOP") break;
        asmLines.push_back(line);
    }
}
