/**
 * @file cell.hpp
 * @brief セルを表すクラスの宣言が書かれている
 * @author mob_a
 * @date 2016/8/3
 */

#ifndef SQUARE_HPP
#define SQUARE_HPP

#include <array>
#include <utility>

#include "status.hpp"

namespace life {
/**
 * @class cell
 * @brief セルを表すクラス
 */
class cell {
 private:
  std::pair<size_t, size_t> point;
  STATUS cell_status;

 public:
  /**
   * @fn セルオブジェクトのコンストラクタ
   * @brief セルオブジェクトのコンストラクタ(デフォルトで死んだ状態)
   * @param (init_point) セルの位置
   * @detail
   * セルオブジェクトのコンストラクタ。デフォルトでセルは死んだ状態で初期化される
   */
  cell(const std::pair<size_t, size_t>& init_point)
      : point(init_point), cell_status(STATUS::DEAD) {}

  /**
   * @fn セルオブジェクトのコンストラクタ
   * @brief セルオブジェクトのコンストラクタ
   * @param (init_point) セルの位置
   * @param (init_status) セルの初期状態
   * @detail
   * セルオブジェクトのコンストラクタ。セルの状態を死んでいる状態で初期化するか、生きた状態で初期化するかを選べる
   */
  cell(const std::pair<size_t, size_t>& init_point, STATUS init_status)
      : point(init_point), cell_status(init_status) {}

  auto change_status(const STATUS) -> void;

  auto get_status() -> STATUS;

  auto get_status_int() -> int;
};
}

#endif
