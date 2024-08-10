/*
VS2:Monsters' Revenge
Copyright (C) 2024 blue-peace2013@github.com 
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
*/
#define SOUND
/**
 * 现在有Ubuntu机子了, 啥时候弄个Linux版的 
 * 最开始写了很多头文件, 现在用namespace捏在一起 
 * @since 2.7.30
 * @author Bintree Development Team
 */

/******** 头文件 ********/

#define mini(x, y) ((x) < (y) ? (x) : (y))
#define maxi(x, y) ((x) > (y) ? (x) : (y))
#include <cstdlib>
#include <cstring>
#include <ctime> 
#ifdef _WIN32
  #include <conio.h>
#endif
#include <fstream>
#ifdef _WIN32
  #include <io.h>
#endif
#include <iostream>
#include <ostream>
#include <random>
#include <sstream>
#ifndef _WIN32
  #include <sys/ioctl.h>
  #include <unistd.h>
#else
  #include <windows.h>
#endif 

/******** 设置 ********/ 

namespace settings {
    const char TITLE[22] = "VS2:Monsters' Revenge";
    const char HACKER_TITLE[25] = "YOU ARE A DIRTY HACKER.";
    const char LOADING[7][53] = {
        "      ________________________________________",
        "    _/_                                      _\\_",
        " __/__/         VS2:Monsters' Revenge        \\__\\__",
        "| < < |            Version 2.7.30            | > > |",
        " --\\--\\           English language           /--/--",
        "    -\\-                                      -/-", 
        "      ----------------------------------------"
    };
    const char NAMING_TABLE[6][26] = {
        "A B C D E F G H I J K L M", 
        "N O P Q R S T U V W X Y Z",
        "a b c d e f g h i j k l m",
        "n o p q r s t u v w x y z", 
        "1 2 3 4 5 6 7 8 9 0 - _ +", 
        "Backspace Confirm"
    };
    // 一堆字符:  ┴┬┤├ ┻┳┫┣
    const unsigned short LOADING_X = 5;
    const unsigned short LOADING_WIDTH = 52;
    const unsigned short MAX_WORLD_HEIGHT = 100;
    const unsigned short MAX_WORLD_WIDTH = 100;
    const unsigned int MAX_NAME_LENGTH = 20;
    const unsigned int MAX_WEAPONS_NUM = 10;
    const unsigned int MAX_MSG_LENGTH = 10050;
    const unsigned short INFO_HEIGHT = 3;
} // namespace settings

/******** 定义 ********/ 

char tmp[10500];

namespace os {
    #ifdef _WIN32
        HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    #endif
    
    std::fstream fs;
    std::stringstream ss;
    
    inline unsigned short getConsoleWidth() {
        #ifdef _WIN32
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            GetConsoleScreenBufferInfo(hOutput, &csbi);
            return csbi.srWindow.Right - csbi.srWindow.Left + 1;
        #else
            struct winsize w;
            ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
            return w.ws_row;
        #endif
    }
    
    inline unsigned short getConsoleHeight() {
        #ifdef _WIN32
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            GetConsoleScreenBufferInfo(hOutput, &csbi);
            return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
        #else
            struct winsize w;
            ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
            return w.ws_col;
        #endif
    }
    
    inline void clearConsole() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }
    
    inline void wait(int ms) {
        #ifdef _WIN32
            Sleep(ms);
        #else
            usleep(ms * 1000);
        #endif
    }
    
    inline void setTitle(const char* title) {
        #ifdef _WIN32
            SetConsoleTitleA(title);
        #else
            printf("\033]0;%s\007", title);
        #endif
    }
    
    inline bool exists(const char* file) {
        ss.str("");
        #ifdef _WIN32
            ss << "C:\\vs2\\";
        #else
            ss << "/usr/vs2/";
        #endif
        ss << file;
        return access(ss.str().c_str(), 0) == 0;
    }
    
    inline void mkfile(const char* file) {
        if (exists(file)) return;
        ss.str("");
        #ifdef _WIN32
            ss << "type nul>C:\\vs2\\";
        #else
            ss << "touch /usr/vs2/";
        #endif
        ss << file;
        system(ss.str().c_str());
    }
    
    inline void rmfile(const char* file) {
        ss.str("");
        #ifdef _WIN32
            ss << "del C:\\vs2\\";
        #else
            ss << "rm -f /usr/vs2/";
        #endif
        ss << file;
        system(ss.str().c_str());
    }
    
    inline char* rdfile(char* file) {
        #ifdef _WIN32
            memmove(file + 7, file, strlen(file));
            file[0] = 'C';
            file[1] = ':';
            file[2] = '\\';
            file[3] = 'v';
            file[4] = 's';
            file[5] = '2';
            file[6] = '\\';
        #else
            memmove(file + 9, file, strlen(file));
            file[0] = '/';
            file[1] = 'u';
            file[2] = 's';
            file[3] = 'r';
            file[4] = '/';
            file[5] = 'v';
            file[6] = 's';
            file[7] = '2';
            file[8] = '/';
        #endif
        return file;
    }
    
    inline void mkdatas() {
        #ifdef _WIN32
            system("mkdir C:\\vs2");
        #else
            system("mkdir /usr/vs2");
        #endif
        mkfile("file");
        clearConsole();
    }
} // namespace os

namespace player {
    enum Direction {
        UP, LEFT, DOWN, RIGHT, LUP, LDOWN, RDOWN, RUP
    };
    
    class Player {
        public: 
            Player();
            ~Player();
            inline void naming(const char* _name);
            inline void move(Direction _direction, int height, int width);
            inline void teleport(short _x, short _y);
            inline bool getWeapon(char weapon);
            bool attack(char weapon);
            inline short getX() const;
            inline short getY() const;
            inline bool hit(short hurt);
            inline bool islive() const;
            inline short gethp() const;
            inline const char* getWeapons() const;
            inline const char* getName() const;
        private:
            char* name;
            Direction direction;
            short x, y;
            short hp;
            char* weapons;
            int weaponsNum;
            int fastNum;
    };
} // namespace player

namespace world {
    class World {
        public:
            World();
            ~World();
            void setSize(short _height, short _width);
            bool load(const char* file); 
            inline void naming(const char* name);
            inline void putWeapon(char who, char weapon);
            inline void pushinfo(const char* info);
            void showWorld();
            char* serialization(char* msg);
        private:
            char** infos;
            char** sekai;
            short height, width;
            player::Player* aid;
            player::Player* hmn;
    };
} // namespace world

namespace vs2 {
    world::World sekai;
    inline int init();
    void run();
} // namespace vs2

namespace cli {
    HANDLE hOutput;
    inline int init();
    inline int getKey();
    void setCursorPosition(short row, short col);
    inline unsigned short getMid();
    inline unsigned short getCol(int strLen);
    void delayPrint(const char* str, int ms); 
    void printStr(short row, short col, const char* str);
    void loading();
    bool confirm();
    inline char* charToStr(char ch, char* str);
    char* naming(char* name);
} // namespace cli

namespace random {
    std::random_device rd;
    std::mt19937 gen;
    inline int init();
    int randInt(int mini, int maxi);
} // namespace random

/******** 实现 ********/

namespace player {
    Player::Player() {
        name = (char*) malloc(settings::MAX_NAME_LENGTH);
        weapons = (char*) malloc(settings::MAX_WEAPONS_NUM);
        memset(name, '\0', sizeof(name));
        memset(weapons, '\0', sizeof(weapons));
        hp = 100;
    }
    
    Player::~Player() {
        free(name);
        free(weapons);
        name = NULL;
        weapons = NULL;
    } 
    
    inline void Player::naming(const char* _name) {
        memcpy(name, _name, strlen(_name));
    }
    
    inline void Player::move(Direction _direction, int height, int width) {
        switch (direction = _direction) {
            case UP: {
                if (x) x--;
                break;
            }
            case LEFT: {
                if (y) y--;
                break;
            }
            case DOWN: {
                if (x < height - 1) x++;
                break;
            }
            case RIGHT: {
                if (y < width - 1) y++;
                break;
            }
            case LUP: {
                move(LEFT, height, width);
                move(UP, height, width);
                break;
            }
            case LDOWN: {
                move(LEFT, height, width);
                move(DOWN, height, width);
                break;
            }
            case RDOWN: {
                move(RIGHT, height, width);
                move(DOWN, height, width);
                break;
            }
            case RUP: {
                move(RIGHT, height, width);
                move(UP, height, width);
                break;
            }
        } 
    }
    
    inline void Player::teleport(short _x, short _y) {
        x = _x;
        y = _y;
    }
    
    inline bool Player::getWeapon(char weapon) {
        if (weaponsNum == settings::MAX_WEAPONS_NUM) return false;
        weapons[weaponsNum++] = weapon;
        return true;
    }
    
    bool Player::attack(char weapon) {
        for (int i = 0; i < weaponsNum; i++) 
            if (weapons[i] == weapon) {
                for (int j = i + 1; j < weaponsNum; j++)
                    weapons[j - 1] = weapons[j];
                weaponsNum--;
                return true;
            } 
        return false;
    }
    
    inline short Player::getX() const {
        return x;
    }
    
    inline short Player::getY() const {
        return y;
    } 
    
    inline bool Player::hit(short hurt) {
        if (islive()) hp -= hurt;
        return islive();
    }
    
    inline bool Player::islive() const {
        return hp > 0;
    }
    
    inline short Player::gethp() const {
        return hp;
    }
    
    inline const char* Player::getWeapons() const {
        return weapons;
    }
    
    inline const char* Player::getName() const {
        return name;
    }
} // namespace player

namespace world {
    World::World() {
        aid = (player::Player*) malloc(sizeof(player::Player));
        hmn = (player::Player*) malloc(sizeof(player::Player));
        new(aid) player::Player();
        new(hmn) player::Player();
        aid->naming("__aid_computer__");
        sekai = (char**) malloc(sizeof(char*) * settings::MAX_WORLD_HEIGHT);
        for (int i = 0; i < settings::MAX_WORLD_HEIGHT; i++) {
            sekai[i] = (char*) malloc(settings::MAX_WORLD_WIDTH);
            memset(sekai[i], '.', sizeof(sekai[i]));
        }
        sekai[0][0] = 'v';
        infos = (char**) malloc(sizeof(char*) * settings::INFO_HEIGHT);
        for (int i = 0; i < settings::INFO_HEIGHT; i++) {
            infos[i] = (char*) malloc(settings::MAX_WORLD_WIDTH);
            memset(infos[i], '\0', sizeof(infos[i]));
        }
    }
    
    World::~World() {
        for (int i = 0; i < settings::MAX_WORLD_HEIGHT; i++)
            free(sekai[i]);
        free(sekai);
        for (int i = 0; i < settings::INFO_HEIGHT; i++)
            free(infos[i]);
        free(infos);
        delete aid;
        delete hmn;
        aid = hmn = NULL;
        sekai = infos = NULL;
    }
    
    void World::setSize(short _height, short _width) {
        height = _height;
        width = _width;
        aid->teleport(height - 1, width - 1);
        sekai[height - 1][width - 1] = '^';
    } 
    
    bool World::load(const char* file) {
        std::ifstream is(file);
        int idx = 0;
        memset(tmp, '\0', sizeof(tmp));
        short hx, hy, ax = -1, ay = -1;
        short hhp, ahp;
        char c = is.get();
        while (c != '\n') {
            if (idx > settings::MAX_NAME_LENGTH)
                return false;
            tmp[idx++] = c;
            c = is.get();
        }
        if (tmp[0] == '_' && tmp[1] == '_' && tmp[2] == 'D' && tmp[3] == 'E' && tmp[4] == 'B' && tmp[5] == 'U' && tmp[6] == 'G' && tmp[7] == '_' && tmp[8] == '_' && tmp[9] == '\0') 
            #define debug
        naming(tmp);
        is >> height >> width >> hx >> hy >> hhp >> ahp;
        if (height < 5 || width < 5) 
            return false;
        if (hx < 0 || hy < 0 || hx >= height || hy >= width)
            return false;
        if (hhp > 100 || ahp > 100)
            return false;
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++) {
                is >> sekai[i][j];
                if (sekai[i][j] == '.')
                    sekai[i][j] = ' ';
                if ((sekai[i][j] == '^' || sekai[i][j] == '<' || sekai[i][j] == 'v' || sekai[i][j] == '>') && i != hx && j != hy)
                    ax = i, ay = j;
            }
        if (sekai[hx][hy] != '^' && sekai[hx][hy] != '<' && sekai[hx][hy] != 'v' && sekai[hx][hy] != '>') return false;
        if (ax == -1 || ay == -1) 
            return false;
        hmn->teleport(hx, hy);
        aid->teleport(ax, ay);
        int x;
        is >> x;
        while (x--) {
            c = is.get();
            if (!hmn->getWeapon(c)) 
                return false;
        }
        is >> x;
        while (x--) {
            c = is.get();
            if (!aid->getWeapon(c)) 
                return false;
        }
        return true;
    }
    
    inline void World::naming(const char* name) {
        if (strlen(name) >= settings::MAX_NAME_LENGTH) {
            #ifndef debug
                os::mkfile("hacker1");
            #endif 
            exit(0);
        }
        hmn->naming(name);
    }
    
    inline void World::putWeapon(char who, char weapon) {
        if (who == 'H') {
            if (hmn->attack(weapon))
                sekai[hmn->getX()][hmn->getY()] = weapon;
        } else {
            if (aid->attack(weapon))
                sekai[aid->getX()][aid->getY()] = weapon;
        }
    }
    
    inline void World::pushinfo(const char* info) {
        memcpy(infos[0], infos[1], settings::MAX_WORLD_WIDTH);
        memcpy(infos[1], infos[2], settings::MAX_WORLD_WIDTH);
        memcpy(infos[2], info, strlen(info));
        memset(infos[2] + strlen(info), '\0', settings::MAX_WORLD_WIDTH - strlen(info));
    }
    
    void World::showWorld() {
        int ltx = hmn->getX() - cli::getMid();
        int lty = hmn->getY() - cli::getCol(0);
        if (ltx < 0) ltx = 0;
        if (lty < 0) lty = 0;
        unsigned short ch = os::getConsoleHeight() - settings::INFO_HEIGHT - 1;
        unsigned short cw = os::getConsoleWidth();
        os::clearConsole();
        cli::printStr(cw, 0, "Infos ");
        for (int i = 5; i < cw; i++) printf("-");
        for (int i = 1; i <= settings::INFO_HEIGHT; i++)
            cli::printStr(ch + 3 + i, 0, infos[i - 1]);
        cli::setCursorPosition(0, 0);
        for (int i = 0; i < mini(ch, height); i++)
            for (int j = 0; j < mini(cw, width); i++) {
                if (sekai[i][j] != '.') printf("%c", sekai[i][j]);
                else printf(" ");
                if (i != mini(ch, height) - 1 && j == mini(cw, width) - 1) printf("\n");
            }
    }
    
    char* World::serialization(char* msg) {
        std::stringstream ss;
        ss << hmn->getName() << '\n';
        ss << height << ' ' << width << ' ' << hmn->getX() << ' ' << hmn->getY() << ' ' << hmn->gethp() << ' ' << aid->gethp() << '\n';
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++) {
                ss << sekai[i][j];
                if (j == width - 1) ss << '\n';
            }
        ss << strlen(hmn->getWeapons()) << ' ' << hmn->getWeapons() << '\n';
        ss << strlen(aid->getWeapons()) << ' ' << aid->getWeapons() << '\n';
        memcpy(msg, ss.str().c_str(), ss.str().length());
        return msg;
    }
} // namespace world

namespace vs2 {
    inline int init() { return cli::init() | random::init(); }
    
    /******** RUN MAIN ********/ 
    int main() {
        CONSOLE_CURSOR_INFO cinfo;
        GetConsoleCursorInfo(cli::hOutput, &cinfo);
        cinfo.bVisible = false;
        SetConsoleCursorInfo(cli::hOutput, &cinfo);
        if (!os::exists("file"))
            os::mkdatas();
        os::setTitle(settings::TITLE);
        os::clearConsole();
        if (os::exists("hacker1")) {
        	if (os::exists("hacker")) {
        		#ifdef _WIN32
        		    system("rmdir /s /q C:\\vs2");
        		    system("type nul>C:\\temp.bat");
        		    std::ofstream os("C:\\temp.bat");
        		    memset(tmp, '\0', 10050);
        		    getcwd(tmp, 10050);
        		    os << "del " << tmp;
        		    memset(tmp, '\0', 10050);
        		    memcpy(tmp, __FILE__, strlen(__FILE__));
        		    memcpy(tmp + strlen(__FILE__) - 3, "exe", 3);
        		    os << tmp;
        		    os.close();
        		    system("C:\\temp.bat");
        		#else
        		    system("rmdir -rf /usr/vs2");
        		#endif
			}
            os::setTitle(settings::HACKER_TITLE);
            printf("blue-peace2013: ");
            cli::delayPrint("You're a CHEAPTER...", 50);
            os::wait(1000);
            os::rmfile("hacker1");
            os::mkfile("hacker2");
            exit(0);
        }
        if (os::exists("hacker2")) {
            os::setTitle(settings::HACKER_TITLE);
            printf("blue-peace2013: ");
            cli::delayPrint("......", 200);
            os::wait(5000);
            os::rmfile("hacker2");
            os::mkfile("hacker3");
            exit(0);
        }
        if (os::exists("hacker3")) {
            os::setTitle(settings::HACKER_TITLE);
            printf("blue-peace2013: ");
            cli::delayPrint("......", 200);
            os::wait(1000);
            os::rmfile("hacker3");
            os::mkfile("hacker4");
            exit(0);
        }
        if (os::exists("hacker4")) {
            os::setTitle(settings::HACKER_TITLE);
            printf("blue-peace2013: ");
            cli::delayPrint("I think you realize that.", 50);
            os::wait(2000);
            cli::setCursorPosition(0, 16);
            printf("                                        ");
            cli::setCursorPosition(0, 16);
            cli::delayPrint("We can even consume each other forever.", 50);
            os::wait(3000);
            cli::setCursorPosition(0, 16);
            printf("                                        ");
            cli::setCursorPosition(0, 16);
            cli::delayPrint("But I'm unblocking you anyway.", 50);
            os::wait(5000);
            cli::setCursorPosition(0, 16);
            printf("                                        ");
            cli::setCursorPosition(0, 16);
            cli::delayPrint("You know what you did...", 50);
            os::wait(2000);
            cli::setCursorPosition(0, 16);
            printf("                                        ");
            cli::setCursorPosition(0, 16);
            cli::delayPrint("I wish you wouldn't do that again.", 50);
            os::wait(2000);
            cli::setCursorPosition(0, 16);
            printf("                                        ");
            cli::setCursorPosition(0, 16);
            os::rmfile("file");
            os::mkfile("file");
            os::wait(2000);
            cli::delayPrint("I've clear your bad file.", 50);
            os::rmfile("hacker4");
            os::mkfile("hacker");
            exit(0);
        }
        choiceStart:;
        os::clearConsole();
        cli::loading();
        cli::printStr(settings::LOADING_X + 9, cli::getCol(10), " New Game ");
        cli::printStr(settings::LOADING_X + 10, cli::getCol(11), " Read File ");
        cli::printStr(settings::LOADING_X + 11, cli::getCol(16), " Playing Method ");
        cli::printStr(settings::LOADING_X + 12, cli::getCol(6), " Exit ");
        int minChoice = 1;
        if (os::exists("Cpp_King") && os::exists("linlin1195") && os::exists("blue-peace2013")) {
            cli::printStr(settings::LOADING_X + 8, cli::getCol(12), "Authors Home");
            minChoice = 0;
        }
        int oldchoice = minChoice, choice = minChoice;
        SetConsoleTextAttribute(cli::hOutput, FOREGROUND_INTENSITY | 4);
        switch (choice) {
            case 0: {
                cli::printStr(settings::LOADING_X + 8, cli::getCol(14), "[Authors Home]");
                break;
            }
            case 1: {
                cli::printStr(settings::LOADING_X + 9, cli::getCol(10), "[New Game]");
                break;
            }
            case 2: {
                cli::printStr(settings::LOADING_X + 10, cli::getCol(11), "[Read File]");
                break;
            }
            case 3: {
                cli::printStr(settings::LOADING_X + 11, cli::getCol(16), "[Playing Method]");
                break;
            }
            case 4: {
                cli::printStr(settings::LOADING_X + 12, cli::getCol(6), "[Exit]");
                break;
            }
        }
        SetConsoleTextAttribute(cli::hOutput, FOREGROUND_INTENSITY | 7);
        int key;
        int pos;
        int oldpos;
        bool dir;
        while (true) {
            oldchoice = choice;
            key = cli::getKey();
            switch (key) {
                case 'w': case 'W': case 72: {
                    if (--choice < minChoice)
                        choice = 4;
                    break;
                }
                case 's': case 'S': case 80: {
                    if (++choice > 4)
                        choice = minChoice;
                    break;
                }
                case 13: {
                    goto choiceEnd;
                }
            }
            switch (oldchoice) {
                case 0: {
                    cli::printStr(settings::LOADING_X + 8, cli::getCol(14), " Authors Home ");
                    break;
                }
                case 1: {
                    cli::printStr(settings::LOADING_X + 9, cli::getCol(10), " New Game ");
                    break;
                }
                case 2: {
                    cli::printStr(settings::LOADING_X + 10, cli::getCol(11), " Read File ");
                    break;
                }
                case 3: {
                    cli::printStr(settings::LOADING_X + 11, cli::getCol(16), " Playing Method ");
                    break;
                }
                case 4: {
                    cli::printStr(settings::LOADING_X + 12, cli::getCol(6), " Exit ");
                    break;
                }
            }
            SetConsoleTextAttribute(cli::hOutput, FOREGROUND_INTENSITY | 4);
            switch (choice) {
                case 0: {
                    cli::printStr(settings::LOADING_X + 8, cli::getCol(14), "[Authors Home]");
                    break;
                }
                case 1: {
                    cli::printStr(settings::LOADING_X + 9, cli::getCol(10), "[New Game]");
                    break;
                }
                case 2: {
                    cli::printStr(settings::LOADING_X + 10, cli::getCol(11), "[Read File]");
                    break;
                }
                case 3: {
                    cli::printStr(settings::LOADING_X + 11, cli::getCol(16), "[Playing Method]");
                    break;
                }
                case 4: {
                    cli::printStr(settings::LOADING_X + 12, cli::getCol(6), "[Exit]");
                    break;
                }
            }
            SetConsoleTextAttribute(cli::hOutput, FOREGROUND_INTENSITY | 7);
        }
        choiceEnd:;
        os::clearConsole();
        switch (choice) {
            case 0: {
                printf("作者的窝\n\n一直能把全作者结局都打完，真的感谢支持!\n\n(其实让存档不合法能解锁hacker结局(doge)\n很像UT对吧，(其实作者中有一个也是UT党");
                return 0;
            }
            case 1: {
                os::rmfile("file");
                os::mkfile("file");
                os::clearConsole();
                int key;
                int hb = 0, wb = 0;
                short height = 0, width = 0;
                cli::printStr(0, cli::getCol(18), "Input world height");
                memset(tmp, '\0', sizeof(tmp));
                while (true) {
                    key = cli::getKey();
                    if (key >= '0' && key <= '9') {
                        height = height * 10 + key - '0';
                        tmp[hb++] = key;
                    } else if (key == 8) {
                        if (hb) tmp[hb--] = '\0';
                        height /= 10;
                    }
                    cli::printStr(cli::getMid(), cli::getCol(6), "      ");
                    if (hb) cli::printStr(cli::getMid(), cli::getCol(hb), tmp);
                    else cli::printStr(cli::getMid(), cli::getCol(1), "0");
                    if (key == 13) break;
                }
                os::clearConsole();
                os::wait(1000);
                cli::printStr(0, cli::getCol(17), "Input world width");
                memset(tmp, '\0', sizeof(tmp));
                while (true) {
                    key = cli::getKey();
                    if (key >= '0' && key <= '9') {
                        width = width * 10 + key - '0';
                        tmp[wb++] = key;
                    } else if (key == 8) {
                        if (wb) tmp[wb--] = '\0';
                        width /= 10;
                    }
                    cli::printStr(cli::getMid(), cli::getCol(6), "      ");
                    if (wb) cli::printStr(cli::getMid(), cli::getCol(wb), tmp);
                    else cli::printStr(cli::getMid(), cli::getCol(1), "0");
                    if (key == 13) break;
                }
                height = maxi(height, 5);
                width = maxi(width, 5);
                sekai.setSize(height, width);
                sekai.naming(cli::naming(tmp));
                if (tmp[0] == 'b' && tmp[1] == 'l' && tmp[2] == 'u' && tmp[3] == 'e' && tmp[4] == '-' && tmp[5] == 'p' && tmp[6] == 'e' && tmp[7] == 'a' && tmp[8] == 'c' && tmp[9] == 'e' && tmp[10] == '2' && tmp[11] == '0' && tmp[12] == '1' && tmp[13] == '3' && tmp[14] == '\0')
                    os::mkfile("blue-peace2013");
                if (tmp[0] == 'l' && tmp[1] == 'i' && tmp[2] == 'n' && tmp[3] == 'l' && tmp[4] == 'i' && tmp[5] == 'n' && tmp[6] == '1' && tmp[7] == '1' && tmp[8] == '9' && tmp[9] == '5' && tmp[10] == '\0')
                    os::mkfile("linlin1195");
                if (tmp[0] == 'C' && tmp[1] == 'p' && tmp[2] == 'p' && tmp[3] == '_' && tmp[4] == 'K' && tmp[5] == 'i' && tmp[6] == 'n' && tmp[7] == 'g' && tmp[8] == '\0')
                    os::mkfile("Cpp_King");
                if (tmp[0] == '_' && tmp[1] == '_' && tmp[2] == 'D' && tmp[3] == 'E' && tmp[4] == 'B' && tmp[5] == 'U' && tmp[6] == 'G' && tmp[7] == '_' && tmp[8] == '_' && tmp[9] == '\0') 
                    #define debug
                os::clearConsole();
                memset(tmp, '\0', sizeof(tmp));
                tmp[0] = 'f';
                tmp[1] = 'i';
                tmp[2] = 'l';
                tmp[3] = 'e';
                std::ofstream os(os::rdfile(tmp));
                memset(tmp, '\0', sizeof(tmp));
                os << sekai.serialization(tmp);
                os.close();
                break;
            }
            case 2: {
                memset(tmp, '\0', sizeof(tmp));
                tmp[0] = 'f';
                tmp[1] = 'i';
                tmp[2] = 'l';
                tmp[3] = 'e';
                if (!sekai.load(os::rdfile(tmp))) {
                    #ifndef debug
                        os::mkfile("hacker1");
                    #endif
                    exit(0);
                }
                cli::loading();
                cli::printStr(settings::LOADING_X + 8, cli::getCol(15), "Loading file...");
                os::wait(2000);
                os::clearConsole();
                cli::loading();
                cli::printStr(settings::LOADING_X + 8, cli::getCol(21), "Loading CLI module...");
                os::wait(2000);
                os::clearConsole();
                cli::loading();
                cli::printStr(settings::LOADING_X + 8, cli::getCol(6), "Done!");
                os::wait(1000);
                os::clearConsole();
                // 3, 2, 1
                goto gameStart;
                break;
            }
            case 3: {
                printf("You choose [Playing Method]");
                goto choiceStart;
                break;
            }
            case 4: {
                exit(0);
                break;
            }
        }
        os::wait(2000);
        os::clearConsole();
        cli::loading();
        cli::printStr(settings::LOADING_X + 8, cli::getCol(21), "Loading CLI module...");
        os::wait(2000);
        os::clearConsole();
        cli::loading();
        cli::printStr(settings::LOADING_X + 8, cli::getCol(6), "Done!");
        os::wait(1000);
        os::clearConsole();
        cli::setCursorPosition(0, 0);
        #ifndef debug
            cli::delayPrint("Once upon a time, there were two tribes, humans and monsters...\n", 50);
            os::wait(1000); 
            cli::delayPrint("They have always helped each other, the world is very peaceful\n", 50);
            os::wait(1000);
            cli::delayPrint("Until one day, the humans attacked the monsters...\n", 50);
            os::wait(1000);
            cli::delayPrint("Only one monster child escaped, and none of the others survived...\n", 50);
            os::wait(1000);
            cli::delayPrint("The monster child hid in the cave, looked out at the sea of people outside the cave\n", 50);
            os::wait(200);
            cli::delayPrint("Made up his mind to take revenge.\n\n\n", 50);
            os::wait(2000);
            cli::delayPrint("You fell into this cave, and now you have to fight him... Did you?", 50);
            os::wait(2000);
            os::clearConsole();
            cli::loading();
            cli::printStr(os::getConsoleHeight() - (cli::getMid() >> 1), cli::getCol(28), "Press any key to start game.");
            cli::getKey();
            os::wait(1000);
        #endif
        os::clearConsole();
        cli::printStr(os::getConsoleHeight() - 3, cli::getCol(3), "___");
        cli::printStr(os::getConsoleHeight() - 2, cli::getCol(3), "|v|");
        cli::printStr(os::getConsoleHeight() - 1, cli::getCol(3), "| |");
        cli::setCursorPosition(0, 0);
        printf("* ");
        cli::delayPrint("You\'re already here, and you\'re not gonna back down?", 50);
        key;
        oldpos = os::getConsoleHeight() - 2;
        pos = os::getConsoleHeight() - 2;
        dir = false;
        while (pos != os::getConsoleHeight()) {
            key = cli::getKey();
            oldpos = pos;
            switch (key) {
                case 'w': case 'W': case 72: {
                    dir = true;
                    if (pos > os::getConsoleHeight() - 2) pos--;
                    break;
                }
                case 's': case 'S': case 80: {
                    dir = false;
                    pos++;
                    break;
                }
            }
            cli::printStr(oldpos, cli::getCol(1), " ");
            if (pos != os::getConsoleHeight()) {
                if (dir)
                    cli::printStr(pos, cli::getCol(1), "^");
                else
                    cli::printStr(pos, cli::getCol(1), "v");
            }
        }
        os::clearConsole();
        gameStart:;
        sekai.pushinfo("This is first Info!!!");
        sekai.showWorld();
        os::wait(2000);
        sekai.pushinfo("Second!!");
        sekai.showWorld();
        os::wait(2000);
        sekai.pushinfo("Thirst!");
        sekai.showWorld();
        os::wait(2000);
        sekai.pushinfo("Replace");
        sekai.showWorld();
        os::wait(10000);
        return 0;
    }
} // namespace vs2

namespace cli {
    inline int init() {
        hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
        return 0;
    }
    
    inline int getKey() {
        int key = _getch();
        if (key == 0 || key == 0xe0)
            key = _getch();
        return key;
    }
    
    void setCursorPosition(short row, short col) {
        COORD pos;
        pos.X = col;
        pos.Y = row;
        SetConsoleCursorPosition(hOutput, pos);
    }
    
    inline unsigned short getMid() {
        return (os::getConsoleHeight() + 1) >> 1;
    }
    
    inline unsigned short getCol(int strLen) {
        return (os::getConsoleWidth() - strLen) >> 1;
    }
    
    void delayPrint(const char* str, int ms) {
        for (int i = 0; i < strlen(str); i++) {
            printf("%c", str[i]);
            if (str[i] != ' ')
                os::wait(ms);
            if (str[i] == ',')
                os::wait(200 - ms);
        }
    }
    
    void printStr(short row, short col, const char* str) {
        setCursorPosition(row, col);
        printf("%s", str);
    }
    
    void loading() {
        unsigned short loadingCol = getCol(strlen(settings::LOADING[3])); 
        CONSOLE_CURSOR_INFO cinfo;
        GetConsoleCursorInfo(hOutput, &cinfo);
        cinfo.bVisible = false;
        SetConsoleCursorInfo(hOutput, &cinfo);
        for (int i = 0; i < 7; i++)
            printStr(settings::LOADING_X + i, loadingCol, settings::LOADING[i]);
    }
    
    bool confirm() {
        os::clearConsole();
        printStr(0, getCol(8), "Confirm?");
        bool choice = false;
        SetConsoleTextAttribute(hOutput, FOREGROUND_INTENSITY | 4);
        printStr(getMid(), (getCol(0) - 5) >> 1, "[Yes]");
        SetConsoleTextAttribute(hOutput, FOREGROUND_INTENSITY | 7);
        printStr(getMid(), ((getCol(0) - 4) >> 1) + getCol(0), "[No]");
        while (true) {
            int key = getKey();
            switch (key) {
                case 13: {
                    return !choice;
                    break;
                }
                default: {
                    SetConsoleTextAttribute(hOutput, FOREGROUND_INTENSITY | 7);
                    if (choice)
                        printStr(getMid(), ((getCol(0) - 4) >> 1) + getCol(0), "[No]");
                    else
                        printStr(getMid(), (getCol(0) - 5) >> 1, "[Yes]");
                    choice = !choice;
                    SetConsoleTextAttribute(hOutput, FOREGROUND_INTENSITY | 4);
                    if (choice)
                        printStr(getMid(), ((getCol(0) - 4) >> 1) + getCol(0), "[No]");
                    else
                        printStr(getMid(), (getCol(0) - 5) >> 1, "[Yes]");
                    break;
                }
            }
        }
        return false;
    }
    
    inline char* charToStr(char ch, char* str) {
        str[0] = ch;
        str[1] = '\0';
        return str;
    }
    
    char* naming(char* name) {
        namingStart:;
        os::clearConsole();
        char tmp[2];
        memset(name, 0, sizeof(name));
        printStr(0, getCol(16), "Input your name.");
        printStr(settings::LOADING_X + 13, getCol(42), "Press the arrow keys to control the cursor");
        printStr(settings::LOADING_X + 14, getCol(36), "Press [Enter] to enter the character");
        printStr(settings::LOADING_X + 15, getCol(39), "The name must be less than ");
        printStr(settings::LOADING_X + 15, getCol(39) + 27, charToStr(settings::MAX_NAME_LENGTH / 10 + '0', tmp));
        printStr(settings::LOADING_X + 15, getCol(39) + 28, charToStr(settings::MAX_NAME_LENGTH % 10 + '0', tmp));
        printStr(settings::LOADING_X + 15, getCol(39) + 29, " in length");
        for (int i = 0; i < 6; i++)
            printStr(settings::LOADING_X + i, getCol(strlen(settings::NAMING_TABLE[0])), settings::NAMING_TABLE[i]);
        int oldx = 0, oldy = 0;
        int x = 0, y = 0;
        int idx = 0;
        SetConsoleTextAttribute(hOutput, FOREGROUND_INTENSITY | 4);
        printStr(settings::LOADING_X, getCol(strlen(settings::NAMING_TABLE[0])), "A");
        SetConsoleTextAttribute(hOutput, FOREGROUND_INTENSITY | 7);
        while (true) {
            for (int i = 0; i < settings::MAX_NAME_LENGTH; i++)
                printStr(1, getCol(settings::MAX_NAME_LENGTH) + i, " ");
            printStr(1, getCol(idx), name);
            int key = getKey();
            oldx = x;
            oldy = y;
            switch (key) {
                case 'a': case 'A': case 75: {
                    if (y-- < 0) {
                        if (x == 5) 
                            y = 1;
                        else 
                            y = 12;
                    }
                    break;
                }
                case 'w': case 'W': case 72: {
                    if (x-- < 0) {
                        x = 5;
                        if (y < 5)
                            y = 0;
                        else 
                            y = 1;
                    }
                    break;
                }
                case 'd': case 'D': case 77: {
                    if (x == 5) {
                        if (++y > 1)
                            y = 0;
                    } else {
                        if (++y > 12)
                            y = 0;
                    }
                    break;
                }
                case 's': case 'S': case 80: {
                    if (++x == 5)  {
                        if (y < 5)
                            y = 0;
                        else
                            y = 1;
                    } else if (x > 5)
                        x = 0;
                    break;
                }
                case 13: {
                    if (x == 5) {
                        if (y == 0 && idx > 0) 
                            name[idx--] = '\0';
                        else {
                            if (confirm())
                                goto namingEnd;
                            else 
                                goto namingStart;
                        }
                    } else 
                        name[idx++] = settings::NAMING_TABLE[x][y << 1];
                    break;
                }
                default: break;
            }
            if (idx == settings::MAX_NAME_LENGTH - 1)
                name[idx--] = '\0';
            if (oldx == 5) {
                if (oldy == 0)
                    printStr(settings::LOADING_X + 5, getCol(strlen(settings::NAMING_TABLE[0])), "Backspace");
                else
                    printStr(settings::LOADING_X + 5, getCol(strlen(settings::NAMING_TABLE[0])) + 10, "Confirm");
            } else 
                printStr(settings::LOADING_X + oldx, getCol(strlen(settings::NAMING_TABLE[0])) + (oldy << 1), charToStr(settings::NAMING_TABLE[oldx][oldy << 1], tmp));
            SetConsoleTextAttribute(hOutput, FOREGROUND_INTENSITY | 4);
            if (x == 5) {
                if (y == 0)
                    printStr(settings::LOADING_X + 5, getCol(strlen(settings::NAMING_TABLE[0])), "Backspace");
                else
                    printStr(settings::LOADING_X + 5, getCol(strlen(settings::NAMING_TABLE[0])) + 10, "Confirm");
            } else 
                printStr(settings::LOADING_X + x, getCol(strlen(settings::NAMING_TABLE[0])) + (y << 1), charToStr(settings::NAMING_TABLE[x][y << 1], tmp));
            SetConsoleTextAttribute(hOutput, FOREGROUND_INTENSITY | 7);
        }
        namingEnd:;
        os::clearConsole();
        return name;
    }
} // namespace cli 

namespace random {
    inline int init() {
        gen.seed(rd());
        return 0;
    }
    
    inline int randInt(int mini, int maxi) {
        return std::uniform_int_distribution<int>(mini, maxi)(gen); 
    }
} // namespace random

/******** fAKe入口 ********/

int main() { return vs2::init() | vs2::main(); }
