NAME_EXECUTABLE = trab3
MAIN_FILE_NAME	= main
SRC             = ./src
INCLUDE         = ./include
OBJ             = ./obj
FLAGS           = -lm -pedantic -Wall -Wextra -I/$(INCLUDE)
COMPILER        = gcc   

C_FILES        = $(wildcard $(SRC)/*.c)
OBJ_PATH_FILES = $(patsubst $(SRC)%,$(OBJ)%,$(C_FILES))
OBJ_FILES      = $(patsubst %.c,%.o,$(OBJ_PATH_FILES))

all: clean create_dir $(OBJ_FILES) create_final_progam

create_final_progam: $(NAME_EXECUTABLE)

# rule for main file
$(OBJ)/$(MAIN_FILE_NAME).o: $(SRC)/$(MAIN_FILE_NAME).c
	@ $(COMPILER) -c $< -I $(INCLUDE) -o $@ $(FLAGS)

# rule for all o files
$(OBJ)/%.o: $(SRC)/%.c $(INCLUDE)/%.h
	@ $(COMPILER) -c $< -I $(INCLUDE) -o $@ $(FLAGS)

# rule for create_final_progam
$(NAME_EXECUTABLE): 
	@ $(COMPILER) $< $(OBJ)/*.o -I $(INCLUDE) -o $@ $(FLAGS)

# create all needed directories
create_dir: 
	@ mkdir $(OBJ)

clean:
	@ rm -rf $(OBJ) $(NAME_EXECUTABLE) $(BIN)
