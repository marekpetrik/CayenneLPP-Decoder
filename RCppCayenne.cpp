// This file exposes the library to R via Rcpp::sourceCPP("RCppCayenne.cpp")

// [[Rcpp::plugins(cpp2a)]]
// [[Rcpp::depends(rcraam)]]

#include "CayenneLPP_Dec.h"
#include "Rcpp.h"

// Parses the hex string to list values
// [[Rcpp::export]]
Rcpp::List parse_hexstring(const std::string& hexstring) {
    auto bytearray = from_hexstring(hexstring);

    auto [error, values] = parse_lpp(bytearray);
    if (error.length() > 0) { Rcpp::stop(error); }

    Rcpp::List result;
    for (const auto& v : values) {
        Rcpp::List vlist =
            Rcpp::List::create(Rcpp::_["channel"] = v.channel, Rcpp::_["type"] = v.type);

        if (std::holds_alternative<uint8_t>(v.value)) {
            vlist.push_back(std::get<uint8_t>(v.value), "value");
        } else if (std::holds_alternative<float>(v.value)) {
            vlist.push_back(std::get<float>(v.value), "value");
        }
        if (std::holds_alternative<std::array<float, 3>>(v.value)) {
            auto varr = std::get<std::array<float, 3>>(v.value);
            vlist.push_back(std::vector<float>({varr[0], varr[1], varr[2]}), "value");
        }
        result.push_back(vlist);
    }

    return result;
}
