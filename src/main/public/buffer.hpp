//
// Created by maros on 05/01/2022.
//

#ifndef FRIENDLY_BUFFER_BUFFER_HPP
#define FRIENDLY_BUFFER_BUFFER_HPP

#include <cstdint>
#include <memory>
#include <string>
#include <array>

namespace bfb {

    /**
     * Thrown when buffer reached capacity and cannot go beyond the specified capacity.
     */
    struct eof_exception
            : std::exception {

    public:
        const size_t readerIndex;
        const size_t writerIndex;
        const size_t capacity;

        eof_exception(const size_t readerIndex, const size_t writerIndex, const size_t capacity);
    };

    enum class byte_order {
        BIG_ENDIAN, LITTLE_ENDIAN
    };

    /**
     * Buffer
     */
    class buffer {
    protected:
        bfb::byte_order byteOrder;

        size_t readerIndex = 0;
        size_t writerIndex = 0;
        size_t capacity = 0;

        std::uint8_t *data = nullptr;
    protected:
        buffer();

    public:
        /**
         * Constructs buffer with specified byte-order, capacity.
         * @param byteOrder Byte order
         * @param capacity  Capacity
         */
        buffer(byte_order byteOrder,
               size_t capacity);

        /**
         * Destructor
         */
        virtual ~buffer();

    public:
        /**
         * Reads byte value.
         * @throws eof_exception
         * @return Value.
         */
        std::uint8_t read_byte();

        /**
         * Writes byte value.
         * @throws eof_exception
         * @param value Value.
         * @return this buffer
         */
        bfb::buffer *write_byte(std::uint8_t value);

    public:
        std::uint16_t read_short();

        std::uint32_t read_int();

        std::uint64_t read_long();

        std::uint32_t read_var_int();

        std::uint64_t read_var_long();

        std::string read_utf();

    public:
        bfb::buffer *write_short(std::uint16_t value);

        bfb::buffer *write_int(std::uint32_t value);

        bfb::buffer *write_long(std::uint64_t value);

        bfb::buffer *write_var_int(std::uint32_t value);

        bfb::buffer *write_var_long(std::uint64_t value);

        bfb::buffer *write_utf(const std::string &value);
    };

    /**
     * Stack buffer
     * @tparam Cap Capacity
     */
    template<size_t Cap>
    class stack_buffer :
            public buffer {

    private:
        std::unique_ptr<std::array<uint8_t, Cap>> underlying =
                std::make_unique<std::array<uint8_t, Cap>>();

    public:
        explicit stack_buffer(bfb::byte_order byteOrder);
        virtual ~stack_buffer();
    };

    template<size_t Cap>
    stack_buffer<Cap>::stack_buffer(bfb::byte_order byteOrder) {
        this->data = underlying->data();
        this->capacity = Cap;
        this->byteOrder = byteOrder;
    }

    template<size_t Cap>
    stack_buffer<Cap>::~stack_buffer() {

    }
}


#endif //FRIENDLY_BUFFER_BUFFER_HPP
