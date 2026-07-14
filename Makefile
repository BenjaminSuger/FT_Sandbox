COMPOSE := $(shell command -v docker-compose 2>/dev/null || command -v podman-compose 2>/dev/null)

ifeq (,$(COMPOSE))
$(error "Neither docker-compose nor podman-compose found. Please install one of them.")
endif

.PHONY: up down re logs test test-unit build clean fclean

up:
	$(COMPOSE) up -d

down:
	$(COMPOSE) down

re: down up

logs:
	$(COMPOSE) logs -f app

test: build
	cd build && ctest --output-on-failure

test-unit: build
	cd build && ctest -LE integration --output-on-failure

build:
	cmake -B build && cmake --build build

clean:
	rm -rf build

fclean: clean down
	$(COMPOSE) down -v
	find . -name '.env' -delete
