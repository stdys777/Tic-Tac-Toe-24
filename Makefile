XPRA_LIST := $(shell xpra list)
XPRA_CMD = xpra start --bind-tcp=0.0.0.0:8080 --mdns=no --dbus-launch='' --notifications=no --tcp-auth=multifile:filename=/home/me/workspace/.theia/password.txt
DISPLAY=

.PHONY : testXpra3 testXpra2 testXpra start stop clean all

all:
ifeq ($(findstring LIVE session at, $(XPRA_LIST)), )
	@echo Xpra server is not running.
	@echo Please run \"make start\" to start the server.
	@echo
else
	$(eval DISPLAY = $(shell echo $(XPRA_LIST) | cut -d : -f4))
	g++ main.cpp -o app -lGL -lglut
	DISPLAY=:$(DISPLAY) ./app
endif

clean:
	rm -f app

stop:
	xpra stop
	@echo Xpra server stopped
	@echo

start:
ifeq ($(findstring LIVE session at, $(XPRA_LIST)), )
	@$(XPRA_CMD) 2> /dev/null
	@echo Please wait for server to start...
	@sleep 5
	@make --no-print-directory testXpra
else
	@echo Xpra server is already running.
	@echo
endif

testXpra:
ifeq ($(findstring LIVE session at, $(shell xpra list)), )
	@echo Still working...
	@sleep 5
	@make --no-print-directory testXpra2
else
	@echo Xpra server is running.
	@echo
endif

testXpra2:
ifeq ($(findstring LIVE session at, $(shell xpra list)), )
	@echo Still working...
	@sleep 5
	@make --no-print-directory testXpra3
else
	@echo Xpra server is running.
	@echo
endif

testXpra3:
ifeq ($(findstring LIVE session at, $(shell xpra list)), )
	@echo Could not start Xpra server.
	@echo Please run \"xpra list\" to check if you have a live session.
	@echo Then run \"make start\" again.
	@echo
else
	@echo Xpra server is running.
	@echo
endif

.PHONY: install
install:
	@printf "socket-dir=/tmp\nsocket-dirs=/tmp\n" > ~/.config/xpra/xpra.conf
	@mkdir -p /home/me/workspace/.theia
	@touch /home/me/workspace/.theia/password.txt
	@echo username\|password > /home/me/workspace/.theia/password.txt
	@echo Installation complete.
	@echo Please update the password.txt file inside the .theia folder in your workspace.
	@echo

.PHONY: pull
pull:
ifeq ($(shell git rev-parse --is-inside-work-tree 2>/dev/null),true)
	@git reset --hard
	@git clean -fdx
	@git pull --ff-only
else
	@echo "No git repository found in the current directory"
endif
