/**
 * @file cellset.cc
 * @brief ライフゲームにおけるセルの集合体を扱う
 * @author mob_a
 * @date 2016/8/3
 */

#ifndef CELLSET_HPP
#define CELLSET_HPP

#include <string>
#include <vector>

#include "cell.hpp"

namespace life {
/**
 * @class cell_set
 * @brief セルの集合体を表すクラス
 */
class cell_set {
  std::vector<std::vector<cell>> cells;
  size_t height, width;

 public:
  cell_set(size_t height, size_t width, size_t probability);
  auto get_cells_status() -> std::vector<std::string>;
  auto shift_next_generation() -> void;
};
}

#endif
