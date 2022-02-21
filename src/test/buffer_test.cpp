//
// Created by maros on 05/01/2022.
//
#include "public/buffer.hpp"

#define DATA_BLOCK

int main() {

    bfb::stack_buffer<4> buffer(bfb::byte_order::BIG_ENDIAN);
    buffer.write_short(0xFFAA);
}