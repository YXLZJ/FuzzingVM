#include <gtest/gtest.h>
#include <vector>
#include "symbol.hpp"
#include "directthreading.cpp"
#include "indirectthreading.cpp"
#include "routinethreading.cpp"
uint32_t float_to_uint32(float value) {
    return *reinterpret_cast<uint32_t*>(&value);
}
//Direct Threading
TEST(Arithmetic, HandlesAddition) {
    std::vector<unsigned> instructions = {DT_IMMI, 5, DT_IMMI, 3, DT_ADD, DT_SEEK, DT_END};
    DirectThreadingVM vm;
    vm.run_vm(instructions);
    EXPECT_EQ(vm.debug_num, 8); 
}

TEST(Arithmetic, HandlesSubtraction) {
    std::vector<unsigned> instructions = {DT_IMMI, 10, DT_IMMI, 4, DT_SUB, DT_SEEK, DT_END};
    DirectThreadingVM vm;
    vm.run_vm(instructions);
    EXPECT_EQ(vm.debug_num, 6);
}


TEST(Arithmetic, HandlesMultiplication) {
    std::vector<uint32_t> instructions = {DT_IMMI, 6, DT_IMMI, 7, DT_MUL, DT_SEEK, DT_END};
    DirectThreadingVM vm;
    vm.run_vm(instructions);
    EXPECT_EQ(vm.debug_num, 42);
}


TEST(Arithmetic, HandlesDivision) {
    std::vector<uint32_t> instructions = {DT_IMMI, 20, DT_IMMI, 5, DT_DIV, DT_SEEK, DT_END};
    DirectThreadingVM vm;
    vm.run_vm(instructions);
    EXPECT_EQ(vm.debug_num, 4);
}

TEST(FloatingPoint, HandlesFPAddition) {
    std::vector<uint32_t> instructions = {
        DT_IMMI, float_to_uint32(4.5f),
        DT_IMMI, float_to_uint32(0.5f),
        DT_FP_ADD, DT_SEEK, DT_END
    };
    DirectThreadingVM vm;
    vm.run_vm(instructions);
    EXPECT_EQ(vm.debug_num, float_to_uint32(5.0f));
}

TEST(ArithmeticOperations, HandleDecrement) {
    std::vector<uint32_t> instructions = {
        DT_IMMI, 5,
        DT_DEC,
        DT_SEEK, DT_END
    };
    DirectThreadingVM vm;
    vm.run_vm(instructions);
    EXPECT_EQ(vm.debug_num, 4); // 5 - 1 = 4
}

TEST(FloatingPoint, HandlesFPSubtraction) {
    std::vector<uint32_t> instructions = {
        DT_IMMI, float_to_uint32(5.5f),
        DT_IMMI, float_to_uint32(1.5f),
        DT_FP_SUB, DT_SEEK, DT_END
    };
    DirectThreadingVM vm;
    vm.run_vm(instructions);
    EXPECT_EQ(vm.debug_num, float_to_uint32(4.0f));
}

TEST(FloatingPoint, HandlesFPMultiplication) {
    std::vector<uint32_t> instructions = {
        DT_IMMI, float_to_uint32(2.0f),
        DT_IMMI, float_to_uint32(3.5f),
        DT_FP_MUL, DT_SEEK, DT_END
    };
    DirectThreadingVM vm;
    vm.run_vm(instructions);
    EXPECT_EQ(vm.debug_num, float_to_uint32(7.0f));
}

TEST(FloatingPoint, HandlesFPDivision) {
    std::vector<uint32_t> instructions = {
        DT_IMMI, float_to_uint32(7.5f),
        DT_IMMI, float_to_uint32(2.5f),
        DT_FP_DIV, DT_SEEK, DT_END
    };
    DirectThreadingVM vm;
    vm.run_vm(instructions);
    EXPECT_EQ(vm.debug_num, float_to_uint32(3.0f));
}

TEST(BitwiseOperations, HandleLeftShift) {
    std::vector<uint32_t> instructions = {
        DT_IMMI, 1,  
        DT_IMMI, 3,  
        DT_SHL,      
        DT_SEEK, DT_END
    };
    DirectThreadingVM vm;
    vm.run_vm(instructions);
    EXPECT_EQ(vm.debug_num, 8); 
}

TEST(BitwiseOperations, HandleRightShift) {
    std::vector<uint32_t> instructions = {
        DT_IMMI, 8,  
        DT_IMMI, 3,  
        DT_SHR,      
        DT_SEEK, DT_END
    };
    DirectThreadingVM vm;
    vm.run_vm(instructions);
    EXPECT_EQ(vm.debug_num, 1); 
}

TEST(MemoryOperations, HandleLoadAndStore) {
    std::vector<uint32_t> instructions = {        
        DT_IMMI, 100,          
        DT_STO, 0,                       
        DT_LOD, 0,              
        DT_SEEK, DT_END
    };
    DirectThreadingVM vm;
    vm.run_vm(instructions);
    EXPECT_EQ(vm.debug_num, 100); 
}

TEST(MemoryOperations, HandleMemoryCopy) {
    std::vector<uint32_t> instructions = {
        DT_STO_IMMI, 0, 123,  
        DT_MEMCPY, 4, 0, 4,   
        DT_LOD, 4,           
        DT_SEEK, DT_END
    };
    DirectThreadingVM vm;
    vm.run_vm(instructions);
    EXPECT_EQ(vm.debug_num, 123);
}

TEST(MemoryOperations, HandleMemorySet) {
    std::vector<uint32_t> instructions = {
        DT_MEMSET, 0, 255, 4, 
        DT_LOD, 0,            
        DT_SEEK, DT_END
    };
    DirectThreadingVM vm;
    vm.run_vm(instructions);
    EXPECT_EQ(vm.debug_num, 0xFFFFFFFF); 
}

TEST(ControlFlow, HandleJump) {
    std::vector<uint32_t> instructions = {DT_IMMI,0,DT_STO_IMMI,0,1,DT_LOD,0,DT_ADD,DT_LOD,0,DT_INC,DT_STO,0,DT_LOD,0,DT_IMMI,100,DT_GT,DT_JZ,5,DT_SEEK,DT_END};
    DirectThreadingVM vm;
    vm.run_vm(instructions);
    EXPECT_EQ(vm.debug_num, 5050); 
}
TEST(ComparisonOperations, HandleLessThan) {
    std::vector<uint32_t> instructions = {
        DT_IMMI, 5,
        DT_IMMI, 10,
        DT_LT,
        DT_SEEK, DT_END
    };
    DirectThreadingVM vm;
    vm.run_vm(instructions);
    EXPECT_EQ(vm.debug_num, 1); // 5 < 10
}

TEST(ComparisonOperations, HandleEqualTo) {
    std::vector<uint32_t> instructions = {
        DT_IMMI, 10,
        DT_IMMI, 10,
        DT_EQ,
        DT_SEEK, DT_END
    };
    DirectThreadingVM vm;
    vm.run_vm(instructions);
    EXPECT_EQ(vm.debug_num, 1); // 10 == 10
}

TEST(ComparisonOperations, HandleGreaterThanEqualTo) {
    std::vector<uint32_t> instructions = {
        DT_IMMI, 10,
        DT_IMMI, 5,
        DT_GT_EQ,
        DT_SEEK, DT_END
    };
    DirectThreadingVM vm;
    vm.run_vm(instructions);
    EXPECT_EQ(vm.debug_num, 1); // 10 >= 5
}

TEST(ComparisonOperations, HandleLessThanEqualTo) {
    std::vector<uint32_t> instructions = {
        DT_IMMI, 5,
        DT_IMMI, 10,
        DT_LT_EQ,
        DT_SEEK, DT_END
    };
    DirectThreadingVM vm;
    vm.run_vm(instructions);
    EXPECT_EQ(vm.debug_num, 1); // 5 <= 10
}

TEST(ControlFlow, HandleIfElse) {
    std::vector<uint32_t> instructions = {
        DT_IMMI, 1,               
        DT_IF_ELSE, 9, 13,         
        DT_IMMI, 0,               
        DT_SEEK, DT_END,
        DT_IMMI, 123,             
        DT_SEEK, DT_END,
        DT_IMMI, 456,             
        DT_SEEK, DT_END
    };
    DirectThreadingVM vm;
    vm.run_vm(instructions);
    EXPECT_EQ(vm.debug_num, 123); 
}

TEST(ControlFlow, HandleConditionalJump) {
    std::vector<uint32_t> instructions = {
        DT_IMMI, 1,               
        DT_JUMP_IF, 8,           
        DT_IMMI, 0,               
        DT_SEEK, DT_END,
        DT_IMMI, 123,            
        DT_SEEK, DT_END
    };
    DirectThreadingVM vm;
    vm.run_vm(instructions);
    EXPECT_EQ(vm.debug_num, 123); 
}

TEST(FunctionCalls, HandleFunctionCallAndReturn) {
    std::vector<uint32_t> instructions = {
        DT_IMMI, 10,              
        DT_CALL, 7, 1,              
        DT_SEEK, DT_END,          
        DT_IMMI, 2,               
        DT_ADD,                  
        DT_RET                    
    };
    DirectThreadingVM vm;
    vm.run_vm(instructions);
    EXPECT_EQ(vm.debug_num, 12);
}

//Indirect Threading
TEST(Arithmetic, HandlesAddition2) {
    std::vector<unsigned> instructions = {DT_IMMI, 5, DT_IMMI, 3, DT_ADD, DT_SEEK, DT_END};
    std::vector<unsigned> thread = {0,2,4,5,6};
    IndirectThreadingVM vm;
    vm.run_vm(instructions,thread);
    EXPECT_EQ(vm.debug_num, 8); 
}

TEST(Arithmetic, HandlesSubtraction2) {
    std::vector<unsigned> instructions = {DT_IMMI, 10, DT_IMMI, 4, DT_SUB, DT_SEEK, DT_END};
    std::vector<unsigned> thread = {0,2,4,5,6};
    IndirectThreadingVM vm;
    vm.run_vm(instructions,thread);
    EXPECT_EQ(vm.debug_num, 6);
}

TEST(Arithmetic, HandlesMultiplication2) {
    std::vector<uint32_t> instructions = {DT_IMMI, 6, DT_IMMI, 7, DT_MUL, DT_SEEK, DT_END};
    std::vector<unsigned> thread = {0,2,4,5,6};
    IndirectThreadingVM vm;
    vm.run_vm(instructions,thread);
    EXPECT_EQ(vm.debug_num, 42);
}

TEST(Arithmetic, HandlesDivision2) {
    std::vector<uint32_t> instructions = {DT_IMMI, 20, DT_IMMI, 5, DT_DIV, DT_SEEK, DT_END};
    std::vector<unsigned> thread = {0,2,4,5,6};
    IndirectThreadingVM vm;
    vm.run_vm(instructions,thread);
    EXPECT_EQ(vm.debug_num, 4);
}

TEST(FloatingPoint, HandlesFPAddition2) {
    std::vector<uint32_t> instructions = {
        DT_IMMI, float_to_uint32(4.5f),
        DT_IMMI, float_to_uint32(0.5f),
        DT_FP_ADD, DT_SEEK, DT_END
    };
    std::vector<unsigned> thread = {0,2,4,5,6};
    IndirectThreadingVM vm;
    vm.run_vm(instructions,thread);
    EXPECT_EQ(vm.debug_num, float_to_uint32(5.0f));
}

TEST(ArithmeticOperations, HandleDecrement2) {
    std::vector<uint32_t> instructions = {
        DT_IMMI, 5,
        DT_DEC,
        DT_SEEK, DT_END
    };
    std::vector<unsigned> thread = {0,2,3,4};
    IndirectThreadingVM vm;
    vm.run_vm(instructions,thread);
    EXPECT_EQ(vm.debug_num, 4); // 5 - 1 = 4
}

TEST(FloatingPoint, HandlesFPSubtraction2) {
    std::vector<uint32_t> instructions = {
        DT_IMMI, float_to_uint32(5.5f),
        DT_IMMI, float_to_uint32(1.5f),
        DT_FP_SUB, DT_SEEK, DT_END
    };
    std::vector<unsigned> thread = {0,2,4,5,6};
    IndirectThreadingVM vm;
    vm.run_vm(instructions,thread);
    EXPECT_EQ(vm.debug_num, float_to_uint32(4.0f));
}

TEST(FloatingPoint, HandlesFPMultiplication2) {
    std::vector<uint32_t> instructions = {
        DT_IMMI, float_to_uint32(2.0f),
        DT_IMMI, float_to_uint32(3.5f),
        DT_FP_MUL, DT_SEEK, DT_END
    };
    std::vector<unsigned> thread = {0,2,4,5,6};
    IndirectThreadingVM vm;
    vm.run_vm(instructions,thread);
    EXPECT_EQ(vm.debug_num, float_to_uint32(7.0f));
}

TEST(FloatingPoint, HandlesFPDivision2) {
    std::vector<uint32_t> instructions = {
        DT_IMMI, float_to_uint32(7.5f),
        DT_IMMI, float_to_uint32(2.5f),
        DT_FP_DIV, DT_SEEK, DT_END
    };
    std::vector<unsigned> thread = {0,2,4,5,6};
    IndirectThreadingVM vm;
    vm.run_vm(instructions,thread);
    EXPECT_EQ(vm.debug_num, float_to_uint32(3.0f));
}

TEST(BitwiseOperations, HandleLeftShift2) {
    std::vector<uint32_t> instructions = {
        DT_IMMI, 1,  
        DT_IMMI, 3,  
        DT_SHL,      
        DT_SEEK, DT_END
    };
    std::vector<unsigned> thread = {0,2,4,5,6};
    IndirectThreadingVM vm;
    vm.run_vm(instructions,thread);
    EXPECT_EQ(vm.debug_num, 8); 
}

TEST(BitwiseOperations, HandleRightShift2) {
    std::vector<uint32_t> instructions = {
        DT_IMMI, 8,  
        DT_IMMI, 3,  
        DT_SHR,      
        DT_SEEK, DT_END
    };
    std::vector<unsigned> thread = {0,2,4,5,6};
    IndirectThreadingVM vm;
    vm.run_vm(instructions,thread);
    EXPECT_EQ(vm.debug_num, 1); 
}

TEST(MemoryOperations, HandleLoadAndStore2) {
    std::vector<uint32_t> instructions = {        
        DT_IMMI, 100,          
        DT_STO, 0,                       
        DT_LOD, 0,              
        DT_SEEK, DT_END
    };
    std::vector<unsigned> thread = { 0, 2, 4, 6, 7 };
    IndirectThreadingVM vm;
    vm.run_vm(instructions,thread);
    EXPECT_EQ(vm.debug_num, 100); 
}

TEST(MemoryOperations, HandleMemoryCopy2) {
    std::vector<uint32_t> instructions = {
        DT_STO_IMMI, 0, 123,  
        DT_MEMCPY, 4, 0, 4,   
        DT_LOD, 4,           
        DT_SEEK, DT_END
    };
    std::vector<unsigned> thread = { 0, 3, 7, 9, 10 };
    IndirectThreadingVM vm;
    vm.run_vm(instructions,thread);
    EXPECT_EQ(vm.debug_num, 123);
}

TEST(MemoryOperations, HandleMemorySet2) {
    std::vector<uint32_t> instructions = {
        DT_MEMSET, 0, 255, 4, 
        DT_LOD, 0,            
        DT_SEEK, DT_END
    };
    std::vector<unsigned> thread = { 0, 4, 6, 7 };
    IndirectThreadingVM vm;
    vm.run_vm(instructions,thread);
    EXPECT_EQ(vm.debug_num, 0xFFFFFFFF); 
}

TEST(ControlFlow, HandleJump2) {
    std::vector<uint32_t> instructions = { DT_IMMI, 0, DT_STO_IMMI, 0, 1, DT_LOD, 0, DT_ADD, DT_LOD, 0, DT_INC, DT_STO, 0, DT_LOD, 0, DT_IMMI, 100, DT_GT, DT_JZ, 2, DT_SEEK, DT_END };
    std::vector<unsigned> thread = { 0, 2, 5, 7, 8, 10, 11, 13, 15, 17, 18, 20, 21 };
    IndirectThreadingVM vm;
    vm.run_vm(instructions,thread);
    EXPECT_EQ(vm.debug_num, 5050); 
}

TEST(ComparisonOperations, HandleLessThan2) {
    std::vector<uint32_t> instructions = {
        DT_IMMI, 5,
        DT_IMMI, 10,
        DT_LT,
        DT_SEEK, DT_END
    };
    std::vector<unsigned> thread = { 0, 2, 4, 5, 6 };
    IndirectThreadingVM vm;
    vm.run_vm(instructions,thread);
    EXPECT_EQ(vm.debug_num, 1); // 5 < 10
}

TEST(ComparisonOperations, HandleEqualTo2) {
    std::vector<uint32_t> instructions = {
        DT_IMMI, 10,
        DT_IMMI, 10,
        DT_EQ,
        DT_SEEK, DT_END
    };
    std::vector<unsigned> thread = { 0, 2, 4, 5, 6 };
    IndirectThreadingVM vm;
    vm.run_vm(instructions,thread);
    EXPECT_EQ(vm.debug_num, 1); // 10 == 10
}

TEST(ComparisonOperations, HandleGreaterThanEqualTo2) {
    std::vector<uint32_t> instructions = {
        DT_IMMI, 10,
        DT_IMMI, 5,
        DT_GT_EQ,
        DT_SEEK, DT_END
    };
    std::vector<unsigned> thread = { 0, 2, 4, 5, 6 };
    IndirectThreadingVM vm;
    vm.run_vm(instructions,thread);
    EXPECT_EQ(vm.debug_num, 1); // 10 >= 5
}

TEST(ComparisonOperations, HandleLessThanEqualTo2) {
    std::vector<uint32_t> instructions = {
        DT_IMMI, 5,
        DT_IMMI, 10,
        DT_LT_EQ,
        DT_SEEK, DT_END
    };
    std::vector<unsigned> thread = { 0, 2, 4, 5, 6 };
    IndirectThreadingVM vm;
    vm.run_vm(instructions,thread);
    EXPECT_EQ(vm.debug_num, 1); // 5 <= 10
}

TEST(ControlFlow, HandleIfElse2) {
    std::vector<uint32_t> instructions = { DT_IMMI, 1, DT_IF_ELSE, 5, 8, DT_IMMI, 0, DT_SEEK, DT_END, DT_IMMI, 123, DT_SEEK, DT_END, DT_IMMI, 456, DT_SEEK, DT_END };
    std::vector<unsigned> thread = { 0, 2, 5, 7, 8, 9, 11, 12, 13, 15, 16 };
    IndirectThreadingVM vm;
    vm.run_vm(instructions,thread);
    EXPECT_EQ(vm.debug_num, 123); 
}

TEST (ControlFlow, HandleConditionalJump2) {
    std::vector<uint32_t> instructions = { DT_IMMI, 1, DT_JUMP_IF, 5, DT_IMMI, 0, DT_SEEK, DT_END, DT_IMMI, 123, DT_SEEK, DT_END };
    std::vector<unsigned> thread = { 0, 2, 4, 6, 7, 8, 10, 11 };
    IndirectThreadingVM vm;
    vm.run_vm(instructions,thread);
    EXPECT_EQ(vm.debug_num, 123); 
}

TEST(FunctionCalls, HandleFunctionCallAndReturn2) {
    std::vector<uint32_t> instructions = { DT_IMMI, 10, DT_CALL, 4, 1, DT_SEEK, DT_END, DT_IMMI, 2, DT_ADD, DT_RET };
    std::vector<unsigned> thread = { 0, 2, 5, 6, 7, 9, 10 };
    IndirectThreadingVM vm;
    vm.run_vm(instructions,thread);
    EXPECT_EQ(vm.debug_num, 12);
}

//Routine Threading
TEST(Arithmetic, HandlesAddition3) {
    std::vector<std::vector<unsigned> > instructions = {{DT_IMMI, 5}, {DT_IMMI, 3}, {DT_ADD}, {DT_SEEK}, {DT_END}};
    RoutineThreadingVM vm;
    vm.run_vm(instructions);
    EXPECT_EQ(vm.debug_num, 8); 
}

TEST(Arithmetic, HandlesSubtraction3) {
    std::vector<std::vector<unsigned> > instructions = {{DT_IMMI, 10}, {DT_IMMI, 4}, {DT_SUB}, {DT_SEEK}, {DT_END}};
    RoutineThreadingVM vm;
    vm.run_vm(instructions);
    EXPECT_EQ(vm.debug_num, 6);
}

TEST(Arithmetic, HandlesMultiplication3) {
    std::vector<std::vector<unsigned> > instructions = {{DT_IMMI, 6}, {DT_IMMI, 7}, {DT_MUL}, {DT_SEEK}, {DT_END}};
    RoutineThreadingVM vm;
    vm.run_vm(instructions);
    EXPECT_EQ(vm.debug_num, 42);
}

TEST(Arithmetic, HandlesDivision3) {
    std::vector<std::vector<unsigned> > instructions = {{DT_IMMI, 20}, {DT_IMMI, 5}, {DT_DIV}, {DT_SEEK}, {DT_END}};
    RoutineThreadingVM vm;
    vm.run_vm(instructions);
    EXPECT_EQ(vm.debug_num, 4);
}

TEST(FloatingPoint, HandlesFPAddition3) {
    std::vector<std::vector<unsigned> > instructions = {
        {DT_IMMI, float_to_uint32(4.5f)},
        {DT_IMMI, float_to_uint32(0.5f)},
        {DT_FP_ADD}, {DT_SEEK}, {DT_END}
    };
    RoutineThreadingVM vm;
    vm.run_vm(instructions);
    EXPECT_EQ(vm.debug_num, float_to_uint32(5.0f));
}

TEST(ArithmeticOperations, HandleDecrement3) {
    std::vector<std::vector<unsigned> > instructions = {
        {DT_IMMI, 5},
        {DT_DEC},
        {DT_SEEK}, {DT_END}
    };
    RoutineThreadingVM vm;
    vm.run_vm(instructions);
    EXPECT_EQ(vm.debug_num, 4); // 5 - 1 = 4
}

TEST(FloatingPoint, HandlesFPSubtraction3) {
    std::vector<std::vector<unsigned> > instructions = {
        {DT_IMMI, float_to_uint32(5.5f)},
        {DT_IMMI, float_to_uint32(1.5f)},
        {DT_FP_SUB}, {DT_SEEK}, {DT_END}
    };
    RoutineThreadingVM vm;
    vm.run_vm(instructions);
    EXPECT_EQ(vm.debug_num, float_to_uint32(4.0f));
}

TEST(FloatingPoint, HandlesFPMultiplication3) {
    std::vector<std::vector<unsigned> > instructions = {
        {DT_IMMI, float_to_uint32(2.0f)},
        {DT_IMMI, float_to_uint32(3.5f)},
        {DT_FP_MUL}, {DT_SEEK}, {DT_END}
    };
    RoutineThreadingVM vm;
    vm.run_vm(instructions);
    EXPECT_EQ(vm.debug_num, float_to_uint32(7.0f));
}

TEST(FloatingPoint, HandlesFPDivision3) {
    std::vector<std::vector<unsigned> > instructions = {
        {DT_IMMI, float_to_uint32(7.5f)},
        {DT_IMMI, float_to_uint32(2.5f)},
        {DT_FP_DIV}, {DT_SEEK}, {DT_END}
    };
    RoutineThreadingVM vm;
    vm.run_vm(instructions);
    EXPECT_EQ(vm.debug_num, float_to_uint32(3.0f));
}

TEST(BitwiseOperations, HandleLeftShift3) {
    std::vector<std::vector<unsigned> > instructions = {
        {DT_IMMI, 1},  
        {DT_IMMI, 3},  
        {DT_SHL},      
        {DT_SEEK}, {DT_END}
    };
    RoutineThreadingVM vm;
    vm.run_vm(instructions);
    EXPECT_EQ(vm.debug_num, 8); 
}

TEST(BitwiseOperations, HandleRightShift3) {
    std::vector<std::vector<unsigned> > instructions = {
        {DT_IMMI, 8},  
        {DT_IMMI, 3},  
        {DT_SHR},      
        {DT_SEEK}, {DT_END}
    };
    RoutineThreadingVM vm;
    vm.run_vm(instructions);
    EXPECT_EQ(vm.debug_num, 1); 
}

TEST(MemoryOperations, HandleLoadAndStore3) {
    std::vector<std::vector<unsigned> > instructions = {        
        {DT_IMMI, 100},          
        {DT_STO, 0},                       
        {DT_LOD, 0},              
        {DT_SEEK}, {DT_END}
    };
    RoutineThreadingVM vm;
    vm.run_vm(instructions);
    EXPECT_EQ(vm.debug_num, 100); 
}

TEST(MemoryOperations, HandleMemoryCopy3) {
    std::vector<std::vector<unsigned> > instructions = {
        {DT_STO_IMMI, 0, 123},  
        {DT_MEMCPY, 4, 0, 4},   
        {DT_LOD, 4},           
        {DT_SEEK}, {DT_END}
    };
    RoutineThreadingVM vm;
    vm.run_vm(instructions);
    EXPECT_EQ(vm.debug_num, 123);
}

TEST(MemoryOperations, HandleMemorySet3) {
    std::vector<std::vector<unsigned> > instructions = {
        {DT_MEMSET, 0, 255, 4}, 
        {DT_LOD, 0},            
        {DT_SEEK}, {DT_END}
    };
    RoutineThreadingVM vm;
    vm.run_vm(instructions);
    EXPECT_EQ(vm.debug_num, 0xFFFFFFFF); 
}

TEST(ControlFlow, HandleJump3) {
    std::vector<std::vector<unsigned> > instructions = { {DT_IMMI, 0},{DT_STO_IMMI, 0, 1},{DT_LOD, 0},{DT_ADD},{DT_LOD, 0},{DT_INC},{DT_STO, 0},{DT_LOD, 0},{DT_IMMI, 100},{DT_GT},{DT_JZ, 2},{DT_SEEK},{DT_END} };
    RoutineThreadingVM vm;
    vm.run_vm(instructions);
    EXPECT_EQ(vm.debug_num, 5050); 
}

TEST(ComparisonOperations, HandleLessThan3) {
    std::vector<std::vector<unsigned> > instructions = {
        {DT_IMMI, 5},
        {DT_IMMI, 10},
        {DT_LT},
        {DT_SEEK}, {DT_END}
    };
    RoutineThreadingVM vm;
    vm.run_vm(instructions);
    EXPECT_EQ(vm.debug_num, 1); // 5 < 10
}

TEST(ComparisonOperations, HandleEqualTo3) {
    std::vector<std::vector<unsigned> > instructions = {
        {DT_IMMI, 10},
        {DT_IMMI, 10},
        {DT_EQ},
        {DT_SEEK}, {DT_END}
    };
    RoutineThreadingVM vm;
    vm.run_vm(instructions);
    EXPECT_EQ(vm.debug_num, 1); // 10 == 10
}

TEST(ComparisonOperations, HandleGreaterThanEqualTo3) {
    std::vector<std::vector<unsigned> > instructions = {
        {DT_IMMI, 10},
        {DT_IMMI, 5},
        {DT_GT_EQ},
        {DT_SEEK}, {DT_END}
    };
    RoutineThreadingVM vm;
    vm.run_vm(instructions);
    EXPECT_EQ(vm.debug_num, 1); // 10 >= 5
}

TEST(ComparisonOperations, HandleLessThanEqualTo3) {
    std::vector<std::vector<unsigned> > instructions = {
        {DT_IMMI, 5},
        {DT_IMMI, 10},
        {DT_LT_EQ},
        {DT_SEEK}, {DT_END}
    };
    RoutineThreadingVM vm;
    vm.run_vm(instructions);
    EXPECT_EQ(vm.debug_num, 1); // 5 <= 10
}

TEST(ControlFlow, HandleIfElse3) {
    std::vector<std::vector<unsigned> > instructions = { {DT_IMMI, 1},{DT_IF_ELSE, 5, 8},{DT_IMMI, 0},{DT_SEEK},{DT_END},{DT_IMMI, 123},{DT_SEEK},{DT_END},{DT_IMMI, 456},{DT_SEEK},{DT_END} };
    RoutineThreadingVM vm;
    vm.run_vm(instructions);
    EXPECT_EQ(vm.debug_num, 123); 
}

TEST (ControlFlow, HandleConditionalJump3) {
    std::vector<std::vector<unsigned> > instructions = { {DT_IMMI, 1},{DT_JUMP_IF, 5},{DT_IMMI, 0},{DT_SEEK},{DT_END},{DT_IMMI, 123},{DT_SEEK},{DT_END} };
    RoutineThreadingVM vm;
    vm.run_vm(instructions);
    EXPECT_EQ(vm.debug_num, 123); 
}

TEST(FunctionCalls, HandleFunctionCallAndReturn3) {
    std::vector<std::vector<unsigned> > instructions = { {DT_IMMI, 10},{DT_CALL, 4, 1},{DT_SEEK},{DT_END},{DT_IMMI, 2},{DT_ADD},{DT_RET} };
    RoutineThreadingVM vm;
    vm.run_vm(instructions);
    EXPECT_EQ(vm.debug_num, 12);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
