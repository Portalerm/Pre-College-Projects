'''
Programming Tic Tac Toe in Python :)
Just a fun game, that's all
Try to get 3 in a row!
'''

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
	user_input = ''

	while not user_input.isdigit() or int(user_input) not in range(1, 10) or board[int(user_input) - 1] != ' ':
		user_input = input(f"Player{player}, choose your positon (1-9): ")
		if not user_input.isdigit() or int(user_input) not in range(1, 10) or board[int(user_input) - 1] != ' ':
			print("Your input was invalid...")

	return int(user_input)

def recieve_choice(choices):
	user_input = None
	while user_input not in choices:
		user_input = input("Enter (" + ' or '.join(str(i) for i in choices) + "): ")
	return user_input

def is_finished(board):
	'''
	returns the winner given the board
	returns 'x' if x won
	returns 'o' if o won
	returns 'The cat' if a tie
	returns 'not over' if the game isn't over yet
	'''
	#check the rows
	for row in range(0, 3):
		start_pos = row * 3
		if board[start_pos] == board[start_pos + 1] and board[start_pos + 1] == board[start_pos + 2] and board[start_pos] != ' ':
			return board[start_pos]

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

	char_to_draw = recieve_choice(['x', 'o'])

	#Because it's player 1's turn, we have to switch the value of char_to_draw
	char_to_draw = 'o' if char_to_draw == 'x' else 'x'

	game_continue = 'y'

	while game_continue == 'y':

		game_board = [' '] * 9
		whose_turn = 1

		while is_finished(game_board) == "not over":
			display_board(game_board)
			game_board[recieve_user_input(whose_turn, game_board) - 1] = char_to_draw.upper()
			char_to_draw = 'o' if char_to_draw == 'x' else 'x'
			whose_turn = 2 if whose_turn == 1 else 1
			print(is_finished(game_board))

		display_board(game_board)
		print(f'{is_finished(game_board)} won!')
		print("Play again?")
		game_continue = recieve_choice(['y', 'n'])

play_game()
