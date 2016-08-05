/**
 * @file status.hpp
 * @brief セルの状態を表す列挙型の定義が書かれている
 * @author mob_a
 * @date 2016/8/3
 */

#ifndef STATUS_HPP
#define STATUS_HPP

namespace life {
/**
 * @class STATUS
 * @brief セルの状態を表現する
 */
enum struct STATUS { LIVE = 1, DEAD = 0 };
}

#endif
