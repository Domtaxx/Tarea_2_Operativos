cmake_minimum_required(VERSION 3.10.0)
    
# here we specify that the project is C language only, so the default
# C compiler on the system will be used
project(myprogram C)

add_executable(myprogram Server.c Server.h hist_equa.c hist_equa.h)
target_link_libraries(myprogram m)