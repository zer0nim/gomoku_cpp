NAME	= gomoku
CPP		= clang++
FLAGS	= -Wall -Wextra -Werror -std=c++11 -pthread

SRC_PATH	= src
INC_PATH	= include
OBJ_PATH	= obj

SRC		=	main.cpp \
			Game.cpp \
			Board.cpp \
			gui/Gui.cpp \
			players/Player.cpp \
			players/RealPlayer.cpp

HEAD	=	Game.hpp \
			Board.hpp \
			Define.hpp \
			gui/Gui.hpp \
			players/Player.hpp \
			players/RealPlayer.hpp

LIBS_FLAGS = -L ~/.brew/lib -lsfml-system -lsfml-window -lsfml-graphics -lsfml-network -rpath ~/.brew/lib

OBJ		= $(SRC:.cpp=.o)

HEADP	= $(addprefix $(INC_PATH)/, $(HEAD))
OBJP	= $(addprefix $(OBJ_PATH)/, $(OBJ))
INCP	= $(foreach dir, $(INC_PATH), -I $(dir))

NORMAL = "\x1B[0m"
RED = "\x1B[31m"
GREEN = "\x1B[32m"
YELLOW = "\x1B[33m"
BLUE = "\x1B[34m"
MAGENTA = "\x1B[35m"
CYAN = "\x1B[36m"
WHITE = "\x1B[37m"
BOLD = "\e[1m"
LIGHT = "\e[2m"
ITALIC = "\e[3m"
ULINE = "\e[4m"

all: $(OBJ_PATH) $(NAME)

$(NAME): $(OBJP)
	@printf $(CYAN)"-> create program : $(NAME)\n"$(NORMAL)
	@$(CPP) $(FLAGS) -o $(NAME) $(OBJP) $(LIBS_FLAGS)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp $(HEADP) $(OBJ_PATH)
	@printf $(YELLOW)"-> $<\n"$(NORMAL)
	@$(CPP) $(FLAGS) -c $< -o $@ $(INCP) -I ~/.brew/Cellar/sfml/2.5.1/include/

$(OBJ_PATH):
	@mkdir -p $(dir $(OBJP))

clean:
	@rm -rf $(OBJ_PATH)

fclean: clean
	@rm -f $(NAME)

re: fclean all

exec: all
	@./$(NAME)

.PHONY: all re clean fclean
