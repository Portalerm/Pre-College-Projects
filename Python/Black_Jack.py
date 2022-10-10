'''
A simplified implementation of Black Jack
Coded in Python :) 
'''

from random import shuffle 

class Card():
	
	suits = ("CLUB", "HEART", "SPADE", "DIAMOND")
	ranks = ("A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K")
	values = {"A" : 11, "2" : 2, "3" : 3, "4" : 4, "5" : 5, "6" : 6, "7" : 7, "8" : 8, "9" : 9, "10" : 10, "J" : 10, "Q" : 10, "K" : 10}

	def __init__(self, suit, rank):

		self.suit = suit
		self.rank = rank
		self.value = Card.values[rank]

	def __str__(self):

		return f'{self.rank}{self.suit[0]}'

class Deck():
	
	def __init__(self):

		self.cards = []
		for suit in Card.suits:
			for rank in Card.ranks:
				self.cards.append(Card(suit, rank))

	def __len__(self):
		return len(self.cards)

	def shuffle(self):
		shuffle(self.cards)

	def deal(self):
		return self.cards.pop()


class Hand():
	
	def __init__(self):
		self.cards = []

	def __str__(self):

		if len(self.cards) == 0:
			return "[]"

		ret_str = "["

		for i, card in enumerate(self.cards):
			if i < len(self.cards) - 1:
				ret_str += str(card) + ', '

		return ret_str + f'{self.cards[-1]}]'

	def amount(self):
		'''
		returns the highest amount the hand is worth without busting (if possible)
		if it's over 21, it's gotta check if you can convert some aces to 1s
		'''
		amount = 0
		for card in self.cards:
			amount += card.value 

		if amount > 21:
			#count how many aces you have in your hand
			num_aces = sum(1 for card in self.cards if card.rank == "A")

			while num_aces > 0 and amount > 21:
				num_aces -= 1
				amount -= 10

		return amount

	def add(self, cards):
		if type(cards) == Card:
			self.cards.append(cards)
		elif type(cards) == type([]):
			self.cards.extend(cards)


class Player():
	
	def __init__(self, name, money):

		self.name = name
		self.money = money
		self.hand = Hand()

	def __str__(self):
		return f"{self.name} with ${self.money} holding {self.hand}"

	def bet(self, money):
		'''
		returns the amount of money bet
		if the user doesn't have enough money, it bets the rest of your money
		'''
		if money > self.money:
			#bet the rest of your money
			temp = self.money
			self.money = 0
			return temp
		else:
			#bet your bet
			self.money -= money
			return money

	def earn(self, money):
		self.money += money

	def reset(self):
		self.hand = Hand()

def get_int(text):
	user_input = "invalid"
	while not user_input.isdigit():
		user_input = input(text)
	return int(user_input)

def black_jack():

	print("Welcome to Black Jack!!!")
	print("You will play against the dealer, who will hit when their hand is less than 16")

	name = input("First things first, what is your name?: ")
	starting_amount = get_int("How much money are you bringing to the table?: ")
	user = Player(name, starting_amount)
	dealer = Player("Isabelle", 1000000)

	print(f"Good to see you, {user.name}! You're dealer will be Isabelle :)")


	while True:
		#Reset the players' hands
		user.reset()
		dealer.reset()

		#Deal cards to the players
		play_deck = Deck()
		play_deck.shuffle()
		for x in range(2):
			user.hand.add(play_deck.deal())
			dealer.hand.add(play_deck.deal())

		#Ask for the user's bet
		user_bet = get_int(f"{dealer.name}: \"Woof! Place your bet!\" (Current Balance:${user.money}): ")

		if user_bet >= user.money:
			print(f"{dealer.name}: \"Wow!!! Going all in!!!\"")

		user_bet = user.bet(user_bet)
		print(f"(Current Balance:${user.money})")

		print(f"{dealer.name}'s hand: [{dealer.hand.cards[0]}, ???]")

		#Play your turn
		user_hit = True
		while user.hand.amount() <= 21 and user_hit:
			print(f"Your hand: {user.hand} (value: {user.hand.amount()})")

			user_input = input(f"{dealer.name}: \"So what is it? Hit or Stay?\": ")

			if(user_input.upper() == 'HIT' or user_input.upper() == 'H'):
				print(f'{dealer.name}: \"Hit is it!!!\"')
				user.hand.add(play_deck.deal())
			else:
				print(f'{dealer.name}: \"Stay it is!!!')
				user_hit = False


		if(user.hand.amount() > 21):
			print(f"Your hand: {user.hand} (value: {user.hand.amount()})")
			print(f'{dealer.name}: \"Uh oh! Looks like you busted!!!\"')
			dealer.earn(user_bet)
			continue

		if(user.hand.amount() == 21):
			print(f'{dealer.name}: \"Wow!!! 21!!! I\'ll have to get pretty lucky to beat you!\" (>///<)')

		#Display the dealer's whole hand
		print()
		print(f"{dealer.name}:\"It's my turn now!\"")
		print(f"{dealer.name}:\"Here's my whole hand!:\" {dealer.hand} (value: {dealer.hand.amount()})")
		print()
		
		#The dealer's turn
		while dealer.hand.amount() <= 16 and dealer.hand.amount() <= user.hand.amount():
			print(f"{dealer.name}:\"Hit!\"")
			dealer.hand.add(play_deck.deal())
			print(f"{dealer.name}\'s hand: {dealer.hand} (value: {dealer.hand.amount()})")

			if dealer.hand.amount() <= 21 and (16 < dealer.hand.amount() or dealer.hand.amount() > user.hand.amount()):
				print(f"{dealer.name}:\"Stay!\"")

		print()
		#Display both hands
		print(f"Your hand: {user.hand} (value: {user.hand.amount()})")
		print(f"{dealer.name}\'s hand: {dealer.hand} (value: {dealer.hand.amount()})")

		if(dealer.hand.amount() > 21):
			print(f'{dealer.name}:\"Uh oh! Looks like I busted!!! (>///<)')

		#Evaluate who won and distribute the money accordingly
		if(dealer.hand.amount() < user.hand.amount() or dealer.hand.amount() > 21):
			print(f'{dealer.name}:\"You won ${user_bet}!!!')
			user.earn(user_bet * 2)
			dealer.bet(user_bet)
		elif(dealer.hand.amount() > user.hand.amount()):
			print(f'{dealer.name}:\"Woof woof! Looks like I won ${user_bet}!!!')
			dealer.earn(user_bet)		
		else:
			print(f'{dealer.name}:\"Looks like a tie\"(O w O)')
			user.earn(user_bet)

		#Display your current balance
		print(f"Your current balance is ${user.money}")
black_jack()