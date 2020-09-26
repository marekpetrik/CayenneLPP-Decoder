// CayenneLPP Decoder
//
// Decodes a CayenneLPP binary buffer to JSON format
//
// https://os.mbed.com/teams/myDevicesIoT/code/Cayenne-LPP
// https://github.com/open-source-parsers/jsoncpp
//
// Copyright (c) 2018 Robbert E. Peters. All rights reserved.
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
//
#pragma once

#include <cstdint>
#include <cstdlib>
#include <stdexcept>
#include <string>
#include <tuple>
#include <variant>
#include <vector>

#include "CayenneLPP.hpp"

struct ParsedValue {
    uint_fast8_t channel;
    std::string type;
    std::variant<uint8_t, float, std::array<float, 3>> value;
};

/*
Example Usage:
CayenneLPP lpp(200);

lpp.addTemperature(1, 10.4f);
lpp.addTemperature(2, -23.5f);

lpp.addDigitalInput(1, 0);
lpp.addDigitalOutput(1, 1);

lpp.addAnalogInput(1, 1.23f);
lpp.addAnalogOutput(1, 3.45f);

lpp.addLuminosity(1, 20304);
lpp.addPresence(1, 1);
lpp.addTemperature(3, 26.5f);
lpp.addRelativeHumidity(1, 86.6f);
lpp.addAccelerometer(1, 1.234f, -1.234f, 0.567f);
lpp.addBarometricPressure(1, 1023.4f);
lpp.addGyrometer(1, -12.34f, 45.56f, 89.01f);
lpp.addGPS(1, 54.184668f, 7.886778f , -6.3f);

//Decode buffer to JSON
Json::Value root;

if (CayenneLPPDec::ParseLPP(lpp.getBuffer(), lpp.getSize(), root))
{
    std::cout << "Found " << root.size() << " entries:\n\n";
    std::cout << root.toStyledString();
}
*/

inline std::pair<std::string, std::vector<ParsedValue>>
parse_lpp(const std::vector<uint8_t>& buffer) {

    auto parse_float1 = [&buffer](size_t pos, uint16_t multiplier) {
        return float(buffer.at(pos + 2)) / float(multiplier);
    };
    auto parse_float = [&buffer](size_t pos, uint16_t multiplier) {
        return float(
                   ((uint16_t(buffer.at(pos + 2)) << 8) | uint16_t(buffer.at(pos + 3)))) /
               float(multiplier);
    };

    auto parse_lat_lon = [&buffer](size_t pos, u_int16_t multiplier) {
        int32_t tvalue =
            (buffer.at(pos + 2) << 16) | (buffer.at(pos + 3) << 8) | buffer.at(pos + 4);
        // handle the sign (?)
        if ((buffer[pos + 2] & 0xF0) == 0xF0) tvalue |= 0xFF000000;
        return float(tvalue) / float(multiplier);
    };

    std::vector<ParsedValue> root;
    size_t pos = 0;
    std::string error = "";

    while (pos < buffer.size() - 2) {
        const uint8_t channel = buffer[pos];
        const uint8_t lpp_type = buffer[pos + 1];
        const auto len = buffer.size() - pos;

        if (lpp_type == LPP_DIGITAL_INPUT) {
            if (len < LPP_DIGITAL_INPUT_SIZE) {
                error += "missing bytes at the end.";
                break;
            }
            ParsedValue v = {
                .channel = channel, .type = "digital_input", .value = buffer[pos + 2]};
            root.push_back(v);

            pos += LPP_DIGITAL_INPUT_SIZE;
        } else if (lpp_type == LPP_DIGITAL_OUTPUT) {
            if (len < LPP_DIGITAL_OUTPUT_SIZE) {
                error += "missing bytes at the end.";
                break;
            }

            ParsedValue v = {
                .channel = channel, .type = "digital_output", .value = buffer[pos + 2]};
            root.push_back(v);

            pos += LPP_DIGITAL_OUTPUT_SIZE;
        } else if (lpp_type == LPP_ANALOG_INPUT) {
            if (len < LPP_ANALOG_INPUT_SIZE) {
                error += "missing bytes at the end.";
                break;
            }

            ParsedValue v = {.channel = channel,
                             .type = "analog_input",
                             .value = parse_float(pos, LPP_ANALOG_INPUT_MULT)};
            root.push_back(v);

            pos += LPP_ANALOG_INPUT_SIZE;
        } else if (lpp_type == LPP_ANALOG_OUTPUT) {
            if (len < LPP_ANALOG_OUTPUT_SIZE) {
                error += "missing bytes at the end.";
                break;
            }

            ParsedValue v = {.channel = channel,
                             .type = "analog_input",
                             .value = parse_float(pos, LPP_ANALOG_OUTPUT_MULT)};
            root.push_back(v);

            pos += LPP_ANALOG_OUTPUT_SIZE;
        } else if (lpp_type == LPP_LUMINOSITY) {
            if (len < LPP_LUMINOSITY_SIZE) {
                error += "missing bytes at the end.";
                break;
            }

            ParsedValue v = {.channel = channel,
                             .type = "analog_output",
                             .value = parse_float(pos, LPP_LUMINOSITY_MULT)};
            root.push_back(v);

            pos += LPP_LUMINOSITY_SIZE;
        } else if (lpp_type == LPP_PRESENCE) {
            if (len < LPP_PRESENCE_SIZE) {
                error += "missing bytes at the end.";
                break;
            }
            ParsedValue v = {
                .channel = channel, .type = "presence", .value = buffer[pos + 2]};
            root.push_back(v);

            pos += LPP_PRESENCE_SIZE;
        } else if (lpp_type == LPP_TEMPERATURE) {
            if (len < LPP_TEMPERATURE_SIZE) {
                error += "missing bytes at the end.";
                break;
            }

            ParsedValue v = {.channel = channel,
                             .type = "temperature",
                             .value = parse_float(pos, LPP_TEMPERATURE_MULT)};
            root.push_back(v);
            pos += LPP_TEMPERATURE_SIZE;
        } else if (lpp_type == LPP_RELATIVE_HUMIDITY) {
            if (len < LPP_RELATIVE_HUMIDITY_SIZE) {
                error += "missing bytes at the end.";
                break;
            }

            ParsedValue v = {.channel = channel,
                             .type = "humidity",
                             .value = parse_float1(pos, LPP_RELATIVE_HUMIDITY_MULT)};
            root.push_back(v);

            pos += LPP_RELATIVE_HUMIDITY_SIZE;
        } else if (lpp_type == LPP_ACCELEROMETER) {
            if (len < LPP_ACCELEROMETER_SIZE) {
                error += "missing bytes at the end.";
                break;
            }

            std::array<float, 3> vals = {parse_float(pos, LPP_ACCELEROMETER_MULT),
                                         parse_float(pos + 2, LPP_ACCELEROMETER_MULT),
                                         parse_float(pos + 4, LPP_ACCELEROMETER_MULT)};
            ParsedValue v = {.channel = channel, .type = "accelerometer", .value = vals};
            root.push_back(v);
            pos += LPP_ACCELEROMETER_SIZE;
        } else if (lpp_type == LPP_BAROMETRIC_PRESSURE) {

            if (len < LPP_BAROMETRIC_PRESSURE_SIZE) {
                error += "missing bytes at the end.";
                break;
            }

            ParsedValue v = {.channel = channel,
                             .type = "pressure",
                             .value = parse_float(pos, LPP_BAROMETRIC_PRESSURE_MULT)};
            root.push_back(v);
            pos += LPP_BAROMETRIC_PRESSURE_SIZE;
        } else if (lpp_type == LPP_CONCENTRATION) {

            if (len < LPP_CONCENTRATION_SIZE) {
                error += "missing bytes at the end.";
                break;
            }

            ParsedValue v = {.channel = channel,
                             .type = "concentration",
                             .value = parse_float(pos, LPP_CONCENTRATION_MULT)};
            root.push_back(v);
            pos += LPP_CONCENTRATION_SIZE;
        }
#ifdef LPP_UNIXTIME
        else if (lpp_type == LPP_UNIXTIME) {
            if (Len < LPP_UNIXTIME_SIZE) return false;

            root[iIndex]["channel"] = channel;
            root[iIndex]["type"] = "unixtime";

            uint32_t value =
                (pBuffer[2] << 24) | (pBuffer[3] << 16) | (pBuffer[4] << 8) | pBuffer[5];
            root[iIndex++]["value"] = value;

            pBuffer += LPP_UNIXTIME_SIZE;
            Len -= LPP_UNIXTIME_SIZE;
        }
#endif // LPP_UNIXTIME
        else if (lpp_type == LPP_GYROMETER) {
            if (len < LPP_GYROMETER_SIZE) {
                error += "missing bytes at the end.";
                break;
            }

            std::array<float, 3> vals = {parse_float(pos, LPP_GYROMETER_MULT),
                                         parse_float(pos + 2, LPP_GYROMETER_MULT),
                                         parse_float(pos + 4, LPP_GYROMETER_MULT)};
            ParsedValue v = {.channel = channel, .type = "gyro", .value = vals};
            root.push_back(v);
            pos += LPP_GYROMETER_SIZE;
        } else if (lpp_type == LPP_GPS) {
            if (len < LPP_GPS_SIZE) {
                error += "missing bytes at the end.";
                break;
            }

            std::array<float, 3> vals = {parse_lat_lon(pos, LPP_GPS_LAT_LON_MULT),
                                         parse_float(pos + 3, LPP_GPS_LAT_LON_MULT),
                                         parse_float(pos + 6, LPP_GPS_ALT_MULT)};
            ParsedValue v = {.channel = channel, .type = "gyro", .value = vals};
            root.push_back(v);

            pos += LPP_GPS_SIZE;
        } else {
            error += "unknown type: " + std::to_string(lpp_type);
            break;
        }
        // account for the channel and type bytes
        pos += 2;
    }
    return {error, std::move(root)};
}

inline std::vector<uint8_t> from_hexstring(const std::string& hex) {
    if (hex.length() % 2 != 0) throw std::runtime_error("the length of hex must be even");

    std::vector<uint8_t> result;
    result.reserve(hex.length() / 2);

    for (int i = 0; i < hex.length(); i += 2) {
        std::string byte_str = hex.substr(i, 2);
        result.push_back(std::strtol(byte_str.c_str(), nullptr, 16));
    }
    return result;
}
