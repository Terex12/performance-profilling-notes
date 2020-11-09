#!/bin/bash

likwid-perfctr -C 0 -m  -g L3CACHE ./matmul-fast 2>&1 | tee fmatmul.pro.txt
likwid-perfctr -C 0 -m  -g L2CACHE ./matmul-fast >> fmatmul.pro.txt
likwid-perfctr -C 0 -m  -g MEM ./matmul-fast >> fmatmul.pro.txt 
likwid-perfctr -C 0 -m  -g CACHES ./matmul-fast >> fmatmul.pro.txt

likwid-perfctr -C 0 -m  -g L3CACHE ./matmul-slow 2>&1 | tee smatmul.pro.txt
likwid-perfctr -C 0 -m  -g L2CACHE ./matmul-slow >> smatmul.pro.txt
likwid-perfctr -C 0 -m  -g MEM ./matmul-slow >> smatmul.pro.txt 
likwid-perfctr -C 0 -m  -g CACHES ./matmul-slow >> smatmul.pro.txt

likwid-perfctr -C 0 -m  -g L3CACHE ./matmul-def 2>&1 | tee defmatmul.pro.txt
likwid-perfctr -C 0 -m  -g L2CACHE ./matmul-def >> defmatmul.pro.txt
likwid-perfctr -C 0 -m  -g MEM ./matmul-def >> defmatmul.pro.txt 
likwid-perfctr -C 0 -m  -g CACHES ./matmul-def >> defmatmul.pro.txt




