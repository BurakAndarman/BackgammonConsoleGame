#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <filesystem>
using namespace std;



class Home {
public:
    char vertical_position;
    char horizontal_position;
    int char_index;
    string flake_number;
    char player;
    int dice;
};




void createTable() {
    remove("DiceRollLog.txt");
    remove("Table.dat");
    ofstream outStream("Table.dat",ios::app);

    string first_line = "A  B  C  D  E  F  G  H  I  J  K  L\n";
    string second_line ="5Y          3X    5X             2Y  1\n";
    string third_line = "                                     2\n";
    string fourth_line ="                                     3\n";
    string fifth_line = "                                     4\n";
    string sixth_line = "5X          3Y    5Y             2X  5";

    if (outStream.is_open()) {
        outStream << first_line;
        outStream << second_line;
        outStream << third_line;
        outStream << fourth_line;
        outStream << fifth_line;
        outStream << sixth_line;
    }
    else {
        std::cout << "File could'nt open or create !";
    }

    outStream.close();
}




void createHomes(vector<Home>& homesX,vector<Home>& homesY) {
    string vertical_positions, horizontal_position1, horizontal_position2, line;
    Home temp;
    const char* vertical_letter;
    char last_character;
    int index=0;

    ifstream fileStream("Table.dat");
    if (fileStream.is_open()) {
        while (getline(fileStream, line)) {
            last_character = line.back();

            switch (last_character)
            {
            case 'L':
                vertical_positions = line;
                break;
            case '1':
                horizontal_position1 = line;
                break;
            case '5':
                horizontal_position2 = line;
                break;
            default:
                break;
            }
        }

        vertical_letter = vertical_positions.c_str();
        for (int i = 0; i < 12; i++) {

            temp.vertical_position = *(vertical_letter);
            temp.horizontal_position = '5';
            temp.char_index = vertical_positions.find(*(vertical_letter));
            homesX.push_back(temp);

            vertical_letter += 3;
        }

        reverse(homesX.begin(), homesX.end());

        for (auto itr = horizontal_position2.begin(); itr != horizontal_position2.end(); itr++) {

            char temp_flake = *(itr);
            if (itr + 1 != horizontal_position2.end())
                itr++;
            char temp_player = *(itr);
            if (itr + 1 != horizontal_position2.end() && itr + 2 != horizontal_position2.end())
                itr += 1;
            

            for (auto itr2 = homesX.begin(); itr2 != homesX.end(); itr2++) {
                if (itr2->char_index == index && itr2->horizontal_position== '5') {
                    itr2->flake_number = temp_flake;
                    itr2->player = temp_player;
                    break;
                }
            }

            index += 3;
            
        }


        index = 0;


        vertical_letter = vertical_positions.c_str();
        for (int i = 0; i < 12; i++) {

            temp.vertical_position = *(vertical_letter);
            temp.horizontal_position = '1';
            temp.char_index = vertical_positions.find(*(vertical_letter));
            homesX.push_back(temp);

            vertical_letter += 3;
        }


        for (auto itr = horizontal_position1.begin(); itr != horizontal_position1.end(); itr++) {

            char temp_flake = *(itr);
            if (itr + 1 != horizontal_position1.end())
                itr++;
            char temp_player = *(itr);
            if (itr + 1 != horizontal_position1.end() && itr + 2 != horizontal_position1.end())
                itr += 1;

            
            for (auto itr2 = homesX.begin(); itr2 != homesX.end(); itr2++) {
                if (itr2->char_index == index && itr2->horizontal_position== '1') {
                    itr2->flake_number = temp_flake;
                    itr2->player = temp_player;
                    break;
                }
            }

            index += 3;

        }

        index = 0;


        vertical_letter = vertical_positions.c_str();
        for (int i = 0; i < 12; i++) {

            temp.vertical_position = *(vertical_letter);
            temp.horizontal_position = '1';
            temp.char_index = vertical_positions.find(*(vertical_letter));
            homesY.push_back(temp);

            vertical_letter += 3;
        }

        reverse(homesY.begin(), homesY.end());

        for (auto itr = horizontal_position1.begin(); itr != horizontal_position1.end(); itr++) {

            char temp_flake = *(itr);
            if (itr + 1 != horizontal_position1.end())
                itr++;
            char temp_player = *(itr);
            if (itr + 1 != horizontal_position1.end() && itr + 2 != horizontal_position1.end())
                itr += 1;


            for (auto itr2 = homesY.begin(); itr2 != homesY.end(); itr2++) {
                if (itr2->char_index == index && itr2->horizontal_position == '1') {
                    itr2->flake_number = temp_flake;
                    itr2->player = temp_player;
                    break;
                }
            }

            index += 3;

        }


        index = 0;


        vertical_letter = vertical_positions.c_str();
        for (int i = 0; i < 12; i++) {

            temp.vertical_position = *(vertical_letter);
            temp.horizontal_position = '5';
            temp.char_index = vertical_positions.find(*(vertical_letter));
            homesY.push_back(temp);

            vertical_letter += 3;
        }


        for (auto itr = horizontal_position2.begin(); itr != horizontal_position2.end(); itr++) {

            char temp_flake = *(itr);
            if (itr + 1 != horizontal_position2.end())
                itr++;
            char temp_player = *(itr);
            if (itr + 1 != horizontal_position2.end() && itr + 2 != horizontal_position2.end())
                itr += 1;


            for (auto itr2 = homesY.begin(); itr2 != homesY.end(); itr2++) {
                if (itr2->char_index == index && itr2->horizontal_position == '5') {
                    itr2->flake_number = temp_flake;
                    itr2->player = temp_player;
                    break;
                }
            }

            index += 3;

        }
    }
    else {
        std::cout << "File could'nt open or create !";
    }

    fileStream.close();
}






void updateHome(char horizontal_position,char vertical_position, int newFlakeNumber, char newPlayer,vector<Home>& homesX,vector<Home>& homesY) {
    string tableLine,updatedLine;

    ifstream existingFile("Table.dat", ios::in);
    ofstream updatedFile("Temp.dat", ios::out);

    if (existingFile.is_open() && updatedFile.is_open()) {

        while (getline(existingFile, tableLine)) {
            
            if (tableLine.back() == horizontal_position) {
                
                for (auto itr = homesX.begin(); itr != homesX.end(); itr++) {

                    if (itr->horizontal_position == horizontal_position && itr->vertical_position == vertical_position) {

                        if (newFlakeNumber == 0 && newPlayer==' ') {

                            string temp1 = tableLine.substr(0, itr->char_index);
                            string temp2 = tableLine.substr(itr->char_index + 2, (tableLine.size() - itr->char_index + 2));
                            string homeUpdate = temp1 + "  "  + temp2;
                            updatedFile << homeUpdate << '\n';

                            itr->flake_number = " ";
                            itr->player = ' ';

                        }
                        else {
                            string temp1 = tableLine.substr(0, itr->char_index);
                            string temp2 = tableLine.substr(itr->char_index + 2, (tableLine.size() - itr->char_index + 2));
                            string homeUpdate = temp1 + to_string(newFlakeNumber) + newPlayer + temp2;
                            updatedFile << homeUpdate << '\n';

                            itr->flake_number = to_string(newFlakeNumber);
                            itr->player = newPlayer;

                        }

                        break;
                    }
                }

                for (auto itr2 = homesY.begin(); itr2 != homesY.end(); itr2++) {

                    if (itr2->horizontal_position == horizontal_position && itr2->vertical_position == vertical_position) {

                        if (newFlakeNumber == 0 && newPlayer == ' ') {

                            itr2->flake_number = " ";
                            itr2->player = ' ';

                        }
                        else {
                            itr2->flake_number = to_string(newFlakeNumber);
                            itr2->player = newPlayer;
                        }
                        break;

                    }
                }
                
            }
            else {
                updatedFile << tableLine << '\n';
            }

        }
    }
    else {
       std::cout << "Files could'nt open or create !";
    }

    existingFile.close();
    updatedFile.close();

    std::remove("Table.dat");
    std::rename("Temp.dat", "Table.dat");
}







void updateBrokenFlakes(char player,int brokenFlakeNumber) {
    string tableLine;

    ifstream existingFile("Table.dat", ios::in);
    ofstream updatedFile("Temp.dat", ios::out);

    if (existingFile.is_open() && updatedFile.is_open()) {

        while (getline(existingFile, tableLine)) {

            if (tableLine.back() == '3') {

                if (player == 'X' && brokenFlakeNumber !=0) {

                    string temp1 = tableLine.substr(0, 12);
                    string temp2 = tableLine.substr(13, tableLine.size() - 13);
                    string brokenFlakeUpdate = temp1+to_string(brokenFlakeNumber)+temp2;
                    updatedFile << brokenFlakeUpdate << '\n';
                    

                }
                else if(player == 'X'){

                    string temp1 = tableLine.substr(0, 12);
                    string temp2 = tableLine.substr(13, tableLine.size() - 13);
                    string brokenFlakeUpdate = temp1 + " " + temp2;
                    updatedFile << brokenFlakeUpdate << '\n';

                }


                if (player == 'Y' && brokenFlakeNumber !=0) {

                    string temp1 = tableLine.substr(0, 21);
                    string temp2 = tableLine.substr(22, tableLine.size() - 22);
                    string brokenFlakeUpdate = temp1 + to_string(brokenFlakeNumber) + temp2;
                    updatedFile << brokenFlakeUpdate << '\n';

                }
                else if(player == 'Y'){

                    string temp1 = tableLine.substr(0, 21);
                    string temp2 = tableLine.substr(22, tableLine.size() - 22);
                    string brokenFlakeUpdate = temp1 + " " + temp2;
                    updatedFile << brokenFlakeUpdate << '\n';
                }
                
            }
            else {
                updatedFile << tableLine << '\n';
            }
        }
    }
    else {
        std::cout << "Files could'nt open or create !";
    }

    existingFile.close();
    updatedFile.close();

    std::remove("Table.dat");
    std::rename("Temp.dat", "Table.dat");
}







int checkBrokenFlakes(char player) {
    ifstream fileStream("Table.dat", ios::in);
    string fileLine;

    if (fileStream.is_open()) {

        while (getline(fileStream, fileLine)) {

            if (fileLine.back() == '3') {

                if (player == 'X') {

                    if (fileLine[12]==' ') {
                        return 0;
                    }
                    else {
                        return (fileLine[12] - '0');
                    }
                }
                else if (player == 'Y') {

                    if (fileLine[21] == ' ') {
                        return 0;
                    }
                    else {
                        return (fileLine[21] - '0');
                    }
                }
            }
        }
    }

    fileStream.close();
}






void printLine(char vertical_position,vector<Home>homes) {
    string playerXside;
    string playerYside;
    string spaces;


    for (auto itr = homes.begin(); itr != homes.end(); itr++) {
        if (itr->vertical_position == vertical_position && itr->horizontal_position == '1') {
            if (itr->flake_number == " ") {
                for (int i = 0; i < 5; i++) {
                    playerXside += " ";
                }
            }
            else {
                for (int j = 0; j < stoi(itr->flake_number); j++) {
                    playerXside += itr->player;
                }
            }
        }
        else if (itr->vertical_position == vertical_position && itr->horizontal_position == '5') {
            if (itr->flake_number == " ") {
                for (int i = 0; i < 5; i++) {
                    playerYside += " ";
                }
            }
            else {
                for (int j = 0; j < stoi(itr->flake_number); j++) {
                    playerYside += itr->player;
                }
            }
        }
    }

    for (int i = 0; i < 12 - (playerXside.size() + playerYside.size()); i++)
    {
        spaces += " ";
    }

    string vertical(1, vertical_position);

    cout <<setw(41)<< vertical+"1 | " + playerXside + spaces + playerYside + " | " + vertical +"5\n";
}





void printTable(vector<Home>homes) {

    cout << endl;
    cout << setw(41) << "----------------------\n";
    printLine('L', homes);
    printLine('K', homes);
    printLine('J', homes);
    printLine('I', homes);
    printLine('H', homes);
    printLine('G', homes);
    cout << setw(10)<<"X's Side          ||||||||||||||||||||||          Y's Side\n";
    printLine('F', homes);
    printLine('E', homes);
    printLine('D', homes);
    printLine('C', homes);
    printLine('B', homes);
    printLine('A', homes);
    cout << setw(41) << "----------------------\n";
    cout << endl;

}





void updateDiceRollLog(char player,int dice1, int dice2) {

    ofstream outStream("DiceRollLog.txt", ios::app);
    
    if (outStream.is_open()) {
        outStream << player << " " << dice1 << " " << dice2 << '\n' ;
    }
    else {

        std::cout << "File could'nt open or create !";
    }

    outStream.close();
}





void updateDiceRollLog(int dice) {

    ofstream outStream("DiceRollLog.txt", ios::app);

    if (outStream.is_open()) {
        outStream << dice << '\n';
    }
    else {

        std::cout << "File could'nt open or create !";
    }

    outStream.close();

}





void updateDiceCondition(int dice1, int dice2) {
    string tableLine;

    ifstream existingFile("Table.dat", ios::in);
    ofstream updatedFile("Temp.dat", ios::out);

    if (existingFile.is_open() && updatedFile.is_open()) {

        while (getline(existingFile, tableLine)) {

            if (tableLine.back()=='3') {
                
                string temp1 = tableLine.substr(0, 15);
                string temp2 = tableLine.substr(16, 2);
                string temp3 = tableLine.substr(19, tableLine.size() - 19);
                string diceUpdate = temp1 + to_string(dice1) +temp2+ to_string(dice2) + temp3;
                updatedFile << diceUpdate << '\n';

            }
            else {
                updatedFile << tableLine<<'\n';
            }
   
        }
    }
    else {
        std::cout << "Files could'nt open or create !";
    }

    existingFile.close();
    updatedFile.close();

    std::remove("Table.dat");
    std::rename("Temp.dat", "Table.dat");
}




string checkLatestDiceRollLog() {

    
    ifstream fs;
    fs.open("DiceRollLog.txt", std::fstream::in);
    if (fs.is_open())
    {
        
        fs.seekg(-1, std::ios_base::end);
        if (fs.peek() == '\n')
        {
            
            fs.seekg(-1, std::ios_base::cur);
            int i = fs.tellg();
            for (i; i > 0; i--)
            {
                if (fs.peek() == '\n')
                {
                    
                    fs.get();
                    break;
                }
                
                fs.seekg(i, std::ios_base::beg);
            }
        }
        std::string lastline;
        getline(fs, lastline);
        return lastline;
    }
    else
    {
        std::cout << "Could not find end line character" << std::endl;
    }
    

}


bool is_file_exist(string fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}



bool positionValidity(Home home,char player) {

    char opponent_player;
    (player == 'X') ? opponent_player = 'Y' : opponent_player = 'X';


    if (home.player == ' ' && home.flake_number==" ") {

        return true;

    }
    else if (home.player == player && stoi(home.flake_number)<5) {

        return true;

    }
    else if(home.player==opponent_player && stoi(home.flake_number)<2){

        return true;
    }

    return false;

}


bool pickUpFlakesCondition(vector<Home>homes,char player) {

    char opponent_player;
    (player == 'X') ? opponent_player = 'Y' : opponent_player = 'X';
    bool flag = false;
    int counter = 1;


    for (auto iter = homes.rbegin(); iter != homes.rend(); iter++, counter++) {

        if (counter==7) {

            break;

        }
        else if (iter->player == opponent_player) {

            return false;
        }
    }

    counter = 1;

    for (auto itr = homes.begin(); itr != homes.end(); itr++,counter++) {

        if (counter==19) {

            break;

        }
        else if (itr->player == player) {


            flag = true;
            break;

        }

    }

    if (checkBrokenFlakes(player) != 0 || flag == true) {

        return false;
    }

    return true;

}


bool winningCondition(vector<Home>homes,char player) {

    for (auto itr = homes.begin(); itr != homes.end(); itr++) {

        if (itr->player == player) {

            return false;
        }

    }

    return true;
}




int main()
{
    char player;
    vector<int>dices;
    vector<Home>homesPlayer;
    vector<Home>viablePositions;
    vector<Home>homesX;
    vector<Home>homesY;

    srand(time(NULL));

    cout << setw(40) << "Console Backgammon Game" << endl << endl;

    cout << "Press 1 to play new game or press 2 to go back saved game." << endl;

    int input;

    do
    {
        cin >> input;

        if (input == 1) {

            createTable();
            createHomes(homesX, homesY);

            cout << setw(40) << "\nDices are rolling to determine whether the X or Y play first." << endl;


            do {

                dices.clear();
                dices.push_back((rand() % 6 + 1));
                dices.push_back((rand() % 6 + 1));

            } while (dices[0] == dices[1]);


            updateDiceRollLog(dices[0]);
            updateDiceRollLog(dices[1]);
            updateDiceCondition(dices[0], dices[1]);


            cout << setw(30) << "X rolled " << dices[0] << endl;
            cout << setw(30) << "Y rolled " << dices[1] << endl;


            if (dices[0] > dices[1]) {

                cout << setw(40) << "X will play the first turn." << endl;
                homesPlayer = homesX;
                player = 'X';

            }
            else {

                cout << setw(40) << "Y will play the first turn." << endl;
                homesPlayer = homesY;
                player = 'Y';

            }

            dices.clear();
        }
        else if(input==2){

            
            if (!is_file_exist("Table.dat")) {

                cout << setw(10) << "Cannot find any game to load.Please create a new game." << endl;
                input = 0;

            }
            else {
                createHomes(homesX, homesY);
                string lastPlayed = checkLatestDiceRollLog();
                
                if (lastPlayed.size() == 1) {
                    
                    string line;
                    ifstream determineFirstTurn("DiceRollLog.txt");

                    if (determineFirstTurn.is_open()) {

                        while (getline(determineFirstTurn, line)) {

                            dices.push_back(stoi(line));
                        }

                        cout << setw(20) << "X rolled " << dices[0] << " before game shut down. "<< endl;
                        cout << setw(20) << "Y rolled " << dices[1] << " before game shut down."<< endl;

                        if (dices[0] > dices[1]) {

                            cout << setw(40) << "X will play the first turn." << endl;
                            homesPlayer = homesX;
                            player = 'X';

                        }
                        else {

                            cout << setw(40) << "Y will play the first turn." << endl;
                            homesPlayer = homesY;
                            player = 'Y';

                        }

                        dices.clear();
                        
                    }
                    else {
                        cout << "File could'nt open or create !"<<endl;
                    }

                }
                else {

                    if (lastPlayed[0] == 'X') {

                        cout << setw(20) << "X played last.Next turn will be played by Y."<<endl;
                        homesPlayer = homesY;
                        player = 'Y';
                    }
                    else {

                        cout << setw(20) << "Y played last.Next turn will be played by X." << endl;
                        homesPlayer = homesX;
                        player = 'X';
                    }

                }

            }

        }

    } while (input != 1 && input != 2 );





    while (true) {


        cout << setw(45) << "You can left your game by pressing 3.To move on to the game please press another number." << endl;
        cin.clear();
        cin >> input;
        

        if (input == 3) {
            
            break;
            
        }
        else {

            
            printTable(homesPlayer);

            dices.push_back((rand() % 6 + 1));
            dices.push_back((rand() % 6 + 1));

            std::cout << "Player " << player << " rolled " << dices[0] << " and " << dices[1] << endl; 

            if (dices[0] == dices[1]) {

                dices.push_back(dices[0]);
                dices.push_back(dices[0]);

            }

            updateDiceRollLog(player, dices[0], dices[1]);
            updateDiceCondition(dices[0], dices[1]);





            if (checkBrokenFlakes(player) != 0) {

                cout << "You have " << checkBrokenFlakes(player) << " broken flakes." << endl;


                while (checkBrokenFlakes(player) != 0 && !dices.empty()) {

                    Home controlHome;
                    vector<Home>::iterator itr_to_home;

                    for (auto itr = dices.begin(); itr != dices.end(); itr++) {

                        itr_to_home = homesPlayer.begin() + (*(itr)-1);
                        controlHome = *(itr_to_home);
                        controlHome.dice = *(itr);

                        if (positionValidity(controlHome, player)) {

                            viablePositions.push_back(controlHome);

                        }

                    }


                    if (viablePositions.empty()) {

                        break;

                    }


                    Home selectedHome;
                    cout << "Valid moves ";


                    if (viablePositions.size() > 1) {

                        if (viablePositions[0].dice == viablePositions[1].dice) {

                            cout << viablePositions[0].vertical_position << viablePositions[0].horizontal_position;

                        }
                        else {

                            for (auto itr = viablePositions.begin(); itr != viablePositions.end(); itr++) {

                                cout << itr->vertical_position << itr->horizontal_position << " ";
                            }
                        }
                    }
                    else {

                        cout << viablePositions[0].vertical_position << viablePositions[0].horizontal_position;

                    }


                    cout << endl;

                    string homeName;
                    bool flag = false;
                    vector<int>::iterator deletor;

                    cout << "Please choose a move " << endl;

                    do
                    {


                        cin >> homeName;

                        for (auto iter = viablePositions.begin(); iter != viablePositions.end(); iter++)
                        {
                            if (homeName == string() + iter->vertical_position + iter->horizontal_position) {

                                selectedHome = *(iter);

                                for (auto iter_to_dice = dices.begin(); iter_to_dice != dices.end(); iter_to_dice++) {

                                    if (selectedHome.dice == *(iter_to_dice)) {

                                        deletor = iter_to_dice;
                                        break;
                                    }

                                }

                                flag = true;
                                break;

                            }
                        }
                        if (flag == false) {
                            cout << "Please enter a valid move." << endl;
                        }

                    } while (flag==false);



                    
                        char opponent_player;
                        (player == 'X') ? opponent_player = 'Y' : opponent_player = 'X';


                        if (selectedHome.player == ' ' && selectedHome.flake_number == " ") {

                            updateHome(selectedHome.horizontal_position, selectedHome.vertical_position, 1, player, homesX, homesY);
                            (player == 'X') ? homesPlayer = homesX : homesPlayer = homesY;
                            updateBrokenFlakes(player, checkBrokenFlakes(player) - 1);
                            

                        }
                        else if (selectedHome.player == player && stoi(selectedHome.flake_number) < 5) {

                            updateHome(selectedHome.horizontal_position, selectedHome.vertical_position, stoi(selectedHome.flake_number) + 1, player, homesX, homesY);
                            (player == 'X') ? homesPlayer = homesX : homesPlayer = homesY;
                            updateBrokenFlakes(player, checkBrokenFlakes(player) - 1);

                        }
                        else if (selectedHome.player == opponent_player && stoi(selectedHome.flake_number) < 2) {

                            updateHome(selectedHome.horizontal_position, selectedHome.vertical_position, 1, player, homesX, homesY);
                            (player == 'X') ? homesPlayer = homesX : homesPlayer = homesY;
                            updateBrokenFlakes(player, checkBrokenFlakes(player) - 1);
                            updateBrokenFlakes(opponent_player, checkBrokenFlakes(opponent_player) + 1);

                        }

                        printTable(homesPlayer);
                        dices.erase(deletor);
                        viablePositions.clear();
                    
                }



                if (checkBrokenFlakes(player)!=0 || dices.empty()) {

                    (player == 'X') ? homesPlayer = homesY : homesPlayer = homesX;
                    (player == 'X') ? player = 'Y' : player = 'X';
                    cout << "There is'nt any move left to play." << "Next turn will be played by " << player << endl;
                    viablePositions.clear();
                    dices.clear();
                    continue;

                }                

            }




            if (!dices.empty() && !pickUpFlakesCondition(homesPlayer,player)) {

                bool flagforinterrupt = false;
                
                while (!dices.empty() && !pickUpFlakesCondition(homesPlayer, player)) {


                    Home controlHome;

                    for (auto i = homesPlayer.begin(); i != homesPlayer.end(); i++)
                    {
                        for (auto itr = dices.begin(); itr != dices.end(); itr++) {

                            if (i->player == player && *(itr) <= (homesPlayer.end() - 1 - i)) {

                                auto itr_to_home = i + *(itr);
                                controlHome = *(itr_to_home);
                                controlHome.dice = *(itr);

                                if (positionValidity(controlHome, player)) {

                                    viablePositions.push_back(controlHome);

                                }
                            }
                        }
                    }


                    if (viablePositions.empty()) {

                        flagforinterrupt = true;
                        break;

                    }

                    viablePositions.clear();

                    cout << "Please choose a right :";

                    for (auto iter = dices.begin(); iter != dices.end(); iter++) {
                        cout << *(iter) << " ";

                    }

                    cout << endl;
                    bool flagForDice = false;
                    int dice;
                    vector<int>::iterator to_dice;



                    do
                    {
                        cin >> dice;

                        for (auto iter = dices.begin(); iter != dices.end(); iter++) {
                            if (dice == *(iter)) {
                                to_dice = iter;
                                flagForDice = true;
                                break;
                            }

                        }
                        if (flagForDice == false) {

                            cout << "Please enter a valid value." << endl;
                        }

                    } while (flagForDice == false);



                    cout << "Please enter a home to play from." << endl;
                    bool checkHome = false;
                    string name;
                    Home selectedHome;
                    Home previousHome;

                    do
                    {
                        cin >> name;


                        for (auto itr = homesPlayer.begin(); itr != homesPlayer.end(); itr++) {

                            if (name == string() + itr->vertical_position + itr->horizontal_position && itr->player == player && dice <= (homesPlayer.end() - 1 - itr)) {

                                previousHome = *(itr);
                                selectedHome = *(itr + dice);

                                if (positionValidity(selectedHome, player)) {
                                    checkHome = true;
                                    break;
                                }


                            }

                        }
                        if (checkHome == false) {

                            cout << "Please enter a valid home." << endl;
                        }

                    } while (checkHome == false);





                    char opponent_player;
                    (player == 'X') ? opponent_player = 'Y' : opponent_player = 'X';




                    if (stoi(previousHome.flake_number) - 1 == 0) {

                        updateHome(previousHome.horizontal_position, previousHome.vertical_position, 0, ' ', homesX, homesY);
                        (player == 'X') ? homesPlayer = homesX : homesPlayer = homesY;

                    }
                    else {

                        updateHome(previousHome.horizontal_position, previousHome.vertical_position, stoi(previousHome.flake_number) - 1, player, homesX, homesY);
                        (player == 'X') ? homesPlayer = homesX : homesPlayer = homesY;
                    }





                    if (selectedHome.player == ' ' && selectedHome.flake_number == " ") {

                        updateHome(selectedHome.horizontal_position, selectedHome.vertical_position, 1, player, homesX, homesY);
                        (player == 'X') ? homesPlayer = homesX : homesPlayer = homesY;


                    }
                    else if (selectedHome.player == player && stoi(selectedHome.flake_number) < 5) {

                        updateHome(selectedHome.horizontal_position, selectedHome.vertical_position, stoi(selectedHome.flake_number) + 1, player, homesX, homesY);
                        (player == 'X') ? homesPlayer = homesX : homesPlayer = homesY;


                    }
                    else if (selectedHome.player == opponent_player && stoi(selectedHome.flake_number) < 2) {

                        updateBrokenFlakes(opponent_player, checkBrokenFlakes(opponent_player) + 1);
                        updateHome(selectedHome.horizontal_position, selectedHome.vertical_position, 1, player, homesX, homesY);
                        (player == 'X') ? homesPlayer = homesX : homesPlayer = homesY;

                    }

                    printTable(homesPlayer);
                    dices.erase(to_dice);

                }


                if (dices.empty() || flagforinterrupt == true ) {

                    (player == 'X') ? homesPlayer = homesY : homesPlayer = homesX;
                    (player == 'X') ? player = 'Y' : player = 'X';
                    cout << "There is'nt any move left to play." << "Next turn will be played by " << player << endl;
                    viablePositions.clear();
                    dices.clear();
                    continue;

                }

            }



            if (pickUpFlakesCondition(homesPlayer, player) && !dices.empty()) {



                while (!dices.empty() && !winningCondition(homesPlayer, player)) {

                    Home selectedHome;
                    Home controlHome;
                    vector<Home>::iterator itr_to_home;

                    for (auto itr = dices.begin(); itr != dices.end(); itr++) {

                        itr_to_home = homesPlayer.end()-1 - (*(itr)-1);
                        controlHome = *(itr_to_home);
                        controlHome.dice = *(itr);

                        if (controlHome.player == player) {

                            viablePositions.push_back(controlHome);

                        }
                        else if (controlHome.player == ' ') {

                            for (auto itr2 = itr_to_home; itr2 != homesPlayer.end(); itr2++) {

                                if (itr2->player == player) {

                                    controlHome = *(itr2);
                                    controlHome.dice = *(itr);
                                    viablePositions.push_back(controlHome);
                                }
                            }
                        }
                    }





                    if (viablePositions.empty()) {

                        break;

                    }
                    else {

                        cout << "Valid moves :";

                        if (viablePositions.size() > 1 ) {

                            if (viablePositions[0].dice == viablePositions[1].dice) {

                                cout << viablePositions[0].vertical_position << viablePositions[0].horizontal_position;

                            }
                            else {

                                for (auto itr = viablePositions.begin(); itr != viablePositions.end(); itr++) {
                                    
                                    cout << itr->vertical_position << itr->horizontal_position<<" ";
                                }
                            }
                        }
                        else {

                            cout << viablePositions[0].vertical_position << viablePositions[0].horizontal_position;

                        }

                        cout << endl;




                        string homeName;
                        bool flag = false;
                        vector<int>::iterator deletor;
                        cout << "Please choose a move " << endl;


                        do
                        {
                            cin.clear();
                            cin >> homeName;

                            for (auto iter = viablePositions.begin(); iter != viablePositions.end(); iter++)
                            {
                                if (homeName == string() + iter->vertical_position + iter->horizontal_position) {

                                    selectedHome = *(iter);

                                    for (auto iter_to_dice = dices.begin(); iter_to_dice != dices.end(); iter_to_dice++) {

                                        if (selectedHome.dice == *(iter_to_dice)) {

                                            deletor = iter_to_dice;
                                            break;
                                        }

                                    }

                                    flag = true;
                                    break;

                                }
                            }
                            if (flag == false) {
                                cout << "Please enter a valid move." << endl;
                            }

                        } while (flag==false);


                        
                        if (stoi(selectedHome.flake_number) - 1 == 0) {

                            updateHome(selectedHome.horizontal_position, selectedHome.vertical_position, 0, ' ', homesX, homesY);
                            (player == 'X') ? homesPlayer = homesX : homesPlayer = homesY;

                        }
                        else {

                            updateHome(selectedHome.horizontal_position, selectedHome.vertical_position, stoi(selectedHome.flake_number) - 1, player, homesX, homesY);
                            (player == 'X') ? homesPlayer = homesX : homesPlayer = homesY;
                        }

                        printTable(homesPlayer);
                        dices.erase(deletor);
                        viablePositions.clear();


                    }                
                }



                if (winningCondition(homesPlayer, player)) {


                    cout << "Player " << player << " picked up all his flakes and win the game." << endl;
                    remove("DiceRollLog.txt");
                    remove("Table.dat");
                    

                    break;
                }
                else {

                    (player == 'X') ? homesPlayer = homesY : homesPlayer = homesX;
                    (player == 'X') ? player = 'Y' : player = 'X';                    
                    cout << "There is'nt any move left to play." << "Next turn will be played by " << player << endl;
                    viablePositions.clear();
                    dices.clear();
                    continue;

                }
            }

        }
    }

    return 0;
}


