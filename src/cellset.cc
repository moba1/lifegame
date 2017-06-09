/**
 * @file cellset.cc
 * @brief ライフゲームにおけるセルの集合体を扱う
 * @author mob_a
 * @date 2016/8/3
 */

#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "cellset.hpp"
#include "data.hpp"

/**
 * @fn セル集合体オブジェクトのコンストラクタ
 * @brief セル集合体オブジェクトのコンストラクタ。初期の高さと幅を要求する
 * @param (height) 初期設定したい高さ
 * @param (width) 初期設定したい幅
 * @param (probability) セルが生存できる確率
 * @detail
 * セル集合体のオブジェクトの初期の高さと幅をユーザーから要求し、その幅と高さにセルの集合体の大きさを設定する。またこの時点でセルの各状態も初期化しておく
 */
life::cell_set::cell_set(size_t height, size_t width, size_t probability)
    : height(height), width(width) {
  std::random_device rd;
  std::mt19937_64 mt(rd());
  std::uniform_int_distribution<size_t> random_cell_status_generator(1, 100);
  cells.resize(static_cast<size_t>(height));

  for (size_t i = 0; i < height; i++) {
    for (size_t j = 0; j < width; j++) {
      // セルを1/2の確率で生きた状態で初期化する
      random_cell_status_generator(mt) > probability
          ? cells[i].push_back(life::cell(std::pair<size_t, size_t>(i, j)))
          : cells[i].push_back(life::cell(std::pair<size_t, size_t>(i, j),
                                          life::STATUS::LIVE));
    }
  }
}

/**
 * @fn セルの状態を取得する
 * @brief セルの状態を文字列で取得する
 * @detail セルの生死状態を文字列で返す
 * @return セルの生死状態
 */
auto life::cell_set::get_cells_status() -> std::vector<std::string> {
  std::vector<std::string> cells_status;

  for (size_t i = 0; i < height; i++) {
    cells_status.push_back(std::string());
    for (size_t j = 0; j < width; j++)
      cells_status[i].append(cells[i][j].get_status() == STATUS::DEAD ? WHITE
                                                                      : BLACK);
  }

  return cells_status;
}

/**
 * @fn セルの集合を次の世代へとシフトさせる
 * @brief セルの集合を次の世代へとシフトさせる
 * @detail セルの集合を次の世代へとシフトさせる
 */
auto life::cell_set::shift_next_generation() -> void {
  std::vector<std::vector<cell>> premodern_generation;

  // セルの前の時代の状態をすべてコピー
  for (auto row : cells) {
    std::vector<cell> r;
    for (auto e : row) r.push_back(e);
    premodern_generation.push_back(r);
  }

  // セルの周囲の状態を見てセルの次世代の状態をアップデート
  for (size_t i = 0; i < height; i++) {
    for (size_t j = 0; j < width; j++) {
      auto alive_num = 0;
      if (i == 0 || i + 1 == height) {
        alive_num +=
            premodern_generation[i == 0 ? i + 1 : i - 1][j].get_status_int();
        if (j == 0)
          alive_num += premodern_generation[i == 0 ? i + 1 : i - 1][j + 1]
                           .get_status_int() +
                       premodern_generation[i][j + 1].get_status_int();
        else if (j + 1 == width)
          alive_num += premodern_generation[i][j - 1].get_status_int() +
                       premodern_generation[i == 0 ? i + 1 : i - 1][j - 1]
                           .get_status_int();
        else
          alive_num += premodern_generation[i == 0 ? i + 1 : i - 1][j + 1]
                           .get_status_int() +
                       premodern_generation[i][j + 1].get_status_int() +
                       premodern_generation[i][j - 1].get_status_int() +
                       premodern_generation[i == 0 ? i + 1 : i - 1][j - 1]
                           .get_status_int();
      } else {
        alive_num += premodern_generation[i + 1][j].get_status_int() +
                     premodern_generation[i - 1][j].get_status_int();
        if (j == 0 || j + 1 == width)
          alive_num +=
              premodern_generation[i][j == 0 ? j + 1 : j - 1].get_status_int() +
              premodern_generation[i + 1][j == 0 ? j + 1 : j - 1]
                  .get_status_int() +
              premodern_generation[i - 1][j == 0 ? j + 1 : j - 1]
                  .get_status_int();
        else
          alive_num += premodern_generation[i - 1][j - 1].get_status_int() +
                       premodern_generation[i][j - 1].get_status_int() +
                       premodern_generation[i + 1][j - 1].get_status_int() +
                       premodern_generation[i + 1][j + 1].get_status_int() +
                       premodern_generation[i][j + 1].get_status_int() +
                       premodern_generation[i - 1][j + 1].get_status_int();
      }
      if (cells[i][j].get_status() == STATUS::LIVE)
        cells[i][j].change_status(
            alive_num == 2 || alive_num == 3 ? STATUS::LIVE : STATUS::DEAD);
      else {
        cells[i][j].change_status(alive_num == 3 ? STATUS::LIVE : STATUS::DEAD);
      }
    }
  }
}
