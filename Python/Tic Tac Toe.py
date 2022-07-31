#Programming Tic Tac Toe in Python :)

def display_board(board):
	'''
		 |	   |
		 |	   |
	_____|_____|_____
		 |	   |	
		 |	   |
	_____|_____|_____
		 |	   |
		 |	   |
		 |	   |	
	'''
	print('     |     |     ')
	print(f'  {board[6]}  |  {board[7]}  |  {board[8]}  ')
	print('_____|_____|_____')
	print('     |     |     ')
	print(f'  {board[3]}  |  {board[4]}  |  {board[5]}  ')
	print('_____|_____|_____')
	print('     |     |     ')
	print(f'  {board[0]}  |  {board[1]}  |  {board[2]}  ')
	print('     |     |     ')

def recieve_user_input(player, board):
	'''
	returns an integer from 1-9, taken from the user
	also ensures that the spot hasn't been taken yet
	'''
	userInput = ''

	while not userInput.isdigit() or int(userInput) not in range(1, 10) or board[int(userInput) - 1] != ' ':
		userInput = input(f"Player{player}, choose your positon (1-9): ")
		if not userInput.isdigit() or int(userInput) not in range(1, 10) or board[int(userInput) - 1] != ' ':
			print("Your input was invalid...")

	return int(userInput)

def recieve_choice(choices):
	userInput = None
	while userInput not in choices:
		userInput = input("Enter (" + ' or '.join(str(i) for i in choices) + "): ")
	return userInput

def isFinished(board):
	'''
	returns the winner given the board
	returns 'x' if x won
	returns 'o' if o won
	returns 'The cat' if a tie
	returns 'not over' if the game isn't over yet
	'''
	#check the rows
	for row in range(0, 3):
		startPos = row * 3
		if board[startPos] == board[startPos + 1] and board[startPos + 1] == board[startPos + 2] and board[startPos] != ' ':
			return board[startPos]

	#check the columns
	for column in range(0, 3):
		if board[column] == board[column + 3] and board[column + 3] == board[column + 6] and board[column] != ' ':
			return board[column]

	#check the diagonals
	if board[0] == board[4] and board[4] == board[8] and board[4] != ' ':
		return board[0]
	if board[6] == board[4] and board[4] == board[2] and board[4] != ' ':
		return board[6]

	#the game might be over, but a tie
	if ' ' not in board:
		return "The cat"

	#we haven't found a match
	return "not over"

def play_game():
	print('Welcome to Tic Tac Toe!!!\n')
	print('Player1 will be playing first')
	print("Let's allow Player2 to decide whether to be X's or O's")

	charToDraw = recieve_choice(['x', 'o'])

	#Because it's player 1's turn, we have to switch the value of charToDraw
	charToDraw = 'o' if charToDraw == 'x' else 'x'

	gameContinue = 'y'

	while gameContinue == 'y':

		gameBoard = [' '] * 9
		whoseTurn = 1

		while isFinished(gameBoard) == "not over":
			display_board(gameBoard)
			gameBoard[recieve_user_input(whoseTurn, gameBoard) - 1] = charToDraw.upper()
			charToDraw = 'o' if charToDraw == 'x' else 'x'
			whoseTurn = 2 if whoseTurn == 1 else 1
			print(isFinished(gameBoard))

		display_board(gameBoard)
		print(f'{isFinished(gameBoard)} won!')
		print("Play again?")
		gameContinue = recieve_choice(['y', 'n'])

play_game()
