bool exist(char** board, int boardSize, int* boardColSize, char* word) {
    int contagem = strlen(word);

    bool busca(int i, int j, int k) {
        if (word[k] == '\0') return true;
        if (i < 0 || j < 0 || i >= boardSize || j >= boardColSize[i]) return false;
        if (board[i][j] != word[k]) return false;

        char temp = board[i][j];
        board[i][j] = '#'; 

        bool sucesso =
            busca(i+1, j, k+1) ||
            busca(i-1, j, k+1) ||
            busca(i, j+1, k+1) ||
            busca(i, j-1, k+1);

        board[i][j] = temp;

        return sucesso;
    }

    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardColSize[i]; j++) {
            if (busca(i, j, 0)) {
                return true;
            }
        }
    }

    return false;
}
