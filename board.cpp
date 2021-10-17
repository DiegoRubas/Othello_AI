#include "board.h"
board::board(){
    
}
board::board(int boardSize){
    size = boardSize ;
    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            grid[i][j] = '.';
        }
    }
    int n1 = round(size/2) ;
    int n2 = round(size/2 -1) ;
    
    stickyTiles.insert("4C") ;
    stickyTiles.insert("3C") ;
    stickyTiles.insert("3F") ;
    stickyTiles.insert("6C") ;
    stickyTiles.insert("6F") ;
    stickyTiles.insert("4F") ;
    stickyTiles.insert("5C") ;
    stickyTiles.insert("5F") ;
    stickyTiles.insert("6D") ;
    stickyTiles.insert("6E") ;
    stickyTiles.insert("3D") ;
    stickyTiles.insert("3E") ;

    //tiles se trouvant au bord 
    cornerTiles.insert("1A");
    cornerTiles.insert("1B");
    cornerTiles.insert("1C");
    cornerTiles.insert("1D");
    cornerTiles.insert("1E");
    cornerTiles.insert("1F");
    cornerTiles.insert("1G");
    cornerTiles.insert("1H");
    cornerTiles.insert("2A");
    cornerTiles.insert("2H");
    cornerTiles.insert("3A");
    cornerTiles.insert("3H");
    cornerTiles.insert("4A");
    cornerTiles.insert("4H");
    cornerTiles.insert("5A");
    cornerTiles.insert("5H");
    cornerTiles.insert("6A");
    cornerTiles.insert("6H");
    cornerTiles.insert("7A");
    cornerTiles.insert("7H");
    cornerTiles.insert("8A");
    cornerTiles.insert("8B");
    cornerTiles.insert("8C");
    cornerTiles.insert("8D");
    cornerTiles.insert("8E");
    cornerTiles.insert("8F");
    cornerTiles.insert("8G");
    cornerTiles.insert("8H");

    //tiles sur l'avant dernière ligne
    secondLastTiles.insert("1B");
    secondLastTiles.insert("1G");
    secondLastTiles.insert("2A");
    secondLastTiles.insert("2H");
    secondLastTiles.insert("7A");
    secondLastTiles.insert("7H");
    secondLastTiles.insert("8B");
    secondLastTiles.insert("8G");

    secondLastTiles.insert("2B");
    secondLastTiles.insert("2C");
    secondLastTiles.insert("2D");
    secondLastTiles.insert("2E");
    secondLastTiles.insert("2F");
    secondLastTiles.insert("2G");
    secondLastTiles.insert("3B");
    secondLastTiles.insert("3G");
    secondLastTiles.insert("4B");
    secondLastTiles.insert("4G");
    secondLastTiles.insert("5B");
    secondLastTiles.insert("5G");
    secondLastTiles.insert("6B");
    secondLastTiles.insert("6G");
    secondLastTiles.insert("7B");
    secondLastTiles.insert("7C");
    secondLastTiles.insert("7D");
    secondLastTiles.insert("7E");
    secondLastTiles.insert("7F");
    secondLastTiles.insert("7G");

    //tiles a prendre en priorite
    powerTiles1.insert("1A");
    powerTiles1.insert("1H");
    powerTiles1.insert("8H");
    powerTiles1.insert("8A");

    powerTiles2.insert("1C");
    powerTiles2.insert("8C");
    powerTiles2.insert("1F");
    powerTiles2.insert("8F");
    powerTiles2.insert("3A");
    powerTiles2.insert("3H");
    powerTiles2.insert("6A");
    powerTiles2.insert("6H");

    powerTiles3.insert("3C");
    powerTiles3.insert("6C");
    powerTiles3.insert("3F");
    powerTiles3.insert("6F");

    grid[n2][n2] = 'O', grid[n1][n1] = 'O';
    grid[n2][n1] = 'X', grid[n1][n2] = 'X';
    
    scorePlayer1 = 2;
    scorePlayer2 = 2;
    
   /* grid[1][1] = 'O'; grid[1][2] = 'O'; grid[1][3] = 'O'; grid[2][3] = 'O';
    grid[3][3] = 'O'; grid[3][2] = 'O'; grid[3][1] = 'O'; grid[2][1] = 'O';
    grid[2][2] = 'X'; //troubleshooting
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == 0 || i == size - 1 || j == 0 || j == size - 1) {
                grid[j][i] = 'X';
                scorePlayer1++;
            } else if (i == 3 && j == 4) {
                grid[i][j] = '.';
            } else {
                grid[j][i] = 'O';
                scorePlayer2++;
            }
        }
    }
    grid[0][0] = 'X'; grid[size - 1][0] = 'X';
    grid[4][3] = 'X' ; */
};

board::~board() = default;

void board::finishGame() {
    if (scorePlayer1 > scorePlayer2) {
        cout << "Player 1 has won the game with " << scorePlayer1 << " points to player 2's " << scorePlayer2 << ". Congratulations Player 1!" << endl;
    } else if (scorePlayer1 < scorePlayer2) {
        cout << "Player 2 has won the game with " << scorePlayer2 << " points to player 1's " << scorePlayer1 << ". Congratulations Player 2!" << endl;
    } else {
        cout << "Both players have the same number of points. It's a tie!";
    }
}

int board::getSize()const {
    return size ;
}

void board::placeDisc(char discColor, int yPos, int xPos) {
    grid[yPos][xPos] = discColor;
    if (discColor == 'X') {
        scorePlayer1++;
    } else {
        scorePlayer2++;
    }

    update_stickyList(yPos, xPos) ; // devrait mettre a jour le MAP moves_P1 et le map moves_P2 et TRIER les MAP
}

int board::update(char discColor, int yPos, int xPos, string directions){
    /*  verifie que le position est valide (...), effectue les changments dans le plateau
    *   compte le nombre de pions échangés durant le coup
    */ 
    // vaut mieux directement vérifier si la position est valide durant l'interaction terminal jeu
    
    placeDisc(discColor, yPos, xPos);
    int i = flip(discColor, yPos, xPos, directions) ;
    return i;
}

void board::print() {
    printBoard();
    printScore();
}

void board::printBoard(ostream & out) const {
    out << endl;
    out << "  ";
    for (int i = 97; i < 105; i++) {
        out << char(i) << ' ';
    }
    out << "  " << endl;
    for (int i = 0; i < size; i++)
    {
        out << i + 1 << ' ';
        for (int j = 0; j < size; j++)
        {
            out << grid[i][j] << ' ' ;
        }
        out << i + 1 << ' ' << endl;
    }
    out << "  ";
    for (int i = 97; i < 105; i++) {
        out << char(i) << ' ';
    }
    out << "  " << endl;
    out << endl;
}

void board::compareBoards(board board2) {
    cout << endl;
    cout << "  ";
    for (int i = 97; i < 105; i++) {
        cout << char(i) << ' ';
    }
    cout << "   |    ";
    for (int i = 97; i < 105; i++) {
        cout << char(i) << ' ';
    }
    cout << "  " << endl;
    for (int i = 0; i < size; i++)
    {
        cout << i + 1 << ' ';
        for (int j = 0; j < size; j++)
        {
            cout << grid[i][j] << ' ' ;
        }
        cout << i + 1 << "  |  " << i + 1 << ' ';
        for (int j = 0; j < size; j++)
        {
            cout << board2.getTile(i, j) << ' ' ;
        }
        cout << i + 1 << ' ' << endl;
    }
    cout << "  ";
    for (int i = 97; i < 105; i++) {
        cout << char(i) << ' ';
    }
    cout << "   |    ";
    for (int i = 97; i < 105; i++) {
        cout << char(i) << ' ';
    }
    cout << "  " << endl;
    cout << endl;
}

void board::printScore(ostream & out) const {
    out << "The current score is:" << endl;
    out << "################";
    if (max(scorePlayer1, scorePlayer2) > 9) {
        out << "#";
    }
    out << endl;
    out << "# Player 1: " << scorePlayer1;
    if (max(scorePlayer1, scorePlayer2) < 10) {
        out << " ";
    }
    out << " #" << endl;
    out << "# Player 2: " << scorePlayer2;
    if (max(scorePlayer1, scorePlayer2) < 10) {
        out << " ";
    }
    out << " #" << endl;
    out << "################";
    if (max(scorePlayer1, scorePlayer2) > 9) {
        out << "#";
    }
    out << endl;
}

int board::flip(char discColor, int yPos, int xPos, string directions) { // on devrait faire une class disc
    int num_flipped = 0 ;
    if (directions[0] == '1') {
        num_flipped += flipUp(discColor, yPos, xPos);
    }
    if (directions[1] == '1') {
        num_flipped += flipUpRight(discColor, yPos, xPos);
    }
    if (directions[2] == '1') {
        num_flipped += flipRight(discColor, yPos, xPos);
    }
    if (directions[3] == '1') {
        num_flipped += flipDownRight(discColor, yPos, xPos);
    }
    if (directions[4] == '1') {
        num_flipped += flipDown(discColor, yPos, xPos);
    }
    if (directions[5] == '1') {
        num_flipped += flipDownLeft(discColor, yPos, xPos);
    }
    if (directions[6] == '1') {
        num_flipped += flipLeft(discColor, yPos, xPos);
    } 
    if (directions[7] == '1') {
        num_flipped += flipUpLeft(discColor, yPos, xPos);
    }
    return num_flipped ;
}

int board::flipUp(char discColor, int yPos, int xPos) {
    int num_flipped = 0 ;
    for (int i = yPos - 1; i >= 0; i--) {
        if (grid[i][xPos] != discColor) {
            grid[i][xPos] = discColor;
            if (discColor == 'X') {
                scorePlayer1++;
                scorePlayer2--;
            } else {
                scorePlayer1--;
                scorePlayer2++;
            }
            num_flipped ++ ;
        } else {
            i = -1;
        }
    }
    return num_flipped ;
}

int board::flipUpRight(char discColor, int yPos, int xPos) {
    int num_flipped = 0 ;
    for (int i = 1; i < min(size - 1 - xPos, yPos); i++) {
        if (grid[yPos - i][xPos + i] != discColor) {
            grid[yPos - i][xPos + i] = discColor;
            if (discColor == 'X') {
                scorePlayer1++;
                scorePlayer2--;
            } else {
                scorePlayer1--;
                scorePlayer2++;
            }
            num_flipped ++ ;
        } else {
            i = size;
        }
    }
    return num_flipped ;
}

int board::flipRight(char discColor, int yPos, int xPos) {
    int num_flipped = 0 ;
    for (int i = xPos + 1; i < size; i++) {
        if (grid[yPos][i] != discColor) {
            grid[yPos][i] = discColor;
            if (discColor == 'X') {
                scorePlayer1++;
                scorePlayer2--;
            } else {
                scorePlayer1--;
                scorePlayer2++;
            }
            num_flipped ++ ;
        } else {
            i = size;
        }
    }
    return num_flipped ;
}

int board::flipDownRight(char discColor, int yPos, int xPos) {
    int num_flipped = 0 ;
    for (int i = 1; i < min(size - 1 - xPos, size - 1 - yPos); i++) {
        if (grid[yPos + i][xPos + i] != discColor) {
            grid[yPos + i][xPos + i] = discColor;
            if (discColor == 'X') {
                scorePlayer1++;
                scorePlayer2--;
            } else {
                scorePlayer1--;
                scorePlayer2++;
            }
            num_flipped ++ ;
        } else {
            i = size;
        }
    }
    return num_flipped ;
}

int board::flipDown(char discColor, int yPos, int xPos) {
    int num_flipped = 0 ;
    for (int i = yPos + 1; i < size; i++) {
        if (grid[i][xPos] != discColor) {
            grid[i][xPos] = discColor;
            if (discColor == 'X') {
                scorePlayer1++;
                scorePlayer2--;
            } else {
                scorePlayer1--;
                scorePlayer2++;
            }
            num_flipped ++ ;
        } else {
            i = size;
        }
    }
    return num_flipped ;
}

int board::flipDownLeft(char discColor, int yPos, int xPos) {
    int num_flipped = 0 ;
    for (int i = 1; i < min(xPos, size - 1 - yPos); i++) {
        if (grid[yPos + i][xPos - i] != discColor) {
            grid[yPos + i][xPos - i] = discColor;
            if (discColor == 'X') {
                scorePlayer1++;
                scorePlayer2--;
            } else {
                scorePlayer1--;
                scorePlayer2++;
            }
            num_flipped ++ ;
        } else {
            i = size;
        }
    }
    return num_flipped ;
}

int board::flipLeft(char discColor, int yPos, int xPos) {
    int num_flipped = 0 ;
    for (int i = xPos - 1; i >= 0; i--) {
        if (grid[yPos][i] != discColor) {
            grid[yPos][i] = discColor;
            if (discColor == 'X') {
                scorePlayer1++;
                scorePlayer2--;
            } else {
                scorePlayer1--;
                scorePlayer2++;
            }
            num_flipped ++ ;
        } else {
            i = -1;
        }
    }
    return num_flipped ;
}

int board::flipUpLeft(char discColor, int yPos, int xPos) {
    int num_flipped = 0 ;
    for (int i = 1; i < min(xPos, yPos); i++) {
        if (grid[yPos - i][xPos - i] != discColor) {
            grid[yPos - i][xPos - i] = discColor;
            if (discColor == 'X') {
                scorePlayer1++;
                scorePlayer2--;
            } else {
                scorePlayer1--;
                scorePlayer2++;
            }
            num_flipped ++ ;
        } else {
            i = size;
        }
    }
    return num_flipped ;
}

char board::getTile(int yPos, int xPos) const{
    return grid[yPos][xPos];
}

void board::setTile(int yPos, int xPos, char color) {
    grid[yPos][xPos] = color;
}

int board::getP1score(){ return scorePlayer1 ;}
int board::getP2score(){ return scorePlayer2 ;}

void board::update_movesList() {
    /* gameMove checkedMove(*this) ;

    // Temporaire
    // attention : faire startMoveList -> commencer d'un set de moves, puis juste 
    // ajouter les moves potentielles crées via un update_movesList
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            string input = "";
            input += char(j + 1 + 48);
            input += char(i + 65);
            if (checkedMove.isValid(1, input, *this) == 0 ) movesList_1->append(input) ;
            else if (checkedMove.isValid(2, input, *this) == 0 ) movesList_2->append(input) ;
        }
    } */
}

string pos_to_string(int y, int x){
    string input = "";
    input += char(y + 1 + 48);
    input += char(x + 65);
    
    return input ;
}

void board::update_stickyList(int yPos, int xPos){
// update stickytiles
    int minX = (xPos == 0) ? 0 : -1;
    int maxX = (xPos == size - 1) ? 0 : 1;
    int minY = (yPos == 0) ? 0 : -1;
    int maxY = (yPos == 0) ? 0 : 1;

    for (int i = minX; i <= maxX; i++) {
        for (int j = minY; j <= maxY; j++) {
            if (grid[yPos+j][xPos+i] == '.') {
                stickyTiles.insert(pos_to_string(yPos + j, xPos + i));
            }
        }
    }

    string position = pos_to_string(yPos, xPos) ;
    set<string>::iterator itr = stickyTiles.find(position) ;
    
    stickyTiles.erase(itr) ; //enleve la position nouvellement occupée
      
} 

set<string> board::getStickyTiles(){return stickyTiles ;}

set<string> board::getCornerTiles(){
    //creation cornerTiles
   /* for (int a = 0; a < 8; a++){
        string str = pos_to_string(1,a);
        cornerTiles.insert(str);
    }
    for (int a = 0; a < 8; a++){
        string str = pos_to_string(8,a);
        cornerTiles.insert(str);
    }*/
    return cornerTiles ;
    }

set<string> board::getSecondLastTiles(){return secondLastTiles ;}


int board::corner_tiles(){
    int num ;

    num = 0 ;
    num+= (grid[0][size-1] == 'X') ? 1 : (grid[0][size-1] == 'O') ? -1 : 0 ;
    num+= (grid[size-1][0] == 'X') ? 1 : (grid[size-1][0] == 'O') ? -1 : 0 ;
    num+= (grid[size-1][size-1] == 'X') ? 1 : (grid[size-1][size-1] == 'O') ? -1 : 0 ;
    num+= (grid[0][0] == 'X') ? 1 : (grid[0][0] == 'O') ? -1 : 0 ;
    
    return num ;
}
int board::border_tiles(){
    int num, i ;
    
    num = 0 ;
    // first row, all 
    for(i=0; i<size; i++){
        num+= (grid[0][i] == 'X') ? 1 : (grid[0][i] == 'O') ? -1 : 0 ;
        num+= (grid[size-1][i] == 'X') ? 1 : (grid[0][i] == 'O') ? -1 : 0 ;
        num+= (grid[size-1][0] == 'X') ? 1 : (grid[0][i] == 'O') ? -1 : 0 ;
        num+= (grid[size-1][0] == 'X') ? 1 : (grid[0][i] == 'O') ? -1 : 0 ;
        
    }
    return num ;
}
int board::border_lines(){
    int i ;
    int perf = 0 ;

    // first line : all columns
    i = 0 ;
    while (i < size)
    {
        int line_length = 0 ;
        
        // scanning next tile until tile number size-2 (starting from 0); and incrementing i
        while(grid[0][i] == 'X'){
            line_length ++ ;
            i ++ ;
        }
        perf += pow(line_length, 2) ;

        line_length = 0 ;
        while(grid[0][i] == 'O'){
            line_length ++ ;
            i ++ ;
        }
        perf -= pow(line_length, 2) ;
        
        i ++ ;
    }
    
    // last line : all columns
    i = 0 ;
    while (i < size)
    {
        int line_length = 0 ;
        
        // scanning next tile until tile number size-2 (starting from 0); and incrementing i
        while(grid[size-1][i] == 'X'){
            line_length ++ ;
            i ++ ;
        }
        perf += pow(line_length, 2) ;


        line_length = 0 ;
        while(grid[size-1][i] == 'O'){
            line_length ++ ;
            i ++ ;
        }
        perf -= pow(line_length, 2) ;

        i ++ ;
    }
    
    // last column : all lines
    i = 0 ;
    while (i < size)
    {
        int line_length = 0 ;
        
        // scanning next tile until tile number size-2 (starting from 0); and incrementing i
        while(grid[i][size-1] == 'X'){
            line_length ++ ;
            i ++ ;
        }
        perf += pow(line_length, 2) ;
        
        line_length = 0 ;
        while(grid[i][size-1] == 'O'){
            line_length ++ ;
            i ++ ;
        }

        perf -= pow(line_length, 2) ;

        i ++ ;
    }
    
    
    // first column : all lines
    i = 0 ;
    while (i < size)
    {
        int line_length = 0 ;
        
        // scanning next tile until tile number size-2 (starting from 0); and incrementing i
        while(grid[i][0] == 'X'){
            line_length ++ ;
            i ++ ;
        }
        perf += pow(line_length, 2) ;
        
        line_length = 0 ;
        while(grid[i][0] == 'O'){
            line_length ++ ;
            i ++ ;
        }
        perf -= pow(line_length, 2) ;
        i ++ ;
    }
    return perf ;
}

int board::border_stack_tiles(){
    return 0 ;
}

int board::power_spots() {
    int value = 0;
    
    for(set<string>::iterator itr = powerTiles2.begin(); itr != powerTiles2.end(); itr ++){
        int xPos, yPos ;
        string input = *itr ;
        yPos = int(input.at(0)) - 48 - 1;
        xPos = (int(input.at(1) < 97)) ? int(input.at(1)) - 65 : int(input.at(1)) - 97;
        value += 8*((grid[yPos][xPos] == 'X') ? 1 : ((grid[yPos][xPos] == 'O') ? -1 : 0)) ;
    }

    for(set<string>::iterator itr = powerTiles1.begin(); itr != powerTiles1.end(); itr ++){
        int xPos, yPos ;
        string input = *itr ;
        yPos = int(input.at(0)) - 48 - 1;
        xPos = (int(input.at(1) < 97)) ? int(input.at(1)) - 65 : int(input.at(1)) - 97;
        value += 8*((grid[yPos][xPos] == 'X') ? 1 : ((grid[yPos][xPos] == 'O') ? -1 : 0)) ;
    }
    return value ;

}

int board::addBonus(string input) {
    int value = 0;
    int xPos, yPos ;
    yPos = int(input.at(0)) - 48 - 1;
    xPos = (int(input.at(1) < 97)) ? int(input.at(1)) - 65 : int(input.at(1)) - 97;
    if(xPos == 0 || xPos == size-1 || yPos == 0 || yPos == size-1){
        value += 2 ;
    } ;

    value += 4*catchLine(yPos, xPos) ;

    if (powerTiles1.count(input)) { // coins
        value += 16;
    }
    else if (powerTiles2.count(input)) { // power spots sur les bords
    //if (powerTiles2.count(input)) {
        value += 4;
    }
    else if (powerTiles3.count(input)) { // power spots sur les diagonales
        value += 8;
    } else if (secondLastTiles.count(input)) {
        value -= 8;
    }
    return value ;
}

// function that count the length of a border line that X has captured by putting a disc at position Y, X
int board::catchLine(int y, int x){
    int i ;
    int linePossibleLength, lineLength ;
    linePossibleLength = lineLength = 0 ;
    // verification premiere ligne
    if(y == 0 || y == size-1){
        int yPos = (y==0)? 0 : size-1 ;
        i = x-1 ;
        while(i>0 && grid[yPos][i] == 'O'){
            i-- ;
            linePossibleLength ++ ;
        }
        if(i>0 && grid[yPos][i] == 'X')
            lineLength += linePossibleLength ;

        i = x+1 ;
        while (i < size && grid[yPos][i] == 'O') 
        {
            i++ ;
            linePossibleLength ++ ;
        }
        if(i<size && grid[yPos][i] == 'X')
            lineLength += linePossibleLength ;
    }
    if(x == 0 || x == size-1){
        int xPos = (x==0)? 0 : size-1 ;
        i = y-1 ;
        while(i>0 && grid[i][xPos] == 'O'){
            i-- ;
            linePossibleLength ++ ;
        }
        if(i>0 && grid[i][xPos] == 'X')
            lineLength += linePossibleLength ;

        i = y+1 ;
        while (i < size && grid[i][xPos] == 'O') 
        {
            i++ ;
            linePossibleLength ++ ;
        }
        if(i<size && grid[i][xPos] == 'X')
            lineLength += linePossibleLength ;
    }
    return lineLength ;
}