PATH  := $(PATH):$(PWD)/bin
SHELL := env PATH=$(PATH) /bin/bash

bin/arduino-cli: ## Install CLI (OSX)
	@curl \
		-fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh \
		| sh
	@arduino-cli core update-index

.PHONY: dep ## Install dependencies
dep: bin/arduino-cli
	@arduino-cli lib install "Adafruit NeoPixel"
	@arduino-cli core install arduino:avr

.PHONY: compile ## Compile sketch
compile: bin/arduino-cli
	@arduino-cli compile \
		--fqbn arduino:avr:nano:cpu=atmega328old \
		goggles-neopixel-rings

PHONY: upload ## Upload sketch to board  
upload: bin/arduino-cli
	@arduino-cli upload \
		-p /dev/ttyACM0 \
		--fqbn arduino:avr:nano:cpu=atmega328old \
		goggles-neopixel-rings

.PHONY: help ## Display this help section (default target)
help:
	@echo ""
	@echo "  Available commands:"
	@echo ""
	@grep -E '^\.PHONY: [a-zA-Z_-]+ .*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = "(: |##)"}; {printf "\033[36m\tmake %-20s\033[0m %s\n", $$2, $$3}'
	@echo ""