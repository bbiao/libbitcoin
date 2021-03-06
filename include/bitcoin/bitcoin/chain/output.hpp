/**
 * Copyright (c) 2011-2015 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
 *
 * libbitcoin is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License with
 * additional permissions to the one published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version. For more information see LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef LIBBITCOIN_CHAIN_OUTPUT_HPP
#define LIBBITCOIN_CHAIN_OUTPUT_HPP

#include <cstddef>
#include <cstdint>
#include <istream>
#include <bitcoin/bitcoin/chain/script/script.hpp>
#include <bitcoin/bitcoin/define.hpp>
#include <bitcoin/bitcoin/utility/reader.hpp>
#include <bitcoin/bitcoin/utility/writer.hpp>

namespace libbitcoin {
namespace chain {

class BC_API output
{
public:
    /// TODO: set not_found as the default/invalid state via the ctor .
    /// This is a sentinel used in .value to indicate not found in store.
    /// This is a sentinel used in cache.value to indicate not populated.
    static const uint64_t not_found;

    typedef std::vector<output> list;

    static output factory_from_data(const data_chunk& data);
    static output factory_from_data(std::istream& stream);
    static output factory_from_data(reader& source);

    bool from_data(const data_chunk& data);
    bool from_data(std::istream& stream);
    bool from_data(reader& source);
    data_chunk to_data() const;
    void to_data(std::ostream& stream) const;
    void to_data(writer& sink) const;
    std::string to_string(uint32_t flags) const;
    bool is_valid() const;
    void reset();
    uint64_t serialized_size() const;
    size_t signature_operations() const;

    uint64_t value;
    chain::script script;
};

} // namespace chain
} // namespace libbitcoin

#endif
