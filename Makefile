NAME = stereo

# --- AGGIUNTA OPENCV ---
OPENCV_FLAGS = `pkg-config --cflags opencv4`
OPENCV_LIBS  = `pkg-config --libs opencv4`
# -----------------------

FLAGS = -Wall -Wextra -Werror -std=c++17 -g3 $(OPENCV_FLAGS)

SRCS_DIR = srcs
OBJS_DIR = objs

SRCS = srcs/main.cpp 

INC = -I ./include/

OBJS = $(SRCS:$(SRCS_DIR)/%.cpp=$(OBJS_DIR)/%.o)
DEPS = $(SRCS:$(SRCS_DIR)/%.cpp=$(OBJS_DIR)/%.d)

all: $(NAME) 

$(NAME): $(OBJS)
	c++ $(FLAGS) $(OBJS) $(OPENCV_LIBS) -o $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp
	@mkdir -p $(dir $@)
	c++ $(FLAGS) $(INC) -MMD -MP -c $< -o $@

-include $(DEPS)

run: all
	./$(NAME)

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -rf build
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re