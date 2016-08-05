/**
 * @file cell.cc
 * @brief セルクラスのメソッドが記述されている
 * @author mob_a
 * @date 2016/8/3
 */

#include "cell.hpp"
#include "status.hpp"

/**
 * @fn セルの状態を変更するメソッド
 * @brief セルの生死状態を変更するメソッド
 * @param (cell_statuses) 周囲８マスのセルの生死情報
 * @detail
 * 周囲８マスのセルの生死状態を元にして、次世代のこのセルオブジェクトの状態を決定する。
 * @return 変更前のセルの生死情報
 */
auto life::cell::change_status(const STATUS status) -> void {
  cell_status = status;
}

/**
 * @fn セルの状態のゲッター
 * @brief セルの状態を返す
 * @detail セルの状態を返す
 * @return セルの状態
 */
auto life::cell::get_status() -> STATUS { return cell_status; }

/**
 * @fn セルの状態を整数で返すゲッター
 * @brif セルの状態を整数値で返す
 * @detail セルの状態を整数値で返す
 * @return セルの状態
 */
auto life::cell::get_status_int() -> int {
  return cell_status == STATUS::DEAD ? 0 : 1;
}
