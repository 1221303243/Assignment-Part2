// *********************************************************
// Course: TCP1101 PROGRAMMING FUNDAMENTALS
// Year: Trimester 1, 2022/23 (T2215)
// Lab: TxxL
// Names: Arif Faisal Bin Zakaria | Aizam Nazmien Bin Alinoordin | KOK YEW YAN
// IDs: 1221303243 | 1221303556 | 1211103790
// Emails: 1221303243@student.mmu.edu.my | 1221303556@student.mmu.edu.my | 1211103790@student.mmu.edu.my
// Phones: 01172428763 | 0146566541 | 0196696608
// *********************************************************

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <cstdlib> // for system()
#include <ctime>   // for time() in srand( time(NULL) );
#include <iomanip> // for setw()
#include <algorithm>
#include <cctype>
#include <limits>
#include <fstream>
#include <sstream>
#include <cmath>
#include <stdlib.h>

using namespace std;

class Mapsetting{
protected:
    int rows, columns,count,Z;

public:
    Mapsetting();
    void setColumns(int columns);
    void setRows(int rows);
    void setCount(int count);
    int getColumns();
    int getRows();
    int getCount();
    void setZ(int Z);
    int getZ() const;
};

class Map{
protected:
    vector<vector<char>> map_; // convention to put trailing underscore
    int dimX_, dimY_; // to indicate private data

public:
    Map(int dimX = 9, int dimY = 5);
    void init(int dimX, int dimY);
    void display() const;
    int getDimX();
    int getDimY();
    void setdimX(int dimX_);
    void setdimY(int dimY_);
    char getObject(int x, int y) const;
    void setObject(int x, int y, char ch);
    bool isEmpty(int x, int y);
    bool isInsideMap(int x, int y);
    int getNextObj(int x, int y, int currTask);
};

class Rover{
protected:
    int x_, y_;

public:
    Rover();
    int getX();
    int getY();
};

class Alien{
protected:
    int hp, atk;

public:
    Alien();
    void setHP(int hp);
    void setATK(int atk);
    int getHP();
    int getATK();
};

class Zombie{
protected:
    int x_, y_,hp,atk,atk_range,left,ttleft;

public:
    Zombie();
    int getHP();int getAtk(); int getAtkRange(); int getX(); int getY();int getleft();    int getttleft();
    void setX(int x_);    void setY(int y_); void setHP(int hp);void setATK(int atk);void setATKRange(int atk_range);void setleft(int left);
    void setttleft(int ttleft);
};

class Save{
protected:
    int oy,ox,o;
    char oo;

public:
    Save();
    void setox(int ox);void setoy(int oy);void setoo(char oo);
    int getox();int getoy();int getoo();void seto(int o);int geto();
};

class Obj : public Rover {
protected:
    int Targetx, Targety;
    char Alien_;

public:
    Obj();
    int getX();int getY(); int getTargetx();    int getTargety();
    void setTargetx(int Targetx);void setTargety(int Targety); void Alien(Map& map); void help(Map& map, int& task);
    void arrow(Map& map, int& task); void save(Map& map); void load(Map& map); void quit(Map& map);
    void up(Map& map, int& task);void down(Map& map, int& task); void right(Map& map, int& task);void left(Map& map, int& task);
    void rock(Map& map, int& task);void trail(Map& map, int& task); void quit(Map& map, int& task);
};

Mapsetting::Mapsetting(){}

void Mapsetting::setColumns(int columns){this->columns = columns;}

void Mapsetting::setRows(int rows){this->rows = rows;}

void Mapsetting::setCount(int count){this->count = count;}

int Mapsetting::getColumns(){return this->columns;}

int Mapsetting::getRows(){return this->rows;}

int Mapsetting::getCount(){return this->count;}

void Mapsetting::setZ(int Z){this->Z = Z;}

int Mapsetting::getZ() const{return Z;}

void Map::setdimX(int dimX_){this->dimX_ = dimX_;}

void Map::setdimY(int dimY_){this->dimY_ = dimY_;}

int Map::getNextObj(int x, int y, int currTask){
    Alien Alien;
    char obj = getObject(x, y);
    switch (obj){
    case '^': return 13;break;

    case 'v':return 14; break;

    case '<': return 15;break;

    case '>': return 16; break;

    case 'p':{
        cout << "it is a pod" << endl;
        cout << "Press enter to continue ..." << endl;
        int saveTask = currTask;
        std::cin.get();
        return 8;
    }

    case 'h':{
        cout << "Alien found a health" << endl;
        cout << "Press enter to continue ..." << endl;
        int saveTask = currTask;
        std::cin.get();
        return 10;
    }

    case '1':
        return 28; break;

    case '2':
        return 29; break;

    case '3':
        return 30; break;

    case '4': 
        return 31; break;

    case '5':
        return 32; break;

    case '6':
        return 33; break;

    case '7':
        return 34; break;

    case '8':
        return 35; break;

    case '9':
        return 36; break;

    case 'r':
        return 11;

    default:
        break; // and so on...
    }
    return currTask;
}
bool Map::isEmpty(int x, int y){return map_[dimY_ - y][x - 1] == ' ';}

bool Map::isInsideMap(int x, int y){return x && y && dimX_ - x + 1 && dimY_ - y + 1;}

void Map::setObject(int x, int y, char ch){map_[dimY_ - y][x - 1] = ch;}

char Map::getObject(int x, int y) const{return map_[dimY_ - y][x - 1];}

int Map::getDimX(){return dimX_;}

int Map::getDimY(){return dimY_;}

Map::Map(int dimx, int dimy){init(dimx, dimy);}

void Map::init(int dimX, int dimY){
    dimX_ = dimX; dimY_ = dimY;
    char objects[] = { ' ', ' ', ' ', 'r', '^', '>', '<', 'v', 'h', 'p' };
    int noOfObjects = 10; // number of objects in the objects array
    // create dynamic 2D array using vector
    map_.resize(dimY_); // create empty rows
    for (int i = 0; i < dimY_; ++i){ map_[i].resize(dimX_);} // resize each row

    // put random characters into the vector array
    for (int i = 0; i < dimY_; ++i){
        for (int j = 0; j < dimX_; ++j){
            int objNo = rand() % noOfObjects;
            map_[i][j] = objects[objNo];
        }
    }
}
void Map::display() const{
    if (2 * dimX_ > 17){
        for (int k = 0; k < (2 * dimX_ - 17) / 2 + 3; ++k) { cout << " ";}
        cout << ">Alien vs Zombie<" << endl;
    }
    else
        cout << ">Alien vs Zombie<" << endl;
    // for each row
    for (int i = 0; i < dimY_; ++i){
        // display upper border of the row
        cout << "  ";
        for (int j = 0; j < dimX_; ++j){ cout << "+-";}
        cout << "+" << endl;
        // display row number
        cout << setw(2) << (dimY_ - i);
        // display cell content and border of each column
        for (int j = 0; j < dimX_; ++j){ cout << "|" << map_[i][j];}
        cout << "|" << endl;
    }
    // display lower border of the last row
    cout << "  ";
    for (int j = 0; j < dimX_; ++j){ cout << "+-";}
    cout << "+" << endl;
    // display column number
    cout << "  ";
    for (int j = 0; j < dimX_; ++j){
        int digit = (j + 1) / 10;
        cout << " ";
        if (digit == 0)
            cout << " ";
        else
            cout << digit;
    }
    cout << endl;
    cout << "  ";
    for (int j = 0; j < dimX_; ++j){ cout << " " << (j + 1) % 10; }
    cout << endl << endl;
}

Rover::Rover(){}

int Rover::getX(){return x_;}

int Rover::getY(){return y_;}

Alien::Alien() {};

void Alien::setHP(int hp){this->hp = hp;};

void Alien::setATK(int atk){this->atk = atk;};

int Alien::getHP(){return this->hp;};

int Alien::getATK(){return this->atk;};

Zombie::Zombie(){
    hp = (rand() % 5 + 2) * 50; // 100 - 300
    atk = (rand() % 5 + 1) * 5; // 5 - 25
    atk_range = rand() % 3 + 1; // 1 - 3
};

int Zombie::getHP(){return hp;};

int Zombie::getAtk(){return atk;};

int Zombie::getAtkRange(){return atk_range;};

void Zombie::setX(int x_){this->x_ = x_;}

void Zombie::setY(int y_){this->y_ = y_;}

int Zombie::getX() {return x_;};

int Zombie::getY(){return y_;};

void Zombie::setHP(int hp){this->hp = hp;}

void Zombie::setATK(int atk){this->atk = atk;}

void Zombie::setATKRange(int atk_range){this->atk_range = atk_range;}

void Zombie::setleft(int left){this->left = left;}

int Zombie::getleft(){return left;}

void Zombie::setttleft(int left){this->ttleft = ttleft;}

int Zombie::getttleft(){return ttleft;}

Obj::Obj(){}

void Obj::Alien(Map& map){
    char Alien = { 'A' };
    x_ = (map.getDimX() + 1) / 2;
    y_ = (map.getDimY() + 1) / 2;
    Alien_ = Alien;
    map.setObject(x_, y_, Alien_);
}

int Obj::getX(){return x_;}

int Obj::getY(){return y_;}

void Obj::setTargetx(int Targetx){this->Targetx = Targetx;}

void Obj::setTargety(int Targety){this->Targety = Targety;}

int Obj::getTargetx(){return Targetx;}

int Obj::getTargety(){return Targety;}

void Obj::up(Map& map, int& nextTask){
    char Alien = map.getObject(x_, y_);
    int targetX = x_, targetY = y_;
    targetY += 1;
    setTargetx(targetX);setTargety(targetY);
    if (map.isInsideMap(targetX, targetY)){
        // Check next
        nextTask = map.getNextObj(targetX, targetY, nextTask);
        if (nextTask == 11){ }
        else if (nextTask == 28 || nextTask == 29 || nextTask == 30 || nextTask == 31 || nextTask == 32 || nextTask == 33 || nextTask == 34 || nextTask == 35 || nextTask == 36){
            targetY -= 1;
            setTargety(targetY);
        }
        // Update
        else{
            map.setObject(x_, y_, '.'); // Remove old
            x_ = targetX;
            y_ = targetY;
            map.setObject(targetX, targetY, Alien_); // New
        }
    }

    else{
        cout << "Alien stop moving" << endl;
        cout << "Press enter to continue ..." << endl;
        std::cin.get();
        nextTask = 12;
    }
}
void Obj::down(Map& map, int& nextTask){
    char Alien = map.getObject(x_, y_);
    int targetX = x_,targetY = y_;
    targetY -= 1;
    setTargetx(targetX); setTargety(targetY);
    if (map.isInsideMap(targetX, targetY)){
        // Check next
        nextTask = map.getNextObj(targetX, targetY, nextTask);
        if (nextTask == 11){}//Nothing
        else if (nextTask == 28 || nextTask == 29 || nextTask == 30 || nextTask == 31 || nextTask == 32 || nextTask == 33 || nextTask == 34 || nextTask == 35 || nextTask == 36){
            targetY += 1;
            setTargety(targetY);
        }// Update
        else{
            map.setObject(x_, y_, '.'); // Remove old
            x_ = targetX; y_ = targetY;
            map.setObject(targetX, targetY, Alien_); // New
        }
    }
    else{
        cout << "Alien stop moving" << endl;
        cout << "Press enter to continue ..." << endl;
        std::cin.get();
        nextTask = 12;
    }
}

void Obj::left(Map& map, int& nextTask){
    char Alien = map.getObject(x_, y_);
    int targetX = x_, targetY = y_;
    targetX -= 1;
    setTargetx(targetX); setTargety(targetY);
    if (map.isInsideMap(targetX, targetY)){
        // Check next
        nextTask = map.getNextObj(targetX, targetY, nextTask);
        if (nextTask == 11){}//Nothing
        else if (nextTask == 28 || nextTask == 29 || nextTask == 30 || nextTask == 31 || nextTask == 32 || nextTask == 33 || nextTask == 34 || nextTask == 35 || nextTask == 36){
            targetX += 1;
            setTargetx(targetX);
        } // Update
        else{
            map.setObject(x_, y_, '.'); // Remove old
            x_ = targetX;
            y_ = targetY;
            map.setObject(targetX, targetY, Alien_); // New
        }
    }
    else{
        cout << "Alien stop moving" << endl;
        cout << "Press enter to continue ..." << endl;
        std::cin.get();
        nextTask = 12;
    }
}

void Obj::right(Map& map, int& nextTask){
    char Alien = map.getObject(x_, y_);
    int targetX = x_, targetY = y_;
    targetX += 1;
    setTargetx(targetX); setTargety(targetY);
    if (map.isInsideMap(targetX, targetY)){ { // Check next
            nextTask = map.getNextObj(targetX, targetY, nextTask);
            if (nextTask == 11){ }
            else if (nextTask == 28 || nextTask == 29 || nextTask == 30 || nextTask == 31 || nextTask == 32 || nextTask == 33 || nextTask == 34 || nextTask == 35 || nextTask == 36){
                targetX -= 1;
                setTargetx(targetX);
            }
            else{                               // Update
                map.setObject(x_, y_, '.'); // Remove old
                x_ = targetX; y_ = targetY;
                map.setObject(targetX, targetY, Alien_); // New
            }
        }
    }
    else{
        cout << "Alien stop moving" << endl;
        cout << "Press enter to continue ..." << endl;
        std::cin.get();
        nextTask = 12;
    }
}
void Obj::trail(Map& map, int& task){
    for (int x = 1; x <= map.getDimX(); x++){
        for (int y = 1; y <= map.getDimY(); y++){
            char obj = map.getObject(x, y);
            if (obj == 46){
                int num = rand() % 10;
                switch (num){
                case 0:obj = 94;break;// ^

                case 1:obj = 60;break;// <

                case 2:obj = 62;break;// >

                case 3:obj = 118;break; // v

                case 4:obj = 112;break; // p

                case 5:obj = 104;break; // h

                case 6:obj = 114;break;// r

                case 7:obj = 32;break;// ' '

                case 8:obj = 32;break;// ' '

                case 9:obj = 32;break;// ' '

                default:break;
                }
                map.setObject(x, y, obj);
            }
        }
    }
    cout << "Alien turn end" << endl;
    cout << "Press enter to continue ..." << endl;
    std::cin.get();
    cout << "Zombie turn" << endl;
    cout << "Press enter to continue ..." << endl;
    std::cin.get();
    task = 17;
}
void Obj::arrow(Map& map, int& task){
    int x, y;
    string turning;
    cout << "key in x coordinate=>";
    cin >> x;
    cout << endl;
    cout << "key in y coordinate=>";
    cin >> y;
    cout << endl;
    if (map.isInsideMap(x, y) && y <= map.getDimY() && y > 0 && x <= map.getDimX() && x > 0){
        char arrow = map.getObject(x, y);
        cout << "key in turning direction(left or right)=>";
        cin >> turning;
        cout << '\n';
        if (turning == "left"){
            switch (arrow){
            case 94:arrow = 60;break; // ^

            case 60:arrow = 118;break;// <

            case 62:arrow = 94;break;// >

            case 118:arrow = 62;break; // v

            default:cout << "not an arrow" << endl;break;
            }
            map.setObject(x, y, arrow);
        }
        else if (turning == "right"){
            switch (arrow){
            case 60:arrow = 94;break;

            case 118:arrow = 60;break;

            case 94:arrow = 62;break;

            case 62:arrow = 118;break;

            default:cout << "not an arrow" << endl;
                cin.clear();break;
            }
            map.setObject(x, y, arrow);
        }
        else{
            cout << "unvalid direction" << endl;
        }
        map.display();
    }

    else{
        cout << "out the map" << endl;
        cin.clear();
        cin.ignore(10, '\n');
    }
    task = 0;
}
void Obj::help(Map& map, int& task){
    cout << "Commands" << endl;
    cout << "1. up     - Move up." << endl;
    cout << "2. down   - Move down." << endl;
    cout << "3. left   - Move left." << endl;
    cout << "4. right  - Move right." << endl;
    cout << "5. arrow  - Change the direction of an arrow." << endl;
    cout << "6. help   - Display these user commands." << endl;
    cout << "7. save   - Save the game." << endl;
    cout << "8. load   - Load a game." << endl;
    cout << "9. quit   - Quit the game." << endl;
    task = 0;
}
void Obj::save(Map& map){cout << "saving..." << endl;}

void Obj::load(Map& map){cout << "loading..." << endl;}

void Obj::quit(Map& map){cout << "quit the game" << endl;}

void Obj::rock(Map& map, int& task){
    int x = getTargetx(), y = getTargety(), num = rand() % 7;
    char obj = map.getObject(x, y);
    switch (num){
    case 0: // ^
        obj = 94;
        cout << "Alien discover an up arrow beneath the rock" << endl;
        cout << endl;break;

    case 1: // <
        obj = 60;
        cout << "Alien discover an left arrow beneath the rock" << endl;
        cout << endl;break;

    case 2: // >
        obj = 62;
        cout << "Alien discover an right arrow beneath the rock" << endl;
        cout << endl;break;

    case 3: // v
        obj = 118;
        cout << "Alien discover an down arrow beneath the rock" << endl;
        cout << endl;break;

    case 4: // p
        obj = 112;
        cout << "Alien discover a pod arrow beneath the rock" << endl;
        cout << endl;break;

    case 5: // h
        obj = 104;
        cout << "Alien discover an health arrow beneath the rock" << endl;
        cout << endl;break;

    case 6: // ' '
        obj = 32;
        cout << "There is nothing beneath the rock" << endl;
        cout << endl; break;

    default:break;
    }
    map.setObject(x, y, obj);
    cout << "Press enter to continue ..." << endl;
    std::cin.get();
    task = 12;
}
void Obj::quit(Map& map, int& task){
    string quit;
    bool qit = true;
    while (qit){
        cout << "Quit the game? y/n =>";
        cin >> quit;
        if (quit == "y"){
            task = 88;
            cout << "Quit the game !" << endl;
            qit = false; break;
        }
        else if (quit == "n"){
            task = 0;
            cout << "game continue" << endl;
            qit = false;break;
        }
        else{
            cout << "Please key in y/n only!" << endl;
        }
    }
}
Save::Save(){}
void Save::setox(int ox){this->ox = ox;}

void Save::setoy(int oy){this->oy = oy;}

void Save::setoo(char oo){this->oo = oo;}

int Save::getox(){return ox;}

int Save::getoy(){return oy;}

int Save::getoo(){return oo;}

void Save::seto(int o){this->o = o;}

int Save::geto(){return o;}

bool lettersOrSpaces(const std::string& str){
    for (size_t i = 0; i < str.size(); i++){
        if (!std::isalpha(str[i]) && !std::isspace(str[i])) return false;
    }
    return true;
}

float getDistance(int x1, int y1, int x2, int y2){
    return sqrt(pow((x1 - x2), 2.0) + pow((y1 - y2), 2.0));
}

void maingame(){
    Mapsetting Mapsetting;
    int gameboard_rows, gameboard_columns, change_settings_num, zombie_count;
    string change_settings; string choose;
    fstream myFile;string filename;string command;
    Obj curiosity;
    Save obj[1000];
    Alien Alien;
    Rover Rover;
    Zombie Array[9];Zombie Zombie;
    int Count,i;
    float distance;
    int ATK, HP, hpleft, attack, damage, Death,o=0;
    int task; // 0 = stop, 1 = up, 2 = down, 3 = left, 4 = right
    int defeated1, defeated2, defeated3, defeated4, defeated5, defeated6, defeated7, defeated8, defeated9;
    bool all = true;
    Mapsetting.setZ(0);
    // Default Game Settings
    gameboard_rows = 5;gameboard_columns = 9;zombie_count = 1;
    while (all){
        cout << "do you want to load game or restart a new game(load/restart)=>";
        cin >> choose;
        if (choose == "load"){
            Mapsetting.setZ(1);
            all = false;
        }
        else if (choose == "restart"){
            Mapsetting.setZ(0);
            all = false;
        }
        else{cout << "unvalid command" << endl;}
    }

    if (Mapsetting.getZ() == 0){
        cout << "Default Game Settings" << endl;
        cout << "-----------------------" << endl;
        cout << "Board Rows    : " << gameboard_rows << endl;
        cout << "Board Columns : " << gameboard_columns << endl;
        cout << "Zombie Count  : " << zombie_count << endl;
        cout << " " << endl;
        cout << "Do you wish to change the game settings (y/n)? => ";
        cin >> change_settings;

        while (change_settings != "y" && change_settings != "n"){
            cout << " " << endl;
            cout << "Please enter y/n only!" << endl;
            cout << "                                                                       " << endl;
            cout << "Do you wish to change the game settings (y/n)? => ";
            cin >> change_settings;
        }
        const char* y = "y";
        const char* n = "n";

        if (change_settings == y){change_settings_num = 1;}

        else{ change_settings_num = 0;}

        cout << " " << endl;

        if (change_settings_num == 1){
            cout << "Board Settings" << endl;
            cout << "----------------" << endl;
            cout << "Enter rows => ";
            while (true) {
                cin >> gameboard_rows;
                if (!cin){
                    cout << "No alphabets or speacial characters, please enter any odd numbers only" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Enter rows => ";
                    continue;
                }
                else if (gameboard_rows % 2 == 0){
                    cout << "Number must be odd number, please try again" << endl;
                    cin.clear();
                    cout << "Enter rows => ";
                    continue;
                }
                else if (gameboard_rows < 0){
                    cout << "Number must be positif" << endl;
                    cin.clear();
                    cout << "Enter rows => ";
                    continue;
                }
                else break;
            }
            cout << "Enter columns => ";
            while (true){
                cin >> gameboard_columns;
                if (!cin){
                    cout << "No alphabets or special characters, please enter any odd numbers only." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Enter columns => "; continue;
                }

                if (gameboard_columns % 2 == 0){
                    cout << "Number must be odd number, please try again." << endl;
                    cin.clear();
                    cout << "Enter columns => "; continue;
                }

                else if (gameboard_columns < 0){
                    cout << "Number must be positif" << endl;
                    cin.clear();
                    cout << "Enter rows => ";continue;
                }
                else break;
            }
        }
        if (change_settings_num == 1){
            cout << " " << endl;
            cout << "Zombie Settings" << endl;
            cout << "----------------" << endl;
            cout << "Enter number of zombies => ";
            while (true) {
                cin >> zombie_count;
                if (!cin){
                    cout << "No alphabets or special characters is allowed" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Enter number of zombies => ";continue;
                }

                else if (zombie_count > 9) {
                    cout << "Numbers more than 9 are not accepted, please try again." << endl;
                    cin.clear();
                    cout << "Enter number of zombies => "; continue;
                }
                else if (zombie_count < 1){
                    cout << "Numbers less than 1 are not accepted, please try again." << endl;
                    cin.clear();
                    cout << "Enter number of zombies => "; continue;
                }
                else break;
            }

            cout << "Settings Updated." << endl;
        }

        if (change_settings_num == 0){cout << "game continues" << endl; }

        Mapsetting.setColumns(gameboard_columns);
        Mapsetting.setRows(gameboard_rows);
        Mapsetting.setCount(zombie_count);
        cout << "board rows: " << gameboard_rows << endl;
        cout << "board columns: " << gameboard_columns << endl;
        cout << "zombie count: " << zombie_count << endl;
        int Columns = Mapsetting.getColumns(), Rows = Mapsetting.getRows();
        Count = Mapsetting.getCount();
        distance;
        for (i = 0; i < Count; i++){
            int x_ = rand() % Columns + 1; int y_ = rand() % Rows + 1;
            Array[i].setX(x_);Array[i].setY(y_);
        }
        Map map = Map(Columns, Rows);
        ATK = 0;HP = 100;hpleft;attack = 0;damage = 0; Death = 0;
        task = 0; // 0 = stop, 1 = up, 2 = down, 3 = left, 4 = right
        defeated1 = 0, defeated2 = 0, defeated3 = 0, defeated4 = 0, defeated5 = 0, defeated6 = 0, defeated7 = 0, defeated8 = 0, defeated9 = 0;
        Alien.setHP(HP);Alien.setATK(ATK);curiosity.Alien(map);
    }
    else if (Mapsetting.getZ() == 1){
        bool txt = true;
        cout << "load game" << endl;
        while (txt){
            cout << " key in the file name want to load (.txt)=>";
            cin >> filename;
            myFile.open(filename, ios::in); // read
            int n = 0;
            bool game;
            if (myFile.is_open()){
                txt = false;
                string line;
                int num, W,a,b;
                char ob;
                while (getline(myFile, line) && n < 223){
                    Map map = Map(Mapsetting.getColumns(), Mapsetting.getRows());
                    ++n;
                    if (n == 3){
                        num = stoi(line);
                        Mapsetting.setColumns(num);
                    }
                    else if (n == 5){
                        num = stoi(line);
                        Mapsetting.setRows(num);
                        map.setdimX(Mapsetting.getColumns());
                        map.setdimY(Mapsetting.getRows());
                    }

                    else if (n == 12){
                        num = stoi(line);
                        Alien.setATK(num);
                    }
                    else if (n == 14){
                        num = stoi(line);
                        Alien.setHP(num);
                    }
                    else if (n == 17){
                        num = stoi(line);
                        Mapsetting.setCount(num);
                        i = Mapsetting.getCount();
                    }
                    else if (n == 19){
                        num = stoi(line);
                        Array->setttleft(num);
                    }
                    else if (n == 22){
                        {
                            num = stoi(line);
                            Array[0].setX(num);
                        }
                    }
                    else if (n == 24){
                        {
                            num = stoi(line);
                            Array[0].setY(num);
                        }
                    }
                    else if (n == 26) {
                        num = stoi(line);
                        Array[0].setATK(num);
                    }
                    else if (n == 28){
                        num = stoi(line);
                        Array[0].setHP(num);
                    }
                    else if (n == 30){
                        num = stoi(line);
                        Array[0].setATKRange(num);
                    }
                    else if (n == 31){
                        num = stoi(line);
                        Array[0].setleft(num);
                    }
                    else if (Mapsetting.getCount() > 1 && n == 34){
                        {
                            num = stoi(line);
                            Array[1].setX(num);
                        }
                    }
                    else if (Mapsetting.getCount() > 1 && n == 36){
                        {
                            num = stoi(line);
                            Array[1].setY(num);
                        }
                    }
                    else if (Mapsetting.getCount() > 1 && n == 38){
                        num = stoi(line);
                        Array[1].setATK(num);
                    }
                    else if (Mapsetting.getCount() > 1 && n == 40){
                        num = stoi(line);
                        Array[1].setHP(num);
                    }
                    else if (Mapsetting.getCount() > 1 && n == 42){
                        num = stoi(line);
                        Array[1].setATKRange(num);
                    }
                    else if (Mapsetting.getCount() > 1 && n == 43) {
                        num = stoi(line);
                        Array[1].setleft(num);
                    }
                    else if (Mapsetting.getCount() > 2 && n == 46){
                        {
                            num = stoi(line);
                            Array[2].setX(num);
                        }
                    }
                    else if (Mapsetting.getCount() > 2 && n == 48){
                        {
                            num = stoi(line);
                            Array[2].setY(num);
                        }
                    }
                    else if (Mapsetting.getCount() > 2 && n == 50){
                        num = stoi(line);
                        Array[2].setATK(num);
                    }
                    else if (Mapsetting.getCount() > 2 && n == 52){
                        num = stoi(line);
                        Array[2].setHP(num);
                    }
                    else if (Mapsetting.getCount() > 2 && n == 54){
                        num = stoi(line);
                        Array[2].setATKRange(num);
                    }
                    else if (Mapsetting.getCount() > 2 && n == 55){
                        num = stoi(line);
                        Array[2].setleft(num);
                    }
                    else if (Mapsetting.getCount() > 3 && n == 58){
                        {
                            num = stoi(line);
                            Array[3].setX(num);
                        }
                    }
                    else if (Mapsetting.getCount() > 3 && n == 60){
                        {
                            num = stoi(line);
                            Array[3].setY(num);
                        }
                    }
                    else if (Mapsetting.getCount() > 3 && n == 62){
                        num = stoi(line);
                        Array[3].setATK(num);
                    }
                    else if (Mapsetting.getCount() > 3 && n == 64){
                        num = stoi(line);
                        Array[3].setHP(num);
                    }
                    else if (Mapsetting.getCount() > 3 && n == 66) {
                        num = stoi(line);
                        Array[3].setATKRange(num);
                    }
                    else if (Mapsetting.getCount() > 3 && n == 67){
                        num = stoi(line);
                        Array[3].setleft(num);
                    }
                    else if (Mapsetting.getCount() > 4 && n == 70){
                        {
                            num = stoi(line);
                            Array[4].setX(num);
                        }
                    }
                    else if (Mapsetting.getCount() > 4 && n == 72){
                        {
                            num = stoi(line);
                            Array[4].setY(num);
                        }
                    }
                    else if (Mapsetting.getCount() > 4 && n == 74){
                        num = stoi(line);
                        Array[4].setATK(num);
                    }
                    else if (Mapsetting.getCount() > 4 && n == 76){
                        num = stoi(line);
                        Array[4].setHP(num);
                    }
                    else if (Mapsetting.getCount() > 4 && n == 78){
                        num = stoi(line);
                        Array[4].setATKRange(num);
                    }
                    else if (Mapsetting.getCount() > 4 && n == 79){
                        num = stoi(line);
                        Array[4].setleft(num);
                    }
                    else if (Mapsetting.getCount() > 5 && n == 82){
                        {
                            num = stoi(line);
                            Array[5].setX(num);
                        }
                    }
                    else if (Mapsetting.getCount() > 5 && n == 84){
                        {
                            num = stoi(line);
                            Array[5].setY(num);
                        }
                    }
                    else if (Mapsetting.getCount() > 5 && n == 86){
                        num = stoi(line);
                        Array[5].setATK(num);
                    }
                    else if (Mapsetting.getCount() > 5 && n == 88){
                        num = stoi(line);
                        Array[5].setHP(num);
                    }
                    else if (Mapsetting.getCount() > 5 && n == 90){
                        num = stoi(line);
                        Array[5].setATKRange(num);
                    }
                    else if (Mapsetting.getCount() > 5 && n == 91){
                        num = stoi(line);
                        Array[5].setleft(num);
                    }
                    else if (Mapsetting.getCount() > 6 && n == 94){
                        {
                            num = stoi(line);
                            Array[6].setX(num);
                        }
                    }
                    else if (Mapsetting.getCount() > 6 && n == 96){
                        {
                            num = stoi(line);
                            Array[6].setY(num);
                        }
                    }
                    else if (Mapsetting.getCount() > 6 && n == 98) {
                        num = stoi(line);
                        Array[6].setATK(num);
                    }
                    else if (Mapsetting.getCount() > 6 && n == 100){
                        num = stoi(line);
                        Array[6].setHP(num);
                    }
                    else if (Mapsetting.getCount() > 6 && n == 102){
                        num = stoi(line);
                        Array[6].setATKRange(num);
                    }
                    else if (Mapsetting.getCount() > 6 && n == 103)
                    {
                        num = stoi(line);
                        Array[6].setleft(num);
                    }
                    else if (Mapsetting.getCount() > 7 && n == 106){
                        {
                            num = stoi(line);
                            Array[7].setX(num);
                        }
                    }
                    else if (Mapsetting.getCount() > 7 && n == 108){
                        {
                            num = stoi(line);
                            Array[7].setY(num);
                        }
                    }
                    else if (Mapsetting.getCount() > 7 && n == 110){
                        num = stoi(line);
                        Array[7].setATK(num);
                    }
                    else if (Mapsetting.getCount() > 7 && n == 112){
                        num = stoi(line);
                        Array[7].setHP(num);
                    }
                    else if (Mapsetting.getCount() > 7 && n == 114) {
                        num = stoi(line);
                        Array[7].setATKRange(num);
                    }
                    else if (Mapsetting.getCount() > 7 && n == 115){
                        num = stoi(line);
                        Array[7].setleft(num);
                    }
                    else if (Mapsetting.getCount() > 8 && n == 118){
                        {
                            num = stoi(line);
                            Array[8].setX(num);
                        }
                    }
                    else if (Mapsetting.getCount() > 8 && n == 120){
                        {
                            num = stoi(line);
                            Array[8].setY(num);
                        }
                    }
                    else if (Mapsetting.getCount() > 8 && n == 122){
                        num = stoi(line);
                        Array[8].setATK(num);
                    }
                    else if (Mapsetting.getCount() > 8 && n == 124){
                        num = stoi(line);
                        Array[8].setHP(num);
                    }
                    else if (Mapsetting.getCount() > 8 && n == 126){
                        num = stoi(line);
                        Array[8].setATKRange(num);
                    }
                    else if (Mapsetting.getCount() > 8 && n == 127){
                        num = stoi(line);
                        Array[8].setleft(num);
                    }
                    else if (line == "obj"){
                        n = 223;W = 1;
                    }
                }
                Map map = Map(Mapsetting.getColumns(), Mapsetting.getRows());
                while (getline(myFile, line) && n >= 223){
                    ++n;
                    if (n > 223){
                        ob = line[0];
                        if (W == 1){
                            ++W; a = stoi(line);obj[o].setox(a);
                        }
                        else if (W == 2){
                            ++W; b = stoi(line);obj[o].setoy(b);
                        }
                        else if (W == 3){
                            obj[o].setoo(ob);
                            W = 1;++o;
                        }
                    }
                }
                obj[0].seto(o);
            }
        }
        myFile.close();
        cout << "game continue" << endl;
    }
    Map map = Map(Mapsetting.getColumns(), Mapsetting.getRows());
    if (Mapsetting.getZ() == 1){
        for (int r = 0; r < obj[0].geto(); r++){ map.setObject(obj[r].getox(), obj[r].getoy(), obj[r].getoo()); }
        Mapsetting.setZ(0);
    }
    else{ curiosity.Alien(map); }
    char Zombie1 = { '1' }, Zombie2 = { '2' }, Zombie3 = { '3' }, Zombie4 = { '4' }, Zombie5 = { '5' }, Zombie6 = { '6' }, Zombie7 = { '7' }, Zombie8 = { '8' }, Zombie9 = { '9' };
    map.setObject(Array[0].getX(), Array[0].getY(), Zombie1);
    if (i > 1){ map.setObject(Array[1].getX(), Array[1].getY(), Zombie2);
        if (i > 2){ map.setObject(Array[2].getX(), Array[2].getY(), Zombie3);
            if (i > 3){ map.setObject(Array[3].getX(), Array[3].getY(), Zombie4);
                if (i > 4){ map.setObject(Array[4].getX(), Array[4].getY(), Zombie5);
                    if (i > 5){ map.setObject(Array[5].getX(), Array[5].getY(), Zombie6);
                        if (i > 6){ map.setObject(Array[6].getX(), Array[6].getY(), Zombie7);
                            if (i > 7){ map.setObject(Array[7].getX(), Array[7].getY(), Zombie8);
                                if (i > 8){ map.setObject(Array[8].getX(), Array[8].getY(), Zombie9);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    map.display();
    cout << "=>";
    cout << "Alien:"<< " " << "HP ="<< " " << Alien.getHP() << " " << "ATK =" << " " << Alien.getATK() << endl;
    cout << "Zombie1:" << " "<< "HP ="<< " "<< Array[0].getHP() << " "<< "ATK ="<< " " << Array[0].getAtk() << " "<< "range="<< " " << Array[0].getAtkRange() << endl;

    if (i > 1){ cout << "Zombie2:" << " " << "HP =" << " " << Array[1].getHP() << " " << "ATK ="<< " " << Array[1].getAtk() << " "  << "range=" << " " << Array[1].getAtkRange() << endl;
        if (i > 2){cout << "Zombie3:" << " " << "HP =" << " " << Array[2].getHP() << " " << "ATK =" << " " << Array[2].getAtk() << " " << "range="<< " " << Array[2].getAtkRange() << endl;
            if (i > 3){cout << "Zombie4:"  << " " << "HP ="  << " " << Array[3].getHP() << " "  << "ATK =" << " " << Array[3].getAtk() << " "<< "range="<< " " << Array[3].getAtkRange() << endl;
                if (i > 4) { cout << "Zombie5:" << " " << "HP =" << " " << Array[4].getHP() << " " << "ATK =" << " " << Array[4].getAtk() << " " << "range=" << " " << Array[4].getAtkRange() << endl;
                    if (i > 5){cout << "Zombie6:" << " " << "HP ="<< " " << Array[5].getHP() << " " << "ATK ="<< " " << Array[5].getAtk() << " " << "range=" << " " << Array[5].getAtkRange() << endl;
                        if (i > 6) {cout << "Zombie7:" << " " << "HP =" << " " << Array[6].getHP() << " " << "ATK ="  << " " << Array[6].getAtk() << " "<< "range=" << " " << Array[6].getAtkRange() << endl;
                            if (i > 7){ cout << "Zombie8:" << " " << "HP =" << " " << Array[7].getHP() << " " << "ATK =" << " " << Array[7].getAtk() << " " << "range=" << " " << Array[7].getAtkRange() << endl;
                                if (i > 8) {cout << "Zombie9:"<< " " << "HP ="  << " " << Array[8].getHP() << " " << "ATK =" << " " << Array[8].getAtk() << " "   << "range=" << " " << Array[8].getAtkRange() << endl;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    bool game = true;
    cout << "For all command, key in 'help'" << endl;
    while (game){
        cout << "command=>";
        cin >> command;
        if (command == "up"){ task = 1;}
        else if (command == "down"){task = 2;}
        else if (command == "left") {task = 3;}
        else if (command == "right"){task = 4;}
        else if (command == "arrow"){ task = 5; }
        else if (command == "help"){task = 6;}
        else if (command == "save"){task = 7; }
        else if (command == "load"){task = 37;}
        else if (command == "quit"){ task = 9;}
        else{
            cout << "unvalid command, please key in again" << endl;
            cin.clear();
        }

        while (task > 0) {
            int atk = Alien.getATK(), hp = Alien.getHP(), saveTask;
            map.display();
            if (attack == 1){
                cout << " Zombie give Alien a damage of" << " " << damage << endl;
                cout << "Press enter to continue ..." << endl;
                std::cin.get();
                if (Alien.getHP() <= 0){
                    task = 0; Death = 1;
                }
                attack = 0;
            }
            else if (attack == 2){
                cout << "Zombie try to attack Alien but fail because Alien is too far away" << endl;
                cout << "Press enter to continue ..." << endl;
                std::cin.get();
                attack = 0;
            }
            else{ }

            if (task < 17){
                cout << "=>" << "Alien:"<< " " << "HP =" << " " << Alien.getHP() << " " << "ATK =" << " " << Alien.getATK() << endl;
            }
            else if (task >= 17) {
                cout << "Alien:" << " " << "HP =" << " " << Alien.getHP() << " " << "ATK =" << " " << Alien.getATK() << endl;
            }
            if (task == 17 || task == 18){
                cout << "=>";
            }
            cout << "Zombie1:" << " " << "HP =" << " " << Array[0].getHP() << " " << "ATK =" << " " << Array[0].getAtk() << " " << "range=" << " " << Array[0].getAtkRange() << endl;
            if (i > 1){
                if (task == 19){ cout << "=>";}
                cout << "Zombie2:" << " " << "HP =" << " " << Array[1].getHP() << " " << "ATK =" << " " << Array[1].getAtk() << " " << "range=" << " " << Array[1].getAtkRange() << endl;
                if (i > 2){
                    if (task == 20){cout << "=>"; }
                    cout << "Zombie3:" << " " << "HP =" << " "<< Array[2].getHP() << " " << "ATK =" << " " << Array[2].getAtk() << " "<< "range="<< " " << Array[2].getAtkRange() << endl;
                    if (i > 3) {
                        if (task == 21){cout << "=>";}
                        cout << "Zombie4:" << " "<< "HP =" << " " << Array[3].getHP() << " "<< "ATK ="<< " " << Array[3].getAtk() << " " << "range=" << " " << Array[3].getAtkRange() << endl;
                        if (i > 4) {
                            if (task == 22){ cout << "=>";}
                            cout << "Zombie5:" << " " << "HP ="<< " " << Array[4].getHP() << " "  << "ATK ="  << " " << Array[4].getAtk() << " " << "range=" << " " << Array[4].getAtkRange() << endl;
                            if (i > 5){
                                if (task == 23){cout << "=>"; }
                                cout << "Zombie6:" << " " << "HP =" << " " << Array[5].getHP() << " " << "ATK ="  << " " << Array[5].getAtk() << " " << "range=" << " " << Array[5].getAtkRange() << endl;
                                if (i > 6){
                                    if (task == 24) { cout << "=>"; }
                                    cout << "Zombie7:" << " " << "HP =" << " " << Array[6].getHP() << " "<< "ATK =" << " " << Array[6].getAtk() << " "  << "range=" << " " << Array[6].getAtkRange() << endl;
                                    if (i > 7)
                                    {
                                        if (task == 25){ cout << "=>"; }
                                        cout << "Zombie8:" << " " << "HP ="<< " " << Array[7].getHP() << " " << "ATK =" << " " << Array[7].getAtk() << " " << "range="<< " " << Array[7].getAtkRange() << endl;
                                        if (i > 8) {
                                            if (task == 26) { cout << "=>";}
                                            cout << "Zombie9:" << " " << "HP =" << " "<< Array[8].getHP() << " " << "ATK =" << " " << Array[8].getAtk() << " "<< "range="<< " " << Array[8].getAtkRange() << endl;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            cout << "Press enter to continue ..." << endl;
            std::cin.get();
            if (Death == 1){
                cout << "Alien death, GAME OVER" << endl;
                game = false;task = 0; break;
            }
            switch (task){
            case 1:
                saveTask = task;
                cout << "command = up" << endl;
                curiosity.up(map, task);break;

            case 2:
                saveTask = task;
                cout << "command = down" << endl;
                curiosity.down(map, task);break;

            case 3:
                saveTask = task;
                cout << "command = left" << endl;
                curiosity.left(map, task);break;

            case 4:
                saveTask = task;
                cout << "command = right" << endl;
                curiosity.right(map, task);break;

            case 5:
                curiosity.arrow(map, task); break;
            case 6:
                curiosity.help(map, task);break;
            case 7:{
                for (int x = 1; x <= map.getDimX(); x++){
                    for (int y = 1; y <= map.getDimY(); y++){
                        char obj = map.getObject(x, y);
                        if (obj == 'A'){
                            curiosity.setTargetx(x); curiosity.setTargety(y);
                        }
                    }
                }
                cout << "key in the file name to save (.txt)=>";
                cin >> filename;
                myFile.open(filename, ios::out); // write
                if (myFile.is_open()){
                    myFile << "MAp setting\n";
                    myFile << "Num of Colums\n"<< Mapsetting.getColumns() << '\n';
                    myFile << "Num of Rows\n"<< Mapsetting.getRows() << '\n';
                    myFile << "Alien stat\n";
                    myFile << "X_\n"<< curiosity.getTargetx() << '\n';
                    myFile << "Y_\n"<< curiosity.getTargety() << '\n';
                    myFile << "ATK\n"<< Alien.getATK() << '\n';
                    myFile << "HP\n"<< Alien.getHP() << '\n';
                    myFile << "Zombie stat\n";
                    myFile << "Num of zombie\n"<< i << '\n';
                    myFile << "Zombie left\n" << Count << '\n'<< "zombie 1\n";
                    myFile << "X_\n"<< Array[0].getX() << '\n';
                    myFile << "Y_\n"<< Array[0].getY() << '\n';
                    myFile << "ATK\n" << Array[0].getAtk() << '\n';
                    myFile << "HP\n"<< Array[0].getHP() << '\n';
                    myFile << "Range\n"<< Array[0].getAtkRange() << '\n';
                    myFile << defeated1 << '\n';
                    if (i > 1) {
                        myFile << "zombie 2\n";
                        myFile << "X_\n"<< Array[1].getX() << '\n';
                        myFile << "Y_\n"<< Array[1].getY() << '\n';
                        myFile << "ATK\n" << Array[1].getAtk() << '\n';
                        myFile << "HP\n"<< Array[1].getHP() << '\n';
                        myFile << "Range\n" << Array[1].getAtkRange() << '\n';
                        myFile << defeated2 << '\n';
                        if (i > 2){
                            myFile << "zombie 3\n";
                            myFile << "X_\n"<< Array[2].getX() << '\n';
                            myFile << "Y_\n" << Array[2].getY() << '\n';
                            myFile << "ATK\n" << Array[2].getAtk() << '\n';
                            myFile << "HP\n" << Array[2].getHP() << '\n';
                            myFile << "Range\n"<< Array[2].getAtkRange() << '\n';
                            myFile << defeated3 << '\n';
                            if (i > 3){
                                myFile << "zombie 4\n";
                                myFile << "X_\n"<< Array[3].getX() << '\n';
                                myFile << "Y_\n" << Array[3].getY() << '\n';
                                myFile << "ATK\n"<< Array[3].getAtk() << '\n';
                                myFile << "HP\n"<< Array[3].getHP() << '\n';
                                myFile << "Range\n"<< Array[3].getAtkRange() << '\n';
                                myFile << defeated4 << '\n';
                                if (i > 4){
                                    myFile << "zombie 5\n";
                                    myFile << "X_\n"<< Array[4].getX() << '\n';
                                    myFile << "Y_\n"<< Array[4].getY() << '\n';
                                    myFile << "ATK\n"<< Array[4].getAtk() << '\n';
                                    myFile << "HP\n"<< Array[4].getHP() << '\n';
                                    myFile << "Range\n"<< Array[4].getAtkRange() << '\n';
                                    myFile << defeated5 << '\n';
                                    if (i > 5){
                                        myFile << "zombie 6\n";
                                        myFile << "X_\n" << Array[5].getX() << '\n';
                                        myFile << "Y_\n" << Array[5].getY() << '\n';
                                        myFile << "ATK\n"<< Array[5].getAtk() << '\n';
                                        myFile << "HP\n" << Array[5].getHP() << '\n';
                                        myFile << "Range\n"<< Array[5].getAtkRange() << '\n';
                                        myFile << defeated6 << '\n';
                                        if (i > 6) {
                                            myFile << "zombie 7\n";
                                            myFile << "X_\n"<< Array[6].getX() << '\n';
                                            myFile << "Y_\n"<< Array[6].getY() << '\n';
                                            myFile << "ATK\n" << Array[6].getAtk() << '\n';
                                            myFile << "HP\n" << Array[6].getHP() << '\n';
                                            myFile << "Range\n"<< Array[6].getAtkRange() << '\n';
                                            myFile << defeated7 << '\n';
                                            if (i > 7) {
                                                myFile << "zombie 8\n";
                                                myFile << "X_\n" << Array[7].getX() << '\n';
                                                myFile << "Y_\n" << Array[7].getY() << '\n';
                                                myFile << "ATK\n"<< Array[7].getAtk() << '\n';
                                                myFile << "HP\n" << Array[7].getHP() << '\n';
                                                myFile << "Range\n" << Array[7].getAtkRange() << '\n';
                                                myFile << defeated8 << '\n';
                                                if (i > 8){
                                                    myFile << "zombie 9\n";
                                                    myFile << "X_\n"<< Array[8].getX() << '\n';
                                                    myFile << "Y_\n" << Array[8].getY() << '\n';
                                                    myFile << "ATK\n" << Array[8].getAtk() << '\n';
                                                    myFile << "HP\n"<< Array[8].getHP() << '\n';
                                                    myFile << "Range\n" << Array[8].getAtkRange() << '\n';
                                                    myFile << defeated9 << '\n' << "obj" << '\n'<< " " << '\n';
                                                }
                                                else{ myFile << "obj" << '\n'; myFile << " " << '\n'; }
                                            }
                                            else{ myFile << "obj" << '\n'; myFile << " " << '\n'; }
                                        }
                                        else{ myFile << "obj" << '\n'; myFile << " " << '\n'; }
                                    }
                                    else { myFile << "obj" << '\n'; myFile << " " << '\n';}
                                }
                                else{ myFile << "obj" << '\n'; myFile << " " << '\n'; }
                            }
                            else{myFile << "obj" << '\n'; myFile << " " << '\n'; }
                        }
                        else{ myFile << "obj" << '\n'; myFile << " " << '\n';}
                    }
                    else{ myFile << "obj" << '\n'; myFile << " " << '\n'; }
                    for (int x = 1; x <= map.getDimX(); x++){
                        for (int y = 1; y <= map.getDimY(); y++){
                            myFile << x << '\n'; myFile << y << '\n'<< map.getObject(x, y) << '\n';
                        }
                    }
                    myFile.close();
                }
                task = 0;
            } break;
            case 37:{
                string load;
                cout << "Is you already save the game?(y/n)=>";
                cin >> load;
                if (load == "y"){
                    game = false; task = 0; Mapsetting.setZ(1);
                }
                else if (load == "n"){
                    cout << "please save your game first" << endl;
                    task = 7;
                }
                else{
                    task = 0;
                }
            } break;

            case 8:{
                task = saveTask;
                int dis = 0;
                float minDis;
                if (defeated1 == 0) { minDis = getDistance(curiosity.getX(), curiosity.getY(), Array[0].getX(), Array[0].getY());}
                else if (defeated1 == 1 && defeated2 == 0){
                    minDis = getDistance(curiosity.getX(), curiosity.getY(), Array[1].getX(), Array[1].getY());
                }
                else if (defeated1 == 1 && defeated2 == 1 && defeated3 == 0){
                    minDis = getDistance(curiosity.getX(), curiosity.getY(), Array[2].getX(), Array[2].getY());
                }
                else if (defeated1 == 1 && defeated2 == 1 && defeated3 == 1 && defeated4 == 0){
                    minDis = getDistance(curiosity.getX(), curiosity.getY(), Array[3].getX(), Array[3].getY());
                }
                else if (defeated1 == 1 && defeated2 == 1 && defeated3 == 1 && defeated4 == 1 && defeated5 == 0){
                    minDis = getDistance(curiosity.getX(), curiosity.getY(), Array[4].getX(), Array[4].getY());
                }
                else if (defeated1 == 1 && defeated2 == 1 && defeated3 == 1 && defeated4 == 1 && defeated5 == 1 && defeated6 == 0){
                    minDis = getDistance(curiosity.getX(), curiosity.getY(), Array[5].getX(), Array[5].getY());
                }
                else if (defeated1 == 1 && defeated2 == 1 && defeated3 == 1 && defeated4 == 1 && defeated5 == 1 && defeated6 == 1 && defeated7 == 0){
                    minDis = getDistance(curiosity.getX(), curiosity.getY(), Array[6].getX(), Array[6].getY());
                }
                else if (defeated1 == 1 && defeated2 == 1 && defeated3 == 1 && defeated4 == 1 && defeated5 == 1 && defeated6 == 1 && defeated7 == 1 && defeated8 == 0){
                    minDis = getDistance(curiosity.getX(), curiosity.getY(), Array[7].getX(), Array[7].getY());
                }
                else if (defeated1 == 1 && defeated2 == 1 && defeated3 == 1 && defeated4 == 1 && defeated5 == 1 && defeated6 == 1 && defeated7 == 1 && defeated8 == 1 && defeated9 == 0) {
                    minDis = getDistance(curiosity.getX(), curiosity.getY(), Array[8].getX(), Array[8].getY());
                }
                else{ break; }
                for (int i = 0; i < zombie_count; i++){
                    if (defeated2 == 1 && i == 1){ }
                    else if (defeated3 == 1 && i == 2) { }
                    else if (defeated4 == 1 && i == 3){ }
                    else if (defeated5 == 1 && i == 4) { }
                    else if (defeated6 == 1 && i == 5) { }
                    else if (defeated7 == 1 && i == 6) { }
                    else if (defeated8 == 1 && i == 7) { }
                    else if (defeated9 == 1 && i == 8){ }
                    else if (i == 9) { }
                    else{
                        float currDix = getDistance(curiosity.getX(), curiosity.getY(), Array[i].getX(), Array[i].getY());
                        if (currDix < minDis) { dis = i;minDis = currDix; }
                        else{ }
                    }
                }
                if (dis == 0 && defeated1 == 0){
                    hpleft = Array[0].getHP() - 10;
                    cout << "Pod give 10 damage to Zombie 1" << endl;
                    cout << "Press enter to continue ..." << endl;
                    if (hpleft <= 0){
                        cout << " Zombie 1 defeated" << endl;
                        Array[0].setHP(0);defeated9 = 1;Count = Count - 1;
                    }
                    else{ Array[0].setHP(hpleft); }
                    std::cin.get();
                }
                else if (dis == 1 || (dis == 0 && defeated1 == 1 && defeated2 == 0)){
                    hpleft = Array[1].getHP() - 10;
                    cout << "Pod give 10 damage to Zombie 2" << endl;
                    cout << "Press enter to continue ..." << endl;
                    if (hpleft <= 0){
                        cout << " Zombie 2 defeated" << endl;
                        Array[1].setHP(0); defeated2 = 1; Count = Count - 1;
                    }
                    else{ Array[1].setHP(hpleft); }
                    std::cin.get();
                }
                else if (dis == 2 || (dis == 0 && defeated1 == 1 && defeated2 == 1 && defeated3 == 0)) {
                    hpleft = Array[2].getHP() - 10;
                    cout << "Pod give 10 damage to Zombie 3" << endl;
                    cout << "Press enter to continue ..." << endl;
                    if (hpleft <= 0){
                        cout << " Zombie 3 defeated" << endl;
                        Array[2].setHP(0);defeated3 = 1;Count = Count - 1;
                    }
                    else{ Array[2].setHP(hpleft); }
                    std::cin.get();
                }
                else if (dis == 3 || (dis == 0 && defeated1 == 1 && defeated2 == 1 && defeated3 == 1 && defeated4 == 0)){
                    hpleft = Array[3].getHP() - 10;
                    cout << "Pod give 10 damage to Zombie 4" << endl;
                    cout << "Press enter to continue ..." << endl;
                    if (hpleft <= 0){
                        cout << " Zombie 4 defeated" << endl; 
                        Array[3].setHP(0); defeated4 = 1;Count = Count - 1;
                    }
                    else{ Array[3].setHP(hpleft);}
                    std::cin.get();
                }
                else if (dis == 4 || (dis == 0 && defeated1 == 1 && defeated2 == 1 && defeated3 == 1 && defeated4 == 1 && defeated5 == 0)){
                    hpleft = Array[4].getHP() - 10;
                    cout << "Pod give 10 damage to Zombie 5" << endl;
                    cout << "Press enter to continue ..." << endl;
                    if (hpleft <= 0) {
                        cout << " Zombie 5 defeated" << endl;
                        Array[4].setHP(0); defeated5 = 1;Count = Count - 1;
                    }
                    else{ Array[4].setHP(hpleft); }
                    std::cin.get();
                }
                else if (dis == 5 || (dis == 0 && defeated1 == 1 && defeated2 == 1 && defeated3 == 1 && defeated4 == 1 && defeated5 == 1 && defeated6 == 0)){
                    hpleft = Array[5].getHP() - 10;
                    cout << "Pod give 10 damage to Zombie 6" << endl;
                    cout << "Press enter to continue ..." << endl;
                    if (hpleft <= 0){
                        cout << " Zombie 6 defeated" << endl;
                        Array[5].setHP(0); defeated6 = 1;Count = Count - 1;
                    }
                    else{ Array[5].setHP(hpleft); }
                    std::cin.get();
                }
                else if (dis == 6 || (dis == 0 && defeated1 == 1 && defeated2 == 1 && defeated3 == 1 && defeated4 == 1 && defeated5 == 1 && defeated6 == 1 && defeated7 == 0)){
                    hpleft = Array[6].getHP() - 10;
                    cout << "Pod give 10 damage to Zombie 7" << endl;
                    cout << "Press enter to continue ..." << endl;
                    if (hpleft <= 0){
                        cout << " Zombie 7 defeated" << endl;
                        Array[6].setHP(0); defeated7 = 1; Count = Count - 1;
                    }
                    else{ Array[6].setHP(hpleft);}
                    std::cin.get();
                }
                else if (dis == 7 || (dis == 0 && defeated1 == 1 && defeated2 == 1 && defeated3 == 1 && defeated4 == 1 && defeated5 == 1 && defeated6 == 1 && defeated7 == 1 && defeated8 == 0)){
                    hpleft = Array[7].getHP() - 10;
                    cout << "Pod give 10 damage to Zombie 8" << endl;
                    cout << "Press enter to continue ..." << endl;
                    if (hpleft <= 0){
                        cout << " Zombie 8 defeated" << endl;
                        Array[7].setHP(0);defeated8 = 1; Count = Count - 1;
                    }
                    else{ Array[7].setHP(hpleft); }
                    std::cin.get();
                }
                else if (dis == 8 || (dis == 0 && defeated1 == 1 && defeated2 == 1 && defeated3 == 1 && defeated4 == 1 && defeated5 == 1 && defeated6 == 1 && defeated7 == 1 && defeated8 == 1 && defeated9 == 0)) {
                    hpleft = Array[8].getHP() - 10;
                    Array[8].setHP(hpleft);
                    cout << "Pod give 10 damage to Zombie 9" << endl;
                    cout << "Press enter to continue ..." << endl;
                    if (hpleft <= 0){
                        cout << " Zombie 9 defeated" << endl;
                        Array[8].setHP(0);defeated9 = 1; Count = Count - 1;
                    }
                    else {Array[8].setHP(hpleft); }
                    std::cin.get();
                }
                else { }
            }break;

            case 9:
                curiosity.quit(map, task);
                if (task == 88){
                    game = false;task = 0;
                }
                else{task = 0; } break;

            case 10:{
                task = saveTask;
                if (hp == 100){
                    cout << "Alien's HP is already full" << endl;
                    cout << "Press enter to continue ..." << endl;
                    ;
                    std::cin.get();break;
                }
                else if (hp >= 90 && hp < 100){
                    cout << "Alien recovers 10HP, HP is full now!" << endl;
                    cout << "Press enter to continue ..." << endl;
                    std::cin.get();
                    Alien.setHP(100); break;
                }
                else{
                    cout << "Alien recovers 10 HP" << endl;
                    cout << "Press enter to continue ..." << endl;
                    std::cin.get();
                    Alien.setHP(hp + 10); break;
                }
            }break;

            case 11:
                cout << "it is a rock" << endl;
                curiosity.rock(map, task); break;

            case 12:
                cout << "reset trail with new object" << endl;
                cout << "reset Alien ATK to 0" << endl;
                Alien.setATK(0);
                cout << "Press enter to continue ..." << endl;
                std::cin.get();
                curiosity.trail(map, task);break;

            case 13:{
                task = 1;
                saveTask = task;
                Alien.setATK(atk + 20);
                cout << "command = up" << endl;
                cout << "Alien ATK increase 20" << endl;
                cout << "Press enter to continue ..." << endl;
                std::cin.get();
                curiosity.up(map, task);
            }break;

            case 14:{
                task = 2;
                saveTask = task;
                Alien.setATK(atk + 20);
                cout << "command = down" << endl;
                cout << "Alien ATK increase 20" << endl;
                cout << "Press enter to continue ..." << endl;
                std::cin.get();
                curiosity.down(map, task);
            }break;

            case 15: {
                task = 3;
                saveTask = task;
                Alien.setATK(atk + 20);
                cout << "command = left" << endl;
                cout << "Alien ATK increase 20" << endl;
                cout << "Press enter to continue ..." << endl;
                std::cin.get();
                curiosity.left(map, task);
            } break;

            case 16:{
                task = 4;
                saveTask = task;
                Alien.setATK(atk + 20);
                cout << "command = right" << endl;
                cout << "Alien ATK increase 20" << endl;
                cout << "Press enter to continue ..." << endl;
                std::cin.get();
                curiosity.right(map, task);
            } break;

            case 17:{
                Alien.setATK(0); task = 18;
            }
            case 18:{
                if (defeated1 == 0){
                    cout << "Zombie1 turn" << endl;
                    cout << "Press enter to continue ..." << endl;
                    std::cin.get();
                    saveTask = task;
                }
                else if (Count == 0){
                    cout << "Win the game!" << endl;
                    game = false;
                    task = 0; break;
                }
                else{saveTask = task; }
            } break;

            case 19:{
                if (defeated2 == 0){
                    cout << "Zombie2 turn" << endl;
                    cout << "Press enter to continue ..." << endl;
                    std::cin.get();
                    saveTask = task;
                }
                else if (Count == 0){
                    cout << "Win the game!" << endl;
                    game = false;
                    task = 0; break;
                }
                else {
                    saveTask = task;
                }
            } break;

            case 20:{
                if (defeated3 == 0){
                    cout << "Zombie3 turn" << endl;
                    cout << "Press enter to continue ..." << endl;
                    std::cin.get();
                    saveTask = task;
                }
                else if (Count == 0) {
                    cout << "Win the game!" << endl;
                    game = false;
                    task = 0;break;
                }
                else{ saveTask = task;}
            }break;

            case 21: {
                if (defeated4 == 0){
                    cout << "Zombie4 turn" << endl;
                    cout << "Press enter to continue ..." << endl;
                    std::cin.get();
                    saveTask = task;
                }
                else if (Count == 0) {
                    cout << "Win the game!" << endl;
                    game = false;
                    task = 0;break;
                }
                else{ saveTask = task; }
            }break;

            case 22:{
                if (defeated5 == 0){
                    cout << "Zombie5 turn" << endl;
                    cout << "Press enter to continue ..." << endl;
                    std::cin.get();
                    saveTask = task;
                }
                else if (Count == 0){
                    cout << "Win the game!" << endl;
                    game = false;
                    task = 0;break;
                }
                else{ saveTask = task;}
            }break;

            case 23:{
                if (defeated6 == 0){
                    cout << "Zombie6 turn" << endl;
                    cout << "Press enter to continue ..." << endl;
                    std::cin.get();
                    saveTask = task;
                }
                else if (Count == 0){
                    cout << "Win the game!" << endl;
                    game = false;
                    task = 0; break;
                }
                else {saveTask = task;}
            }break;

            case 24: {
                if (defeated7 == 0){
                    cout << "Zombie7 turn" << endl;
                    cout << "Press enter to continue ..." << endl;
                    std::cin.get();
                    saveTask = task;
                }
                else if (Count == 0) {
                    cout << "Win the game!" << endl;
                    game = false;
                    task = 0;break;
                }
                else {saveTask = task;}
            } break;

            case 25:{
                if (defeated8 == 0){
                    cout << "Zombie8 turn" << endl;
                    cout << "Press enter to continue ..." << endl;
                    std::cin.get();
                    saveTask = task;
                }
                else if (Count == 0){
                    cout << "Win the game!" << endl;
                    game = false;
                    task = 0;break;
                }
                else{ saveTask = task;}
            }break;

            case 26: {
                if (defeated9 == 0){
                    cout << "Zombie9 turn" << endl;
                    cout << "Press enter to continue ..." << endl;
                    std::cin.get();
                    saveTask = task;
                }
                else if (Count == 0) {
                    cout << "Win the game!" << endl;
                    game = false;
                    task = 0;break;
                }
                else{saveTask = task;}
            }break;

            case 27:{
                cout << "round end" << endl;
                task = 0;
            }break;

            case 28: {
                hpleft = Array[0].getHP() - Alien.getATK();
                cout << "Alien give zombie 1 a damage of " << " " << Alien.getATK() << endl;
                if (hpleft <= 0) {
                    cout << " Zombie 1 defeated" << endl;
                    Array[0].setHP(0);Count = Count - 1; defeated1 = 1;task = saveTask;
                    map.setObject(curiosity.getTargetx(), curiosity.getTargety(), '.');
                    map.setObject(Array[0].getX(), Array[0].getY(), 'A');
                }
                else{
                    Array[0].setHP(hpleft);task = 12;
                }
            } break;

            case 29:{
                hpleft = Array[1].getHP() - Alien.getATK();
                cout << "Alien give zombie 2 a damage of " << " " << Alien.getATK() << endl;
                if (hpleft <= 0) {
                    cout << " Zombie 2 defeated" << endl;
                    Array[1].setHP(0);
                    Count = Count - 1; defeated2 = 1;task = saveTask;
                    map.setObject(curiosity.getTargetx(), curiosity.getTargety(), '.');
                    map.setObject(Array[1].getX(), Array[1].getY(), 'A');
                }
                else{
                    Array[1].setHP(hpleft);
                    task = 12;
                }
            } break;

            case 30:{
                hpleft = Array[2].getHP() - Alien.getATK();
                cout << "Alien give zombie 3 a damage of " << " " << Alien.getATK() << endl;
                if (hpleft <= 0){
                    cout << " Zombie 3 defeated" << endl;
                    Array[2].setHP(0); Count = Count - 1;defeated3 = 1; task = saveTask;
                    map.setObject(curiosity.getTargetx(), curiosity.getTargety(), '.');
                    map.setObject(Array[2].getX(), Array[2].getY(), 'A');
                }
                else{
                    Array[2].setHP(hpleft);
                    task = 12;
                }
            }break;
            case 31: {
                hpleft = Array[3].getHP() - Alien.getATK();
                cout << "Alien give zombie 4 a damage of " << " " << Alien.getATK() << endl;
                if (hpleft <= 0){
                    cout << " Zombie 4 defeated" << endl;
                    Array[3].setHP(0); Count = Count - 1;defeated4 = 4; task = saveTask;
                    map.setObject(curiosity.getTargetx(), curiosity.getTargety(), '.');
                    map.setObject(Array[3].getX(), Array[3].getY(), 'A');
                }
                else{
                    Array[3].setHP(hpleft);
                    task = 12;
                }
            }break;
            case 32:{
                hpleft = Array[4].getHP() - Alien.getATK();
                cout << "Alien give zombie 5 a damage of " << " " << Alien.getATK() << endl;
                if (hpleft <= 0) {
                    cout << " Zombie 5 defeated" << endl;
                    Array[4].setHP(0);
                    Count = Count - 1;
                    defeated5 = 1;
                    task = saveTask;
                    map.setObject(curiosity.getTargetx(), curiosity.getTargety(), '.');
                    map.setObject(Array[4].getX(), Array[4].getY(), 'A');
                }
                else{
                    Array[4].setHP(hpleft);
                    task = 12;
                }
            }break;
            case 33:{
                hpleft = Array[5].getHP() - Alien.getATK();
                cout << "Alien give zombie 6 a damage of " << " " << Alien.getATK() << endl;
                if (hpleft <= 0){
                    cout << " Zombie 6 defeated" << endl;
                    Array[5].setHP(0);Count = Count - 1; defeated6 = 1;task = saveTask;
                    map.setObject(curiosity.getTargetx(), curiosity.getTargety(), '.');
                    map.setObject(Array[5].getX(), Array[5].getY(), 'A');
                }
                else{
                    Array[5].setHP(hpleft);
                    task = 12;
                }
            }break;

            case 34:{
                hpleft = Array[6].getHP() - Alien.getATK();
                cout << "Alien give zombie 7 a damage of " << " " << Alien.getATK() << endl;
                if (hpleft <= 0){
                    cout << " Zombie 7 defeated" << endl;
                    Array[6].setHP(0);Count = Count - 1; defeated7 = 1;task = saveTask;
                    map.setObject(curiosity.getTargetx(), curiosity.getTargety(), '.');
                    map.setObject(Array[6].getX(), Array[6].getY(), 'A');
                }
                else{
                    Array[6].setHP(hpleft);
                    task = 12;
                }
            } break;

            case 35:{
                hpleft = Array[7].getHP() - Alien.getATK();
                cout << "Alien give zombie 8 a damage of "<< " " << Alien.getATK() << endl;
                if (hpleft <= 0){
                    cout << " Zombie 8 defeated" << endl;
                    Array[7].setHP(0);Count = Count - 1;defeated8 = 1; task = saveTask;
                    map.setObject(curiosity.getTargetx(), curiosity.getTargety(), '.');
                    map.setObject(Array[7].getX(), Array[7].getY(), 'A');
                }
                else{
                    Array[7].setHP(hpleft);
                    task = 12;
                }
            }break;

            case 36: {
                hpleft = Array[8].getHP() - Alien.getATK();
                cout << "Alien give zombie 9 a damage of "<< " " << Alien.getATK() << endl;
                if (hpleft <= 0){
                    cout << " Zombie 9 defeated" << endl;
                    Array[8].setHP(0); defeated9 = 1;Count = Count - 1;task = saveTask;
                    map.setObject(curiosity.getTargetx(), curiosity.getTargety(), '.');
                    map.setObject(Array[8].getX(), Array[8].getY(), 'A');
                }
                else{
                    Array[8].setHP(hpleft);
                    task = 12;
                }
            }break;
            }
            int xz, yz;
            char Zom;
            if (task >= 18 && task < 27){
                {
                    if (task == 26) {
                        xz = Array[8].getX();yz = Array[8].getY(); Zom = map.getObject(xz, yz);task = 27;
                    }

                    else if (task == 25){ xz = Array[7].getX(); yz = Array[7].getY(); Zom = map.getObject(xz, yz);
                        if (i > 8){ task = 26;}

                        else{ task = 27; }
                    }

                    else if (task == 24){
                        xz = Array[6].getX();yz = Array[6].getY();Zom = map.getObject(xz, yz);
                        if (i > 7){task = 25; }

                        else {task = 27; }
                    }

                    if (task == 23){
                        xz = Array[5].getX(); yz = Array[5].getY(); Zom = map.getObject(xz, yz);
                        if (i > 6) { task = 24; }

                        else{task = 27; }
                    }

                    if (task == 22) {
                        xz = Array[4].getX(); yz = Array[4].getY(); Zom = map.getObject(xz, yz);
                        if (i > 5){task = 23;}

                        else { task = 27; }
                    }

                    if (task == 21){ xz = Array[3].getX(); yz = Array[3].getY();Zom = map.getObject(xz, yz);
                        if (i > 4){ task = 22; }

                        else{ task = 27;}
                    }

                    else if (task == 20){
                        xz = Array[2].getX();yz = Array[2].getY(); Zom = map.getObject(xz, yz);
                        if (i > 3) { task = 21;}

                        else{task = 27;}

                    }

                    else if (task == 19){ 
                        xz = Array[1].getX();yz = Array[1].getY();Zom = map.getObject(xz, yz);
                        if (i > 2) { task = 20;}

                        else {task = 27;}
                    }

                    else if (task == 18){
                        xz = Array[0].getX();yz = Array[0].getY(); Zom = map.getObject(xz, yz);
                        if (i > 1){task = 19;}

                        else{ task = 27; }
                    }
                }
            }
            if (task >= 18 && task <= 27){
                int targetX = xz,targetY = yz, num = rand() % 4;
                switch (num){
                case 0: // ^
                    targetY += 1;
                    cout << "Zombie want to move up" << endl;
                    cout << " Press enter to continue... " << endl;
                    std::cin.get(); break;

                case 1: // <
                    targetX -= 1;
                    cout << "Zombie want to move left" << endl;
                    cout << " Press enter to continue... " << endl;
                    std::cin.get(); break;

                case 2: // >
                    targetX += 1;
                    cout << "Zombie want to move right" << endl;
                    cout << " Press enter to continue... " << endl;
                    std::cin.get();break;

                case 3: // v
                    targetY -= 1;
                    cout << "Zombie want to move down" << endl;
                    cout << " Press enter to continue... " << endl;
                    std::cin.get(); break;

                default:break;
                }

                if (map.isInsideMap(targetX, targetY)){
                    char elm = map.getObject(targetX, targetY);
                    if (elm == 'A'){ cout << "Zombie meets Alien and stop moving" << endl;}

                    else if (elm == '1') { cout << "Zombie meets other zombie and stop moving" << endl; }

                    else if (elm == '2'){cout << "Zombie meets other zombie and stop moving" << endl; }

                    else if (elm == '3'){ cout << "Zombie meets other zombie and stop moving" << endl; }

                    else if (elm == '4') {cout << "Zombie meets other zombie and stop moving" << endl;}

                    else if (elm == '5') {cout << "Zombie meets other zombie and stop moving" << endl;}

                    else if (elm == '6') {cout << "Zombie meets other zombie and stop moving" << endl;}

                    else if (elm == '7'){cout << "Zombie meets other zombie and stop moving" << endl;}

                    else if (elm == '8'){cout << "Zombie meets other zombie and stop moving" << endl; }

                    else if (elm == '9'){ cout << "Zombie meets other zombie and stop moving" << endl;}

                    else {
                        map.setObject(xz, yz, ' '); // Remove old
                        xz = targetX;
                        yz = targetY;
                        map.setObject(xz, yz, Zom); // New
                    }
                }
                else{ cout << "zombie hit the wall angryly" << endl;}

                if (Zom == '1') {
                    Array[0].setX(xz); Array[0].setY(yz);
                    distance = getDistance(curiosity.getX(), curiosity.getY(), Array[0].getX(), Array[0].getY());
                    if (distance <= Array[0].getAtkRange()){
                        damage = Array[0].getAtk();
                        hpleft = Alien.getHP() - damage;
                        if (hpleft > 0){Alien.setHP(hpleft);}
                        else{ Alien.setHP(0);}
                        attack = 1;
                    }
                    else{ attack = 2; }
                }
                else if (Zom == '2'){
                    Array[1].setX(xz); Array[1].setY(yz);
                    distance = getDistance(curiosity.getX(), curiosity.getY(), Array[1].getX(), Array[1].getY());
                    if (distance <= Array[1].getAtkRange()){
                        damage = Array[1].getAtk();hpleft = Alien.getHP() - damage;
                        if (hpleft > 0){ Alien.setHP(hpleft);}

                        else{Alien.setHP(0);}
                        attack = 1;
                    }
                    else{ attack = 2;}
                }
                else if (Zom == '3'){
                    Array[2].setX(xz);Array[2].setY(yz);
                    distance = getDistance(curiosity.getX(), curiosity.getY(), Array[2].getX(), Array[2].getY());
                    if (distance <= Array[2].getAtkRange()) {
                        damage = Array[2].getAtk(); hpleft = Alien.getHP() - damage;
                        if (hpleft > 0){Alien.setHP(hpleft); }

                        else{Alien.setHP(0); }
                        attack = 1;
                    }
                    else {attack = 2;}
                }
                else if (Zom == '4') {
                    Array[3].setX(xz); Array[3].setY(yz);
                    distance = getDistance(curiosity.getX(), curiosity.getY(), Array[3].getX(), Array[3].getY());
                    if (distance <= Array[3].getAtkRange()){
                        damage = Array[3].getAtk();
                        hpleft = Alien.getHP() - damage;
                        if (hpleft > 0) {Alien.setHP(hpleft);}

                        else{Alien.setHP(0);}
                        attack = 1;
                    }
                    else{ attack = 2;}
                }
                else if (Zom == '5'){
                    Array[4].setX(xz);Array[4].setY(yz);
                    distance = getDistance(curiosity.getX(), curiosity.getY(), Array[4].getX(), Array[4].getY());
                    if (distance <= Array[4].getAtkRange()){
                        damage = Array[4].getAtk();hpleft = Alien.getHP() - damage;
                        if (hpleft > 0){ Alien.setHP(hpleft);}

                        else {Alien.setHP(0); }
                        attack = 1;
                    }
                    else { attack = 2;}
                }
                else if (Zom == '6') {
                    Array[5].setX(xz); Array[5].setY(yz);
                    distance = getDistance(curiosity.getX(), curiosity.getY(), Array[5].getX(), Array[5].getY());
                    if (distance <= Array[5].getAtkRange()){
                        damage = Array[5].getAtk();hpleft = Alien.getHP() - damage;
                        if (hpleft > 0) { Alien.setHP(hpleft);}

                        else{Alien.setHP(0);}
                        attack = 1;
                    }
                    else{ attack = 2;}
                }
                else if (Zom == '7') {
                    Array[6].setX(xz);Array[6].setY(yz);
                    distance = getDistance(curiosity.getX(), curiosity.getY(), Array[6].getX(), Array[6].getY());
                    if (distance <= Array[6].getAtkRange()){
                        damage = Array[6].getAtk(); hpleft = Alien.getHP() - damage;
                        if (hpleft > 0){Alien.setHP(hpleft);}

                        else{ Alien.setHP(0);}
                        attack = 1;
                    }
                    else{attack = 2; }
                }
                else if (Zom == '8') {
                    Array[7].setX(xz);Array[7].setY(yz);
                    distance = getDistance(curiosity.getX(), curiosity.getY(), Array[7].getX(), Array[7].getY());
                    if (distance <= Array[7].getAtkRange()) {
                        damage = Array[7].getAtk(); hpleft = Alien.getHP() - damage;
                        if (hpleft > 0) {  Alien.setHP(hpleft);}

                        else{Alien.setHP(0);}
                        attack = 1;
                    }
                    else{ attack = 2;}
                }
                else if (Zom == '9') {
                    Array[8].setX(xz); Array[8].setY(yz);
                    distance = getDistance(curiosity.getX(), curiosity.getY(), Array[8].getX(), Array[8].getY());
                    if (distance <= Array[8].getAtkRange()){
                        damage = Array[8].getAtk();hpleft = Alien.getHP() - damage;
                        if (hpleft > 0){ Alien.setHP(hpleft);}

                        else{Alien.setHP(0); }
                        attack = 1;
                    }
                    else{attack = 2;}
                }
                else{ }
            }
        }
    }
}

void restart(){
    string restart;
    bool game, rst = true;
    while (rst){
        cout << "do you want to restart/load the game? y/n=>";
        cin >> restart;
        if (restart == "y"){
            cout << endl;
            cout << "you choose restart / load  the game " << endl;
            cout << " Press enter to continue... " << endl;
            std::cin.get();
            game = true;
            maingame();
        }
        else if (restart == "n"){
            cout << "see you again!" << endl;
            rst = false;
        }
        else{
            cout << "Please enter y/n only!" << endl;
            cout << "failed to restart the game" << endl;
        }
    }
}
int main(){
    Mapsetting setting;
    setting.setZ(0);
    string lr;
    cout << "Assignment (Part 1)" << endl;
    cout << "Let's Get Started!" << endl;
    cout << "Press enter to continue ..." << endl;
    std::cin.get();
    // srand(1); // use this for fixed map during testing
    srand(time(NULL)); // try this for random map
    maingame();
    restart();
}