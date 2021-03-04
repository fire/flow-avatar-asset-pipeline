/* distributed under MIT license:
 * 
 * Copyright (c) 2021 Kota Iguchi
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include <string>
#include <vector>
#include "json.hpp"

using json = nlohmann::json;

static inline std::vector<std::string> json_get_items(std::string name, json obj)
{
    const auto items_obj = obj[name];
    std::vector<std::string> items;
    if (items_obj.is_array()) {
        for (const auto& item : items_obj) {
            items.push_back(item.get<std::string>());
        }
    }
    return items;
}

static inline bool json_parse(std::string json_file, json* json)
{
    std::ifstream f(json_file, std::ios::in);
    if (f.fail()) {
        std::cout << "[ERROR] failed to parse JSON file " << json_file << std::endl;
        return false;
    }

    try {
        f >> *json;
     } catch (json::parse_error& e) {
        std::cout << "[ERROR] failed to parse JSON file " << json_file << std::endl;
        std::cout << "\t" << e.what() << std::endl;
        return false;
    }

    return true;
}