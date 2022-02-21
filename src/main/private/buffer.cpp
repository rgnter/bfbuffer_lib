//
// Created by maros on 05/01/2022.
//

#include "../public/buffer.hpp"


bfb::eof_exception::eof_exception(const size_t readerIndex, const size_t writerIndex, const size_t capacity)
        : readerIndex(readerIndex), writerIndex(writerIndex), capacity(capacity) {}

bfb::buffer::buffer() {}

bfb::buffer::buffer(bfb::byte_order byteOrder,
                    size_t capacity)
        : byteOrder(byteOrder), capacity(capacity) {
    this->data = (uint8_t *) std::malloc(capacity);
}

bfb::buffer::~buffer() {
    if(this->data != nullptr)
    std::free(this->data);
}

std::uint8_t bfb::buffer::read_byte() {
    if (++this->readerIndex > this->capacity)
        throw eof_exception(this->readerIndex,
                            this->writerIndex,
                            this->capacity);
    return this->data[this->readerIndex];
}

bfb::buffer *bfb::buffer::write_byte(std::uint8_t value) {
    if (this->writerIndex + 1 > this->capacity)
        throw eof_exception(this->readerIndex,
                            this->writerIndex,
                            this->capacity);
    this->data[this->writerIndex++] = value;
    return this;
}

std::uint16_t bfb::buffer::read_short() {
    std::uint16_t value = 0;
    if(byteOrder == byte_order::BIG_ENDIAN) {
        value+=((std::uint16_t)read_byte() >> 8);
        value+=read_byte();
    } else {

    }
    return value;
}

bfb::buffer *bfb::buffer::write_short(std::uint16_t value) {
    if(byteOrder == byte_order::BIG_ENDIAN) {
        write_byte(value >> 8); // write hi bit
        write_byte(value); // write lo bit
    } else {

    }
    return this;
}






