#include <cstdint>
#include <iomanip>
#include <sstream>
#include <string>

template <typename Game>
std::string hashGameState(const Game& game)
{
    const uint64_t MOD = 1000000007ULL;
    const uint64_t BASE = 31;

    uint64_t hash = 17;

    // Incorporate board size
    int n = game.getBoardSize();
    hash = (hash * BASE + n) % MOD;

    // Incorporate cell ownership in row-major order
    for (int row = 0; row < n; ++row)
    {
        for (int col = 0; col < n; ++col)
        {
            int owner = game.getCellOwner(row, col);
            hash = (hash * BASE + owner) % MOD;
        }
    }

    // Incorporate current player
    hash = (hash * BASE +
            game.getCurrentPlayer()) % MOD;

    // Incorporate game status
    hash = (hash * BASE +
            game.getGameStatus()) % MOD;

    // Convert to eight-digit uppercase hexadecimal
    std::ostringstream output;
    output << std::uppercase
           << std::hex
           << std::setw(8)
           << std::setfill('0')
           << hash;

    return output.str();
}
