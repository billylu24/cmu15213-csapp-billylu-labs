cmake_minimum_required(VERSION 4.0)
project(CSAPP_HW_Giaok C)

set(CMAKE_C_STANDARD 11)

include_directories(cprogramminglab-handout-BillyLu)

add_executable(CSAPP_HW_Giaok
        cprogramminglab-handout-BillyLu/console.c
        cprogramminglab-handout-BillyLu/console.h
        cprogramminglab-handout-BillyLu/harness.c
        cprogramminglab-handout-BillyLu/harness.h
        cprogramminglab-handout-BillyLu/qtest.c
        cprogramminglab-handout-BillyLu/queue.c
        cprogramminglab-handout-BillyLu/queue.h
        cprogramminglab-handout-BillyLu/report.c
        cprogramminglab-handout-BillyLu/report.h)
