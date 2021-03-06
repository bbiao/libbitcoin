/**
 * Copyright (c) 2011-2016 libbitcoin developers (see AUTHORS)
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
#include <bitcoin/bitcoin/chain/output_point.hpp>

#include <cstddef>
#include <cstdint>
#include <bitcoin/bitcoin/constants.hpp>
#include <bitcoin/bitcoin/chain/point.hpp>

namespace libbitcoin {
namespace chain {

const size_t output_point::not_coinbase = max_size_t;

// The metadata properties are not configured for initializer syntax.

output_point::output_point()
  : cache({ output::not_found, {} }),
    spent(false),
    confirmed(false)
{
}

output_point::output_point(const output_point& other)
  : point(other),
    cache(other.cache),
    spent(other.spent),
    confirmed(other.confirmed)
{
}

output_point::output_point(const chain::point& value)
  : point(value),
    cache({ output::not_found, {} }),
    spent(false),
    confirmed(false)
{
}

output_point::output_point(const hash_digest& hash, uint32_t index)
  : point({ hash, index }),
    cache({ output::not_found, {} }),
    spent(false),
    confirmed(false)
{
}

void output_point::reset()
{
    spent = false;
    confirmed = false;
    cache.value = output::not_found;
    cache.script.reset();
    static_cast<point>(*this).reset();
}

// For tx pool validation target_height is that of the *next* block.
// For block validation target_height is that for which block is considered.
// Returns true if the previous output is mature enough to spend from height.
bool output_point::is_mature(size_t target_height) const
{
    // If the prevout is not null then it is not from a coinbase transaction.
    // If the prevout is null and its tx is valid then it must be a coinbase.
    return !is_null() || ((target_height - 1) - height >= coinbase_maturity);
}

bool output_point::operator==(const output_point& other) const
{
    // Cash is not considered in comparisons.
    return static_cast<point>(*this) == static_cast<point>(other);
}

bool output_point::operator!=(const output_point& other) const
{
    // Cash is not considered in comparisons.
    return !(*this == other);
}

} // namespace chain
} // namespace libbitcoin
