cmake_minimum_required(VERSION 3.20)
project(MyShot C)

set(CMAKE_C_STANDARD 11)

add_executable(MyShot
        main.c
        calculator.c
        calculator.h
        tokenizer.h
        tokenizer.c
        symboltable.h
        symboltable.c
        stack.h
        stack.c
        dict.h
        dict.c
        shunting-yard.h
        shunting-yard.c
        list.h
        list.c)
