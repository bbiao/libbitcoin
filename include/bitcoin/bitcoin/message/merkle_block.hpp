/*
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
#ifndef LIBBITCOIN_MESSAGE_MERKLE_BLOCK_HPP
#define LIBBITCOIN_MESSAGE_MERKLE_BLOCK_HPP

#include <istream>
#include <memory>
#include <string>
#include <bitcoin/bitcoin/define.hpp>
#include <bitcoin/bitcoin/chain/header.hpp>
#include <bitcoin/bitcoin/utility/data.hpp>
#include <bitcoin/bitcoin/utility/reader.hpp>
#include <bitcoin/bitcoin/utility/writer.hpp>

namespace libbitcoin {
namespace message {

class BC_API merkle_block
{
public:
    typedef std::vector<merkle_block> list;
    typedef std::shared_ptr<merkle_block> ptr;
    typedef std::shared_ptr<const merkle_block> const_ptr;

    static merkle_block factory_from_data(uint32_t version,
        const data_chunk& data);
    static merkle_block factory_from_data(uint32_t version,
        std::istream& stream);
    static merkle_block factory_from_data(uint32_t version, reader& source);

    bool operator==(const merkle_block& other) const;
    bool operator!=(const merkle_block& other) const;

    bool from_data(uint32_t version, const data_chunk& data);
    bool from_data(uint32_t version, std::istream& stream);
    bool from_data(uint32_t version, reader& source);
    data_chunk to_data(uint32_t version) const;
    void to_data(uint32_t version, std::ostream& stream) const;
    void to_data(uint32_t version, writer& sink) const;
    bool is_valid() const;
    void reset();
    uint64_t serialized_size(uint32_t version) const;

    static const std::string command;
    static const uint32_t version_minimum;
    static const uint32_t version_maximum;

    chain::header header;
    hash_list hashes;

    // TODO: provide utility to compute this from the list of hashes based on
    // the assumption that the hash list represents that of a complete block.
    data_chunk flags;
};

} // end message
} // end libbitcoin

#endif
