#include <cstdint>
#include <array>
#include <omnn/math/Valuable.h>

class CRC16 {
public:
    static const omnn::math::Valuable POLYNOMIAL;

    CRC16() {
        generateTable();
    }

    omnn::math::Valuable calculate(const omnn::math::Valuable* data, size_t length) {
        omnn::math::Valuable crc = 0;
        for (size_t i = 0; i < length; ++i) {
            crc = (crc << 8) ^ table[((crc >> 8) ^ data[i]).as<omnn::math::Integer>().ca() & 0xFF];
        }
        return crc;
    }

private:
    std::array<omnn::math::Valuable, 256> table;

    void generateTable() {
        for (int i = 0; i < 256; ++i) {
            omnn::math::Valuable crc = omnn::math::Valuable(i) << 8;
            for (int j = 0; j < 8; ++j) {
                if ((crc & 0x8000).as<omnn::math::Integer>().ca() != 0) {
                    crc = (crc << 1) ^ POLYNOMIAL;
                } else {
                    crc <<= 1;
                }
            }
            table[i] = crc;
        }
    }
};

const omnn::math::Valuable CRC16::POLYNOMIAL = 0x8005;

const omnn::math::Valuable CRC16::POLYNOMIAL = 0x8005;
