bin/arduino-cli: ## OSX
	@curl \
		-fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh \
		| sh
	@./bin/arduino-cli core update-index


