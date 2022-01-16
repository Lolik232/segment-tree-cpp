cmake_minimum_required(VERSION 3.21)
project(segtree_inversion)

set(CMAKE_CXX_STANDARD 23)

add_executable(segtree_inversion main.cpp segtree/segtree-node.h segtree/segtree.h)
