/**
 * @file life.cc
 * @brief ライフゲームはこのファイルから実行される
 * @author mob_a
 * @date 2016/8/3
 */

#include <getopt.h>
#include <locale.h>
#include <ncurses.h>
#include <chrono>
#include <iostream>
#include <thread>

#include "cellset.hpp"
#include "data.hpp"

/**
 * @fn ヘルプを指定された出力ストリームに表示する
 * @brief ヘルプを出力する
 * @param (os) 出力したいストリーム
 * @param (program_name) このプログラムのプロセス名
 * @detail
 * 指定された出力ストリーム(std::coutやstd::cerrなど)にこのプログラムの簡単なヘルプを表示する
 */
auto show_help(std::ostream& os, const char* program_name) -> void {
  os << "Usage:" << std::endl;
  os << "  " << program_name << " [Options]" << std::endl;
  os << "Options:" << std::endl;
  os << "  -h, --help        Show help" << std::endl;
  os << "  -v, --version     Show version" << std::endl;
  os << "  --height          Set height" << std::endl;
  os << "  --width           Set width" << std::endl;
  os << "  -p, --probability Set generating probability of living cell"
     << std::endl;
}

/**
 * @fn バージョンを表示する
 * @brief バージョンを表示する
 * @param (program_name) このプログラムのプロセス名
 * @detail このプログラムのバージョン情報と作成者を表示する
 */
auto show_version(const char* program_name) -> void {
  std::cout << program_name << " version 0.1, author: mob_a" << std::endl;
}

/**
 * @fn main関数
 * @brief main関数
 * @param (argc) このプログラムに渡された引数の数
 * @param (argv) このプログラムに渡された引数
 * @detail このプログラムのmainルーチンが記述された関数
 * @return プログラムの終了値
 */
auto main(int argc, char* argv[]) -> int {
  int parse_result, height = 20, width = 20, probability = 60;
  auto stopping = false, finish = false;
  const option options[] = {{"height", required_argument, NULL, 'e'},
                            {"width", required_argument, NULL, 'w'},
                            {"help", no_argument, NULL, 'h'},
                            {"version", no_argument, NULL, 'v'},
                            {"probability", required_argument, NULL, 'p'},
                            {0, 0, 0, 0}};

  // オプション解析
  while ((parse_result = getopt_long(argc, argv, "hvp:", options, NULL)) != -1) {
    switch (parse_result) {
      case 'e':
        height = atoi(optarg);
        if (height <= 10) {
          std::cerr << argv[0]
                    << ": `--height' requires what is greater than 10"
                    << std::endl;
          return 2;
        }
        break;
      case 'w':
        width = atoi(optarg);
        if (width <= 10) {
          std::cerr << argv[0] << ": `--width' requires what is greater than 10"
                    << std::endl;
          return 2;
        }
        break;
      case 'h':
        show_help(std::cout, argv[0]);
        return 0;
      case 'v':
        show_version(argv[0]);
        return 0;
      case 'p':
        probability = atoi(optarg);
        if (probability <= 0) {
          std::cerr << argv[0]
                    << ": `--probability' requires what is graeter than 0"
                    << std::endl;
          return 2;
        }
        break;
      default:
        show_help(std::cerr, argv[0]);
        return 1;
    }
  }

  setlocale(LC_ALL, "");
  initscr(), timeout(0);

  // ライフゲームのメインルーチン
  life::cell_set cells(height, width, probability);

  while (!finish) {
    if (!stopping) {
      auto statuses = cells.get_cells_status();

      clear();
      for (auto status : statuses) printw("%s\n", status.c_str());
      refresh();
      std::this_thread::sleep_for(std::chrono::microseconds(100000));
      cells.shift_next_generation();
    }
    switch (getch()) {
      case 'q':
        finish = true;
        break;
      case 's':
        stopping = stopping ? false : true;
        break;
      default:
        break;
    }
  }

  endwin();
}
