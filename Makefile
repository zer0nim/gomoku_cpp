NAME	= gomoku
CPP		= clang++

SIZE = 1000
SIZE_VAR = -DGUI_WIN_W
BOARD_SZ = 19
BOARD_SZ_VAR = -DBOARD_SZ
NB_ALIGNED_VICTORY = 5
NB_ALIGNED_VICTORY_VAR = -DNB_ALIGNED_VICTORY
NB_DESTROYED_VICTORY = 10
NB_DESTROYED_VICTORY_VAR = -DNB_DESTROYED_VICTORY

VAR_ARGS =	$(SIZE_VAR)=$(SIZE) \
			$(BOARD_SZ_VAR)=$(BOARD_SZ) \
			$(NB_ALIGNED_VICTORY_VAR)=$(NB_ALIGNED_VICTORY) \
			$(NB_DESTROYED_VICTORY_VAR)=$(NB_DESTROYED_VICTORY)

# FLAGS	= -Wall -Wextra -Werror -std=c++11 -g3 -fsanitize=address
FLAGS	= -Wall -Wextra -Werror -std=c++11 -Ofast
# If os !== macos add pthread FLAGS
UNAME_S := $(shell uname -s)
ifneq ($(UNAME_S), Darwin)
	FLAGS += -pthread
endif

SRC_PATH	= src
INC_PATH	= include
OBJ_PATH	= obj

SRC		=	main.cpp \
			Game.cpp \
			Board.cpp \
			gui/Gui.cpp \
			players/Player.cpp \
			players/RealPlayer.cpp \
			players/AIPlayer.cpp \
			players/HybridePlayer.cpp \
			Node.cpp \
			Heuristic.cpp \
			miniMax.cpp \
			utils/Stats.cpp

HEAD	=	Game.hpp \
			Board.hpp \
			Define.hpp \
			gui/Gui.hpp \
			players/Player.hpp \
			players/RealPlayer.hpp \
			players/AIPlayer.hpp \
			players/HybridePlayer.hpp \
			Node.hpp \
			Heuristic.hpp \
			miniMax.hpp \
			utils/Stats.hpp

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

all: $(NAME)

$(NAME): $(OBJ_PATH) $(OBJP)
	@printf $(CYAN)"-> create program : $(NAME)\n"$(NORMAL)
	@$(CPP) $(FLAGS) -o $(NAME) $(OBJP) $(LIBS_FLAGS)
	@printf "Make with these parameters:\n"
	@printf "\tSIZE = $(SIZE)\n"
	@printf "\tBOARD_SZ = $(BOARD_SZ)\n"
	@printf "\tNB_ALIGNED_VICTORY = $(NB_ALIGNED_VICTORY)\n"
	@printf "\tNB_DESTROYED_VICTORY = $(NB_DESTROYED_VICTORY)\n"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp $(HEADP)
	@printf $(YELLOW)"-> $<\n"$(NORMAL)
	@$(CPP) $(FLAGS) -c $< -o $@ $(INCP) $(VAR_ARGS) -I ~/.brew/Cellar/sfml/2.5.1/include/

$(OBJ_PATH):
	@mkdir -p $(dir $(OBJP))

clean:
	@rm -rf $(OBJ_PATH)

fclean: clean
	@rm -f $(NAME)

re:
	@make fclean
	@make all

exec: all
	@./$(NAME)

help:
	@printf "Help:\n"
	@printf "\tTo change the size of the win: SIZE ($(SIZE))\n"
	@printf "\tTo change the size of the board (max 21): BOARD_SZ ($(BOARD_SZ))\n"
	@printf "\tTo change the number of stone to align to win: NB_ALIGNED_VICTORY ($(NB_ALIGNED_VICTORY))\n"
	@printf "\tTo change the number of stone to destroy to win: NB_DESTROYED_VICTORY ($(NB_DESTROYED_VICTORY))\n"
	@printf $(BOLD)"/!\ If you change a parameter, remake all the project\n"$(NORMAL)

.PHONY: all re clean fclean exec
