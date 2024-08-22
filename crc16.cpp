#include <cstdint>
#include <array>

class CRC16 {
public:
    static constexpr uint16_t POLYNOMIAL = 0x8005;

    CRC16() {
        generateTable();
    }

    uint16_t calculate(const uint8_t* data, size_t length) {
        uint16_t crc = 0;
        for (size_t i = 0; i < length; ++i) {
            crc = (crc << 8) ^ table[(crc >> 8) ^ data[i]];
        }
        return crc;
    }

private:
    std::array<uint16_t, 256> table;

    void generateTable() {
        for (uint16_t i = 0; i < 256; ++i) {
            uint16_t crc = i << 8;
            for (int j = 0; j < 8; ++j) {
                if (crc & 0x8000) {
                    crc = (crc << 1) ^ POLYNOMIAL;
                } else {
                    crc <<= 1;
                }
            }
            table[i] = crc;
        }
    }
};
