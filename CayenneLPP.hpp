// Adapted from https://developer.mbed.org/teams/myDevicesIoT/code/Cayenne-LPP/

// Copyright © 2017 The Things Network
// Use of this source code is governed by the MIT license that can be found in the LICENSE file.
#pragma once

#include <cstdint>

constexpr uint16_t LPP_DIGITAL_INPUT = 0;         // 1 byte
constexpr uint16_t LPP_DIGITAL_OUTPUT = 1;        // 1 byte
constexpr uint16_t LPP_ANALOG_INPUT = 2;          // 2 bytes, 0.01 signed
constexpr uint16_t LPP_ANALOG_OUTPUT = 3;         // 2 bytes, 0.01 signed
constexpr uint16_t LPP_GENERIC_SENSOR = 100;      // 4 bytes, unsigned
constexpr uint16_t LPP_LUMINOSITY = 101;          // 2 bytes, 1 lux unsigned
constexpr uint16_t LPP_PRESENCE = 102;            // 1 byte, bool
constexpr uint16_t LPP_TEMPERATURE = 103;         // 2 bytes, 0.1°C signed
constexpr uint16_t LPP_RELATIVE_HUMIDITY = 104;   // 1 byte, 0.5% unsigned
constexpr uint16_t LPP_ACCELEROMETER = 113;       // 2 bytes per axis, 0.001G
constexpr uint16_t LPP_BAROMETRIC_PRESSURE = 115; // 2 bytes 0.1hPa unsigned
constexpr uint16_t LPP_VOLTAGE = 116;             // 2 bytes 0.01V unsigned
constexpr uint16_t LPP_CURRENT = 117;             // 2 bytes 0.001A unsigned
constexpr uint16_t LPP_FREQUENCY = 118;           // 4 bytes 1Hz unsigned
constexpr uint16_t LPP_PERCENTAGE = 120;          // 1 byte 1-100% unsigned
constexpr uint16_t LPP_ALTITUDE = 121;            // 2 byte 1m signed
constexpr uint16_t LPP_CONCENTRATION = 125;       // 2 bytes, 1 ppm unsigned
constexpr uint16_t LPP_POWER = 128;               // 2 byte, 1W, unsigned
constexpr uint16_t LPP_DISTANCE = 130;            // 4 byte, 0.001m, unsigned
constexpr uint16_t LPP_ENERGY = 131;              // 4 byte, 0.001kWh, unsigned
constexpr uint16_t LPP_DIRECTION = 132;           // 2 bytes, 1deg, unsigned
constexpr uint16_t LPP_UNIXTIME = 133;            // 4 bytes, unsigned
constexpr uint16_t LPP_GYROMETER = 134;           // 2 bytes per axis, 0.01 °/s
constexpr uint16_t LPP_COLOUR = 135;              // 1 byte per RGB Color
constexpr uint16_t LPP_GPS = 136;    // 3 byte lon/lat 0.0001 °, 3 bytes alt 0.01 meter
constexpr uint16_t LPP_SWITCH = 142; // 1 byte, 0/1

// Only Data Size
constexpr uint16_t LPP_DIGITAL_INPUT_SIZE = 1;
constexpr uint16_t LPP_DIGITAL_OUTPUT_SIZE = 1;
constexpr uint16_t LPP_ANALOG_INPUT_SIZE = 2;
constexpr uint16_t LPP_ANALOG_OUTPUT_SIZE = 2;
constexpr uint16_t LPP_GENERIC_SENSOR_SIZE = 4;
constexpr uint16_t LPP_LUMINOSITY_SIZE = 2;
constexpr uint16_t LPP_PRESENCE_SIZE = 1;
constexpr uint16_t LPP_TEMPERATURE_SIZE = 2;
constexpr uint16_t LPP_RELATIVE_HUMIDITY_SIZE = 1;
constexpr uint16_t LPP_ACCELEROMETER_SIZE = 6;
constexpr uint16_t LPP_BAROMETRIC_PRESSURE_SIZE = 2;
constexpr uint16_t LPP_VOLTAGE_SIZE = 2;
constexpr uint16_t LPP_CURRENT_SIZE = 2;
constexpr uint16_t LPP_FREQUENCY_SIZE = 4;
constexpr uint16_t LPP_PERCENTAGE_SIZE = 1;
constexpr uint16_t LPP_ALTITUDE_SIZE = 2;
constexpr uint16_t LPP_POWER_SIZE = 2;
constexpr uint16_t LPP_DISTANCE_SIZE = 4;
constexpr uint16_t LPP_ENERGY_SIZE = 4;
constexpr uint16_t LPP_DIRECTION_SIZE = 2;
constexpr uint16_t LPP_UNIXTIME_SIZE = 4;
constexpr uint16_t LPP_GYROMETER_SIZE = 6;
constexpr uint16_t LPP_GPS_SIZE = 9;
constexpr uint16_t LPP_SWITCH_SIZE = 1;
constexpr uint16_t LPP_CONCENTRATION_SIZE = 2;
constexpr uint16_t LPP_COLOUR_SIZE = 3;

// Multipliers
//constexpr uint16_t LPP_DIGITAL_INPUT_MULT = 1;
//constexpr uint16_t LPP_DIGITAL_OUTPUT_MULT = 1;
constexpr uint16_t LPP_ANALOG_INPUT_MULT = 100;
constexpr uint16_t LPP_ANALOG_OUTPUT_MULT = 100;
constexpr uint16_t LPP_GENERIC_SENSOR_MULT = 1;
constexpr uint16_t LPP_LUMINOSITY_MULT = 1;
constexpr uint16_t LPP_PRESENCE_MULT = 1;
constexpr uint16_t LPP_TEMPERATURE_MULT = 10;
constexpr uint16_t LPP_RELATIVE_HUMIDITY_MULT = 2;
constexpr uint16_t LPP_ACCELEROMETER_MULT = 1000;
constexpr uint16_t LPP_BAROMETRIC_PRESSURE_MULT = 10;
constexpr uint16_t LPP_VOLTAGE_MULT = 100;
constexpr uint16_t LPP_CURRENT_MULT = 1000;
constexpr uint16_t LPP_FREQUENCY_MULT = 1;
constexpr uint16_t LPP_PERCENTAGE_MULT = 1;
constexpr uint16_t LPP_ALTITUDE_MULT = 1;
constexpr uint16_t LPP_POWER_MULT = 1;
constexpr uint16_t LPP_DISTANCE_MULT = 1000;
constexpr uint16_t LPP_ENERGY_MULT = 1000;
constexpr uint16_t LPP_DIRECTION_MULT = 1;
constexpr uint16_t LPP_UNIXTIME_MULT = 1;
constexpr uint16_t LPP_GYROMETER_MULT = 100;
constexpr uint16_t LPP_GPS_LAT_LON_MULT = 10000;
constexpr uint16_t LPP_GPS_ALT_MULT = 100;
constexpr uint16_t LPP_SWITCH_MULT = 1;
constexpr uint16_t LPP_CONCENTRATION_MULT = 1;
constexpr uint16_t LPP_COLOUR_MULT = 1;

constexpr uint16_t LPP_ERROR_OK = 0;
constexpr uint16_t LPP_ERROR_OVERFLOW = 1;
constexpr uint16_t LPP_ERROR_UNKOWN_TYPE = 2;
